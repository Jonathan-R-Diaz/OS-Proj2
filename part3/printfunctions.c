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

static ssize_t elevator_status(char *buf, int len){
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

    len += snprintf(buf + len, BUFSIZE - len, "Elevator status: %d L, %d C, %d D\n", l, c, d);
    return len;
}

static ssize_t printStat(char* buf, int len, char* str, int num){
    return snprintf(buf + len, BUFSIZE - len, "%s: %d\n", str, num);
}

static ssize_t printList(char* buf, int len, struct passenger* start){

    struct passenger* curr = start -> next;
    while(curr -> type != 'E'){
        len += snprintf(buf + len, BUFSIZE - len, "%c", curr -> type);
        if (curr -> next -> type != 'E')
            len += snprintf(buf + len, BUFSIZE - len, ", ");
    }
    return len;
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
    len += elevator_status(buf, len);
    len += printStat(buf, len, "Number of passengers", PASSENGERS);
    len += snprintf(buf + len, BUFSIZE - len, "Number of passengers waiting: %d\n", totalWaiting());
    len += printStat(buf, len, "Number of passengers serviced", SERVICED);
    
    // Floors
    for (int i = MAX_FLOORS - 1; i >= 0; i--){
        len += snprintf(buf + len, BUFSIZE - len, "[ ] Floor %d: %d ", i, size(&floors[i]));
        len += snprintf(buf + len, BUFSIZE - len, "\n");
        //printk(KERN_DEBUG "[DEBUG] len: %d, buf: %s", len, buf);
    }

    len += snprintf(buf + len, BUFSIZE - len, "\n");
    
    return len;
}
