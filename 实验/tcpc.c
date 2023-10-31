#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    struct sockaddr_in server_addr;
    server_addr.sin_len = sizeof(struct sockaddr_in);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(11334);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    bzero(&(server_addr.sin_zero), 8);

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        perror("socket error");
        return 1;
    }

    char recv_msg[1024];
    char reply_msg[1024];

    if (connect(server_socket, (struct sockaddr *)&server_addr,
                sizeof(struct sockaddr)) == 0)
    {
        while (1)
        {
            bzero(recv_msg, 1024);
            bzero(reply_msg, 1024);

            long byte_num = recv(server_socket, recv_msg, 1024, 0);
            recv_msg[byte_num] = '\0';
            printf("server:%s\n", recv_msg);

            printf("reply:");
            scanf("%s", reply_msg);

            if (send(server_socket, reply_msg, 1024, 0) == -1)
            {
                perror("send error");
            }
        }
    }
    return 0;
}
