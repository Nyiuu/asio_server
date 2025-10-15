-- xmake.lua

-- 设置项目名称
set_project("asio_echo_server")

-- 添加可执行目标
target("asio_echo_server")
    -- 设置目标类型为可执行程序
    set_kind("binary")

    -- 添加源文件
    add_files("echo_co_server.cpp") 

    -- 设置 C++ 标准为 C++20，因为代码使用了 C++ 协程 (co_await)
    set_languages("cxx20")

    -- 添加 Asio 库的依赖
    -- Asio 通常作为头文件库使用，但如果需要编译系统库（如Boost.Asio或Asio独立版，
    -- 特别是需要链接系统网络库时），可能需要添加链接器设置。
    -- 对于 Asio 独立版，它通常是纯头文件，但可能需要系统网络库。
    -- 对于使用 C++ 协程的版本，可能需要链接系统协程库（如 liburing, 或在某些系统上不需额外链接）。
    
    -- 1. 链接系统网络库（通常是必需的）
    -- Linux/macOS
    if is_plat("linux", "macosx") then
        add_links("pthread")
    end
    -- Windows (Winsock)
    if is_plat("windows") then
        add_links("ws2_32", "mswsock")
    end

    -- 2. 添加 Asio 头文件路径
    -- 假设 Asio 库的头文件位于您的项目中，或者您可以通过系统路径找到它。
    -- 如果是纯头文件，这步通常是可选的，除非头文件不在标准搜索路径中。
    -- 如果你使用 xrepo 安装 Asio:
    -- add_packages("asio")
    
    -- 3. （可选）如果你安装了 Asio 的包，比如通过 xrepo
    -- add_packages("asio")

    -- 4. 启用 Boost.Context 或其他协程后端（对于某些旧版本或特定配置可能需要）
    -- 对于 Asio 独立版的 C++20 协程，通常不需要额外设置，编译器会自动处理。