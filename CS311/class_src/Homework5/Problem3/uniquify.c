/*
#
#   Name:           Eric Rouse
#   Email Address:  rousee@onid.orst.edu
#   Class Name:     CS311-400
#   Assignment:     Homework #5
#
*/

#include "functions.h"
/* signal handler for SIGINT */
void sigi_handler(int sig)
{
    while (wait(NULL) > 0 );
    exit(EXIT_FAILURE);
}
int main (int argc, char **argv)
{
        /* init vars */
    char opt;
    int numforks = 1;
    int msqid;
    int c;
    int i = 0;
    int j = 0;
    int bucket = 0;
    int found_word = 0;
    int msgLen;
    int msgTypes[MAXFORKS+1];
    int EOM = 0;
    char s[MXSTRGLEN];
    char t[MXSTRGLEN];
    struct linkedList * master;
    struct linkedList * childlist[MAXFORKS+1];
    struct mbuf m_toChild;
    struct mbuf m_toParent;
    /* sigaction for SIGINT  */
    struct sigaction si;
    struct sigaction ti;
    /* set up signal handling SIGINT  */
    si.sa_handler = sigi_handler;
    sigemptyset(&si.sa_mask);
    si.sa_flags = 0;
    /* initialize the actions */
    sigaction(SIGINT, &si, &ti);
    /*
       use getopt to parse command line options
       pull in the options from the command line
       convert the numbers to longs using strtol
       acceptable options:
       -n: number of sort forks to create
    */
    while ((opt = getopt (argc,argv,"n:"))!= -1)
        switch (opt){
            case 'n':
                numforks = (int)strtol(argv[optind-1], (char**)NULL, 10);
                break;
            case '?':
                printf("******error******\n");
            default:
                printf("bad input detected\n");
                exit(EXIT_FAILURE);
        }
    
    /*generate a message queue*/
    msqid = msgget(IPC_PRIVATE, S_IRUSR | S_IWUSR);
    

    /*make sure numforks is valid*/
    if (numforks > MAXFORKS) numforks = MAXFORKS;
    else if (numforks < 1) numforks = 1;
    /*bucketize messages into MAXFORKS/numforks buckets
    (most efficient for when MAXFORKS % numforks = 0*/
    bucket = 1;
    for (i = 1; i <= MAXFORKS; i++){
        msgTypes[i] = bucket;
        if (i % ((MAXFORKS ) / numforks) == 0 && bucket < numforks) bucket++;
    }
    /*fork and exec the spec'd no. of times*/
    for (i = 1; i <= numforks; i++){
        switch(fork()){
            case -1:
                perror("fork");
                exit(EXIT_FAILURE);
            case 0:

                /*init linked list for this child*/
                childlist[i]= createLinkedList();
                /*recieve messages until EOM sent*/
                while(!EOM){
                    msgrcv(msqid, &m_toChild, MXSTRGLEN, i, 0);
                    memcpy(t, m_toChild.mtext, MXSTRGLEN);
                    if(strcmp(t,"<EOM>\0") == 0){
                        EOM = 1;
                    }
                    else{
                    /*add received message to list*/
                        addSorted(childlist[i], t);
                    }
                }
                /*send linked list as a message*/
                /*printList(childlist[i]);*/
                sendList(childlist[i], i, msqid, &m_toParent);
                strcpy(m_toParent.mtext,"<EOM>\0");
                m_toParent.mtype = i;
                msgsnd(msqid, &m_toParent, MXSTRGLEN,0);
                /*printList(childlist[i]);*/

                exit(EXIT_SUCCESS);
            default:
                break;

        }
    }
    master = createLinkedList();
    /*parse the text, send it to sort processes*/
    i = 0;
    while ((c =fgetc(stdin)) != EOF )
    {
        /*if it's an alpha, convert it to lower case*/
        if (isalpha(c))
        {
            found_word = 1;
            c = tolower(c);
            /*fputc(c, stdout);*/
            s[j] = c;
            j++;
        }
        else if (found_word) {
            /*fputc('\n', stdout);*/
            s[j] = '\0';
            msgLen = j+1;
            memcpy(m_toChild.mtext, s, msgLen);
            j=0;
            i=0;
            found_word=0;
            m_toChild.mtype = msgTypify(s[0],msgTypes);
            /*addSorted(master, s);*/
            if (msgsnd(msqid, &m_toChild, msgLen, 0) == -1){
                perror("msgsnd");
                exit(EXIT_FAILURE);
            }
        }
    }
    /*send the sort processes the End Of Message*/
    memcpy(m_toChild.mtext, "<EOM>\0", sizeof("<EOM>\0"));
    for (i = 1; i <= numforks; i++){
        m_toChild.mtype = i;
        if (msgsnd(msqid, &m_toChild, msgLen, 0) == -1){
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }
    }

    /*combine*/


    EOM = 0;
    while(EOM < numforks){
        msgrcv(msqid, &m_toParent, MXSTRGLEN, 0, 0);
        strcpy(s, m_toParent.mtext);
        if(strcmp(s,"<EOM>\0")==0) EOM++;
        else addBackList(master, s);
    }

    printList(master);

    /*kill the queue*/
    msgctl(msqid, IPC_RMID, NULL);

    /*wait for children to finish*/
    while (numforks > 1){
        wait(NULL);
        --numforks;
    }
    


    exit(EXIT_SUCCESS);
}