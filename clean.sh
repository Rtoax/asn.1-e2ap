#!/bin/bash
# 荣涛 2021年8月23日

rm -f *.c *.h *.sample

# v0.9.29 会生成下面的文件
rm -f converter-example.mk Makefile.am.asn1convert Makefile.am.libasncodec

# 删除build 文件夹中的文件

rm -rf build/*
