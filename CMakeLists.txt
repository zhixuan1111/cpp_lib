# 指定CMake最低版本
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(CppLib)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 指定要编译的源文件
set(SOURCE_FILES smart_pointer/shared_ptr/shared_ptr.cpp)

# 创建静态库
add_library(shared_ptr STATIC ${SOURCE_FILES})

# 设置静态库的输出目录
# ARCHIVE_OUTPUT_DIRECTORY用于静态库
# LIBRARY_OUTPUT_DIRECTORY用于动态库
set_target_properties(shared_ptr PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"  # 静态库输出目录
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/lib/debug"  # 调试版本
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/lib/release"  # 发布版本
)