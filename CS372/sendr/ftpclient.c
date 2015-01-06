/*
** Eric Rouse
** Project #2
** FTPCLIENT.C
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
#include <sys/stat.h> 
#include <fcntl.h>

#include <arpa/inet.h>


#define MAXDATASIZE 500 // max number of bytes we can get at once 

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void usage(){
    
    fprintf(stderr,"usage 1: chatclient hostname port -l port\n");
    fprintf(stderr,"usage 2: ftpclient hostname port -g filename port\n");

    exit(1);
}
//based heavily on http://www.linuxhowtos.org/data/6/server.c
void data(int fd, int portno)
{
    int sockfd, newsockfd;
    socklen_t clilen;
    char buff[MAXDATASIZE];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){ 
    perror("ERROR opening socket");
    exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
          sizeof(serv_addr)) < 0){
        perror("ERROR on binding");
        exit(0);
    }
    listen(sockfd,10);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0){
        perror("ERROR on accept");
        exit(0);
    }
    bzero(buff,MAXDATASIZE);


    for(;;){

        n = read(newsockfd,buff,MAXDATASIZE);
        if (n < 0){
            perror("ERROR reading from socket");
            exit(0);
        }else if (n == 0){
            break;
        }else
            write(fd, buff, n);
    }

    close(newsockfd);
    close(sockfd);
    printf("\nclient: data connection closed\n");
    return; 
}

int main(int argc, char *argv[])
{
    int sockfd, numbytes; 
    char * serverhandle = "::server>";
    int servermsg = 1; 
    char buf[MAXDATASIZE];
    char msg[MAXDATASIZE];
    char get_input[MAXDATASIZE - 1];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int i;
    char s[INET6_ADDRSTRLEN];
    char lst_msg[6];
    char get_msg[6];
    int newmsg = 0;
    int fd = -1;
    int dataport;

    strcpy(lst_msg, "-l\n\0");
    strcpy(get_msg, "-g ");

    if (argc == 5) {
        if (strcmp(argv[3],"-l") != 0) usage();
        strcpy(msg, lst_msg);
        newmsg = 1;
    }
    else if (argc == 6) {
        if (strcmp(argv[3],"-g") != 0) usage();
        strcpy(msg, get_msg);
        strcat(msg, argv[4]);
        strcat(msg, " ");
        strcat(msg, argv[5]);
        char path[255];
        strcpy(path,"./");
        strcat(path, argv[4]);
        strcat(path, ".copy");
        dataport = atoi(argv[5]);
        if (dataport < 10000 || dataport > 65535){
            perror("invalid data port specified");
            exit(0);
        }

        newmsg = 2;
        fd = open(path, O_RDWR | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH);
        if (fd == -1){
            perror("duplicate filename detected");
            exit(0);
        }
    }
    else {
        usage();
    }


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

    int wait = 0;
    for(;;){


        if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
            perror("recv");
            exit(1);
        }

        buf[numbytes] = '\0';
        
        servermsg = 1;
        for(i = 0; i < strlen(serverhandle); i++){
            //printf("%c, %c, %s\n", buf[numbytes-2-i], serverhandle[i], buf);//debug
            if (buf[i] != serverhandle[i]){
                servermsg = 0;
                break;
            }

        }

        if (numbytes > 0){
            if (!servermsg){
                data(fd, dataport);
                wait = 1;
            }else{
                printf("%s", buf);
                wait = 0;
            }
        }
        if (newmsg){
            send(sockfd, msg, strlen(msg), 0);
            newmsg = 0;
        }else if (wait == 0){
            printf("\n*\t*\t*that's all folks!*\t*\t*\n");
            break;
        }
    }
    close(fd);
    close(sockfd);

    return 0;
}
