#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>


#define PORT 8080
#define BUFFER_SIZE 1024
#define SERVER_IP "127.0.0.1" // 服务器IP地址

int main() {
  int sockfd;
  char buffer[BUFFER_SIZE];
  char *message = "Hello from UDP client";
  struct sockaddr_in servaddr;

  // 1. 创建UDP套接字
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  // 初始化服务器地址结构
  memset(&servaddr, 0, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);

  // 转换IP地址为二进制形式
  if (inet_pton(AF_INET, SERVER_IP, &servaddr.sin_addr) <= 0) {
    perror("无效的地址/地址不可达");
    exit(EXIT_FAILURE);
  }

  // 2. 发送数据到服务器
  sendto(sockfd, (const char *)message, strlen(message), MSG_CONFIRM,
         (const struct sockaddr *)&servaddr, sizeof(servaddr));
  printf("消息已发送: %s\n", message);

  // 3. 接收服务器响应
  socklen_t len = sizeof(servaddr);
  ssize_t n = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, MSG_WAITALL,
                       (struct sockaddr *)&servaddr, &len);
  buffer[n] = '\0';
  printf("收到服务器响应: %s\n", buffer);

  // 4. 关闭套接字
  close(sockfd);
  return 0;
}
