/*
#
#   Name: 			Eric Rouse
#   Email Address:	rousee@onid.orst.edu
#   Class Name:		CS311-400
#   Assignment:		Homework #4
#
*/
#include "functions.h"


/*MAIN*/
int main(int argc, char ** argv){
    /* init vars */
	char c;
		
	/*
	   use getopt to parse command line options
	   pull in the options from the command line
	   convert the numbers to longs using strtol
    */
    while ((c = getopt (argc,argv,"q:x:t:v:d:A:w:"))!= -1)
        switch (c){
            case 'q':
                quick_add(argc-optind,optind,argv,optarg);
                exit(EXIT_SUCCESS);
            case 'x':
            	extract(argc-optind,optind,argv,optarg);
                exit(EXIT_SUCCESS);
            case 't':
            	toc(optarg);
                exit(EXIT_SUCCESS);
			case 'v':
				vtoc(optarg);
                exit(EXIT_SUCCESS);
			case 'd':
				delete(argc-optind,optind,argv,optarg);
                exit(EXIT_SUCCESS);
			case 'A':
				append(optarg);
                exit(EXIT_SUCCESS);
            case 'w':
				add_mods(strtol(argv[optind], (char**)NULL, 10), optarg);
                exit(EXIT_SUCCESS);
            case '?':
                printf("******error******\n");
            default:
                printf("bad input detected\n");
                exit(EXIT_FAILURE);
        }
	
	
	
    exit(EXIT_SUCCESS);
}
