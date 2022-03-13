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

void add(char *name, int priority, int burst){

}

void schedule(){

        // traverse and pass task of each node into run()
        // execute run(Task *task, int slice) from list
        // pass in every node of the list until null?
        struct node *temp;
        temp = head;
        while(temp != NULL){
                //find out what slice does
                run(temp->task, int slice) 
                temp = temp->next;

        }


}
