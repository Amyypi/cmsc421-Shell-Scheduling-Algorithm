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
 struct node* current;
        current = head;
        int nodeAdded = 1;           // task is intialize with 1, if newNode is added to the list -
                                     //     it will turn into 0 to stop while loop

        if(current == NULL){
                //node should've been assigned to be head in add(), if not here - then its a error
                printf("error: current node emtpy\n");
        }else if(current == head && current->task->burst > newNode->task->burst){
                //if head is not empty, and newNode's burst is lower than the first node,
                //        move newNode to be the new head
                newNode->next = head;
                head = newNode;
                printf("Task made as new head ");
                printf("[%s] [%d] [%d]\n",newNode->task->name, newNode->task->priority, newNode->task->burst);

        }else{
                //traverse through the list until it hits next node is null or node's burst
                //        is higher than the newNode's burst
                while(nodeAdded != 0 && current->next != NULL && current->task->burst <= newNode->task->burst){
                        //if priority is the same as the newNode's, add newNode to the end of the same priority list
                        if(current->task->burst == newNode->task->burst){
                                printf("Encountered a task with the same priority, this will be added at the end of the same priority list\n");
				while(current->next != NULL && current->next->task->burst == newNode->task->burst){
                                        current = current->next;
                                }
                                nodeAdded = 0;
                        }else{
                                //just regular traverse through list
                                current = current->next;
                        }
                }
		                printf("Inserted task, ");
                printf("[%s] [%d] [%d] ",newNode->task->name, newNode->task->priority, newNode->task->burst);
                printf("after, ");
                printf("[%s] [%d] [%d].\n",current->task->name, current->task->priority, current->task->burst);
                newNode->next = current->next;
                current->next = newNode;
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

        // Add a new node to the linked list, if head == null, make the new node the head
        if(head == NULL){
		printf("If priority are the same, algorithm will follow a first come, first served basis\n\n");
                task_list->next = head;
                head = task_list;
		printf("Inserted task as head, ");
                printf("[%s] [%d] [%d].\n",taskNode->name, taskNode->priority, taskNode->burst);

        }else{
                //insert the node in the linked list based on the burst number
		//      in increasing order
		sortedInsert(task_list);
	}
        return;
}

void schedule(){
        printf("\n\n");

	printf("List shown in the order of CPU burst(increasing order)\n");
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
                run(temp->task, temp->task->burst);
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
