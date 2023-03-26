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

static ssize_t elevator_status(char *buf, int len, struct list_head* head){
    printk(KERN_DEBUG "in elevator_status()\n");

    int l = 0, c = 0, d = 0;

    struct passenger *pass;
    struct list_head *pos;

    list_for_each(pos, head){
        if (pass -> type == 'L')
            l++;
        if (pass -> type == 'C')
            c++;
        if (pass -> type == 'D')
            d++;
    }

    len += snprintf(buf + len, BUFSIZE - len, "Elevator status: %d L, %d C, %d D\n", l, c, d);
    printk(KERN_DEBUG "leaving elevator_status()\n");
    return len;
}

static ssize_t printStat(char* buf, int len, char* str, int num){
    return snprintf(buf + len, BUFSIZE - len, "%s: %d\n", str, num);
}

static ssize_t printList(char* buf, int len, struct list_head* head){
    struct passenger *pass;
    struct list_head *pos;

    list_for_each(pos, head){
        pass = list_entry(pos, struct passenger, list_node);
        len += snprintf(buf + len, BUFSIZE - len, "%c ", pass -> type);
    }

    return len;
}

int size(struct list_head* head){
    int size = 0;
    struct list_head *pos;
    list_for_each(pos, head){
        size++;
    }
    return size;
}

int totalWaiting(void){
    int total = 0;
    for (int i = 0; i < MAX_FLOORS - 1; i++){
        total += size(&floors[i]);
    }
    return total;
}

static ssize_t printElevator(char* buf){
    int len = 0;
    
    // Print Stats 
    len += snprintf(buf, BUFSIZE, "\nElevator state: %s\n", currentState(STATE));
    len += printStat(buf, len, "Current floor", FLOOR); 
    len += printStat(buf, len, "Current weight", WEIGHT);
    len += elevator_status(buf, len, &elevator_list);
    len += printStat(buf, len, "Number of passengers", PASSENGERS);
    len += snprintf(buf + len, BUFSIZE - len, "Number of passengers waiting: %d\n", totalWaiting());
    len += printStat(buf, len, "Number of passengers serviced", SERVICED);
    
    // Floors
    for (int i = MAX_FLOORS - 1; i >= 0; i--){
        printk(KERN_DEBUG "TOP OF FOR LOOP len: %d\n", len);
        //Implement this too
        if (i == FLOOR)
            len += snprintf(buf + len, BUFSIZE - len, "[*] Floor %d: %d ", i, size(&floors[i]));
        else
            len += snprintf(buf + len, BUFSIZE - len, "[ ] Floor %d: %d ", i, size(&floors[i]));
        //Implement this
        printk(KERN_DEBUG "len before printList (leaving FOR LOOP): %d\n", len);
        len = printList(buf, len, &floors[i]);
        printk(KERN_DEBUG "len after printList: %d\n", len);
        len += snprintf(buf + len, BUFSIZE - len, "\n");
        printk(KERN_DEBUG "len end: %d\n", len);
        //printk(KERN_DEBUG "[DEBUG] len: %d, buf: %s", len, buf);
    }

    // Build dudes, test print functions

    len += snprintf(buf + len, BUFSIZE - len, "\n");
    
    return len;
}
