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
        printf("From client: %s\t To client : ", buff);

        n = 0;
        if (strcmp("0", buff) == 0) {
            printf("Server Exit...\n");
            break;
        } else if (strcmp("1", buff) == 0) {
            printf("Load...\n");
            bzero(buff, MAX);
            for(int k = 0; k < 3; k++){
                char numberAsString[100];
                sprintf(numberAsString, "%d", arr[k]);
                strcat(buff, numberAsString);
                strcat(); // not ready!!!
            }
            write(sockfd, buff, sizeof(buff));
        } else if (strcmp("2", buff) == 0) {
            printf("Server Exit...\n");
            break;
        } else if (strcmp("3", buff) == 0) {
            printf("Server Exit...\n");
            break;
        }

         else {
            bzero(buff, MAX);
            // copy server message in the buffer
            buff[0] = 'f';
            buff[1] = 'a';
            buff[2] = 'i';
            buff[3] = 'l';
            buff[4] = '\0';

            // and send that buffer to client
            write(sockfd, buff, sizeof(buff));
            break;
        }
    }
}

// Driver function
int main()
{
    puts("Testing linked list");
    puts("Testing Reading from file");
    return 0;
}
