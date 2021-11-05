aux_source_directory(. SRC_LIST)

add_executable(ChatClient ${SRC_LIST})

# 指定可执行文件链接时需要依赖的库文件
target_link_libraries(ChatClient pthread)