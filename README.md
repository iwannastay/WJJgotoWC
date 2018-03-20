# WJJgotoWC
开发环境:Visual Studio 2015
开发语言:C++
运行系统环境: Win10 x64

支持基本功能 -c -w -l -o 
支持扩展功能 -s -a -e
支持高级功能 -x

源代码: .\WordCount.cpp
控制台程序: .\BIN\WJJgotoWC.exe
图形界面程序: .\BIN\WordCountUI.exe
文本样例: .\BIN\file.c
         .\BIN\FileSample\cc.c
         .\BIN\FileSample\JJJ.c
默认输出文件: .\BIN\result.txt
指定参考输出文件: .\BIN\Xresult.txt
停用词文件: .\BIN\stopList.txt
10个测试样例: .\BIN\TestList.txt


程序说明：
1.定义：1）字符：任意字符包括空格、逗号等符号及控制字符（换行符仅统计'\n'）；
       2）单词：空格、逗号、换行符及制表符分开的任意字符串；
       3）行数：包括但不仅限于代码行、空行、注释行，即后三者之和<=总行数，具体定义见下文。
       4）目录递归处理：包含目录及目录下子文件所有复合条件的文件，支持＊通配符。
       5）行分类：代码行：从左到右遇到注释标志或到行尾之前包含一个以上代码字符（此处字符要求为有效字符，如abc123等，不包括空格、回车符等无义字符）；
                 空行：不含任何字符；
                 注释行：以//开头，或//左侧含有小于两个有效字符；
       6）停用词：停用词与检查文本严格对应，不联想包含关系，如停用词为“asd”，检测文本中某单词为“111asd111”，则后者仍计入单词数；
       7）高级功能：程序WordCountUI.exe 应与WJJgotoWC.exe 放在同一路径下，可由WJJgotoWC.exe 通过命令行参数"WJJgotoWC.exe -x"打开，也可直接打开。

2.使用方法：
    1）进入CMD控制台，转入目标程序文件夹下，如"D:\Users\6666>Program Files>"；
    2）输入命令，如"WJJgotoWC.exe -c -w -l -o Xresult.txt -s -a -e stopList.txt file.c"，具体功能参数可自行选择，-o 与 -e 不能单独使用，后面必须附有相应文件名；
    3）单独使用"WJJgotoWC.exe -x" 使用高级功能。
    
3.测试脚本：
    想提高自己能力的助教可以尝试编写，答案略。
                 
