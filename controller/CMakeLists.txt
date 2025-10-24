# 目标名称
set(tgt_name controller)

# 收集头文件和源文件
file(GLOB_RECURSE HEADERS include/controller/*.h include/controller/*.hpp)
file(GLOB_RECURSE SOURCES src/*.c src/*.cpp src/*.cc src/*.cxx)

add_library(${tgt_name} ${HEADERS} ${SOURCES})

# 添加头文件路径
target_include_directories(${tgt_name} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

# 链接依赖库
if(UNIX)
  target_link_libraries(${tgt_name} PRIVATE ${THREAD_LIB})
endif()

target_link_libraries(${tgt_name} PUBLIC fmt::fmt)
target_link_libraries(${tgt_name} PUBLIC cpp-httplib)
target_link_libraries(${tgt_name} PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(${tgt_name} PUBLIC viewobject)
