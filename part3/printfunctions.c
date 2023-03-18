
static ssize_t printElevator(char *buf){
    int len = 0;
    // Print Stats 
    len += snprintf(buf, BUFSIZE, "\nElevator state: _\n");
    len += snprintf(buf + len, BUFSIZE - len, "Current floor: _\n");
    len += snprintf(buf + len, BUFSIZE - len, "Current weight: _\n");
    len += snprintf(buf + len, BUFSIZE - len, "Elevator status: _\n");
    len += snprintf(buf + len, BUFSIZE - len, "Number of passengers: _\n");
    len += snprintf(buf + len, BUFSIZE - len, "Number of passengers waiting: _\n");
    len += snprintf(buf + len, BUFSIZE - len, "Number passengers serviced: _\n\n");
    
    // Floors
    for (int i = 9; i >= 0; i--){
        len += snprintf(buf + len, BUFSIZE - len, "[ ] Floor %d:\n", i);
        printk(KERN_DEBUG "[DEBUG] len: %d, buf: %s", len, buf);
    }

    len += snprintf(buf + len, BUFSIZE - len, "\n");
    
    return len;
}
