// Write CPP code here
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define MAX 80
#define PORT 8081
#define SA struct sockaddr
void menu(){
    puts("");
    puts("0.Exit");
    puts("1.Load file:");
    puts("-->Available files with .dat extension");
    system("ls *.dat");
    puts("-->Example 1 fileName");
    puts("2.Search element:");
    puts("-->Example 2 80");
    puts("3.Fast search element");
    puts("-->Example 3 80");
}
void func(int sockfd)
{
    char buff[MAX];
    int n;
    for (;;) {
        bzero(buff, sizeof(buff));
        menu();
        printf("Please enter your input : ");
        n = 0;
        // Client enters his input
        char ch;
        while ((ch = getchar()) != '\n'){
            buff[n++] = ch;
        }

        // send message to server

        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));

        // receives message from server
        read(sockfd, buff, sizeof(buff));
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit... Thank you for using us!\n");
            break;
        }
        printf("From Server : %s",buff);


    }
}

int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    // socket create and varification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    // function for chat
    printf("**********\n" );
    func(sockfd);

    // close the socket
    close(sockfd);
}
