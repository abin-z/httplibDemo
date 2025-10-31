add_library(viewobject src/module_stub.cxx)

# 添加 VO 头文件路径
target_include_directories(viewobject PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
)

# 链接 nlohmann_json
target_link_libraries(viewobject PUBLIC nlohmann_json::nlohmann_json)
