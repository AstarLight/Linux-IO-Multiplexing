#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include<sys/socket.h>  
#include<netinet/in.h>  
#include<arpa/inet.h>  
  
int client_tcp(char *serIP,in_port_t serPort,char *data);  
int main()  
{  
    int port=8888;  
    client_tcp("127.0.0.1",port,"Hello Server1!");  
    client_tcp("127.0.0.1",port,"Hello Server2!");  
    client_tcp("127.0.0.1",port,"Hello Server3!");  
    client_tcp("127.0.0.1",port,"quit");  
	return 0;
}  
  
  
int client_tcp(char *serIP,in_port_t serPort,char *data)  
{  
    //创建socket  
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  
    if (sock < 0) {  
        printf("socket Error!");  
        exit(0);  
    }  
  
    //填充sockaddr_in  
    struct sockaddr_in serAddr;  
    memset(&serAddr, 0, sizeof(serAddr));  
    serAddr.sin_family = AF_INET;  
    serAddr.sin_port = htons(serPort);  
    int rtn = inet_pton(AF_INET, serIP, &serAddr.sin_addr.s_addr);  
    //或者是  serAddr.sin_addr.s_addr=inet_addr(serIP);  
    if (rtn <= 0) {  
        printf("inet_pton Error!");  
        exit(0);  
    }  
  
    printf("目标服务器地址：%s: %d\n", inet_ntoa(serAddr.sin_addr), ntohs(serAddr.sin_port));  
    printf("     网络层协议：%s\n", serAddr.sin_family == 2 ? "IPv4" : "IPv6");  
    printf("     传输层协议：TCP\n");  
  
  
    //链接服务器  
    if (connect(sock, (struct sockaddr *) &serAddr, sizeof(serAddr)) < 0) {  
        printf("connect Error!!\n");  
        exit(0);  
    }  
    //show the other side  
    printf("connected Server %s : %d\n", inet_ntoa(serAddr.sin_addr), ntohs(serAddr.sin_port));  
  
    //发送数据  
    int bufsize = strlen(data);  
    int num = send(sock, data, bufsize, 0);  
    if (num <= 0) {  
        printf("Send Error!!\n");  
        exit(0);  
    }  
  
    //接收数据  
    fputs("Received: ", stdout);  
    char buffer[100];  
    int n = recv(sock, buffer, 100 - 1, 0);  
    if (n <= 0) {  
        printf("Receive Error!!\n");  
        exit(0);  
    } else {  
        buffer[n] = '\0';  
        printf("%s\n", buffer);  
    }  
  
    //关闭socket  
    close(sock);  
    //exit(0);  
    return 0;  
}  