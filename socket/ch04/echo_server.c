#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define BUF_SIZE 1024
void error_handling(char *message);
int main(int argc,char* argv[]){
    int serv_sock,clnt_sock;
    struct sockaddr_in serv_addr,clnt_addr;
    socklen_t clnt_addr_size;
    int str_len,i;
    char message[BUF_SIZE];
    if (argc!=2) {
        printf("Usage:%s <port>\n",argv[0]);
        exit(1);
    }
    // 创建TCP socket
    serv_sock = socket(PF_INET,SOCK_STREAM , 0);
    printf("serv_sock is:%d",serv_sock);
    if (serv_sock == -1) {
        error_handling("socket() error");
    }else {
        printf("serv_sock is:%d",serv_sock);
    }

    // 格式化内存
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(argv[1]));
    if (bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1) {
        error_handling("bind() error");
    }
    if (listen(serv_sock,5)==-1) {
        error_handling("listen() error");
    }
    clnt_addr_size= sizeof(clnt_addr);
    // server 打印出来connected 字段，需要客户端那边退出，断开连接
    for( i=0;i<5;i++){
        clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
        if (clnt_sock==-1) {
            error_handling("accept() error");
        }else {
            printf("Connected client:%d",i+1);
        }
        while ((str_len=read(clnt_sock, message,BUF_SIZE ))!=0) {
            write(clnt_sock, message,str_len);
        }
        
        close(clnt_sock);
    }
    close(serv_sock);
    return 0;

}
void error_handling(char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}