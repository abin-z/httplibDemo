# 目标名称
set(tgt_name mainapp)

file(GLOB_RECURSE headers include/*.h include/*.hpp)
file(GLOB_RECURSE sources src/*.c src/*.cpp src/*.cc src/*.cxx)

add_executable(${tgt_name} ${headers} ${sources})

target_include_directories(${tgt_name} PUBLIC include)

target_link_libraries(${tgt_name} PRIVATE fmt::fmt)
target_link_libraries(${tgt_name} PRIVATE webserver)