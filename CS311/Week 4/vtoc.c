/*
#
#   Name: 			Eric Rouse
#   Email Address:	rousee@onid.orst.edu
#   Class Name:		CS311-400
#   Assignment:		Homework #4
#
*/

#include "functions.h"
/*  mode_vtoc, vtoc helper function
    expects:
        mode value
    
    returns:
        properly formatted mode string
*/
void mode_vtoc(char * mode, char * output){
    /*input mode iterator for parsing mode digits, 0 to 2*/
    int i;
    /*offset from iterator in output string*/
    int o = 0;
    for (i = 0; i < 3; i++){
        switch (mode[i]){
          case '7':
            output[o+0] = 'r';
            output[o+1] = 'w';
            output[o+2] = 'x';
            o+=3;
            break;
          case '6':
            output[o+0] = 'r';
            output[o+1] = 'w';
            output[o+2] = '-';
            o+=3;
            break;;
          case '5':
            output[o+0] = 'r';
            output[o+1] = '-';
            output[o+2] = 'x';
            o+=3;
            break;
          case '4':
            output[o+0] = 'r';
            output[o+1] = '-';
            output[o+2] = '-';
            o+=3;
            break;
          case '3':
            output[o+0] = '-';
            output[o+1] = 'w';
            output[o+2] = 'x';
            o+=3;
            break;
          case '2':
            output[o+0] = '-';
            output[o+1] = 'w';
            output[o+2] = '-';
            o+=3;
            break;
          case '1':
            output[o+0] = '-';
            output[o+1] = '-';
            output[o+2] = 'x';
            o+=3;
            break;
          case '0':
            output[o+0] = '-';
            output[o+1] = '-';
            output[o+2] = '-';
            o+=3;
            break;
          default:
            break;
        }
    }

}
/*  time_vtoc, vtoc helper function
    expects:
        time vtoc unprocessed time string line

    
    returns:
        properly formatted time string
*/
void time_vtoc(char * time, char * output){

    struct tm *ts;
    time_t t = strtol(time, (char**)NULL, 10);
    
    ts = localtime(&t);
    strftime(output, 100, "%b %d %H:%M %Y", ts);

}
/*  proc_vtoc, vtoc helper function
    expects:
        vtoc unprocessed line
        offset  length  description                 type
        0	    16	    File name	                ASCII
        16	    12	    File modification timestamp	Decimal
        28	    6	    Owner ID	                Decimal
        34	    6	    Group ID	                Decimal
        40	    8	    File mode               	Octal
        48	    10	    File size in bytes	        Decimal
        58	    2       File magic	                0x60 0x0A

    
    returns:
        nothing, the vtoc processed line is printed
*/
void proc_vtoc(char * line){
    char out_line[60];
    char temp[10];
    char time_int[17];
    char time_str[17];
    char mode_int[3];
    char mode_str[9];
    /*iterator*/
    int i;
    /*offset*/
    int j;
    /*length*/
    int k;
    /*length + offset*/
    int jk;
    /*iterated length*/
    int l;
    /*temp int*/
    int t;
    /*master index of output line*/
    int m = 9;
    /*file mode*/
    k = 8;
    j = 43;
    jk = j+k;
    for(i = 0; i < 3; i++){
        if (line[j] == ' ') break;
        if (j > jk) break;
        mode_int[i] = line[j];
        j++;
    }
    mode_vtoc(mode_int, mode_str);
    for(i = 0; i < m; i++) out_line[i] = mode_str[i];

    out_line[m] = ' ';
    /*owner id*/
    m++;
    i = m;
    k = 6;
    m = m + k;
    j = 28;
    jk = j + k;
    for(i = i; i < m; i++){
        if (line[j] == ' ') break;
        if (j > jk) break;
        out_line[i] = line[j];
        j++;
        k--;
    }
    m = m - k;
    out_line[m] = '/';
    /*group id*/
    m++;
    i = m;
    k = 6;
    m = m + k;
    j = 34;
    jk = j + k;
    for(i = i; i < m; i++){
        if (line[j] == ' ') break;
        if (j > jk) break;
        out_line[i] = line[j];
        j++;
        k--;
    }    
    m = m - k;

    /*file size in bytes*/

    t = m;
    k = 10;
    m = m + k;
    j = 48;
    jk = j + k;
    l = 0;
    for(i = 0; i < k; i++){
        if (line[j] == ' ') break;
        if (j > jk) break;
        temp[i] = line[j];
        j++;
        l++;
    }
    i = t;
    t = k-l-3;
    k = 0;
    l = 0;
    for(i = i; i < m; i++){
        
        if (l >= t){
            out_line[i] = temp[k];
            k++;
        }
        else out_line[i] = ' ';
        l++;
    }
    m = m - 3;    
    out_line[m] = ' ';
    /*m timestamp*/
    m++;
    t = m;
    k = 12;
    m = m + k + 5;
    j = 16;
    jk = j + k;
    /*
    for(i = i; i < m; i++){
        if (line[j] == ' ') break;
        if (j > jk) break;
        out_line[i] = line[j];
        j++;
        k--;
    }    
    */
    for(i = 0; i < k; i++){
        if (line[j] == ' ') break;
        if (j > jk) break;
        time_int[i] = line[j];
        j++;
    }
    time_vtoc(time_int, time_str);
    j = 0;
    
    for(i = t; i < m; i++){
        out_line[i] = time_str[j];
        j++;
    }
    out_line[m] = ' ';
    /*filename*/
    m++;
    i = m;
    k = 16;
    m = m + k;
    j = 0;
    jk = j + k;
    for(i = i; i < m; i++){
        if (line[j] == ' ' || line[j] == '/') break;
        if (j > jk) break;
        out_line[i] = line[j];
        j++;
        k--;
    }
    m = m - k;
    out_line[m] = ' ';

    /*append newline*/
    out_line[m] = '\n';
    write(STDOUT_FILENO, out_line, m+1);
}
/*  vtoc, -v, print verbose table of contents
    expects:
        archive_name = the name (and path) of the archive we are printing
    
    returns:
        nothing, the vtoc is printed
*/
void vtoc(char * archive_name){
    /*vars*/
    int i;
    int fd = is_archive(archive_name);
    int size = BLOCKSIZE;
    char buf[BLOCKSIZE];
    char line[60];
    int line_idx;
    int file_ptr;
    int file_end;
    int fnd_newline = 1;
    int fnd_tick = 0;
    /*find the end of the file*/
    file_end = lseek(fd, -1, SEEK_END);
    /*set the pointer to the beginning of the file*/
    file_ptr = lseek(fd, 0, SEEK_SET);
    /*meat and potatoes*/
    while(file_ptr < file_end ){
        /*read the file, one byte at a time*/
        read(fd, buf, size);
        /*we found the file attributes line!!!*/
        if (fnd_tick){
            proc_vtoc(line);
            fnd_newline = 0;
            fnd_tick = 0;
            line_idx = 0;   
        }
        /*check for newline*/
        if (buf[0] == '\n'){
            fnd_newline = 1;
            line_idx = 0;
            fnd_tick = 0;
        }
        /*check for tick*/
        if (buf[0] == '`' && fnd_newline){
            fnd_tick = 1;
        }
        /*if we found a newline and are still before the tick, record the line*/
        if (fnd_newline && !fnd_tick && line_idx <= sizeof(line) && buf[0] != '\n'){
            line[line_idx] = buf[0];
            line[line_idx+1] = '\n';
            line_idx++;
            
        }
        /*if we go past the index without finding the tick, we are not on a good line*/
        if (line_idx > sizeof(line)){
            line_idx = 0;
            fnd_newline = 0;
            for(i = 0; i < sizeof(line); i++) line[i] = '\0';
        } 
        /*increment to the next byte*/
        file_ptr = lseek(fd, 0, SEEK_CUR);
    }
    close(fd);
    return;
}
