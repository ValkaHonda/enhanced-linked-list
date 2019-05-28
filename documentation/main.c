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
//Linked list:
struct node{
    int number;
    struct node* next;
};
struct node* pushBack (struct node* head, int value) {
    if (head == NULL) {
        head = (struct node*) malloc (sizeof(struct node));
        head->number = value;

        return head;
    }
    struct node* newElement = (struct node*) malloc (sizeof(struct node));
    newElement->number = value;
    newElement->next = NULL;
    struct node* currentElement = head;
    while (currentElement->next != NULL) {
        currentElement = currentElement->next;
    }
    currentElement->next = newElement;
    return head;
}

int main()
{
    puts("Testing split of a string:");
    char str[] = "strtok needs to be called several times to split a string";
	int init_size = strlen(str);
	char delim[] = " ";

	char *ptr = strtok(str, delim);

	while (ptr != NULL)
	{
		printf("'%s'\n", ptr);
		ptr = strtok(NULL, delim);
	}
    puts("After spliting:");
    printf("%s\n****************************\n", str);

    puts("Testing linked list:");
    struct node* head = NULL;
    head = pushBack(head, 10);
    head =  pushBack(head, 20);
    head = pushBack(head, 30);
    printf("The value is == %d\n", head->number);
    printf("The value is == %d\n", head->next->number);
    printf("The value is == %d\n", head->next->next->number);
    if (head->next->next->next == NULL) {
        puts("This is the end of the linked list.");
    }
    puts("*********************************");

    puts("Testing writing to binary file:");
    FILE *outfile;
    outfile = fopen ("numbers", "wb");
    if (outfile == NULL)
    {
        fprintf(stderr, "\nError opend file\n");
        exit (1);
    }
    if (fwrite (&head, sizeof(struct node), 1, outfile) == 0){
        printf("error writing file !\n");
    }
    fclose (outfile);
    puts("*********************************");

    puts("Testing reading from binary file.");
    FILE *inputFile;
    inputFile = fopen("numbers", "rb");
    if(inputFile == NULL){
        fprintf(stderr, "\nError opend file\n");
        exit (1);
    }

    struct node* inputNodeHead;
    if(fread(&inputNodeHead, sizeof(struct node), 1, inputFile) == 0){
        printf("error writing file !\n");
    }
    fclose(inputFile);
    if(inputNodeHead != NULL){
        printf("successfully read!\n" );
        printf("%d\n", inputNodeHead->number);
    }

    return 0;
}
