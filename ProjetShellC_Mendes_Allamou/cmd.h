#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Command is well-formed
#define MYSHELL_CMD_OK 0
#define APPEND 1
#define OVERRIDE 2

#define STDIN   0
#define STDOUT  1
#define STDERR  2


typedef struct {
    //the command originally inputed by the user
    char *initCmd;

    //number of members
    unsigned int nbCmdMembers;

    //each position holds a command member
    char **cmdMembers;

    //cmd_members_args[i][j] holds the jth argument of the ith member
    char ***cmdMembersArgs;

    //number of arguments per member
    unsigned int *nbMembersArgs;

    //the path to the redirection file
    char ***redirection;

    //the redirection type (append vs. override)
    int **redirectionType;
} cmd;

//Prints the command
void printCmd(cmd *cmd);
//Frees memory associated to a cmd
void freeCmd(cmd  * cmd);
//Initializes the initial_cmd, membres_cmd et nb_membres fields
void parseMembers(char *s,cmd *c);
//Separer éléments dans chaîne
void add_cmd_members(cmd * s);

void add_cmd_members_args(cmd * s);

void init_redirection(cmd * s);
