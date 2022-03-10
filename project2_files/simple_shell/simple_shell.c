/*
CMSC421 Spring 2022 - Section 4
Author:        Amy Phan
Email:         mphan1@umbc.edu
ID:            CM82779

Project name: Project 2 part 1
*/
#include <unistd.h>
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

//Define global constants
#define NUMBER_OF_BUILTINS = 1; //change if more builtins are added

//List of functions//
char **pars(char *line);
char *ask_cmd(void);

//List of command builtin functions:
int exit_cmd(char **args);

char *builtin_cmd_list[] = {
	"exit"
};

int(*builtin_func[])(char **) = {
	&exit_cmd
};
int num_builtins(){
	return sizeof(builtin_cmd_list) / sizeof(char *);
}

/////////////////////////////////////////////
// Functions                               //
/////////////////////////////////////////////
int exit_cmd(char **args){
	printf("exit_cmd called \n");
	//command exit entered
	return 0;
}

void shell(){
	char *line;
	char **argument;
	//char *argument_esc;
	int status = 1;

	do{
		printf("$");
		line = ask_cmd();
		argument = pars(line);

		printf("this is argument: %s \n", argument[0]);

		if(argument[0] == NULL){
			printf("Empty argument");
		/*
		}else if(strcmp(argument[0], builtin_cmd_list[0])){
			printf("exit called\n");
			status = exit_cmd(argument);
		*/
		}else{
			//argument_esc = unescape(argument[1], "unescape failed");
			//printf("this is unescape %s\n",  argument_esc);
			status = execute_cmd(argument);
		}


		free(line);
		free(argument);
	//	free(argument_esc);
	}while(status || status == -1);

	line = NULL;
	argument = NULL;
//	argument_esc = NULL;

	printf("\n Exit out");
}

int launch_cmd(char **args){
	pid_t pid, wpid;
	int counter = 0;
//	int length = strlen(args);
	int status;

	printf("Before fork\n");
	pid = fork();

	if(pid  == 0){
		printf("ls -l has taken control\n");
		if(execvp(args[0], args) == -1){
			perror("lsh");
			printf("fork fail 1\n");
		}
		exit(EXIT_FAILURE);

	}else if(pid < 0){
		perror("lsh");
		printf("fork failure 2\n");
	}else{
		printf("this line will be printed - fork failed\n");
		do{
		wpid = waitpid(pid, &status, WUNTRACED);
		}while(!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return 1;
}



int execute_cmd(char **args){
	int i;
	int ret;
	printf("Execute running\n");
	for(i = 0; i < num_builtins(); i++){
		printf("Running for loop execute\n");
		if(strcmp(args[0], builtin_cmd_list[i]) == 0){
			printf("Exit called\n");
			ret = (*builtin_func[i])(args);
			printf("ret is %s \n", ret);
			return ret;
		}
	}

	printf("launch called\n");
	return launch_cmd(args);
}



char **pars(char *line){
	printf("Enter pars\n");

	int bufsize = 64;
	int position = 0;
	char **tokens = malloc(bufsize *sizeof(char*));
	char *token;

	if(!tokens){
		fprintf(stderr,"allocation error\n");
		exit(EXIT_FAILURE);
	}
	token = strtok(line," \n");
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
		token = strtok(NULL," \n");
	}
	printf("Parsing complete");
	tokens[position];
	return tokens;
}

//this should be fine
char *ask_cmd(void){
	unsigned int len_max = 100;  //buffersize
	unsigned int current_size = 0;
	char *pStr = malloc(len_max);
	int counter;
	current_size = len_max;

	if(pStr != NULL){
		int c = EOF;
		unsigned int i = 0;

		//accept user input until hit enter or end of file
		while (1){
			c = getchar();
			if(c == EOF || c == '\n'){
				printf("End of ask\n");
				printf("string: %s \n", pStr);
				//printf("length: %ld \n", strlen(pStr));
				pStr[i] = '\0';
				return pStr;
			}else{
			pStr[i]=c;
			}
			i++;
			//if i reached maximize size then realloc size
			if(i >= current_size)
			{
				current_size = i+len_max;
				pStr = realloc(pStr, current_size);
			}
		}
	}
	return NULL;
}

int main(int argc, char **argv){
	//start shell and ask user a command
        shell();

	return EXIT_SUCCESS;
}
