char* currentState(int state){
    if (state == 0)
        return "OFFLINE";
    if (state == 1)
        return "IDLE";
    if (state == 2)
        return "LOADING";
    if (state == 3)
        return "UP";
    if (state == 4)
        return "DOWN";

    return NULL;
}

static ssize_t printElevator(char *buf){
    int len = 0;
    // Print Stats 
    len += snprintf(buf, BUFSIZE, "\nElevator state: %s\n", currentState(STATE));
    len += snprintf(buf + len, BUFSIZE - len, "Current floor: %d\n", FLOOR);
    len += snprintf(buf + len, BUFSIZE - len, "Current weight: %d\n", WEIGHT);
    len += snprintf(buf + len, BUFSIZE - len, "Elevator status: _\n"); //fuck
    len += snprintf(buf + len, BUFSIZE - len, "Number of passengers: %d\n", PASSENGERS);
    len += snprintf(buf + len, BUFSIZE - len, "Number of passengers waiting: _\n");
    len += snprintf(buf + len, BUFSIZE - len, "Number passengers serviced: %d\n\n", SERVICED);
    
    // Floors
    for (int i = 9; i >= 0; i--){
        len += snprintf(buf + len, BUFSIZE - len, "[ ] Floor %d:\n", i);
        //printk(KERN_DEBUG "[DEBUG] len: %d, buf: %s", len, buf);
    }

    len += snprintf(buf + len, BUFSIZE - len, "\n");
    
    return len;
}
