#include<stdio.h>
/*
snprintf的用法

1、注意第二个参数的值不代表结果字符串的长度，结果字符串的长度是n-1!!!
2、不能自己复制到自己，各种奇怪。

http://www.cplusplus.com/reference/cstdio/snprintf/
*/
int main(int argc, char argv)
{
 char str1[10] = "abcdef";
 char str2[512];
 
 //snprintf(str1, sizeof(str1), "%s---%s","aaaa","0123456789012345678");
 //printf("%s\n", str1);
 //sizeof限制最终字符串的最大长度

 //snprintf(str1, 10, "%s---%s",str1,"0123456789012345678");
 //printf("str1 to str1 %s\n", str1);
 //自己复制到自己是不行的,str1的部分消失了
 
 snprintf(str1, 10, "dddd%s---%s",str1,"0123456789012345678");
 printf("str1 to str1 %s\n", str1);
 //结果居然是ddddddddd 
 
 snprintf(str2, sizeof(str2), "%s---%s",str1,"0123456789012345678");
 printf("str1 to str2 %s\n", str2);
 //OK
 
 char outputline[512];
 char tmp[512];

 snprintf(outputline, 512, "%s", "111");
 int i=5;
 while (i >0){
	snprintf(tmp, 512, "%s", outputline);
	snprintf(outputline, 512, "%s--%s", tmp, "AAA");
	i--;
 }
 printf("outputline %s\n", outputline);
 
 return 0;
}