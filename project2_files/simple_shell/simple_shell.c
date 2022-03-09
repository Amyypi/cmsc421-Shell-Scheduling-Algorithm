/*
CMSC421 Spring 2022 - Section 4
Author:        Amy Phan
Email:         mphan1@umbc.edu
ID:            CM82779

Project name: Project 2 part 1
*/

#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "utils.h"
/*
	includes functions:
	extern size_t count_spaces(const char *str);
	extern void flush_input(FILE *fp);
	extern char *unescape(const char *str, FILE *errf);
	extern int first_unquoted_space(const char *str);
*/


// Predefined variables or constants//
//change this later to be changable sizes
char cmd[10];            //String holder for command
char *argv[10];          // an array for commands and arguments
pid_t pid;               // global variable for the child process ID
char i;                  // global for loop counter

// Function list //
void shell(void);            // to start the shell
char *ask_cmd(void);          // ask the command line from user
char **pars(char *);
void error();

/*
Function Declaration for builtin shell commands:
*/
int cmd_help(char **args);
int cmd_exit(char **args);
void cmd_echo(char **args);

char *builtin_str[] = {
	"echo"
	"help"
	"exit"
};


int (*builtin_func[])(char **) ={
	&cmd_echo,
	&cmd_help,
	&cmd_exit
};

int cmd_num_builtins(){
	return sizeof(builtin_str) / sizeof(char*);
}

/////////////////////////////////////////////
void shell(void){
	char *line;
	char **argument;
	char *argument_esc;
	int status;
	do{
		printf("$");
		line = ask_cmd();

		if(!line){
			//continue to ask again
		//split command into separate strings
		}else if(count_spaces(line) == 0){
			// no need to parse
			printf("No space, no parsing");
			status = 0;
		}else if(count_spaces(line) > 0){
			//more than one line // needs parsing
			//parse
			printf("more than one space \n");

			argument = pars(line);
			printf("this is argument: %s \n", argument[0]);
			//unescape

			argument_esc = unescape(argument[1], "unescape failed");
			printf("this is unescape %s\n",  argument_esc);
			status = 0;
		}

		
		free(line);
		free(argument);
		free(argument_esc);
		line = NULL;
		argument = NULL;
		argument_esc = NULL;
	}while(status);

}
char **pars(char *line){
	int bufsize = 64;
	int position = 0;
	char **tokens = malloc(bufsize *sizeof(char*));
	char *token;

	if(!tokens){
		fprintf(stderr,"allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \t\r\n\a");
	while (token != NULL){
		tokens[position] = token;
		position++;

		if(position >= bufsize){
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if(!tokens){
				fprintf(stderr, "allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL,"  \t\r\n\a");
	}
	tokens[position];


	return tokens;
}


char *ask_cmd(void){
	unsigned int len_max = 2;  //buffersize
	unsigned int current_size = 0;
	char *pStr = malloc(len_max);
	int counter;
	current_size = len_max;



	if(pStr != NULL){
		int c = EOF;
		unsigned int i = 0;

		//accept user input until hit enter or end of file
		while (( c = getchar() ) != '\n' && c != EOF){
			pStr[i++]=(char)c;
			//if i reached maximize size then realloc size
			if(i >= current_size)
			{
				current_size = i+len_max;
				pStr = realloc(pStr, current_size);
			}
		}

		pStr[i] = '\0';
		printf("length of string %ld \n",strlen(pStr) );
		printf("\nLong String value: %s \n\n", pStr);


		//free(pStr);
		//pStr = NULL;
	}
	return pStr;
}


/*
change directory ( I dont need this)
*/
int cmd_cd(char **args){
	if (args[1] == NULL){
		fprintf(stderr, "cmd: expected argument to \"cd\"\n");
	}else{
		if(chdir(args[1]) != 0){
			perror("lsh");
		}
	}
	return 1;
}

/*
print builtin command: print help
Param args list of args. not examined
return always return 1, to continue executing
*/
int cmd_help(char **args)
{
	int i;
	printf("Stephen Brennan's LSH\n");
	printf("Type program names and arguments, and hit enter.\n");
	printf("The following are built in:\n");

	for(i = 0; i <  cmd_num_builtins(); i++){
		printf(" %s\n", builtin_str[i]);
	}

	printf("Use the man command for information on other programs.\n");
	return 1;
}

/*
command exit
list of args. not examined
return 0, to terminate execution
*/
int cmd_exit(char **args){

	
	return 0;
}

void cmd_echo(char **args){
	

}


int cmd_execute(char **args){
	int i;
	if(args[0] = NULL){
		//if empty command was entered
		return 1;
	}

	for(i = 0; i < cmd_num_builtins(); i++){
		if(strcmp(args[0], builtin_str[i]) == 0){
			return(*builtin_func[i])(args);
		}
	}
	return 0;
}

void main(){
	//start shell and ask user a command
        shell();

}
