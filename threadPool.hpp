#include <thread>                // 用于多线程支持
#include <mutex>                 // 用于线程同步
#include <vector>                // 用于存储线程对象
#include <deque>                 // 用于任务队列
#include <functional>            // 用于存储可调用对象
#include <condition_variable>    // 用于线程间的条件变量
using namespace std;

// 线程池类
class threadPool
{
public:
    // 构造函数，初始化线程池
    // 参数 size 指定线程池中的线程数量，默认为硬件支持的最大线程数
    threadPool(int size = std::thread::hardware_concurrency())
    {
        maxCore = size;  // 设置线程池的最大线程数
        stop = false;    // 初始化停止标志为 false
        // 创建指定数量的线程，并将它们加入线程池
        for (int i = 0; i < size; ++i)
        {
            workes.emplace_back(&threadPool::workerLoop, this); // 每个线程执行 workerLoop 方法
        }
    }

    // 析构函数，销毁线程池
    ~threadPool() {
        {
            unique_lock<std::mutex> lock(taskMutex); // 加锁以保护共享资源
            stop = true;                             // 设置停止标志为 true
        }
        condition.notify_all(); // 通知所有线程退出等待状态
        // 等待所有线程完成并退出
        for (auto& work : workes) {
            work.join();
        }
    }

    // 添加任务到线程池
    // 参数 t 是任务函数，args 是任务函数的参数
    template<typename T, typename... Args>
    void addTasks(T&& t, Args&&... args) {
        // 使用 std::bind 将任务函数和参数绑定为一个可调用对象
        auto task = bind(forward<T>(t), forward<Args>(args)...);
        {
            unique_lock<std::mutex> lock(taskMutex); // 加锁以保护任务队列
            tasks.push_back(task);                  // 将任务加入队列
        }
        condition.notify_one(); // 通知一个线程处理任务
    }
    bool empty() {
        return tasks.empty();
    }
private:
    int maxCore;                        // 最大线程数
    vector<std::thread> workes;         // 存储线程对象的容器
    deque<function<void()>> tasks;      // 任务队列，存储待执行的任务
    mutex taskMutex;                    // 保护任务队列的互斥锁
    std::condition_variable condition;  // 条件变量，用于线程间的同步
    bool stop;                          // 停止标志，指示线程池是否停止

    // 线程的工作循环
    void workerLoop()
    {
        while (true)
        {
            function<void()> task; // 用于存储从任务队列中取出的任务
            {
                unique_lock<std::mutex> lock(taskMutex); // 加锁以保护任务队列
                // 等待条件变量，直到有任务或线程池停止
                condition.wait(lock, [this]
                               { return stop || !tasks.empty(); });
                // 如果线程池停止且任务队列为空，则退出循环
                if (stop && tasks.empty())
                {
                    return;
                }
                // 从任务队列中取出一个任务
                task = move(tasks.front());
                tasks.pop_front();
            }
            task(); // 执行任务
        }
    }
};