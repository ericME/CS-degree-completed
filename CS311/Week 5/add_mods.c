/*
#
#   Name:           Eric Rouse
#   Email Address:	rousee@onid.orst.edu
#   Class Name:		CS311-400
#   Assignment:		Homework #4
#
*/

#include "functions.h"
/*  add_mods, -w, add modified files
    !!!<NOTE>!!!
    this function will add any files in the current directory to the archive if they are modified
    between the time the function is invoked and the given timeout
    it only updates at 1 second intervals so as to avoid overduplication
    so a file saved 12 times in a second will only see the 12th update append.
    !!!</NOTE>!!!
    expects:
        timeout = seconds to try and add modified files
        archive_name = the name (and path) of the archive we are appending to
    
    returns:
        nothing, the archive is appended to
    directory searching based heavily on code from stack overflow
    http://stackoverflow.com/questions/4204666/how-to-list-files-in-a-directory-in-a-c-program
*/
void add_mods(int timeout, char * archive_name){
    /*vars*/
    int i;
    long epoch_secs;
    long start_secs;
    long now_secs;
    char * name[1];
    char title_name[TITLELEN];
    char title_time[12];
    int temp_fd = is_archive(archive_name);
    time_t t;
    struct timespec ts;
    DIR           *d;
    struct dirent *dir;
    
    /*blatant errors check - temp_fd is checked as an archive above, close it out*/
    close(temp_fd);
    /*meat and potatoes*/
    /*record start time*/
    start_secs = time(&t);
    now_secs = start_secs;
    /*set up the time struct for .95 second intervals*/
    ts.tv_sec = 0;
    ts.tv_nsec = 950000000;
    /*open the directory we are in, if it opens, cycle through it*/
    d = opendir(".");
    if (d)
    {
        /*while we are timeing keep cycling through the directory*/
        while(now_secs <= start_secs + timeout)
        {
            
            d = opendir(".");
            /* directory cycling, read the directory until the end, or we reach timeout*/
            while ((dir = readdir(d)) != NULL && now_secs <= start_secs + timeout)
                {
                    /*if the file is a regular file and it isn't the archive, append it to our archive*/
                    if (dir->d_type == DT_REG && strcmp(dir->d_name, archive_name) != 0)
                    {
                        name[0] = dir->d_name;
                        title(name[0], title_name);
                        /*search the title for the modified time stamp convert it to a long int*/
                        for(i = 0; i < 12 ; i++) title_time[i] = title_name[16+i];
                        epoch_secs = strtol(title_time, (char**)NULL, 10);
                        /*see if that timestamp was created in the last second befor now up to the timeout*/
                        if(epoch_secs >= now_secs - 1 && epoch_secs <= start_secs + timeout){
                            printf("%s\n", name[0]);
                            quick_add(1, 0, name, archive_name);
                            nanosleep(&ts,0);
                        }


                    }
                    now_secs = time(&t);
                }

            closedir(d);
            now_secs = time(&t);
        }
    }
    return;
}


