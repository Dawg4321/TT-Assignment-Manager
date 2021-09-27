#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include <string.h>

#include "date.c"


int main(int argc, char **argv){
// *** Processing CLI Options ***
    int lflag = 0, aflag = 0, rflag = 0, hflag = 0; // CLI option flags

    if (argv[1][0] == '-' && strlen(argv[1])==2){ // check if CLI option is correct
        switch(argv[1][1]){
            // ** Options **
            case 'l': // list assignments opt
                lflag = 1;
                break;
            case 'a': // add assignment opt
                aflag = 1;
                break;
            case 'r': // remove assignment opt
                rflag = 1;
                break;
            case 'h': // help option
                hflag = 1;
                break;
            default:
                printf("Error message"); // TODO: Create a propr output message regarding incorrect option
                return 1; 
        }
    }
    
    // *** Parsing CLI Arguments ***
    // Remove [program] [option] from argv to before processing args
    int len_args = argc - 1;
    char **args = malloc(len_args); // array to hold args 
    
    for (int i = 1; i < argc; i++){ // Copying args into new array (args = argv[2 -> (argc-1)])
        args[i-1] = malloc(sizeof(argv[i]));
        strcpy(args[i-1], argv[i]);
    }


    int opt, dflag = 0, cflag = 0, nflag = 0; // CLI argument flags
    char *cvalue, *dvalue, *nvalue; // CLI argument values

    opterr = 0; // disable getopt() error printout

    while((opt = getopt(len_args,args,"d:n:c:r:i:")) != -1){ // loop through each arg 
        switch(opt){
            // ** Arguments **
            case 'd': // due date arg
                dflag = 1;
                dvalue = optarg;
                break;
            case 'c': // class name arg
                cflag = 1;
                cvalue = optarg;
                break;
            case 'n': // assignment name arg
                nflag = 1;
                nvalue = optarg;
                break;
            case '?':
                // TODO: Implement ? case
                break;
        }
    }
    return 0;
}