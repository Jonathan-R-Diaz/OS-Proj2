#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/syscalls.h>

/* System call stub */
long (*STUB_start_elevator)(void) = NULL;
EXPORT_SYMBOL(STUB_start_elevator);

long (*STUB_issue_request)(int, int, int) = NULL;
EXPORT_SYMBOL(STUB_issue_request);

long (*STUB_stop_elevator)(void) = NULL;
EXPORT_SYMBOL(STUB_stop_elevator);

SYSCALL_DEFINE0(start_elevator){
	printk(KERN_NOTICE "Starting elevator");
	
	if (STUB_start_elevator != NULL)
		return STUB_start_elevator(start_elevator);
	else
		return -ENOSYS;
}

SYSCALL_DEFINE3(issue_request, int, start, int, dest, int, type){
	printk(KERN_NOTICE "Starting elevator");
	
	if (STUB_start_elevator != NULL)
		return STUB_issue_request(issue_request, start, dest, type);
	else
		return -ENOSYS;
}

SYSCALL_DEFINE0(stop_elevator){
	printk(KERN_NOTICE "Starting elevator");
	
	if (STUB_start_elevator != NULL)
		return STUB_stop_elevator(stop_elevator);
	else
		return -ENOSYS;
}
