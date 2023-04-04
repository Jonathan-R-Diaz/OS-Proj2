#include <linux/module.h>	/* Needed by all modules */
#include <linux/moduleparam.h>
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/init.h>     /* Needed for __init and __exit */
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/list.h>
#include <linux/random.h>

#define DRIVER_LICENSE "GPL"
#define DRIVER_AUTHOR "Jonathan Diaz <jrd17j@fsu.edu>"
#define DRIVER_DESC   "Elevator Module"
#define PROC_NAME "elevator"

#define BUFSIZE 4098

#define MAX_FLOORS 10
#define MAX_WEIGHT 100


// Passengers
typedef struct passenger{
    char type;
    int dest;
    int weight;
    struct list_head list_node;
} passenger;

// Lists
struct list_head elevator_list;
struct list_head floors[MAX_FLOORS];

// Elevator
enum STATES {OFFLINE, IDLE, LOADING, UP, DOWN};
unsigned int STATE;
unsigned int FLOOR = 0;
unsigned int WEIGHT = 0;
unsigned int PASSENGERS = 0;
unsigned int SERVICED = 0;

#include "listmanager.c"
#include "tests.c"

static int init(void){
    STATE = OFFLINE;
    
    // Elevator list initializer
    INIT_LIST_HEAD(&elevator_list);
     
    // Floors array initializer
    for (int i = 0; i < MAX_FLOORS; i++){
        INIT_LIST_HEAD(&floors[i]);
    }

    testcase2(100);
    return 0;
}

static void cleanup_elevator(void){
    
    for (int i = 0; i < MAX_FLOORS; i++) {
        // free each passenger node in each floor
        struct passenger *pass;
        struct list_head *pos, *q;
        list_for_each_safe(pos, q, &floors[i]) {
            pass = list_entry(pos, struct passenger, list_node);
            list_del(pos);
            kfree(pass);
        }
    }

    // clean up the elevator list
    struct passenger *pass;
    struct list_head *pos, *q;
    list_for_each_safe(pos, q, &elevator_list) {
        pass = list_entry(pos, struct passenger, list_node);
        list_del(pos);
        kfree(pass);
    }
}

#include "printfunctions.c"
#include "proc_ops.c"
