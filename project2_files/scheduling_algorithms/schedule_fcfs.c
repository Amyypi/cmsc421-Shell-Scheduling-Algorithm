#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>

#include "list.h"
#include "task.h"
#include "schedulers.h"
#include "cpu.h"

// define MIN_PRIORITY 1
// deifne MAX_PRIORITY 10
typedef struct task *task_list = NULL;

struct node *head = NULL;

void add(char *name, int priority, int burst){

//check task->name for insertion etc

	printf("add function executed\n");
	task *taskNode;
	taskNode = (task*)malloc(sizeof(taskNode));
	taskNode->name = name;
	taskNode->tid = NULL;
	taskNode->priority = priority;
	taskNode->burst = burst;
	printf("Successful new task added in\n");

	printf("make new task_list node\n");
	//add task to the list
	struct node *task_list = malloc(sizeof(struct node));
	task_list->task = taskNode;
	task_list->next = NULL;
	printf("Successful task_list node made\n");

	printf("Before adding node to head list\n");
	//
	if(head == NULL){
		printf("make new node head\n");
		*head = task_list;
		head->next = NULL;
		printf("Successful head node\n");
	}else{
		printf("Add node to the end of the list\n");
		struct node *temp = head;

		//traverse until last node and add node at end
		do{
			if(temp->next != NULL){
				printf("added task to task list success\n");
				temp->next = task_list;
				temp->next->next = NULL;
			}
			temp=temp->next;
		}while(temp->next != NULL);
		printf("Successful node added at the end of list - add()\n");
		free(temp);
	}

}

void schedule(){


	
	//do algorithm

	// loop - make new list of ordered algorithm
	// execute list.h
	// void insert(struct node **head, Task *task);
        	//add a new task to the list of tasks
	// void delete(struct node **head, Task *task); 
        	//delete the selected task from the list
	// void traverse(struct node *head); 
        	//traverse the list


///////////////////////////////////////

	// traverse and pass task of each node into run()
        // execute run(Task *task, int slice) from list
        // pass in every node of the list until null?

	printf("Schedule exectued\n");
	// assign node list to this
	struct node *temp;
	temp = head;
	printf("Before traversing through list schedule()\n");
	while(temp != NULL){
		//find out what slice does
		run(temp->task, 5)
		temp = temp->next;
	}
	printf("Successful traverse list print, freeing node and exit\n");
	free(temp);
	free(head);
}
