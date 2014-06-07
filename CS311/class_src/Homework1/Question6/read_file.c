/*

  $RCSfile$
  $Revision$
  $Author$
  $Date$
  $Log$

  from:
  http://www.programmingsimplified.com/c-program-read-file

 */

#include "read_file.h"
#include <stdio.h>
#include <errno.h>

int main()
{
   char ch, file_name[25];
   FILE *fp;
   int fd = 0;
   int num_read;
 
   printf("Enter the name of file you wish to see\n");
   fgets(file_name, 25, stdin);

   fp = fopen(file_name, O_RDONLY);
   if (fp < 0)
     {
       perror("Error while opening the file.\n");
       exit(EXIT_FAILURE);
     }
   printf("The contents of %s file are :\n", file_name);

   for (;;)
     {
       num_read = read(fd, &ch, sizeof(ch));
       if (num_read < '0')
	 {
	   perror("Error while reading the file.\n");
	   exit(EXIT_FAILURE);
	 }
       if (num_read == 0)
	 {
	   break;
	 }
       write(STDOUT_FILENO, &ch, sizeof(ch));
     }
   return ch;
}
