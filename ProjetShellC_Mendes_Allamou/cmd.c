#include "cmd.h"

//Prints the command
void printCmd(cmd *cmd){
    printf("//-------------------CMD-------------------------//\n");
    printf("initCmd : %s\n",cmd->initCmd);
    printf("nbCmdMembers : %d\n", cmd->nbCmdMembers);
    for(int i =0; i < cmd->nbCmdMembers; i++)
    {
        printf("cmdMembers [%d] : %s \n", i, cmd->cmdMembers[i]);
    }
    printf("\n");

    for(int i =0; i < cmd->nbCmdMembers; i++)
    {
        printf("nbMembersArgs [%d] : %d\n",i, cmd->nbMembersArgs[i]);
        for (int j = 0; j < cmd->nbMembersArgs[i]; j++)
        {
            printf("cmdMembersArgs [%d][%d] : %s \n", i, j, cmd->cmdMembersArgs[i][j]);
        }

    }
    printf("\n");
    for(int i = 0; i < cmd->nbCmdMembers; i++)
    {

        printf("redirection [%d] [STDIN] : %s\n", i ,cmd->redirection[i][STDIN]);
        printf("redirection [%d] [STDOUT] : %s\n", i ,cmd->redirection[i][STDOUT]);
        printf("redirection [%d] [STDERR] : %s\n", i ,cmd->redirection[i][STDERR]);

        if (cmd->redirection[i][STDOUT] != NULL)
        {
            if (cmd->redirectionType[i][STDOUT] == APPEND) printf("redirectionType [%d] [STDOUT] : APPEND\n");
            else printf("redirectionType [%d] [STDOUT] : OVERRIDE\n");
        }
        if (cmd->redirection[i][STDERR] != NULL)
        {
            if (cmd->redirectionType[i][STDERR] == APPEND) printf("redirectionType [%d] [STDERR] : APPEND\n");
            else printf("redirectionType [%d] [STDERR] : OVERRIDE\n");
        }
    }
    printf("\n");
	//your implementation comes here
}

//Initializes the initial_cmd, membres_cmd et nb_membres fields
void parseMembers(char *inputString,cmd *cmd){

    cmd->initCmd = malloc(strlen(inputString)*sizeof(char));
    strcpy(cmd->initCmd, inputString);
    printf("%s\n",cmd->initCmd);
    add_cmd_members(cmd);
    init_redirection(cmd);
    add_cmd_members_args(cmd);
}

//Frees memory associated to a cmd
void freeCmd(cmd  * cmd){

}


void add_cmd_members(cmd * s)
{
    const char delimiter[2] = "|";
    char str[100];
    strcpy(str,s->initCmd);
    char * token;
    int i = 0;
    token = strtok(str, delimiter);
    s->cmdMembers = malloc(sizeof(char *));
    while(token != NULL)
    {
        s->cmdMembers = realloc(s->cmdMembers, i+1*sizeof(char *));
        s->cmdMembers[i] = malloc(strlen(token)*sizeof(char));
        strcpy(s->cmdMembers[i] , token);
        printf("%s \n", token);
        token = strtok(NULL, delimiter);
        i++;
    }
    s->nbCmdMembers = i;
}


/*
    Gérer redirections dans If pour terminer peuplement struct
*/
void add_cmd_members_args(cmd * s)
{
    const char delimiter[2] = " ";
    int red_in = 0;
    int red_out = 0;
    s->cmdMembersArgs =(char ***) malloc(sizeof(char **)*s->nbCmdMembers);
    s->nbMembersArgs = (int *) malloc(sizeof(int) * s->nbCmdMembers);
    for (int i = 0; i < s->nbCmdMembers; i++)
    {
        char * token;
        char str[100];
        int j = 0;
        char * redir = NULL;


        s->cmdMembersArgs[i] = (char **)malloc(sizeof(char *));
        strcpy(str,s->cmdMembers[i]);
        token = strtok(str, delimiter);

        while(token != NULL)
        {
            printf("token : %s\n", token);
            s->cmdMembersArgs[i] = (char **)realloc(s->cmdMembersArgs[i], j+1*sizeof(char *));
            if (redir != NULL)
            {


                if (strcmp(redir,"<") == 0)
                {
                    s->redirection[i][STDIN] = (char *)malloc(strlen(token)*sizeof(char)+1);
                    strcpy(s->redirection[i][STDIN], token);
                    if (red_in == 1){ printf("Impossible to have more than one '<'\n"); exit(EXIT_FAILURE);}
                    red_in = 1;
                }
                else if (strcmp(redir,">") == 0)
                {
                    s->redirection[i][STDOUT] = (char *)malloc(strlen(token)*sizeof(char)+1);
                    strcpy(s->redirection[i][STDOUT], token);
                    if (red_out == 1) { printf("Impossible to have more than one '>'\n") ;exit(EXIT_FAILURE);}
                    red_out = 1;
                    s->redirectionType[i][STDOUT] = APPEND;
                }
                else if (strcmp(redir,">>") == 0)
                {
                    s->redirection[i][STDOUT] = (char *)malloc(strlen(token)*sizeof(char)+1);
                    strcpy(s->redirection[i][STDOUT], token);
                    s->redirectionType[i][STDOUT] = OVERRIDE;
                }
                else if (strcmp(redir,"2>") == 0)
                {
                    s->redirection[i][STDERR] = (char *)malloc(strlen(token)*sizeof(char)+1);
                    strcpy(s->redirection[i][STDERR], token);
                    s->redirectionType[i][STDERR] = APPEND;
                }
                else if (strcmp(redir,"2>>") == 0)
                {
                    s->redirection[i][STDERR] = (char *)malloc(strlen(token)*sizeof(char)+1);
                    strcpy(s->redirection[i][STDERR], token);
                    s->redirectionType[i][STDERR] = OVERRIDE;
                }
                token = strtok(NULL, delimiter);
                redir = NULL;
            }
            else
            {
                if(token[0] == '<'||token[0] == '>')
                {
                    s->cmdMembersArgs[i][j] = NULL;
                    redir = malloc(strlen(token)*sizeof(char));
                    strcpy(redir,token);
                }
                else
                {
                    printf("token : %s\n", token);
                    s->cmdMembersArgs[i][j] = (char *)malloc(strlen(token)*sizeof(char)+1);
                    //printf("%s", s->cmdMembersArgs[i]);
                    printf("%s", s->cmdMembersArgs[i][j]);
                    printf("token : %s\n", token);
                    strcpy(s->cmdMembersArgs[i][j],token);
                    printf("%s \n", token);
                    token = strtok(NULL, delimiter);
                    j++;
                }
            }




        }
        //s->cmdMembersArgs[i][j+1] = NULL;
        s->nbMembersArgs[i] = j;
    }


}


void init_redirection(cmd * s)
{
    s->redirection = (char ***) malloc(s->nbCmdMembers*sizeof(char **));
    s->redirectionType = (int **) malloc(s->nbCmdMembers*sizeof(int*));
    for(int i = 0; i < s->nbCmdMembers; i++)
    {
        s->redirection[i] = (char **) malloc(3*sizeof(char*));
        s->redirectionType[i] = (int *) malloc(2*sizeof(int));

        s->redirection[i][STDIN] = NULL;
        s->redirection[i][STDOUT] = NULL;
        s->redirection[i][STDERR] = NULL;

        //s->redirectionType[i][STDIN] = NULL;
        s->redirectionType[i][STDOUT] = NULL;
        s->redirectionType[i][STDERR] = NULL;
    }
}

