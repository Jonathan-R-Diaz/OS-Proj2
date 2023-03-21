#include <linux/module.h>	/* Needed by all modules */
#include <linux/moduleparam.h>
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/init.h>     /* Needed for __init and __exit */
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/list.h>

#define DRIVER_LICENSE "GPL"
#define DRIVER_AUTHOR "Jonathan Diaz <jrd17j@fsu.edu>"
#define DRIVER_DESC   "Elevator Module"
#define PROC_NAME "elevator"

#define BUFSIZE 4098

#define MAX_FLOORS 10
#define MAX_WEIGHT 100


// Passengers
typedef struct {
    char type;
    int dest;
    int weight;
    struct list_head list;
} passenger;

typedef struct {
    passenger pass;
    struct list_head list;
} passenger_list;

// Floors
passenger_list floors[MAX_FLOORS];

// Elevator
enum STATES {OFFLINE, IDLE, LOADING, UP, DOWN};
unsigned int STATE;
unsigned int FLOOR = 0;
unsigned int WEIGHT = 0;
passenger_list elevator_list;
unsigned int PASSENGERS = 0;
unsigned int SERVICED = 0;

#include "mylist.c"

void init(void){
    STATE = OFFLINE;
    
    // Elevator list initializer
    LIST_HEAD(&elevator_list);
     
    // Floors array initializer
    for (int i = 0; i < MAX_FLOORS; i++){
        LIST_HEAD(floors[i]);
    }
}

#include "printfunctions.c"
#include "proc_ops.c"
