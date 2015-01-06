/*
** Eric Rouse
** Project #1
** FTPSERVE.CPP
** base heavily on:
** selectserver.c -- a cheezy multiperson chat server
** from beej.us
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>


using namespace std;


#define MAXDATASIZE 500 // max number of bytes we can get at once 
#define MAXHANDLE 10    // maximum size of user chat handle
#define PORTNAMELEN 5   // length of a port number/name


/*
from a linuxquestions forum post by jtshaw
http://www.linuxquestions.org/questions/programming-9/c-list-files-in-directory-379323/
*/
int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

//based heavily on http://www.linuxhowtos.org/data/6/client.c
int data(int fd, int portno)
{
    int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char hostname[1024];

    
    printf("trying to establish connection\n");
    sleep(1);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){ 
        perror("ERROR opening socket");
        close(sockfd);
        send(sockfd, NULL, 0, 0);
        return -1;
    }
    
    hostname[1023]='\0';
    gethostname(hostname, 1023);
    server = gethostbyname(hostname);
    printf("connecting to: %s\n", hostname);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        close(sockfd);
        send(sockfd, NULL, 0, 0);
        return -1;
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){ 
        perror("ERROR connecting");
        close(sockfd);
        send(sockfd, NULL, 0, 0);
        return -1;
    }

    uint8_t buff[MAXDATASIZE];
    int actually_read;
    do{
        actually_read = read(fd, buff, sizeof(buff));
        printf("%s\n\n\tbytes sent:\t%i\n\n", buff, actually_read);
        send(sockfd, buff, actually_read, 0);
        bzero(buff, MAXDATASIZE);
    } while(actually_read > 0);


    
    close(sockfd);
    return 88;
}

