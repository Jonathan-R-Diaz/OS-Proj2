
static int printElevator(){
    char buf[BUFSIZE];
    int len = 0;
    printk("In printElevator()\n");

    len += snprintf("Elevator state: _\n");
    len += snprintf("Current floor: _\n");
    len += snprintf("Current weight: _\n");
    len += snprintf("Elevator status: _\n");
    len += snprintf("Number of passengers: _\n");
    len += snprintf("Number of passengers waiting: _\n");
    len += snprintf("Number passengers serviced: _\n\n");
    
    for (int i = 10; i > 0; i--){
        len += snprintf("[ ] Floor %d:\n", i);
    }

    return len;
}
