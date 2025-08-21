cmake_minimum_required(VERSION 3.0)
project(CppLibrariesBuild)

# 定义输出库的文件夹路径，比如叫“output_libs”，可按需改
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/output_libs) 

add_subdirectory(design_patterns)