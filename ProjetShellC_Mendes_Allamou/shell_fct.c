#include "shell_fct.h"

int exec_command(cmd* my_cmd){
    //Your implementation comes here
    //i) declare auxiliary variables
    pid_t   * pid_l;
    int     * status;
    int     ** tube;

    char buffer[100];
    pid_l   = malloc(cmd->nbCmdMembers * sizeof(pid_t));
    status  = malloc(cmd->nbCmdMembers * sizeof(int));
    tube    = malloc(cmd->nbCmdMembers * sizeof(int *))
    for (int i = 0; i < my_cmd->nbCmdMembers; i++)
    {
        tube[i] = malloc(2*sizeof(int));
        //Init fork()
        pipe(tube[i]);
        pid_l[i] = fork();
        //TODO: Redirections (maybe create a child and sent it path)
        if (pid_l[i] == 0)
        {
            close(tube[i][0]);
            dup2(tube[i][1], 1);
            close(tube[i][1]);
            char args [100];
            for (int j = 0; j < my_cmd->nbMembersArgs; j++)
            {
                strcat(args,my_cmd->cmdMembersArgs[i][j]);
            }
            if (execlp(my_cmd->cmdMembers[i],my_cmd->cmdMembers[i],args, NULL))
            {
                perror("execlp");
                exit(EXIT_FAILURE);
            }
        }
        if (i == 0) close(tube[i][1]);
        else if (i == my_cmd->nbMembersArgs-1) close(tube[i][0]);
        if (i == 0) {close(tube[i][1]); close(tube[i][0]);}

    }

    for (int i = 0; i < my_cmd->nbCmdMembers; i++)
    {
        waitpid(pid_l[i], &status[i], 0);
    }

    while(fgets(buffer, 20,stdin) != NULL) {printf(my_cmd->initCmd, buffer); printf("\n");}


    return 0; //your return code goes here
}
