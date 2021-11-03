# g++ -o server -g muduo_server.cpp xxx.cpp -l/usr/include -L/usr/lib -lmuduo_net -lmuduo_base -lpthread

cmake_minimum_required(VERSION 3.0)
project(main)

# 配置编译选项 -O2 -g
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

# 配置头文件搜索路径 -l/usr/include
# include_directories()

# 配置库文件搜索路径 -l/usr/lib
# link_directories()

# 设置需要编译的源文件列表
set(SRC_LIST muduo_server.cpp)

# 设置可执行文件最终存储的路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 把.指定路径下的所有源文件名字放入变量SRC_LIST里面
# aux_source_directory(. SRC_LIST)

add_executable(server ${SRC_LIST})

# server需要链接库文件
target_link_libraries(server muduo_net muduo_base pthread)