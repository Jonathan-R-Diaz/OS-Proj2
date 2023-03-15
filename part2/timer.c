#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/init.h>     /* Needed for __init and __exit */
#include <linux/time.h>

#define DRIVER_LICENSE "GPL"
#define DRIVER_AUTHOR "Jonathan Diaz <jrd17j@fsu.edu>"
#define DRIVER_DESC   "Timer module"

void current_kernel_time()
{
    printk(KERN_INFO "In current_kernel_time()");
    printk(KERN_INFO "Leaving current_kernel_time()");
}

static int __init my_timer_init(void)
{
	printk(KERN_INFO "Starting timer\n");
    current_kernel_time();
	/* 
	 * A non 0 return means init_module failed; module can't be loaded. 
	 */
	return 0;
}

static void __exit my_timer_exit(void)
{
	printk(KERN_INFO "elapsed time: \n");
}

module_init(my_timer_init);
module_exit(my_timer_exit);

MODULE_LICENSE(DRIVER_LICENSE);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
