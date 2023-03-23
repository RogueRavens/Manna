#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<winsock.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define MYPORT 3490    // the port users will be connecting to

int main(int argc, char *argv[])
{
    int sockfd, numbytes;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];

    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed.\n");
        exit(1);
    }

    if (argc < 3) {
        fprintf(stderr,"usage %s hostname port\n", argv[0]);
        exit(0);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        perror("ERROR opening socket");

    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        perror("ERROR connecting");

    printf("Please enter your nickname: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    buffer[strlen(buffer)-1] = '\0';
    sprintf(buffer, "NICK %s\r\n", buffer);
    n = send(sockfd, buffer, strlen(buffer), 0);

    printf("Please enter your username: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    buffer[strlen(buffer)-1] = '\0';
    sprintf(buffer, "USER %s 0 0 :%s\r\n", buffer, buffer);
    n = send(sockfd, buffer, strlen(buffer), 0);

    printf("Please enter the channel name: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    buffer[strlen(buffer)-1] = '\0';
    sprintf(buffer, "JOIN #%s\r\n", buffer);
    n = send(sockfd, buffer, strlen(buffer),
}

//Send file over the existing TCP connection
void send_file(int sockfd, char* filename) {
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Failed to open file\n");
        return;
    }

    char buffer[MAX_BUFFER_SIZE];
    int bytes_read = 0;

    while ((bytes_read = fread(buffer, sizeof(char), MAX_BUFFER_SIZE, fp)) > 0) {
        if (send(sockfd, buffer, bytes_read, 0) != bytes_read) {
            printf("Error sending file\n");
            break;
        }
    }

    fclose(fp);
}

// Receive file over the existing TCP connection
void receive_file(int sockfd, char* filename, int file_size) {
    FILE* fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("Failed to open file\n");
        return;
    }

    char buffer[MAX_BUFFER_SIZE];
    int bytes_received = 0;

    while (file_size > 0) {
        int bytes_to_receive = (file_size < MAX_BUFFER_SIZE) ? file_size : MAX_BUFFER_SIZE;
        bytes_received = recv(sockfd, buffer, bytes_to_receive, 0);

        if (bytes_received <= 0) {
            printf("Error receiving file\n");
            break;
        }

        fwrite(buffer, sizeof(char), bytes_received, fp);
        file_size -= bytes_received;
    }

    fclose(fp);
}

void handle_file_transfer_acknowledgment(int sockfd, MessageHeader* header) {
    char* filename = "file.txt";

    // Get file size from server
    int file_size;
    recv(sockfd, &file_size, sizeof(int), 0);

    // Receive file
    receive_file(sockfd, filename, file_size);
}

void handle_file_transfer_acknowledgment(int sockfd, MessageHeader* header) {
    char* filename = "file.txt";

    // Get file size from server
    int file_size;
    recv(sockfd, &file_size, sizeof(int), 0);

    // Receive file
    receive_file(sockfd, filename, file_size);

}
  return 0;
}
    