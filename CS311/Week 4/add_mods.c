/*
#
#   Name: 			Eric Rouse
#   Email Address:	rousee@onid.orst.edu
#   Class Name:		CS311-400
#   Assignment:		Homework #4
#
*/

#include "functions.h"
/*  add_mods, -w, add modified files
    expects:
        timeout = seconds to try and add modified files
        archive_name = the name (and path) of the archive we are appending to
    
    returns:
        nothing, the archive is appended to
*/
void add_mods(int timeout, char * archive_name){
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

