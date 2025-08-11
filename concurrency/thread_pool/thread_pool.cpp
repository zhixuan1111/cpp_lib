#include <iostream>
#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

class ThreadPool 
{
public:
    // 构造函数，初始化线程池
    ThreadPool(size_t threads) : stop(false) 
    {
        for (size_t i = 0; i < threads; ++i) 
        {
            workers.emplace_back([this] 
                {
                while (true) 
                {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        this->condition.wait(lock, [this] 
                            {
                            return this->stop || !this->tasks.empty();
                        });
                        if (this->stop && this->tasks.empty())
                            return;
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    // 析构函数，清理线程池资源
    ~ThreadPool() 
    {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread &worker : workers) 
        {
            worker.join();
        }
    }

    // 向线程池添加任务
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) 
        -> std::future<typename std::result_of<F(Args...)>::type> 
        {
        using return_type = typename std::result_of<F(Args...)>::type;

        auto task = std::make_shared< std::packaged_task<return_type()> >(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        
        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            // 不允许在线程池停止后添加新任务
            if (stop)
                throw std::runtime_error("enqueue on stopped ThreadPool");
            tasks.emplace([task]() { (*task)(); });
        }
        condition.notify_one();
        return res;
    }

private:
    // 工作线程集合
    std::vector<std::thread> workers;
    // 任务队列
    std::queue<std::function<void()>> tasks;
    
    // 同步相关
    std::mutex queue_mutex;
    std::condition_variable condition;
    // 线程池停止标志
    bool stop;
};

// 使用示例
int main() 
{
    // 创建一个包含4个线程的线程池
    ThreadPool pool(4);
    
    // 创建一个存储 future 对象的向量，用于获取任务结果
    std::vector< std::future<int> > results;

    // 向线程池添加10个任务
    for(int i = 0; i < 10; ++i) 
    {
        results.emplace_back(
            pool.enqueue([i] 
                {
                std::cout << "task " << i << " by " << std::this_thread::get_id() << " doing" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                return i * i;
            })
        );
    }

    // 输出每个任务的结果
    for(auto && result : results)
        std::cout << "task reslult: " << result.get() << std::endl;
    
    return 0;
}    