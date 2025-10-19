# inhttplibifile.h 头文件库（Header-Only） INTERFACE 类型
# INTERFACE 目标不会生成 .a 或 .so 文件，但可以被 target_link_libraries 依赖。
add_library(cpp-httplib INTERFACE)
target_include_directories(cpp-httplib INTERFACE ${CMAKE_CURRENT_LIST_DIR})