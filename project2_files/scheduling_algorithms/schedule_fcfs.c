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
struct node *head;

void add(char *name, int priority, int burst){

//check task->name for insertion etc

	//printf("add function executed\n");
	struct task *taskNode;
	taskNode = malloc(sizeof(taskNode) * (5));
	taskNode->name = name;
	taskNode->tid = 0;
	taskNode->priority = priority;
	taskNode->burst = burst;
	//printf("Successful new task added in\n");

	//printf("make new task_list node\n");
	//add task to the list
	struct node *task_list = malloc(sizeof(struct node));
	task_list->task = taskNode;
	task_list->next = NULL;
	//printf("Successful task_list node made\n");

	struct node *temp = head;

	//printf("Before adding node to head list\n");
	//
	if(head == NULL){
		//printf("make new node head\n");
		task_list->next = head;
		head = task_list;
		//head->next = NULL;
		//printf("Successful head node\n");
	}else{
		//printf("Add node to the end of the list\n");
		//struct node *temp;
		//temp = head;

		//traverse until last node and add node at end
		while(temp->next != NULL){
			temp = temp->next;
		}
		printf("Inserted task, ");
		printf("[%s] [%d] [%d].\n",taskNode->name, taskNode->priority, taskNode->burst);
		temp->next = task_list;

		//printf("Successful node added at the end of list - add()\n");

	}
	//free(temp);
	printf("\n");
	return;
}

void schedule(){


	printf("\n\n");
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
        // pass in every node of the list until null
	// Once done, free each node and task

	// assign node list to this
	struct node *temp;
	temp = head;
	printf("Print list of tasks\n");
	while(temp != NULL){
		run(temp->task, 10);
		temp = temp->next;
	}

	printf("Successful traverse list print, freeing node and exit\n");
	struct task *task_temp;
	temp = head;
	while(head != NULL){
		temp = head;
		task_temp = temp->task;
		head = head->next;
		free(task_temp);
		free(temp);
	}

}
