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

static ssize_t elevator_status(char *buf, int *len){
    int l = 0, c = 0, d = 0;

    struct passenger *pass = elevator_list.first;

    while (pass != NULL){
        if (pass -> type == 'L')
            l++;
        if (pass -> type == 'C')
            c++;
        if (pass -> type == 'D')
            d++;
        pass = pass -> next;
    }

    len += snprintf(buf + *len, BUFSIZE - *len, "Elevator status: %d L, %d C, %d D\n", l, c, d);
    return len;
}

static ssize_t printStat(char* buf, int* len, char* str, int num){
    len += snprintf(buf + *len, BUFSIZE - *len, "%s: %d\n", num);
    return len;
}

static ssize_t printElevator(char* buf){
    int len = 0;
    // Print Stats 
    len += snprintf(buf, BUFSIZE, "\nElevator state: %s\n", currentState(STATE));
    printStat(buf, len, "Current floor:", FLOOR); 
    //len += snprintf(buf + len, BUFSIZE - len, "Current floor: %d\n", FLOOR);
    printStat(buf, len, "Current weight:", WEIGHT);
    //len += snprintf(buf + len, BUFSIZE - len, "Current weight: %d\n", WEIGHT);
    len += elevator_status(buf, len);
    //len += snprintf(buf + len, BUFSIZE - len, "Number of passengers: %d\n", PASSENGERS); 
    printStat(buf, &len, "Number of passengers:", PASSENGERS);
    len += snprintf(buf + len, BUFSIZE - len, "Number of passengers waiting: _\n");
    //len += snprintf(buf + len, BUFSIZE - len, "Number passengers serviced: %d\n\n", SERVICED);
    printStat(buf, len, "Number of passengers serviced:", SERVICED);
    
    // Floors
    for (int i = 9; i >= 0; i--){
        len += snprintf(buf + len, BUFSIZE - len, "[ ] Floor %d:\n", i);
        //printk(KERN_DEBUG "[DEBUG] len: %d, buf: %s", len, buf);
    }

    len += snprintf(buf + len, BUFSIZE - len, "\n");
    
    return len;
}
