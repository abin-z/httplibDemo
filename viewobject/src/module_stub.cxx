/**
 *  ##########################
 *  ###### 不要删除该文件 ######
 *  #########################
 * 
 * @file module_stub.cxx
 * @brief Build context file for the viewobject library.
 *
 * 中文说明：
 * 本文件用于为 viewobject 模块提供编译上下文（Translation Unit）。
 * 因为该模块大部分是仅包含头文件的代码，如果不提供 .cpp 源文件，
 * CMake 可能不会为它生成完整的编译信息，导致 clangd、IDE 等工具
 * 无法正确识别头文件依赖（如 nlohmann/json.hpp），从而出现虚假报错。
 *
 * 注意：
 * - 请不要删除这个文件
 * - 文件内容无需任何逻辑
 * - 存在的目的仅是为了构建支持与开发工具兼容性
 *
 * This translation unit exists to ensure that CMake generates proper
 * compile commands for all header-only components inside this module.
 * Without this file, some IDE tools (such as clangd) might not be able to
 * provide correct code completion or include path analysis.
 *
 * Note:
 * - Do NOT remove this file
 * - No implementation is required here
 * - Exists solely for build system and tools compatibility
 */
