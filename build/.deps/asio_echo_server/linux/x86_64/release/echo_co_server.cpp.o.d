{
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-std=c++20"
        }
    },
    files = {
        "echo_co_server.cpp"
    },
    depfiles_gcc = "echo_co_server.o: echo_co_server.cpp\
"
}