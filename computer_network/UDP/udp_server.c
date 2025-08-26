#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>


#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
  int server_fd;
  char buffer[BUFFER_SIZE];
  struct sockaddr_in server_addr, client_addr;

  // 1. 创建UDP套接字
  if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  // 初始化服务器地址结构
  memset(&server_addr, 0, sizeof(server_addr));
  memset(&client_addr, 0, sizeof(client_addr));

  server_addr.sin_family = AF_INET;         // IPv4
  server_addr.sin_addr.s_addr = INADDR_ANY; // 绑定到所有可用接口
  server_addr.sin_port = htons(PORT);       // 端口号，转换为网络字节序

  // 2. 绑定套接字到指定端口
  if (bind(server_fd, (const struct sockaddr *)&server_addr,
           sizeof(server_addr)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  printf("UDP服务器启动，等待数据...\n");

  while (1) {
    socklen_t len = sizeof(client_addr);

    // 3. 接收客户端数据
    ssize_t n = recvfrom(server_fd, (char *)buffer, BUFFER_SIZE, MSG_WAITALL,
                         (struct sockaddr *)&client_addr, &len);
    buffer[n] = '\0';
    printf("收到客户端消息: %s\n", buffer);

    // 4. 向客户端发送响应
    const char *response = "消息已收到";
    sendto(server_fd, (const char *)response, strlen(response), MSG_CONFIRM,
           (const struct sockaddr *)&client_addr, len);
    printf("响应已发送\n");
  }

  // 5. 关闭套接字（实际不会执行到这里，因为上面是无限循环）
  close(server_fd);
  return 0;
}
