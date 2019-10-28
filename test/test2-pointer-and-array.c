#include<stdio.h> //printf
/*
理解数组名和指针


变量名本质上是一个代号，当我们使用变量名时，系统默认会【根据这个变量名找到对应的地址并且取出其中的值】，就好比我们叫“张三”的时候，默认是想要找到张三本人一样（程序和现实逻辑还是很相符的）。

=======详细举例对比=========
我对公司前台说“我要找张三"，前台根据他的记录（比如员工位置表）知道张三在某个位置，把张三找来了。只根据名字就可以找到正真的人。

程序中也是一样，我们写语句“printf (%s,a)”,通过变量的名字就可以得到变量中存储的值（编译过程记录了变量和存储地址的关系？）
=======详细举例对比=========


指针也是一个变量，它有自己的【变量名、地址、存储的值】。特殊之处在于，他的值是另外一个变量的地址。

但是调用数组名时，其默认行为与调用普通变量名的默认行为是有所不同的：
数组中存有多个值，就相当于一个集体（公司），调用数组名，就相当于说我要找某某公司，响应者没有办法把所有人都给你找来，就告诉你该公司地址，后续你再自己想办法。

所以，当调用变量时，普通变量的默认行为是【根据它的名字，找到它的位置，获取它的值】；数组变量的默认行为是【根据它的名字，找到他的位置】
*/

int main( int argc , char *argv[])
{	
	int a =10;
	int b[] = {0,1,2,3};
	
	printf("\n");
	printf("a = %d",a); //默认行为，根据它的名字，找到它的位置，获取它的值。
	printf("\n");
	printf("&a = %d",&a);//我只需要知道他的位置，不需要找到他本人
	printf("\n");
	printf("b = %d",b); //数组的默认行为，就相当于说我要找某某公司，没有办法把所有人都给你找来，就只告诉你地址，你自己再决定
	printf("\n");
	printf("b[0] = %d",b[0]);//我要找某某公司的第一个员工。
	printf("\n");
	printf("&b[0] = %d",&b[0]);//我要找某某公司的第一个员工的位置。
	printf("\n");
    return 0;
}