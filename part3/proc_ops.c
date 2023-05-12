static struct proc_dir_entry *entry;

extern long (*STUB_start_elevator)(void);
extern long (*STUB_issue_request)(int, int, int);
extern long (*STUB_stop_elevator)(void);

static ssize_t myread(struct file *file, char *ubuf, size_t count, loff_t *ppos)
{
    char buf[BUFSIZE];
    int len = 0;
    printk(KERN_DEBUG "read handler\n");

    if(*ppos > 0 || count < BUFSIZE){ return 0; }
    
    len = printElevator(buf);

    // Kernel space to user space
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

static struct proc_ops myops = 
{
    .proc_read = myread,
    .proc_write = mywrite,
};

static int __init elevator_init(void)
{
    STUB_start_elevator = start_elevator;
    STUB_issue_request = issue_request;
    STUB_stop_elevator = stop_elevator;
    entry = proc_create(PROC_NAME, 0660, NULL, &myops);
    printk(KERN_INFO "/proc/%s created\n", PROC_NAME);
    return init();
}

static void __exit elevator_exit(void)
{
    printk(KERN_INFO "/proc/%s DELETED\n", PROC_NAME);
    proc_remove(entry);
}

module_init(elevator_init);
module_exit(elevator_exit);

MODULE_LICENSE(DRIVER_LICENSE);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
