#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//child_t represents child structure 

struct child_t {

//PCB index of one child process
    int child_index;  
    
    struct child_t *next;
};

//Each PCB is a structure consisting of only two fields 
struct pcb_t {
//a PCB index corresponding to the process's creator 
    int parent_index;

//a pointer to a linked list 
    struct child_t *children;
};

struct pcb_t *pcbs[10] = { NULL };
int g_pcb_count = 0;

void create(int p)
{ 
    
// represents the create function executed by process PCB[p]. 
// The function creates a new child process PCB[q] of process PCB[p] 
    struct pcb_t *p_child_pcb;
    struct child_t *p_child, *p_node;


//That's the next line where it'll go next 

    g_pcb_count++;

// allocate a free PCB[q]  
    p_child_pcb = (struct pcb_t *) malloc(sizeof(struct pcb_t));
    pcbs[g_pcb_count] = p_child_pcb;

// record the parent's index, p, in PCB[q] 
    p_child_pcb->parent_index = p;

// initialize the list of children of PCB[q] as empty 
    p_child_pcb->children = NULL;

//create a new link containing the child's index q 
    p_child = (struct child_t *) malloc(sizeof(struct child_t));
    
//The next line adds child's index to list */
    p_child->child_index = g_pcb_count; 
    p_child->next = NULL;
    
//Checks if the list is NULL then we need to make the children point to that child. ONE SPECIAL case

//So that one basically creates the head 

    if (pcbs[p]->children == NULL) {
        pcbs[p]->children = p_child;
    } else {
// Create pointer to head node of parent's `children`... */
        p_node = pcbs[p]->children;

        /* Move node pointer past any existing 'child' nodes... */
        while (p_node->next != NULL) {  /* If 'child' is not NULL then loop... */
            p_node = p_node->next;
        }

        /* append the link to the linked list of PCB[p] */
        p_node->next = p_child;
    }
}

void destroy(int p)
{  /* represents the destroy function executed by process PCB[p].
    * The function recursively destroys all descendent processes
    * (child, grandchild, etc.) of process PCB[p]
    */
    struct child_t *p_next_child;

    /* for each element q on the linked list of children of PCB[p] */
    struct child_t *p_child = pcbs[p]->children;

    /* Loop through list of `children`, if any... */
    while (p_child != NULL) {
        /* destroy(q) recursively destroy all progenies */
        destroy(p_child->child_index);

        /* free PCB[q] */
        free(pcbs[p_child->child_index]);
        pcbs[p_child->child_index] = NULL;
        g_pcb_count--;

        /* deallocate the element q from the linked list */
        p_next_child = p_child->next;
        free(p_child);
        p_child = p_next_child;
    }

    pcbs[p]->children = NULL;
}

int main(void)
{
//clock_t is the structure, clock_start is where it starts and clock_time represents how much time your process is taking
    clock_t clock_start, clock_time;
    double seconds;
    int i;

    pcbs[0] = (struct pcb_t *) malloc(sizeof(struct pcb_t));
    pcbs[0]->parent_index = 0;
    pcbs[0]->children = NULL;

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
