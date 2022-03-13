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

//Define global constants
#define NUMBER_OF_BUILTINS = 1; //change if more builtins are added

//List of functions//
char **pars_with_quote(char *line, int num_spaces);
char **pars(char *line, char delin[]);
char *ask_cmd(void);
size_t count_spaces_with_quote(const char *str, int first_space);

/////////////////////////////////////////////////////////////////
// List of command builtin functions and builtin functions:    //
////////////////////////////////////////////////////////////////
int exit_cmd(char **args);
int proc_cmd(char **args);

char *builtin_cmd_list[] = {
	"exit",
	"proc"
};

int(*builtin_func[])(char **) = {
	&exit_cmd,
	&proc_cmd
};
int num_builtins(){
	return sizeof(builtin_cmd_list) / sizeof(char *);
}

int proc_cmd(char **args){
        FILE * pFile;
        long lSize;
        char buffer[10000];
        size_t result;
        char* procDir;
        char **argument;
        char* procName = "/proc/";

        argument = pars(args[1], "/");

        if(strcmp(argument[0], "pid") == 0){
                //if we have display pid/...
                pid_t pid = getpid();

                char mypid[5];
                sprintf(mypid, "%d", pid);
                procDir = malloc(strlen(argument)*10);
                strcpy(procDir, procName);
                strcat(procDir, mypid);
                strcat(procDir,"/");
                strcat(procDir, argument[1]);


        }else{
                //regular proc with no pid/...
                procDir = malloc(strlen(args)*10);
                strcpy(procDir, procName);
                strcat(procDir, args[1]);
        }


        pFile = fopen(procDir, "r");
        if(pFile != NULL){
                do{
                        result = fread(buffer, 1, sizeof buffer, pFile);
                        if(result != 0){
                                fwrite(buffer, 1, result, stdout);
                        }
                }while(result != 0);
        }else{
                printf("Failed proc command\n");
        }
	fclose(pFile);
	free(procDir);
        free(argument);
	procDir = NULL;
        argument = NULL;
        return 1;
}

int exit_cmd(char **args){
        int arg_num = 0;
        //printf("exit_cmd called \n");

	/*
        // zero argument given
        if(args[1] == NULL){
                //printf("No argument given in exit cmd");
                return (char *)0;
        // one argument given
        }else{
                //parsing failed
                if(arg_num == -1){
                        return (char *)0;
                }else{
			return -1;
		}
        }
	*/
        //command exit entered
        return (char *)0;
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

void shell(){
	char *line;
	char **argument;
	int status = 1;
	int first_space = 0;
	int num_of_spaces = -1;

	do{
		//ask for command from user
		printf("$");
		line = ask_cmd();

		//checks if there are any quotes in the command line
		first_space = first_unquoted_space(line);

		//if there is a quote, do parsing with quote
		if(first_space >= 0){
			num_of_spaces = 0;
			//count how many spaces there are before quote
			num_of_spaces = count_spaces_with_quote(line, first_space);

			//parse with quote
			argument = pars_with_quote(line, num_of_spaces);
			argument[1] = unescape(argument[1], "error");
			status = execute_cmd(argument);
			free(argument[1]);
			argument[1] = NULL;
		//if there aren't any quotes, do regular parsing
		}else{
			argument = pars(line, " \n");
			//check if input isn't empty;
			if(argument[0] == NULL){
				printf("Empty argument\n");
			}else{
				status = execute_cmd(argument);
			}
		}
		free(line);
		free(argument);
	}while(status || status == -1);

	line = NULL;
	argument = NULL;
	printf("\n Exit out\n\n");
}

int launch_cmd(char **args){
	pid_t pid = NULL;
	pid_t wpid = NULL;
	int counter = 0;
	int status = 0;

	pid = fork();

	if(pid  == 0){
		if(execvp(args[0], args) == -1){
			perror("lsh");
			printf("fork fail 1\n");
		}
		exit(EXIT_FAILURE);

	}else if(pid < 0){
		perror("lsh");
		printf("fork failure 2\n");
	}else{
		do{
		wpid = waitpid(pid, &status, WUNTRACED);
		}while(!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return 1;
}

int execute_cmd(char **args){
	int i = 0;
	int ret = 0;

	for(i = 0; i < num_builtins(); i++){
		if(strcmp(args[0], builtin_cmd_list[i]) == 0){
			ret = (*builtin_func[i])(args);
			return ret;
		}
	}
	return launch_cmd(args);
}

// Parsing with quotes
char **pars_with_quote(char *line, int num_spaces){
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
	//If there is more than one space in command line
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
	//Parse the quote to be a full line
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
        tokens[position];
        return tokens;
}


// Regular parsing without quotations
char **pars(char *line, char delin[]){
	int bufsize = 64;
	int position = 0;
	char **tokens = malloc(bufsize *sizeof(char*));
	char *token;

	if(!tokens){
		fprintf(stderr,"allocation error\n");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, delin);
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
		token = strtok(NULL, delin);
	}
	tokens[position];
	return tokens;
}

// Ask for user to input a command
char *ask_cmd(void){
	unsigned int len_max = 100;      // buffersize
	unsigned int current_size = 0;   // used to keep track of the char size
	char *pStr = malloc(len_max);    // initialize char 
	//int counter;
	current_size = len_max;

	if(pStr != NULL){
		int c = EOF;
		unsigned int i = 0;
		//accept user input until hit enter or end of file
		while (1){
			c = getchar();
			if(c == EOF || c == '\n'){
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
	//start shell
        shell();
	return EXIT_SUCCESS;
}
