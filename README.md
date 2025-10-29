# HttpLibDemo

本项目主要演示 [cpp-httplib](https://github.com/yhirose/cpp-httplib) 库的基本使用, 这个库很适合用在嵌入式程序中, 方便小巧易于使用!

`cpp-httplib` 是一个非常流行、**轻量级、单头文件、C++11兼容** 的 HTTP/HTTPS 服务器与客户端库。它的设计目标是简单易用、零依赖（或最小依赖），在嵌入式系统和小型项目中尤其受欢迎。

主要优点: 

- 单头文件、零依赖、默认仅依赖 C++11 标准库
- 支持 HTTP 服务端 + 客户端
- 完整的 HTTP 功能支持, 也支持HTTPS
- 跨平台兼容, 支持 Linux / macOS / Windows / Android / iOS。
- 线程安全与多线程支持
- 体积小、内存占用低, 适合内存紧张（RAM < 100MB ）的嵌入式系统或微服务

局限:

- 非异步 I/O, 使用阻塞式 socket，无法高并发（>1k连接）。
- 没有websocket
