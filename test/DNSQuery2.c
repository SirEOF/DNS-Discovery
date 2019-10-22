/*************************************************************************
    > File Name: MyFiles/C和C++程序/socket/getIP.c
    > Author: mr_zys
    > Mail: 247629929@qq.com
    > Created Time: Thu 12 Jun 2014 05:22:06 PM CST
    > Operating System: Ubuntu 12.04 LTS
    > Programming Language: Linux c
    > Compiler: gcc
    > Description: this is a program with Linux socket APIs to ask DNS server for domain name's IP adress!
 ************************************************************************/
 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>

#define MAX_SIZE 1024
#define SERVER_PORT 53
 
void setHead(unsigned char *buf)
{
    buf[0] = 0x00;
    buf[1] = 0;
    buf[2] = 0x01;
    buf[3] = 0;
    buf[4] = 0;
    buf[5] = 1;
    buf[6] = 0;
    buf[7] = 0;
    buf[8] = buf[9] = buf[10] = buf[11] = 0;
}
 
void setQuery(char *name, unsigned char *buf, int len)
{
    strcat(buf+12,name);
    int pos = len + 12;
    buf[pos] = 0;
    buf[pos+1] = 1;
    buf[pos+2] = 0;
    buf[pos+3] = 1;
}
int changeDN(char *DN,char *name)
{
    int i = strlen(DN) - 1;
    int j = i + 1;
    int k;
    name[j+1] = 0;
    for(k = 0; i >= 0; i--,j--) {
        if(DN[i] == '.') {
            name[j] = k;
            k = 0;
        }
        else {
            name[j] = DN[i];
            k++;
        }
    }
    name[0] = k;
    return (strlen(DN) + 2);
}
void printName(int len, char *name)
{
    int i;
    for(i = 0; i < len; i++) printf("%x.",name[i]);
    printf("\n");
}
 
int sendDNSPacket(unsigned char *buf, int len, char *recvMsg)
{
    int s;
    struct sockaddr_in sin;
 
    memset(&sin,0,sizeof(sin));
    sin.sin_addr.s_addr = inet_addr("223.5.5.5");
    sin.sin_family = AF_INET;
    sin.sin_port = htons(SERVER_PORT);
 
    s = socket(PF_INET,SOCK_DGRAM,0);
    sendto(s,buf,len,0,(struct sockaddr *)&sin,sizeof(sin));
    return recv(s,recvMsg,MAX_SIZE,0);
 
}
void resolve(unsigned char *recvMsg, int len, int len_recvMsg)
{
    int pos = len;
    int cnt = 12;
    while(pos < len_recvMsg) {
        unsigned char now_pos = recvMsg[pos+1];
        unsigned char retype = recvMsg[pos+3];
        unsigned char reclass = recvMsg[pos+5];
        unsigned char offset = recvMsg[pos+11];
        if(retype == 1) {
            if(now_pos == cnt && reclass == 1) {
                printf("%u.%u.%u.%u\n",recvMsg[pos+12],recvMsg[pos+13],recvMsg[pos+14],recvMsg[pos+15]);
            }
        }
        else if(retype == 5) {
            cnt = pos + 12 ;
        }
        pos = pos + 12 + offset;
    }
}
int main()
{
    unsigned char buf[MAX_SIZE]; /* socket发送的数据 */
    char DN[MAX_SIZE]; /* 将要解析的域名(www.xxx.xxx) */
    char name[MAX_SIZE]; /* 转换为符合DNS报文格式的域名 */
    char recvMsg[MAX_SIZE]; /* 接收的数据 */
    int len; /* socket发送数据的长度 */
    int s; /* socket handler */
 
    printf("输入需要解析的域名：");
    scanf("%s",DN);
     
    len = changeDN(DN,name);
    //printName(len,name); /* 打印转换后的域名，检测是否转换正确 */
    int j;
    //printf("len is %d\n",len);
    setHead(buf);
    setQuery(name,buf,len);
    len += 16;
    int len_recvMsg = sendDNSPacket(buf,len,recvMsg);
    printf("接收的报文长度为 %d 字节\n",len_recvMsg);
    printf("下面是接收报文的16进制表示：\n");
    int i;
    for(i = 0; i < len_recvMsg; i++) {
        printf("%x.",(unsigned char)recvMsg[i]);
    }
    printf("\n");
    printf("%s的IP地址为：\n",DN);
    resolve(recvMsg,len,len_recvMsg);
 
}
