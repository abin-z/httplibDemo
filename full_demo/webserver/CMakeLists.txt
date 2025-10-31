# 目标名称
set(tgt_name webserver)

file(GLOB_RECURSE headers include/*.h include/*.hpp)
file(GLOB_RECURSE sources src/*.c src/*.cpp src/*.cc src/*.cxx)

add_library(${tgt_name} ${headers} ${sources})

target_include_directories(${tgt_name} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)

if(UNIX)
  target_link_libraries(${tgt_name} PRIVATE ${THREAD_LIB})
endif()
target_link_libraries(${tgt_name} PRIVATE fmt::fmt)
target_link_libraries(${tgt_name} PUBLIC cpp-httplib)
target_link_libraries(${tgt_name} PUBLIC controller)
