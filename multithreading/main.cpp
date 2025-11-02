#include <atomic>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
#include <future>
#include <atomic>


struct ThreadPool {
  std::vector<std::thread> workers;       // Lists Of All Thread
  std::queue<std::function<void()>> tasks; // Lists of All Tasks;

  std::mutex queueLock;              // Prevent Unstable Data Accessing
  std::condition_variable condition; // Condition For Synchronous thread
  std::atomic<bool> stop;            // Trigger flags;

  explicit ThreadPool(size_t numThreads) : stop(false) {
    workers.reserve(numThreads);

    // Manager Give Thread Tasks
    for (size_t i = 0; i < numThreads; ++i) {
      workers.emplace_back([this]() {
        while (true) {
          std::function<void()> task;
          // Lock in
          {
            std::unique_lock<std::mutex> lock(queueLock);

            // Wait until there is a task or stop signal
            condition.wait(lock, [this]() { return stop || !tasks.empty(); });

            if(stop && tasks.empty()) return; // Stop The Tasks When Its Done
            
            //Make Tasks Clear and Done
            task = std::move(tasks.front());
            tasks.pop();
          }
          //Executing tasks 
        task();
        }
      });
    };
  }
  ~ThreadPool(){
    stop=true;
    condition.notify_all();

    for(auto& worker : workers){
      worker.join();
    }
  }

  //Enqueue a new tasks into the pool
  template<class F,class... Args>
  auto enqueue(F&& f,Args&&... args)->std::future<typename std::invoke_result<F,Args...>::type>{
    using returnType = typename std::invoke_result<F,Args...>::type;

    auto task = std::make_shared<std::packaged_task<returnType()>>(
      std::bind(std::forward<F>(f),std::forward<Args>(args)...)
    );

    std::future<returnType> res = task->get_future();
    {
      std::unique_lock<std::mutex> lock(queueLock);

      if(stop) throw std::runtime_error("Enqueue on stopped ThreadPool");
      tasks.push([task]() { (*task)(); });  // Add the task to the queue
    }

    condition.notify_one(); // Notify All Slaves; 
    return res;
  }
};

int main() {
  ThreadPool pool(4);

  auto result_1 = pool.enqueue([](){
      std::cout << "Tasks 1 is running\n" << std::endl;
      return 1;
  });
  std::cout << "Result_1: " << result_1.get() << std::endl;
  std::cout << "Hello from main thread" << std::endl;

  return 0;
}
