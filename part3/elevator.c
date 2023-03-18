#include <linux/module.h>	/* Needed by all modules */
#include <linux/moduleparam.h>
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/init.h>     /* Needed for __init and __exit */

#include <linux/proc_fs.h>
#include <asm/uaccess.h>

#include "elevator.c"

#define DRIVER_LICENSE "GPL"
#define DRIVER_AUTHOR "Jonathan Diaz <jrd17j@fsu.edu>"
#define DRIVER_DESC   "Elevator Module"

#define PROC_NAME "elevator"
#define BUFSIZE 256

//Initalization of elevator

#include "proc_ops.c"
#include "printfunctions.c"
