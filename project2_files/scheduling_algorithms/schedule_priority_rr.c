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
#define TIME_QUANTUM 10;
struct node *head;

void sortedInsert(struct node *newNode){
        struct node* current;
        current = head;

        if(current == NULL){
                //node should've been assigned to be head in add(), if not here - then its a error
                printf("error: current node emtpy\n");
        }else if(current->task->burst >  newNode->task->burst){
                //if head is not empty, and newNode's burst is lower than the first node,
                //        move newNode to be the new head
                newNode->next = head;
                head = newNode;
        }else{
                //traverse through the list until it hits next node is null or node's burst
                //        is higher than the newNode's burst
                while(current->next != NULL && current->next->task->burst < newNode->task->burst){
                        current = current->next;
                }
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

        //struct node *temp = head;
        struct node* result = NULL;
        struct node* current = head;
        struct node* next;

        // Add a new node to the linked list, if head == null, make the new node the head
        if(head == NULL){
                task_list->next = head;
                head = task_list;
        }else{
                //put the taskNode in the proper order position in the linked list based on priority
                sortedInsert(task_list);
        }
        //printf("\n");
        return;
}

void schedule(){
        unsigned int time_quantum = 10;
        unsigned int count = 0, j=0, n=0, remain=0, flag=0;
        unsigned int time = 0;
        unsigned int task_counter = 0;
        unsigned int num = 0;
	char *temp_name;

        //traverse through list to know # of tasks
        struct node *temp;
        temp= head;
        while(temp !=NULL){
                printf("temp traverse for task_counter\n");
                task_counter++;
                temp = temp->next;
        }
        remain = task_counter;

	//at[] -> arrival
	//pt[] -> priority
	//bt[] -> burst
	//task_name[] -> task name
        unsigned int at[remain],pt[remain], bt[remain],rt[remain];
	char *task_name[remain];

        printf("Enter inializing at,bt,rt\n");
        for(count=0;count<remain;count++){
                at[count] = 0;
                bt[count] = 0;
                rt[count] = 0;
		pt[count] = 0;
        }
	temp=head;
        for(count=0;count<remain;count++){
                num = (unsigned int)(temp->task->burst);
		temp_name = (char *)(temp->task->name);
		task_name[count] = temp_name;
                bt[count] = num;
                rt[count] = num;
		pt[count] = (unsigned int)(temp->task->priority);
                at[count] = 0;
                temp = temp->next;
        }

        printf("Before rr calc\n");
	printf("Task name | Priority | turnaround time | Waiting time\n");
        //do RR scheduling calculations
        for(time=0,count=0;remain!=0;){
                if(rt[count]<=time_quantum && rt[count]>0){
                        time+=rt[count];
                        rt[count]=0;
                        flag=1;
                }else if(rt[count]>0){
                        rt[count]-=time_quantum;
                        time+=time_quantum;
                }
                if(rt[count]==0 && flag==1){
                        remain--;
                        printf("%s\t|\t%d\t|\t%d\t|\t%d\n", task_name[count],pt[count],time-at[count],time-at[count]-bt[count]);
                        flag=0;
                }
                if(count==task_counter-1){
                        count=0;
                }else if(at[count+1]<=time){
                        count++;
                }else{
                        count=0;
                }
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
