set_project("asio_client_server")

target("server")
    set_kind("binary")
    add_files("server.cpp") 
    set_languages("cxx20")

target("client")
    set_kind("binary")
    add_files("client.cpp")
    set_languages("cxx20")