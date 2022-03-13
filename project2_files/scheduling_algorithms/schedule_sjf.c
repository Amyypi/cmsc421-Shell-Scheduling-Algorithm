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

void sortedInsert(struct node *newNode){
	//struct node dummy;
	struct node* current;
	current = head;
	//dummy.next = head;

	if(current == NULL){
		printf("current emtpy\n");
	}else if(current->task->burst >  newNode->task->burst){
		//burst is bigger than new node's burst

		newNode->next = head;
		head = newNode;


	}else{
		while(current->next != NULL && current->next->task->burst < newNode->task->burst){
			current = current->next;
		}
		newNode->next = current->next;
		current->next = newNode;
		//head = dummy.next;
	}
}


void add(char *name, int priority, int burst){
        // create a new task and put values into task
        struct task *taskNode;
        taskNode = malloc(sizeof(taskNode) * (5));
        taskNode->name = name;
        taskNode->tid = 0;
        taskNode->priority = priority;
        taskNode->burst = burst;

        //create a new node, and put task in it
        struct node *task_list = malloc(sizeof(struct node));
        task_list->task = taskNode;
        task_list->next = NULL;

        //struct node *temp = head;
	struct node* result = NULL;
	struct node* current = head;
	struct node* next;

        // Add a new node to the linked list, if head == null, make the new node the head
        if(head == NULL){
                task_list->next = head;
                head = task_list;
        }else{
                //traverse until last node and add node at end
                /*
		while(temp->next != NULL){
                        temp = temp->next;
                }
                printf("Inserted task, ");
                printf("[%s] [%d] [%d].\n",taskNode->name, taskNode->priority, taskNode->burst);
                temp->next = task_list;
		*/

		//while(current != NULL){

		//	next = current->next;
			sortedInsert(task_list);
		//	current = next;

		//}
		//head = result;
	}
        printf("\n");
        return;
}

void schedule(){
        printf("\n\n");


	//order based on cpu burst?


///////////////////////////////////////

        // traverse and pass task of each node into run()
        // execute run(Task *task, int slice) from list
        // pass in every node of the list until null
        // Once done, free each node and task

        // print out each task
        struct node *temp;
        temp = head;
        printf("Print list of tasks\n");
        while(temp != NULL){
                run(temp->task, 10);
                temp = temp->next;
        }

        // once done with printing, free all the nodes/tasks and exit
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
