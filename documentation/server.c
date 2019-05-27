#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80
#define PORT 8081
#define SA struct sockaddr

// Function designed for chat between client and server.
void func(int sockfd)
{
    char buff[MAX];
    int n;
    int arr[3];
    arr[0] = 1;
    arr[1] = 11;
    arr[2] = 2;
    // infinite loop for chat
    for (;;) {
        bzero(buff, MAX);

        // read the message from client and copy it in buffer
        read(sockfd, buff, sizeof(buff));
        // print buffer which contains the client contents
        printf("From client: %s\t\n ", buff);

        n = 0;
        if (buff[0] == '0') {
            printf("Server Exit...\n");
            write(sockfd, "exit", sizeof(buff));
            break;
        } else if (buff[0] == '1') { // need a fix
            printf("Load...\n");
            bzero(buff, MAX);
            for(int k = 0; k < 3; k++){
                char numberAsString[100];
                sprintf(numberAsString, "%d", arr[k]);
                strcat(buff, numberAsString);
                //strcat(); // not ready!!!
            }
            printf("%s Should be successfully send\n", buff);
            write(sockfd, buff, sizeof(buff));
        } else if (buff[0] == '2') {
            bzero(buff, MAX);
            write(sockfd, "Option 2 not implemented.", sizeof(buff));
        } else if (buff[0] == '3') {
            bzero(buff, MAX);
            write(sockfd, "Option 3 not implemented.", sizeof(buff));
        }

         else {
            bzero(buff, MAX);
            // copy server message in the buffer
            buff[0] = 'f';
            buff[1] = 'a';
            buff[2] = 'i';
            buff[3] = 'l';

            // and send that buffer to client
            write(sockfd, buff, sizeof(buff));
            break;
        }
    }
}

// Driver function
int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
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
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);

    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("server acccept failed...\n");
        exit(0);
    }
    else
        printf("server acccept the client...\n");

    // Function for chatting between client and server
    func(connfd);

    // After chatting close the socket
    close(sockfd);
}
