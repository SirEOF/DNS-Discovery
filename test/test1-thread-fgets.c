#include<stdio.h> //printf
#include<string.h>    //strlen
#include<stdlib.h>    //malloc
#include<pthread.h>
 
pthread_mutex_t mutexsum;

/*
多线程测试程序1：
检查fgets是否是线程安全的？
结论：是线程安全的（在C11标准下）

通过多线程通过fgets函数从文件中读取内容，从输出结果和原始文件进行对比
输出条目个数和原始文件中行数相等，表明是线程安全的。

//C.11 makes thread safety guarantees on file operations

*/

//该函数在本程序下无用
void ngethostbyname(unsigned char *host , int query_type)
{
	pthread_mutex_lock(&mutexsum);//1、上锁
	
	pthread_mutex_unlock(&mutexsum);//3、解锁
    return;
}

//该函数的作用是去除换行符，类似java中的trim()
void chomp(char * str)
{
  while (*str) {
    if (*str == '\n' || *str == '\r') {
      *str = 0;
      return;
    }
    str++;
  }
}

void * dns_discovery(void * file)
//这个函数的返回值类型，参数类型都有严格要求
//须符合pthread_created函数的参数规范
{
    char line[256];
    char hostname[512];
	FILE * wordlist = (FILE *) file;
    while (fgets(line, sizeof line, wordlist) != NULL) {
        chomp(line);
		//字符串拼接 hostname=line+"."+domain，#include <stdio.h>
        snprintf(hostname, sizeof hostname, "%s.%s", line, "jr.jd.com");
		printf("%s\n",hostname);
        //ngethostbyname(hostname,T_A);
    }
}
 
int main( int argc , char *argv[])
{	
	int i;
	pthread_t * threads;
	threads = (pthread_t * ) malloc(10000 * sizeof(pthread_t)); 
	FILE * wordlist = fopen("test.wl", "r");
    for (i = 0; i < 10000; i++) {//创建线程
        if (pthread_create(&threads[i], NULL, dns_discovery, (void *)wordlist) != 0)
            printf("pthread_create");
    }
    for (i = 0; i < 10000; i++) {//等待线程结束
        pthread_join(threads[i], NULL);
    }
  
    free(threads);
    fclose(wordlist);
    return 0;
}