#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <string.h>

#include "date.h"

// *** Global Variables ***
const int g_name_buff_size = 25; // maximum name string size
const int g_class_buff_size = 25; // maximum class string size

// *** Function  foward declarations ***
bool ParseArgs(int argc, char **argv, char **cvalue, char **dvalue, char **nvalue, bool rflag, bool aflag);
void ListAssignments();
bool ReadAssignments();

// *** Main ***
int main(int argc, char **argv){

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
                    ListAssignments();
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
// ~~~~~~~~~~~~~~~
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

bool ReadAssignments(Assignment **passed_arr, int *len_arr){
    
    FILE *txtfile;
    txtfile = fopen("assignments.txt","r");

    if (!txtfile){ // ensuring txt file exists
        printf("No assignments to list"); // TODO: Implement proper error output
        return false;
    }
    
    // preallocating array to hold assignments
    const int len_assign_arr = 5; //number of assignmnets to preallocate before loading from file 
    Assignment *assign_arr = malloc(len_assign_arr*sizeof(Assignment));
    
    // buffers for txt file transfer
    Date date_buff; 
    Assignment assign_buff;
    char name[g_name_buff_size], class[g_class_buff_size]; // string buffers
    int d, m, y; // date buffers

    int num_assign = 0; // variable to track number of assignments added to assign_arr
    while(fscanf(txtfile, "%s %s %d %d %d", name, class, &d, &m, &y) != EOF){
        
        // assigning assignment values from txt file to buffers
        date_buff.day = d;
        date_buff.month = m;
        date_buff.year = y;        
        strcpy(assign_buff.name, name);
        strcpy(assign_buff.class, class);
        assign_buff.AssDate = date_buff;

         
        if(num_assign >= len_assign_arr){ // if the number assignments allocated is bigger than the preallocated
            Assignment *temp_arr = realloc(assign_arr, (num_assign + 1)*sizeof(Assignment));
            if (temp_arr){ // if realloc successful, transfer array to original copy
                assign_arr = temp_arr;
                assign_arr[num_assign] = assign_buff;
            }
            else{
                //TODO: Implement error message for when realloc fail
                return false;
            }
        }
        else
            assign_arr[num_assign] = assign_buff; // appending end of assign_arr

        num_assign++; // incrementing num of assignments in arr
    }

    // passing assignments and num of assignments back 
    *len_arr = num_assign;
    *passed_arr = assign_arr;

    return true;
}

void ListAssignments(){
    Assignment *assign_arr;
    int len_assign_arr;

    if (ReadAssignments(&assign_arr, &len_assign_arr)){
        // titles for assignment list
        char n_title[] = "Assignment";
        char c_title[] = "Subject";
        // gathering lengths of titles
        int len_name = strlen(n_title);
        int len_class = strlen(c_title);

        // determining the length of longest name for table fitting
        // if all names are shorter than title, length of title is used
        for(int i = 0; i < len_assign_arr; i++){
            if(strlen(assign_arr[i].name)>len_name)
                len_name = strlen(assign_arr[i].name);
            if(strlen(assign_arr[i].class)>len_class)
                len_class = strlen(assign_arr[i].class);
        }
    
        char line[] = "-----------------------------------------------";
        
        // printing table title
        printf("+%.*s+%.*s+%.*s+%.*s+%.*s+\n", 3, line, len_name, line, len_class, line, 10, line, 4, line);   

        printf("| # |%*s|%*s|%10s|%s|\n", len_name, n_title, len_class, c_title, "Due Date ", "#Day");

        printf("+%.*s+%.*s+%.*s+%.*s+%.*s+\n", 3, line, len_name, line, len_class, line, 10, line, 4, line);

        // printing  all assignments 
        for(int i = 0; i < len_assign_arr; i++){
            printf("|%03d",i+1);
            DiplayAssignment(assign_arr[i],len_name,len_class);
        }
        printf("+%.*s+%.*s+%.*s+%.*s+%.*s+\n", 3, line, len_name, line, len_class, line, 10, line, 4, line);   
    }
    else{
        // TODO: Implement error message
    }

    return;
}