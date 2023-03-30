#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define DEFAULT_PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int listenSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    char recvBuffer[BUFFER_SIZE];
    socklen_t clientAddrLen = sizeof(clientAddr);
    ssize_t bytesReceived;
    char response[BUFFER_SIZE];
    FILE *fp;
    char htmlContent[BUFFER_SIZE];

    listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (listenSocket < 0) {
        printf("Error creating listen socket.\n");
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(DEFAULT_PORT);

    if (bind(listenSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        printf("Error binding listen socket.\n");
        close(listenSocket);
        return 1;
    }

    if (listen(listenSocket, SOMAXCONN) < 0) {
        printf("Error listening on socket.\n");
        close(listenSocket);
        return 1;
    }

    printf("Server listening on port %d.\n", DEFAULT_PORT);

    while (1) {
        clientSocket = accept(listenSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);

        if (clientSocket < 0) {
            printf("Error accepting client connection.\n");
            close(listenSocket);
            return 1;
        }

        bytesReceived = recv(clientSocket, recvBuffer, BUFFER_SIZE, 0);

        if (bytesReceived > 0) {
            printf("Received request:\n%s", recvBuffer);

            if (strncmp(recvBuffer, "GET /app", 8) == 0) {
                fp = fopen("app.html", "r");

                if (fp == NULL) {
                    printf("Error opening file.\n");
                    close(listenSocket);
                    return 1;
                }

                fgets(htmlContent, BUFFER_SIZE, fp);

                strcpy(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");

                strcat(response, htmlContent);

                while (fgets(htmlContent, BUFFER_SIZE, fp) != NULL) {
                    strcat(response, htmlContent);
                }

                send(clientSocket, response, strlen(response), 0);

                fclose(fp);
            } else if (strncmp(recvBuffer, "GET /error", 9) == 0) {
                fp = fopen("403.html", "r");

                if (fp == NULL) {
                    printf("Error opening file.\n");
                    close(listenSocket);
                    return 1;
                }

                fgets(htmlContent, BUFFER_SIZE, fp);

                strcpy(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");

                strcat(response, htmlContent);

                while (fgets(htmlContent, BUFFER_SIZE, fp) != NULL) {
                    strcat(response, htmlContent);
                }

                send(clientSocket, response, strlen(response), 0);

                fclose(fp);
            } else if (strncmp(recvBuffer, "GET /", 5) == 0) {
                fp = fopen("index.html", "r");

                if (fp == NULL) {
                    printf("Error opening file.\n");
                    close(listenSocket);
                    return 1;
                }

                fgets(htmlContent, BUFFER_SIZE, fp);

                strcpy(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");

                strcat(response, htmlContent);

                while (fgets(htmlContent, BUFFER_SIZE, fp) != NULL)
                {
                    strcat(response, htmlContent);
                }

                send(clientSocket, response, strlen(response), 0);

                fclose(fp);
            }
            else
            {
                strcpy(response, "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<html><body><h1>404 Not Found</h1></body></html>");

                send(clientSocket, response, strlen(response), 0);
            }
        }

        close(clientSocket);
    }

    close(listenSocket);

    return 0;
}
