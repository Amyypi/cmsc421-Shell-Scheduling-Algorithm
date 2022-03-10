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
char **pars_with_quote(char *line, int num_spaces);
char **pars(char *line);
char *ask_cmd(void);
size_t count_spaces_with_quote(const char *str, int first_space);

///////////////////////////////////////////
// List of command builtin functions:    //
//////////////////////////////////////////
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
size_t count_spaces_with_quote(const char *str, int first_space){
	size_t num_of_spaces = 0;
	int char_counter = 0;
        do{
		if(*str){
			return num_of_spaces;
		}
		if(isspace(*str++)){
                num_of_spaces++;
        	}
       		char_counter++;
        }while(char_counter != first_space);
	return num_of_spaces;
}

int exit_cmd(char **args){
	int arg_num = 0;
	printf("exit_cmd called \n");

	// zero argument given
	if(args[1] == NULL){
		printf("No argument given in exit cmd");
		return (char *)0;
	// one argument given
	}else{
		//parsing failed
		if(arg_num == -1){
			return (char *)0;
		}
	}
	//command exit entered
	return (char *)0;
}

void shell(){
	char *line;
	char **argument;
	//char *argument_esc;
	int status = 1;
	int first_space;
	int char_counter;
	int num_of_spaces;

	do{

		//ask for command from user
		printf("$");
		line = ask_cmd();

		//checks if there are any quotes in the command line
		first_space = first_unquoted_space(line);

		//if there is a quote, do parsing with quote
		if(first_space >= 0){
			num_of_spaces = 0;
			char_counter = 0;
			//count how many spaces there are before quote
			num_of_spaces = count_spaces_with_quote(line, first_space);
			printf("line after isspace: %s\n", line);


			//parse with quote
			argument = pars_with_quote(line, num_of_spaces);

			printf("argument with quote 1: %s\n", argument[0]);
			printf("argument with quote 2: %s\n", argument[1]);

			argument[1] = unescape(argument[1], "error");
			printf("Print echo here: \n");
			status = execute_cmd(argument);
			free(argument[1]);
			argument[1] = NULL;
		//if there aren't any quotes, do regular parsing
		}else{
			argument = pars(line);
			printf("this is argument: %s \n", argument[0]);
			//check if input isn't empty;
			if(argument[0] == NULL){
				printf("Empty argument");
			}else{
				status = execute_cmd(argument);
			}
		}
		free(line);

		free(argument);
	//	free(argument_esc);
	}while(status || status == -1);

	line = NULL;
	argument = NULL;

	printf("\n Exit out");
}

int launch_cmd(char **args){
	pid_t pid, wpid;
	int counter = 0;
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
			//printf("ret is %s \n", ret);
			return ret;
		}
	}

	printf("launch called\n");
	return launch_cmd(args);
}

char **pars_with_quote(char *line, int num_spaces){
        printf("Enter pars with quote\n");
        int bufsize = 64;
        int position = 0;
	int counter = 0;
        char **tokens = malloc(bufsize *sizeof(char*));
        char *token;

        if(!tokens){
                fprintf(stderr,"allocation error\n");
                exit(EXIT_FAILURE);
        }

        token = strtok(line," ");
	if(num_spaces > 1){
		for(counter = 0; counter < num_spaces - 1; counter++){
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
                	token = strtok(NULL," ");
        	}
	}

        for(counter = 0; counter < 2; counter++){
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
                token = strtok(NULL,"\"");
        }

        printf("Parsing with quote complete");
        tokens[position];
        return tokens;
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
				//printf("length: %ld \n", trlen(pStr));
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
