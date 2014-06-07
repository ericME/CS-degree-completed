/*
#
#   Name: 			Eric Rouse
#   Email Address:	rousee@onid.orst.edu
#   Class Name:		CS311-400
#   Assignment:		Homework #4
#
*/

#include "functions.h"
/*  append, -A, append regular files in the current directory
    expects:
        archive_name = the name (and path) of the archive we are appending to
        
    
    returns:
        nothing, the archive is appended
        
    directory searching based heavily on code from stack overflow
    http://stackoverflow.com/questions/4204666/how-to-list-files-in-a-directory-in-a-c-program
*/
void append(char * archive_name){
    /*vars*/
    char * name[1];
    int temp_fd = is_archive(archive_name);
    DIR           *d;
    struct dirent *dir;
    d = opendir(".");
    /*blatant errors check*/
    close(temp_fd);
    /*meat and potatoes*/
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
            {
                if (dir->d_type == DT_REG && strcmp(dir->d_name, archive_name) != 0)
                {
                    name[0] = dir->d_name;
                    printf("%s\n", name[0]);
                    quick_add(1, 0, name, archive_name);
                }
            }

        closedir(d);
    }
    return;
}
