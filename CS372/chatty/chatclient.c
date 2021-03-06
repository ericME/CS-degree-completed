/*
** Eric Rouse
** Project #1
** CHATCLIENT.C
** base heavily on "client.c -- a stream socket client demo"
** from beej.us
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <arpa/inet.h>


#define MAXDATASIZE 500 // max number of bytes we can get at once 
#define MAXHANDLE 10    // maximum size of user chat handle

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[])
{
    int sockfd, numbytes; 
    char * quitmsg = "tiuq\\";
    int quitcmd = 1; 
    char buf[MAXDATASIZE];
    char msg[MAXDATASIZE];
    char get_input[MAXDATASIZE - MAXHANDLE - 1];
    char handle[MAXHANDLE + 1];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int i;
    char s[INET6_ADDRSTRLEN];

    if (argc != 3) {
        fprintf(stderr,"usage: chatclient hostname port\n");

        exit(1);
    }


    //get handle
    printf("What handle would you like to be known as?\n");
    fgets(handle, MAXHANDLE, stdin);
    handle[strlen(handle)+1] = '\0';
    handle[strlen(handle)] = '\0';
    handle[strlen(handle)-1] = '>';
    handle[strlen(handle)] = ' ';

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(argv[1], argv[2], &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("client: connect");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
            s, sizeof s);
    printf("client: connecting to %s\n", s);

    freeaddrinfo(servinfo); // all done with this structure

    for(;;){

        if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
            perror("recv");
            exit(1);
        }

        buf[numbytes] = '\0';
        
        quitcmd = 1;
        for(i = 0; i < strlen(quitmsg); i++){
            //printf("%c, %c, %s\n", buf[numbytes-2-i], quitmsg[i], buf);//debug
            if (buf[numbytes-2-i] != quitmsg[i]){
                quitcmd = 0;
                break;
            }

        }

        if(quitcmd != 0){
            printf("BOOTED FROM SERVER\n");
            return 0;
        }
        printf("%s", buf);

        printf("%s ", handle);
        fgets(get_input, MAXDATASIZE, stdin);

        if(strcmp(get_input, "\\quit\n") == 0){
            printf("GOODBYE\n");
            return 0;
        }
        else{
            strcpy(msg, handle);
            strcat(msg, get_input);
            send(sockfd, msg, strlen(msg), 0);
        }
    }

    close(sockfd);

    return 0;
}
