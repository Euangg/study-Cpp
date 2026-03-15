#include<assert.h>
#include<ctype.h>//13	字符类测试
#include<errno.h>
#include<float.h>
#include<limits.h>
#include<locale.h>
#include<math.h>//22	数学函数
#include<setjmp.h>
#include<signal.h>//2	信号处理
#include<stdarg.h>
#include<stddef.h>
#include<stdio.h>//41	标准输入输出
#include<stdlib.h>//28	实用函数
#include<string.h>//22	字符串处理函数
#include<time.h>//9		日期与时间
//共15个头文件137个库函数


void func_ctype() {
	isalnum(5);//判断是否是字母或数字
	isalpha(5);//判断是否是字母
	iscntrl(5);//判断是否是控制字符
	isdigit(5);//判断是否是数字
	isgraph(5);//是否是可显示字符
	islower(5);//判断是否是小写字母
	isupper(5);//判断是否是大写字母
	isprint(5);//是否是可显示字符
	ispunct(5);//是否是标点字符
	isspace(5);//是否是空白字符
	isxdigit(5);//是否为16进制
	tolower(5);//转换为小写字母
	toupper(5);//转换为大写字母
}