int main(int argc, char * argv[])
{
    fd_set master;    // master file descriptor list
    fd_set read_fds;  // temp file descriptor list for select()
    int fdmax;        // maximum file descriptor number
    int listener;     // listening socket descriptor
    int newfd;        // newly accept()ed socket descriptor
    struct sockaddr_storage remoteaddr; // client address
    socklen_t addrlen;

    char buf[256];    // buffer for client data
    int nbytes;
    int nclients = 0;

	char remoteIP[INET6_ADDRSTRLEN];

    int sendfilecommand = 0;
    int fd = -1;

    int yes=1;        // for setsockopt() SO_REUSEADDR, below
    int i, j, rv;
    char lst_msg[6];
    char get_msg[6];

	struct addrinfo hints, *ai, *p;

    struct stat s;
    
    //char get_input[MAXDATASIZE - MAXHANDLE - 1];
    char msg[MAXDATASIZE];
    char handle[MAXHANDLE + 1];
    string dir = string(".");

    char file_name[255];
    int dataport;
    

    strcpy(handle, "::server> \0");
    strcpy(lst_msg, "-l\n\0");
    strcpy(get_msg, "-g ");
    

    FD_ZERO(&master);    // clear the master and temp sets
    FD_ZERO(&read_fds);

    if (argc != 2) {
        fprintf(stderr,"usage: ftpserve port\n");

        exit(1);
    }



	// get us a socket and bind it
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	if ((rv = getaddrinfo(NULL, argv[1], &hints, &ai)) != 0) {
		fprintf(stderr, "selectserver: %s\n", gai_strerror(rv));
		exit(1);
	}
	
	for(p = ai; p != NULL; p = p->ai_next) {
    	listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (listener < 0) { 
			continue;
		}
		
		// lose the pesky "address already in use" error message
		setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

		if (bind(listener, p->ai_addr, p->ai_addrlen) < 0) {
			close(listener);
			continue;
		}

		break;
	}

	// if we got here, it means we didn't get bound
	if (p == NULL) {
		fprintf(stderr, "selectserver: failed to bind\n");
		exit(2);
	}

	freeaddrinfo(ai); // all done with this

    // listen
    if (listen(listener, 10) == -1) {
        perror("listen");
        exit(3);
    }

    // add the listener to the master set
    FD_SET(listener, &master);

    // keep track of the biggest file descriptor
    fdmax = listener; // so far, it's this one

    // main loop
    for(;;) {
        read_fds = master; // copy it
        if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(4);
        }

        // run through the existing connections looking for data to read
        for(i = 0; i <= fdmax; i++) {
            if (FD_ISSET(i, &read_fds)) { // we got one!!
                if (i == listener) {
                    // handle new connections
                    addrlen = sizeof remoteaddr;
					newfd = accept(listener,
						(struct sockaddr *)&remoteaddr,
						&addrlen);

					if (newfd == -1) {
                        perror("accept");
                    } else {
                        FD_SET(newfd, &master); // add to master set
                        if (newfd > fdmax) {    // keep track of the max
                            fdmax = newfd;
                        }
                        printf("selectserver: new connection from %s on "
                            "socket %d\n",
							inet_ntop(remoteaddr.ss_family,
								get_in_addr((struct sockaddr*)&remoteaddr),
								remoteIP, INET6_ADDRSTRLEN),
							newfd);
                        strcpy(msg, handle);
                        strcat(msg, "Connected!\n");
                        send(newfd, msg, strlen(msg), 0);
                        nclients++;
                    }
                } else {
                    // handle data from a client
                    if ((nbytes = recv(i, buf, sizeof buf, 0)) <= 0) {
                        // got error or connection closed by client
                        if (nbytes == 0) {
                            // connection closed
                            printf("selectserver: socket %d hung up\n", i);
                        } else {
                            perror("recv");
                        }
                        close(i); // bye!
                        FD_CLR(i, &master); // remove from master set
                        nclients--;
                    } else {
                        buf[nbytes] = '\0';

                        printf("%s", buf);

                        strcpy(msg, handle);
                        strcat(msg, "Ready!\n");
                        //listen for the list command
                        if (strcmp(buf, lst_msg) == 0){
                            vector<string> files = vector<string>();
                            getdir(dir,files);
                            strcpy(msg, handle);
                            strcat(msg, "File listing: \n");
                            for (unsigned int k = 0;k < files.size();k++) {
                                string t(files[k].begin(), files[k].end());
                                strcat(msg, &t[0]);
                                strcat(msg, "\n");
                            }
                        }
                        else{
                            //listen for the get file command
                            int getcmd = 1;
                            for(i = 0; i < strlen(get_msg); i++){
                                if (buf[i] != get_msg[i]){
                                    getcmd = 0;
                                    break;
                                }

                            }

                            if(getcmd == 0){
                                strcpy(msg, handle);
                                strcat(msg, "DIDN'T UNDERSTAND INPUT\n\0");
                                printf("%s", msg);
                            }
                            //if we are getting a file, read the file name and check that it exists
                            else{
                                
                                strcpy(file_name, &buf[strlen(get_msg)]);
                                int portstart = strlen(file_name) - PORTNAMELEN;
                                printf ("filename: %s  \tport:%s", file_name, &file_name[portstart]);
                                dataport = atoi(&file_name[portstart]);
                                file_name[portstart-1] = '\0';

                                printf("\nfile: %s\n", file_name);
                                printf("\nport: %i\n", dataport);
                                fd = open(file_name, O_RDONLY);
                                
                                /*blatant errors check*/
                                if(fd == -1){
                                    strcpy(msg, handle);
                                    strcat(msg, "No such file.\n\0");
                                    printf("%s: No such file\n", file_name);
                                    close(fd);
                                }
                                // if it exists, let's use it.
                                else{
                                    fstat(fd, &s);
                                    sendfilecommand=1;
                                }

                            }
                        }

                        if (nclients == 1){//one client wants to talk to server
                            //send a msg to all
                            //printf("%s", handle);
                            //fgets(get_input, MAXDATASIZE - MAXHANDLE - 1, stdin);
                            for(j = 0; j <= fdmax; j++) {
                                // send to everyone!
                                if (FD_ISSET(j, &master)) {
                                    // except the listener
                                    if (j != listener && sendfilecommand == 0) {
                                        printf("%s", msg);

                                        if (send(j, msg, strlen(msg), 0) == -1) {
                                            perror("send");
                                        }
                                    }
                                    if (j != listener && sendfilecommand == 1) {
                                        sendfilecommand = 0;
                                        printf("sending file, %ld bytes\n", (long)s.st_size);

                                        send(newfd, "data start\0", strlen("data start\0"), 0);

                                        if (data(fd, dataport) < 0){
                                            strcpy(msg, handle);
                                            strcat(msg, "Data Connection Error.");
                                            send(newfd, msg, strlen(msg), 0);
                                            exit(88);
                                        }

                                        close(fd);
                                        strcpy(msg, handle);
                                        strcat(msg, "Transmission complete, sent File: ");
                                        strcat(msg, file_name);
                                        strcat(msg, ".\nNow terminating connection.");
                                        send(newfd, msg, strlen(msg), 0);
                                    }
                                }
                            }
                        }
                    }
                } // END handle data from client
            } // END got new incoming connection
        } // END looping through file descriptors
    } // END for(;;)--and you thought it would never end!
    
    return 0;
}
