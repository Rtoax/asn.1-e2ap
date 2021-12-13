#!/bin/bash
# 
# 将 O-RAN E2AP ASN.1 转化为 C语言
# 理论上，这个脚本并不限于 E2AP，其他 由 Nokia 发布的
# O-RAN 文档 中的 ASN.1 均可由 此脚本进行C语言的生成，
# 
# 荣涛 rongtao@sylincom.com
# 2021年8月24日
# 

# 默认的 ASN.1 文件
file_asn1=""

DEFAULT_GEN_DEMO="converter-example.c"

function INFO() {
	echo -e "\033[1;34m $1 \033[0m"
}
function ERROR() {
	echo -e "\033[1;31m $1 \033[0m"
}


# 帮助信息
function usage() {
	echo ""
	echo Usage: ./genc.sh [ASN.1 file]
	echo ""
	echo "	[ASN.1 file] is ASN.1 file from some where that i dont know."
	echo ""
	echo "	You must install asn1c-s1ap, download in https://github.com/nokia/asn1c, version is v0.9.29"
	echo "	asn1c's version must be v0.9.29"
	echo ""
}

# 检查软件是否安装，版本是否对应
function check_asn1c() {
	which asn1c > /dev/null
	if [ $? != 0 ]; then
		ERROR "FATAL: asn1c not install"
		exit 1
	fi

	# 必须使用 Nokia 的 https://github.com/nokia/asn1c ，也就是 asn1c-s1ap
	if [ $(asn1c -v 2>&1 | grep ASN | awk '{print $3}') != "v0.9.29" ]; then
		ERROR "FATAL: wrong asn1c version, must v0.9.29(https://github.com/nokia/asn1c)"
		exit 1
	fi

}

# 检查 入参，以及 ASN.1 文件是否存在
function check_asn1_file() {
	if [ $# -lt 1 ]; then
		usage
		exit 1
	fi
	file_asn1=$1
	if [ ! -f $file_asn1 ]; then
		ERROR "FATAL: file \"$file_asn1\" not exist."
		exit 1
	fi
}

# 使用 asn1c 编译
function compile_asn1_file() {

	# 编译成 C语言
	asn1c -fcompound-names \
			-fincludes-quoted \
			-fno-include-deps \
			-findirect-choice \
			-gen-PER -D. \
			$file_asn1
}

# 修改 生成的 C语言测试文件
function modify_test_demo() {
	if [ ! -f $DEFAULT_GEN_DEMO ]; then
		WARNING "WARNING: file \"$DEFAULT_GEN_DEMO\" not exist."
		return 1
	fi
	echo "#include <stdio.h>" > $DEFAULT_GEN_DEMO
	echo "" >> $DEFAULT_GEN_DEMO
	echo "int main(int argc, char *argv[])" >> $DEFAULT_GEN_DEMO
	echo "{" >> $DEFAULT_GEN_DEMO
	echo "    printf(\"ASN.1 test running.\n\");" >> $DEFAULT_GEN_DEMO
	echo "    return 0;" >> $DEFAULT_GEN_DEMO
	echo "}" >> $DEFAULT_GEN_DEMO
}


# 检查软件是否安装，版本是否对应
INFO "Check asn1c software"
check_asn1c
INFO "Check asn1c software, OK"

# 检查 输入的文件
INFO "Check ASN.1 file"
check_asn1_file $*
INFO "Check ASN.1 file, OK"

# 使用 asn1c 编译
INFO "Compile ASN.1 file"
compile_asn1_file $file_asn1
INFO "Compile ASN.1 file, DONE"


# 修改 自动生成的 测试代码
#INFO "Modify C file"
#modify_test_demo
#INFO "Modify C file, DONE"

INFO ""
INFO "Now, you can do some thing like:"
INFO "$ mkdir build"
INFO "$ cd build"
INFO "$ cmake .."
INFO "$ make"
INFO "$ ./test"

# 修改 测试例文件
function modify_test() {
sed -i '24i #include "my-test/my_test.h"' converter-example.c
sed -i '199i test();' converter-example.c
}

modify_test
