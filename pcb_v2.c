#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct pcb_t {

//each PCB contains the 4 integer fields */
    int parent;  /* a PCB index corresponding to the process's creator*/

    int first_child;
    int older_sibling;
    int younger_sibling;
};

// Create PCBs array (size n)
struct pcb_t *pcbs[10];

//Count of PCBs to use for index when creating new pcb in `pcbs[]`
int pcb_q_index = 0;

void create(int p)
{ 
//represents the create function executed by process PCB[p]. 
// The function creates a new child process PCB[q] of process PCB[p] 
    struct pcb_t *p_pcb_q;
    int younger_sibling, youngest_sibling = -1;

//Increment process number... 
    pcb_q_index++;

//allocate a free PCB[q] 
    p_pcb_q = (struct pcb_t *) malloc(sizeof(struct pcb_t));
    pcbs[pcb_q_index] = p_pcb_q;

// record the parent's index, p, in PCB[q] 
    p_pcb_q->parent = p;

// initialize child of PCB[q] as empty 
    p_pcb_q->first_child = -1;
    p_pcb_q->younger_sibling = -1;

// create a new link containing the child's index q 

// If parent has a child...
    if (pcbs[p]->first_child > 0) {
//Create a pointer to that child's younger sibling's index (if any)... 
        youngest_sibling = pcbs[p]->first_child;
        younger_sibling = pcbs[pcbs[p]->first_child]->younger_sibling;
        while ( younger_sibling > 0) {
                youngest_sibling = younger_sibling;
                younger_sibling = pcbs[younger_sibling]->younger_sibling;
        }

// Get youngest sibling's pcb from `pcbs` array and give it our index...
        if (youngest_sibling != -1) {
            pcbs[youngest_sibling]->younger_sibling = pcb_q_index;
        }

// Set our older sibling to the previously youngest sibling... 
        p_pcb_q->older_sibling = youngest_sibling;

    } else { 
    
// Otherwise, if no `first_child` on parent... 
//Set us as parent's first child... 
        pcbs[p]->first_child = pcb_q_index;

// And therfore, we don't have any older siblings... 
        p_pcb_q->older_sibling = -1;
    }
}

void destroy(int p)
{  

// represents the destroy function executed by process PCB[p].
// The function recursively destroys all descendent processes
// (child, grandchild, etc.) of process PCB[p]


// for `first_child` of PCB[p] 

// Recurse `first_child` if it exists
//  by calling `destroy()` on `first_child`... 
    if (pcbs[p]->first_child > 0) {
// destroy(q) recursively destroy all progenies (aka. children, decendents) 
// If (yes) there are children then follow arrow to drill (recursively)
// into them...
         
        destroy(pcbs[p]->first_child);

// free PCB[q] 
        free(pcbs[pcbs[p]->first_child]);

// deallocate the element q from the linked list 
        pcbs[p]->first_child = -1;

//  Decrement pcb index count...
        pcb_q_index--;
    }

// After that, check if we have a `younger_sibling`
// if we do then recurse to destroy any of its children & siblings... */
    if (pcbs[p]->younger_sibling > 0) {
// destroy(q) recursively destroy all progenies */
// If (yes) there is a younger sibling then follow arrow to drill (recursively)
// into it...
         
        destroy(pcbs[p]->younger_sibling);

// After destroying the younger_sibling's children & siblings, if any,
// then free PCB[q] 
        free(pcbs[pcbs[p]->younger_sibling]);

// deallocate the element q from the linked list
        pcbs[p]->younger_sibling = -1;

// Decrement pcb index count... 
        pcb_q_index--;
    }

/* ...The two IF blocks, above, will keep pausing the current function saving its place, and calling itself again (with first_child and younger_sibling)
     * until it reaches the far ends (ie. leaves) of the process tree...
     * Then it finally starts running the stuff just below the `destroy()` call
     * to free the memory (that was allocated, with `malloc()`, in `create()`)
     * and remove (ie. empty) the PCBs array element (by replacing it with `-1`)...
     */
}

int main(void)
{
    clock_t clock_start, clock_time;
    double seconds;
    int i;

    pcbs[0] = (struct pcb_t *) malloc(sizeof(struct pcb_t));
    pcbs[0]->parent = -1;
    pcbs[0]->first_child = -1;
    pcbs[0]->younger_sibling = -1;
    pcbs[0]->older_sibling = -1;

    //How long the process has been running?
    for (int n = 0; n < 10000; n++) {
        clock_start = clock();
    
        for (i = 0; i < 1000; i++) {
            create(0);   /* creates 1st child of PCB[0] at PCB[1] */
            create(0);   /* creates 2nd child of PCB[0] at PCB[2] */
            create(2);   /* creates 1st child of PCB[2] at PCB[3] */
            create(0);   /* creates 3rd child of PCB[0] at PCB[4] */
            destroy(0);  /* destroys all descendents of PCB[0],
                          * which includes processes PCB[1] through PCB[4]
                          */
        }
    
        clock_time = clock() - clock_start;
        seconds = (double)clock_time / CLOCKS_PER_SEC;
        
        printf("%f\n", seconds);
        //printf("It took %f seconds of CPU time to run the functions %d times.\n", seconds, i);
    }

    return 0;
}

