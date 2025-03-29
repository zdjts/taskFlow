# 🧵✨ 自定义线程池示例：多线程的魔法工厂 ✨🧵

## 简介
欢迎来到 **线程池的奇妙世界**！  
在这里，你将见证如何用 C++11 的多线程特性打造一个高效的任务处理工厂。线程池就像一群勤劳的小蜜蜂，帮你分担繁重的任务，让你的程序飞速运行！  
无论你是刚接触 C++ 多线程的萌新，还是想要优化代码性能的老手，这个项目都能让你感受到多线程的魅力和乐趣！

## 特性
- 🌟 **基于 C++11 标准库**：不依赖任何外部库，纯净的 C++11 实现，简单又强大。
- 🛠️ **任务队列管理**：支持任务的动态添加和执行，线程池会自动调度任务，像流水线一样高效。
- 💤 **线程池的优雅停止**：线程池支持动态停止，线程们会乖乖退出，绝不罢工。
- 🚀 **性能对比**：提供多线程与单线程的性能对比示例，看看多线程到底有多快！
- 🧪 **学习友好**：代码清晰，注释详细，非常适合学习 C++ 多线程的同学。

## 使用方法
1. 克隆项目到本地：
   ```bash
   git clone https://github.com/YourRepo/BoostHive.git
   cd BoostHive/TaskFlow
   ```

2. 编译代码：
   使用支持 C++11 的编译器（如 g++）进行编译：
   ```bash
   g++ -std=c++11 -pthread text.cpp -o threadPoolExample
   ```

3. 运行程序：
   ```bash
   ./threadPoolExample
   ```

4. 观察输出：
   程序会输出多线程和单线程的素数统计结果，以及两种方式的执行时间对比。  
   你会惊叹于多线程的速度，简直像开了挂！

## 示例输出
运行程序后，你可能会看到类似以下的输出：
```
Multi-threaded sum = 303
Multi-threaded time: 50 ms
Single-threaded sum = 303
Single-threaded time: 150 ms
```
是不是很酷？多线程让计算效率飞速提升！🚀

## 项目结构
```
BoostHive/
├── TaskFlow/
│   ├── threadPool.hpp   # 线程池实现
│   ├── text.cpp         # 示例代码
│   └── READEM.MD        # 项目说明文件
```

## 学习目标
通过本项目，你将学会：
1. 如何使用 C++11 的多线程库（`std::thread`、`std::mutex`、`std::condition_variable`）。
2. 如何实现一个简单的线程池。
3. 如何通过多线程提升程序性能。
4. 如何优雅地管理线程的生命周期。

## 注意事项
- 本项目主要用于学习目的，未进行性能优化。
- 如果需要更高效的线程池实现，可参考 Boost 或 Intel TBB 等库。

## 最后
如果你觉得这个项目对你有帮助，请给个 ⭐Star⭐ ![GitHub stars](https://img.shields.io/github/stars/zdjts/ttaskFlow?style=social)
 支持一下吧！  
多线程的世界很精彩，快来一起探索吧！😄
