# 定义了一个SRC_LIST变量，包含了该目录下所有源文件, .为指定路径
aux_source_directory(. SRC_LIST)

# 指定生成可执行文件
add_executable(ChatClient ${SRC_LIST})

#客户端读写两个线程，读线程负责接收ChatServer消息，写线程负责发送相应的业务数据
# 指定可执行文件链接时需要依赖的库文件
target_link_libraries(ChatClient pthread)