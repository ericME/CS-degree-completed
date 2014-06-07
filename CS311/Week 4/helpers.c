/*
#
#   Name: 			Eric Rouse
#   Email Address:	rousee@onid.orst.edu
#   Class Name:		CS311-400
#   Assignment:		Homework #4
#
*/

#include "functions.h"


/*  is_archive, checks a file for existance, then if it is an archive
    expects:
        archive_name = the name (and path) of the archive we are creating
    
    returns:
        file descritor for file exist and is an archive.
        0 for all else.
*/
int is_archive(char * archive_name){
    /*vars*/
    char buf[7];
    int fd = open(archive_name, O_RDONLY);

    /*blatant errors check*/
    if(fd == -1){
        printf("./myar: %s: No such file or directory\n", archive_name);
        close(fd);
        exit(EXIT_FAILURE);
    }
    read(fd, buf, 7);
    if (strcmp(buf, "!<arch>") != 0){
        printf("./myar: %s: File format not recognized\n", archive_name);
        close(fd);
        exit(EXIT_FAILURE);
    }
    /*  if we made it through the errors, it is an archive.
        pass the file descriptor please */
    return fd;
}

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
void itoa(int i, char b[BUFFERMAX], int base){
    char const digit[] = "0123456789";
    char* p = b;
    int shifter;
    if(i<0){
        *p++ = '-';
        i = -1;
    }
    shifter = i;
    do{
        ++p;
        shifter = shifter/base;
    }while(shifter);
    *p = '\0';
    do{
        *--p = digit[i%base];
        i = i/base;
    }while(i);
}
/*  title, creates a title for a file using stat and file name
    expects:
        archive_name = the name (and path) of the file we are archiving
        title_name = the name of the title to output

    returns:
        string that is an appropriately formated title
        offset  length  description                 type
        0	    16	    File name	                ASCII
        16	    12	    File modification timestamp	Decimal
        28	    6	    Owner ID	                Decimal
        34	    6	    Group ID	                Decimal
        40	    8	    File mode               	Octal
        48	    10	    File size in bytes	        Decimal
        58	    2       File magic	                0x60 0x0A
        EXAMPLE: 1-s.txt/        1366003473  500   500   100644  41        `
*/
void title (char * file_name, char title_name[TITLELEN]){
    /*vars*/
    char time[BUFFERMAX];
    char uid[BUFFERMAX];
    char gid[BUFFERMAX];
    char mode[BUFFERMAX];
    char size[BUFFERMAX];
    char magic[] = "`\n";
    int i;
    int j;
    int slashed;
    int term;

    
    struct stat s;
    stat(file_name, &s); 
    /*blatant errors check*/
    /*debug print statements
    printf("stat results: %s, modified: %ld, UID: %i, GID: %i, mode: %lo, size: %ld\n",
                    file_name, (long)s.st_mtime, s.st_uid, s.st_gid, (unsigned long)s.st_mode, (long)s.st_size);
    printf("%i: %s\t%s\t%c\t%c\n", i, title_name, file_name, title_name[i], file_name[i-j]);
    printf("%s", title_name);
    */
    itoa(s.st_mtime, time, 10);
    itoa(s.st_uid, uid, 10);
    itoa(s.st_gid, gid, 10);
    itoa(s.st_mode, mode, 8);
    itoa(s.st_size, size, 10);
    
    slashed  = 0;
    term = 0;
    i = -1;
    while(i <= TITLELEN){
        i++;
        if (i < 0+16){
        /*file name*/
            /*offset*/
            j = 0;
            /*copy up to null termintator*/
            if (file_name[i - j] != '\0' && term == 0) title_name[i] = file_name[i - j];
            /*catch null termintator and finish with spaces/term chars*/
            else if (slashed == 0){
                title_name[i] = '/';
                slashed = 1;
                term = 1;
            }
            else title_name[i] = ' ';
        }else if (i < 16+12){
        /*file modified time stamp*/
            /*offset, reset terminator*/
            j = 16;
            if (i == j) term = 0;
             /*copy up to null termintator*/
            if (time[i - j] != '\0' && term == 0) title_name[i] = time[i - j];
            /*catch null termintator and finish with spaces/term chars*/
            else if(time[i - j] == '\0'){
                term = 1;
                title_name[i] = ' ';
            }else title_name[i] = ' ';
        }else if (i < 28+6){
        /*owner ID*/
            /*offset, reset terminator*/
            j = 28;
            if (i == j) term = 0;
             /*copy up to null termintator*/
            if (uid[i - j] != '\0' && term == 0) title_name[i] = uid[i - j];
            /*catch null termintator and finish with spaces/term chars*/
            else if(uid[i - j] == '\0'){
                term = 1;
                title_name[i] = ' ';
            }else title_name[i] = ' ';
        }else if (i < 34+6){
        /*group ID*/
            /*offset, reset terminator*/
            j = 34;
            if (i == j) term = 0;
             /*copy up to null termintator*/
            if (gid[i - j] != '\0' && term == 0) title_name[i] = gid[i - j];
            /*catch null termintator and finish with spaces/term chars*/
            else if(gid[i - j] == '\0'){
                term = 1;
                title_name[i] = ' ';
            }else title_name[i] = ' ';
        }else if (i < 40+8){
        /*file mode*/
            /*offset, reset terminator*/
            j = 40;
            if (i == j) term = 0;
             /*copy up to null termintator*/
            if (mode[i - j] != '\0' && term == 0) title_name[i] = mode[i - j];
            /*catch null termintator and finish with spaces/term chars*/
            else if(mode[i - j] == '\0'){
                term = 1;
                title_name[i] = ' ';
            }else title_name[i] = ' ';
        }else if (i < 48+10){
        /*file size in bytes*/
            /*offset, reset terminator*/
            j = 48;
            if (i == j) term = 0;
             /*copy up to null termintator*/
            if (size[i - j] != '\0' && term == 0) title_name[i] = size[i - j];
            /*catch null termintator and finish with spaces/term chars*/
            else if(size[i - j] == '\0'){
                term = 1;
                title_name[i] = ' ';
            }else title_name[i] = ' ';
        }else if (i < 58+2){
        /*file magic*/
            /*offset, reset terminator*/
            j = 58;
            if (i == j) term = 0;
             /*copy up to null termintator*/
            if (magic[i - j] != '\0' && term == 0) title_name[i] = magic[i - j];
            /*catch null termintator and finish with spaces/term chars*/
            else if(magic[i - j] == '\0'){
                term = 1;
                title_name[i] = ' ';
            }else title_name[i] = ' ';
        }
        
    }
    

}
/*  find_name, finds file names in an archive
    expects:
        file descriptor of an archive
            !!YOU HAVE TO MAKE SURE IT IS AN ARCHIVE!!
            !!YOU HAVE TO MAKE SURE lseek IS UPDATED TO THE CORRECT POSITION!!
        found_name = an initialized string of 16 bytes for file names to be passed back upon
    
    returns:
        byte of beginning of name, found_name is updated
*/
int find_name(int fd, char found_name[16], int start){
    /*vars*/
    int i;
    int size = BLOCKSIZE;
    char buf[BLOCKSIZE];
    int name_idx;
    int file_ptr;
    int file_end;
    int fnd_newline = 1;
    int fnd_slash = 0;
    /*find the end of the file*/
    file_end = lseek(fd, -1, SEEK_END);
    /*set the pointer to the beginning of the file*/
    file_ptr = lseek(fd, start, SEEK_SET);
    /*meat and potatoes*/
    fnd_newline = 0;
    fnd_slash = 0;
    name_idx = 0;
    while(file_ptr < file_end ){
        /*read the file, one byte at a time*/
        read(fd, buf, size);
        /*we found the file name!!!*/
        if (fnd_slash){
            return file_ptr-name_idx-1;   
        }
        /*check for newline*/
        if (buf[0] == '\n'){
            fnd_newline = 1;
            name_idx = 0;
            fnd_slash = 0;
        }
        /*check for slash*/
        if (buf[0] == '/' && fnd_newline){
            fnd_slash = 1;
        }
        /*if we found a newline and are still before the slash, record the name*/
        if (fnd_newline && !fnd_slash && name_idx <= sizeof(found_name) && buf[0] != '\n'){
            found_name[name_idx] = buf[0];
            name_idx++;
            
        }
        /*if we go past the index without finding the slash, we are not on a good line*/
        if (name_idx > sizeof(found_name)){
            name_idx = 0;
            fnd_newline = 0;
            for(i = 0; i < sizeof(found_name); i++) found_name[i] = '\0';
        } 
        /*increment to the next byte*/
        file_ptr = lseek(fd, 0, SEEK_CUR);
    }
    return file_ptr-name_idx-1;
}

