#include "cmd.h"

//Prints the command
void printCmd(cmd *cmd){
	//your implementation comes here
}

//Initializes the initial_cmd, membres_cmd et nb_membres fields
void parseMembers(char *inputString,cmd *cmd){
    cmd = malloc(sizeof(cmd));
    cmd->initCmd = inputString;
    add_cmd_members(cmd);
    add_cmd_members_args(cmd);
}

//Frees memory associated to a cmd
void freeCmd(cmd  * cmd){
  
}

void add_cmd_members(cmd * s)
{
	cmd->cmdMembers = NULL;
	cmd->nbCmdMembers = 0;
	char cmd [50];
	int i = 0;
	int cmpt = i;
	while(s->initCmd[i] != '\0')
	{
		if (s->initCmd[i] == '|')
		{
			cmd[cmpt] = '\0'; 
			if (cmd->nbCmdMembers == 0) cmd->cmdMembers = malloc(sizeof(char*));
			else cmd->cmdMembers = realloc(cmd->cmdMembers, (cmd->nbCmdMembers+1)*sizeof(char *));
			strcpy(cmd->cmdMembers[cmd->nbCmdMembers], cmd);
			cmd = "";
			cmd->nbCmdMembers ++; 
			cmpt = 0;
		}
		else cmd[cmpt] = s->initCmd[i];
		i++;
	}
	cmd->cmdMembers = realloc(cmd->cmdMembers, (cmd->nbCmdMembers+1)*sizeof(char *));
	strcpy(cmdMembers[cmd->nbCmdMembers], cmd);
	cmd->nbCmdMembers ++; 
}


/* 	1. Gérer '<' '>' dans le if  
	2. Ajouter le dernier élément
*/
void add_cmd_members_args(cmd * s)
{
	cmd->cmdMembersArgs = NULL;

	for(int i = 0; i < cmd->nbCmdMembers; i++)
	{
		char cmd [50];
		int j = 0;
		int cmpt = j;

		while(s->cmdMembers[i][j] != '\0')
		{
			if (s->cmdMembers[i][j] == ' ' && )
			{
				cmd[cmpt] = '\0'; 
				if (cmd->nbMembersArgs[i] == 0) cmd->cmdMembersArgs = (char ***)malloc(sizeof(char**));
				else cmd->cmdMembersArgs[i] = (char **) realloc(cmd->cmdMembersArgs, (cmd->nbMembersArgs+1)*sizeof(char *));
				cmd->cmdMembersArgs[i][cmd->nbMembersArgs[i]] = malloc(sizeof(char));
				strcpy(cmd->cmdMembersArgs[cmd->nbMembersArgs[i]], cmd);
				cmd = "";
				cmd->cmdMembersArgs[i]++; 
				cmpt = 0;
			}
			else cmd[cmpt] = s->cmdMembersArgs[i][j];
			j++;
		}
		if 
		cmd->cmdMembers = realloc(cmd->cmdMembersArgs, (cmd->nbMembersArgs+1)*sizeof(char *));
		strcpy(cmdMembers[cmd->nbCmdMembers], cmd);
		cmd->nbCmdMembers ++; 
	}
	
}
