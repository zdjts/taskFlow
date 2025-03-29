#include <iostream>
#include <vector>
#include <chrono>             // 用于时间测量
#include "threadPool.hpp"
using namespace std;

int main() {
    mutex tm;                 // 用于保护共享资源的互斥锁
    vector<int> primes;       // 用于存储素数
    int sum = 0;              // 素数计数器
    int count = 2000000; // 任务数量
    // 记录多线程开始时间
    auto startMulti = chrono::high_resolution_clock::now();

    {
        threadPool td;     // 创建一个线程池，包含 3 个线程

        // 向线程池添加任务，检查 0 到 2049 的素数
        for (int i = 0; i < count; ++i) {
            td.addTasks([i, &tm, &primes, &sum]() -> void {
                // 检查当前数字是否为素数
                for (int z = 2; z < i; ++z) {
                    if (i % z == 0) { // 如果能被 z 整除，则不是素数
                        return;
                    }
                }

                // 如果是素数，更新计数器并存储到 primes
                unique_lock<std::mutex> lock(tm); // 加锁以保护共享资源
                primes.push_back(i);              // 将素数存入 vector
                sum++;                            // 增加素数计数
            });
        }
    } // 离开作用域时，线程池析构，等待所有任务完成

    // 记录多线程结束时间
    auto endMulti = chrono::high_resolution_clock::now();
    auto multiThreadDuration = chrono::duration_cast<chrono::milliseconds>(endMulti - startMulti).count();

    // 输出多线程结果
    cout << "sum = " << sum << endl;
    cout << "多线程时间为" << multiThreadDuration << " ms" << endl;

    // 清空 primes 和 sum，准备单线程测试
    primes.clear();
    sum = 0;

    // 记录单线程开始时间
    auto startSingle = chrono::high_resolution_clock::now();

    // 单线程检查素数
    // for (int i = 0; i < count; ++i) {
    //     bool isPrime = true;
    //     for (int z = 2; z < i; ++z) {
    //         if (i % z == 0) { // 如果能被 z 整除，则不是素数
    //             isPrime = false;
    //             break;
    //         }
    //     }
    //     if (isPrime) {
    //         primes.push_back(i); // 将素数存入 vector
    //         sum++;               // 增加素数计数
    //     }
    // }

    // 记录单线程结束时间
    auto endSingle = chrono::high_resolution_clock::now();
    auto singleThreadDuration = chrono::duration_cast<chrono::milliseconds>(endSingle - startSingle).count();

    // 输出单线程结果
    cout << "sum = " << sum << endl;
    cout << "单一线程所用时间为: " << singleThreadDuration << " ms" << endl;

    return 0;
}
