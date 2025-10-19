
# 定义一个函数来添加可执行文件并链接所需的库
function(add_web_target tgt src)
add_executable(${tgt} ${src})
    # 链接 cpp-httplib 头文件库
    target_link_libraries(${tgt} PRIVATE cpp-httplib)
  if(UNIX)
    # 链接 pthread 库（如果适用）
    target_link_libraries(${tgt} PRIVATE ${THREAD_LIB})
  endif()
endfunction()

# Define web server and client targets
add_web_target(webserver server.cpp)
add_web_target(client client.cpp)
add_web_target(logintest logintest.cpp)
