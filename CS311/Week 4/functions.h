/*
#
#   Name: 			Eric Rouse
#   Email Address:	rousee@onid.orst.edu
#   Class Name:		CS311-400
#   Assignment:		Homework #4
#
*/

#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <dirent.h> 

#define BLOCKSIZE 1
#define BUFFERMAX 20
#define TITLELEN 60
/*  find_name, finds file names in an archive
    expects:
        file descriptor of an archive
            !!YOU HAVE TO MAKE SURE IT IS AN ARCHIVE!!
        found_name = an initialized string of 16 bytes for file names to be passed back upon
        start = place to start looking for the file
    
    returns:
        nothing, found_name is updated
*/
int find_name(int fd, char found_name[16], int start);
/*  itoa, converts an integer to a string
    leveraged from stackoverflow.com
    http://stackoverflow.com/questions/9655202/how-to-convert-integer-to-string-in-c
    
    expects:
        i, integer to conver
        b, buffer to store the string
        base, the base of the integer (10 for decimal, 8 for octal, etc)

    returns:
        converted string
*/
void itoa(int i, char b[BUFFERMAX], int base);
/*  title, creates a title for a file using stat and file name
    expects:
        archive_name = the name (and path) of the file we are archiving
    
    returns:
        string that is an appropriately formated title
*/
void title (char * file_name, char title_name[TITLELEN]);
/*  is_archive, checks a file for existance, then if it is an archive
    expects:
        archive_name = the name (and path) of the archive we are creating
    
    returns:
        file descritor for file exist and is an archive.
        0 for all else.
*/
int is_archive(char * archive_name);
/*  quick add, -q, quickly append named members
    expects:
        files_amount = number of files to add
        files_start = the starting indicy of the argv array, where the file names start
        files_name = the argv array, where the file names are stored
        archive_name = the name (and path) of the archive we are creating
    
    returns:
        nothing, the archive is created
*/
void quick_add(int files_amount, int files_start, char ** files_name, char * archive_name);
/*  extract, -x, extract named members
    expects:
        files_amount = number of files to extract (if zero, extract all)
        files_start = the starting indicy of the argv array, where the file names start
        files_name = the argv array, where the file names are stored
        archive_name = the name (and path) of the archive we are extracting from
    
    returns:
        nothing, the archive is extracted
*/
void extract(int files_amount, int files_start, char ** files_name, char * archive_name);
void toc(char * archive_name);


/*  proc_vtoc, vtoc helper function
    expects:
        vtoc unprocessed line
        0	16	File name	ASCII
        16	12	File modification timestamp	Decimal
        28	6	Owner ID	Decimal
        34	6	Group ID	Decimal
        40	8	File mode	Octal
        48	10	File size in bytes	Decimal
        58	2	File magic	0x60 0x0A

    
    returns:
        nothing, the vtoc processed line is printed
*/
void proc_vtoc(char * line);
/*  vtoc, -v, print verbose table of contents
    expects:
        archive_name = the name (and path) of the archive we are printing
    
    returns:
        nothing, the vtoc is printed
*/
void vtoc(char * archive_name);

/*  del, -d, delete named members
    expects:
        files_amount = number of files to delete (if zero, extract all)
        files_start = the starting indicy of the argv array, where the file names start
        files_name = the argv array, where the file names are stored
        archive_name = the name (and path) of the archive we are extracting from
    
    returns:
        nothing, the archive is deleted from
*/
void delete(int files_amount, int files_start, char ** files_name, char * archive_name);

/*  append, -A, append regular files in the current directory
    expects:
        archive_name = the name (and path) of the archive we are appending to
    
    returns:
        nothing, the archive is appended
*/
void append(char * archive_name);

/*  add_mods, -w, add modified files
    expects:
        timeout = seconds to try and add modified files
        archive_name = the name (and path) of the archive we are appending to
    
    returns:
        nothing, the archive is appended to
*/
void add_mods(int timeout, char * archive_name);
