#include <stdio.h>
#include <getopt.h>
#include <sys/utsname.h>
#include <time.h>
#include <sys/stat.h>

int main(int argc, char ** argv){
    char c;
    struct utsname uname_pointer;
    time_t time_raw_format;
    struct stat s;
    
    while ((c = getopt (argc,argv,"htf:"))!= -1)
        switch (c){
            case 'h':
                uname(&uname_pointer);
                printf("Hostname = %s \n", uname_pointer.nodename);
                break;
            case 't':
                time(&time_raw_format);
                printf("The current local time: %s", 
                ctime(&time_raw_format));
                break;
            case 'f':
                if (stat(optarg, &s) == 0) {
                    printf("size of file '%s' is %d bytes\n"
                    , optarg, (int) s.st_size);
                } else {
                    printf("file '%s' not found\n", optarg);
                }
                break;
            case '?':
                printf("******error******\n");
            default:
                printf("no input detected\n");
                break;
        }
                
    
    return 0;
}
