###################################################
# 编译使用 asn1c 编译 ASN.1 文件而生成的 C语言 程序
#
# 作者：荣涛 
# 时间：2021年8月
###################################################

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(e2ap)

aux_source_directory(./ DIR_SRCS)
aux_source_directory(./my-test DIR_SRCS)
aux_source_directory(./wrapper DIR_SRCS)

include_directories(./)

find_library(CONFIG config /usr/lib64)
link_libraries(${CONFIG})

# -DPDU=RICcontrolRequest
add_definitions(-ggdb -g -MD -Wall -DPDU=RICcontrolRequest)

ADD_EXECUTABLE(test ${DIR_SRCS})
