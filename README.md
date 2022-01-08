README
==================

# asn.1-e2ap
ASN.1 coding

[https://github.com/Rtoax/test/tree/master/ASN.1/asn1c/jt_sran/e2ap](https://github.com/Rtoax/test/tree/master/ASN.1/asn1c/jt_sran/e2ap)


本文件夹内的 ASN.1 编码来源 <O-RAN.WG3.E2AP-v01.01.docx>

荣涛<rongtao@sylincom.com> 整理。

[Rong Tao](https://github.com/Rtoax)

- 👋 Hi, I’m [@rtoax](https://github.com/Rtoax), you can see me in [@linux-visor](https://github.com/linux-visor) too.
- 👀 I’m interested in [Linux](https://github.com/torvalds/linux)
- 🌱 I’m currently learning [Linux](https://github.com/torvalds/linux)
- 💞️ I’m looking to collaborate on [libcareplus](https://github.com/Rtoax/libcareplus), [test-linux](https://github.com/Rtoax/test-linux) and [more](https://github.com/Rtoax).
- 📫 How to reach me [GitHub](https://github.com/Rtoax), [CSDN](https://rtoax.blog.csdn.net/), [Gitee](https://gitee.com/rtoax) and 哆啦Linux梦.

步骤
======================

1. 生成 C语言

```bash
./genc.sh asn-file.asn1
```

2. 编辑代码

上一步的脚本中会将代码修改为

```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("ASN.1 test running.\n");
    return 0;
}
```

3. 生成 Makefile

```
mkdir build 
cd build 
cmake ..
```

4. 编译和运行

```
make
./test
```

清理
======================

该步骤会删除 `生成 C语言` 步骤中生成的 C语言文件
```bash
./clean.sh
```
