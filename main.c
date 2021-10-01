#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <time.h>
#include <string.h>

#include "date.c"

 bool ParseArgs(int argc, char **argv, char **cvalue, char **dvalue, char **nvalue, bool rflag, bool aflag);


// *** main() ***
int main(int argc, char **argv){
// ** Processing CLI Options **
    bool lflag, aflag, rflag, hflag; // CLI option flags
    lflag = aflag = rflag = hflag = false;
    char *cvalue, *dvalue, *nvalue; // CLI argument values
    
    bool parse_flag = 0; // flag to determine if ParseArgs() succeeds

    if (argv[1][0] == '-' && strlen(argv[1])==2){ // check if CLI option is the correct format
        switch(argv[1][1]){
            case 'l': // list assignments option
                if (argc >= 3){ // argc >= means that input with -l option has args. This is incorrect behaviour as -l requires no args 
                    printf("shouldn't have args with l"); // TODO: Implement proper error message for -l with largs
                    return -1;
                }
                else{
                    lflag = true;
                    break;
                }
            case 'a': // add assignment option
                aflag = true;
                if(ParseArgs(argc, argv, &cvalue, &dvalue, &nvalue, rflag, aflag));
                    printf("n=%s\nc=%s\nd=%s\n",nvalue,cvalue,dvalue);
                break;
            case 'r': // remove assignment option
                rflag = true;
                if(ParseArgs(argc, argv, &cvalue, &dvalue, &nvalue, rflag, aflag));
                    printf("n=%s\n",nvalue,cvalue,dvalue);
                break;
            case 'h': // help option
                hflag = true;
                if(ParseArgs(argc, argv, &cvalue, &dvalue, &nvalue, rflag, aflag));
                    printf("n=%s\nc=%s\nd=%s\n",nvalue,cvalue,dvalue);
                break;
            default:
                printf("Error message"); // TODO: Create a propr output message regarding incorrect option
                return -1; 
        }
    }
    return 0;
}

// *** Functions ***

// ~~~ParseArgs~~~
 bool ParseArgs(int argc, char **argv, char **cvalue, char **dvalue, char **nvalue, bool rflag, bool aflag){

    // Removing argv[0] before processing args 
    int len_args = argc - 1;
    char **args = malloc(len_args); // array to hold args during processing 
    
    for (int i = 1; i < argc; i++){ // Copying args from argv into new array (args = argv[2 -> (argc-1)])
        args[i-1] = malloc(sizeof(argv[i]));
        strcpy(args[i-1], argv[i]);
    }
  
    int opt; 

    bool dflag, cflag, nflag; // flags to determine if arg appears twice
    dflag = aflag = nflag = false;

    opterr = 0; // disable getopt() error printout
    while((opt = getopt(len_args,args,"d:n:c:")) != -1){ // loop through each arg 
        switch(opt){
            case 'd': // due date arg
                if(aflag && !dflag){
                    dflag = true;
                    *dvalue = optarg;
                }
                else{
                    printf("error");
                    // TODO: Implement error output
                    return false;
                }
                break;
            case 'c': // class name arg
                if(aflag && !cflag){
                    cflag = true; 
                    *cvalue = optarg;
                }
                else{
                    printf("error");
                    // TODO: Implement error output
                    return false;
                }
                break;
            case 'n': // assignment name arg
                if(aflag||rflag && !nflag){
                    nflag = true;
                    *nvalue = optarg;
                }
                else{
                    printf("error");
                    // TODO: Implement error output
                    return false;
                }
                break;
            case '?':
                printf("error");
                // TODO: Implement ? case + error messages
                break;
        }
    }
    return true;  
}
