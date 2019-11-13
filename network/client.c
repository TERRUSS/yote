#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
  
#define PORT     8080 
#define MAXLINE 1024 
  

char *inputString(FILE* fp, size_t size);


// Driver code 
int main() { 
	int sockfd; 
	char buffer[MAXLINE]; 
	char *data; 
	struct sockaddr_in     servaddr; 
  
	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 
  
	memset(&servaddr, 0, sizeof(servaddr)); 
	  
	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	  
	int n, len;

	printf("input string : ");
  data = inputString(stdin, 10);
	  
	sendto(sockfd, (const char *)data, strlen(data), 
		MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
			sizeof(servaddr)); 
	printf("Hello message sent.\n"); 
		  
	n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
				MSG_WAITALL, (struct sockaddr *) &servaddr, 
				&len); 
	buffer[n] = '\0'; 
	printf("Server : %s\n", buffer); 
  
	free(data);
	close(sockfd); 
	return 0; 
} 

char *inputString(FILE* fp, size_t size){
//The size is extended by the input with the value of the provisional
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(char)*size);//size is start size
    if(!str)return str;
    while(EOF!=(ch=fgetc(fp)) && ch != '\n'){
        str[len++]=ch;
        if(len==size){
            str = realloc(str, sizeof(char)*(size+=16));
            if(!str)return str;
        }
    }
    str[len++]='\0';

    return realloc(str, sizeof(char)*len);
}