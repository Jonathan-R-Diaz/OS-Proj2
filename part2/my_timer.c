#include <linux/module.h>	/* Needed by all modules */
#include <linux/moduleparam.h>
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/init.h>     /* Needed for __init and __exit */

#include <linux/proc_fs.h>
#include <asm/uaccess.h>

#include <linux/time64.h>
#include <linux/timekeeping.h>

#define DRIVER_LICENSE "GPL"
#define DRIVER_AUTHOR "Jonathan Diaz <jrd17j@fsu.edu>"
#define DRIVER_DESC   "Timer Module"

#define PROC_NAME "timer"
#define BUFSIZE 256

static struct proc_dir_entry *entry;
static struct timespec *ts;

static time64_t current_kernel_time(void)
{
    time64_t ret = ktime_get_seconds();
    return ret;
}

static ssize_t myread(struct file *file, char *ubuf, size_t count, loff_t *ppos)
{
    char buf[BUFSIZE];
    int len = 0;
    printk(KERN_DEBUG "read handler\n");

    if(*ppos > 0 || count < BUFSIZE) return 0;

    //len += sprintf(buf, "irq = %d\n", irq);
    //len += sprintf(buf + len, "mode = %d\n", mode);

    if (copy_to_user(ubuf, buf, len))
        return -EFAULT;

    *ppos = len;

    return len;
}

static ssize_t mywrite(struct file *file, const char __user *ubuf, size_t count, loff_t *ppos)
{
    printk(KERN_DEBUG "write handler\n");
    return -1;
} 

static int myopen(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "Im gonna jump off a cliff\n");
    return 0;
}

static struct proc_ops myops = 
{
    .proc_read = myread,
    .proc_write = mywrite,
    .proc_open = myopen,
};

static int __init my_timer_init(void)
{
	entry = proc_create(PROC_NAME, 0660, NULL, &myops);
    printk(KERN_INFO "/proc/%s created\n", PROC_NAME);
    return 0;
}

static void __exit my_timer_exit(void)
{
	printk(KERN_INFO "elapsed time: \n");
    printk(KERN_INFO "/proc/%s deleted\n", PROC_NAME);
    proc_remove(entry);
}

module_init(my_timer_init);
module_exit(my_timer_exit);

MODULE_LICENSE(DRIVER_LICENSE);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
