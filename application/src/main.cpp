#include <fmt/core.h>

#include <ghc/filesystem.hpp>

#include "webserver/webserver.h"

namespace fs = ghc::filesystem;

int main(int argc, char* argv[])
{
    try
    {
        // 获取当前可执行文件路径
        fs::path exe_path = fs::canonical(argv[0]);

        // 获取可执行文件所在目录
        fs::path exe_dir = exe_path.parent_path();
        fmt::println("hello world!");
        fmt::print("Executable path: {}\n", exe_path.string());
        fmt::print("Executable directory: {}\n", exe_dir.string());

        // webserver服务
        WebServer server("192.168.128.128", 8848);
        server.run(); // 会阻塞当前线程

        // // 启动服务器线程
        // std::thread server_thread([&server]() {
        //     server.run();  // 阻塞直到 stop() 被调用
        // });

        // // 模拟业务逻辑
        // std::this_thread::sleep_for(std::chrono::seconds(10));

        // // 停止服务器
        // std::cout << "Stopping server..." << std::endl;
        // server.stop();

        // // 等待线程退出
        // if (server_thread.joinable()) server_thread.join();

    }
    catch (const std::exception& e)
    {
        fmt::print(stderr, "Error: {}\n", e.what());
        return 1;
    }

    return 0;
}
