# QurnavaGPT.Website `Beta`
## Introduction
A web server is a software application that listens for incoming HTTP requests from clients and responds with HTTP responses. In this guide, we will learn how to build a simple web server in C for Windows, and how to modify it to serve multiple HTML pages.
## Prerequisites

To follow this guide, you will need the following:

- A Windows machine
- A C compiler for Windows (such as MinGW or Visual Studio)
- Basic knowledge of the C programming language

## Building the Web Server

**To build the web server, follow these steps:**

1. Create a new C file with your preferred text editor (such as Notepad or Visual Studio Code).
2. Copy and paste the code for the C web server (which you can find in other parts of this conversation) into the file.
3. Save the file with a .c extension (such as "web-server.c").
4. Open a command prompt or terminal window.
5. Compile the C file using the C compiler. For example, if you are using MinGW, you can run the following command
```bash 
gcc -o web-server web-server.c -lws2_32 
```
This will compile the C file into an executable named "web-server.exe". The "-lws2_32" flag links the program to the Winsock library, which is required for network programming on Windows.
6. Run the executable by double-clicking it or running it from the command line. By default, the web server will listen on port 8080.
Modifying the Web Server
## To modify the web server to serve multiple HTML pages, follow these steps:
7. Add a new HTML file to the same directory as the C file. For example, you can create a file named "new_page.html".
8. Modify the C code to check for requests for the new HTML page. For example, you can add the following code to the while loop that listens for incoming requests:
```c
if (strncmp(recvBuffer, "GET /new_page", 13) == 0)
{
    fp = fopen("new_page.html", "r");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        closesocket(listenSocket);
        WSACleanup();
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
```
This code checks if the incoming request is for the "/new_page" path, and if so, sends the contents of the "new_page.html" file as the response.
9. Save the modified C file and recompile it using the C compiler.
10. Run the modified executable by double-clicking it or running it from the command line.

You can modify the C code further to serve additional HTML pages, or to customize the response for different paths or HTTP methods.
