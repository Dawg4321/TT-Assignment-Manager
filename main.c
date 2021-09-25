#include <stdio.h>
#include <getopt.h>
#include <time.h>

#include "date.c"


int main(int argc, char** argv){
    
    int opt, lflag = 0, dflag = 0, cflag = 0, nflag = 0, aflag = 0, rflag = 0;
    char *cvalue, *dvalue, *nvalue;


    // *** Parsing Opts and Args ***
    while((opt = getopt(argc,argv,"lad:n:c:r:i:")) != -1){ // loop through each option 
        switch(opt){
            
            // ** Options **
            case 'l': // list assignments opt
                lflag = 1;
                break;
            case 'a': // add assignment opt
                lflag = 1;
                break;
            case 'r': // remove assignment opt
                lflag = 1;
                break;

            // ** Args for opts **
            case 'd': // due date arg
                dflag = 1;
                dvalue = optarg;
                break;
            case 'c': // class name arg
                nflag = 1;
                nvalue = optarg;
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

}