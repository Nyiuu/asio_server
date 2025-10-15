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

    if is_plat("linux", "macosx") then
        add_links("pthread")
    end
    -- Windows (Winsock)
    if is_plat("windows") then
        add_links("ws2_32", "mswsock")
    end

    add_includedirs("/opt/homebrew/opt/asio/include")