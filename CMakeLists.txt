cmake_minimum_required(VERSION 3.0)
project(chatserver)

#配置编译选项  2
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

#指定搜索子目录
#add_subdirectory(testmuduo)

#配置最终的可执行文件输出的路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#头文件的搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/server)
include_directories(${PROJECT_SOURCE_DIR}/include/server/db)
include_directories(${PROJECT_SOURCE_DIR}/include/server/model)
include_directories(${PROJECT_SOURCE_DIR}/include/server/redis)
include_directories(${PROJECT_SOURCE_DIR}/shirdparty)

link_directories(/usr/lib64/mysql)
#默认路径
#link_directories(/usr/lib)
#link_directories(/usr/local/lib)

#加载子目录
add_subdirectory(src)