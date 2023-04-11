int rng(int lower, int upper){
    int num;
    get_random_bytes(&num, sizeof(num));
    int ret = abs((num % ++upper) + lower);
    printk(KERN_DEBUG "random num: %d\n", ret);
    return ret;
}

void testcase2(int num){
   
    printk(KERN_DEBUG "in testcase2\n"); 
    int type;
    int start;
    int dest;
    int i;
    for(i = 0; i < num; i+=1)
    {
        type = rng(0,2);
        start = rng(0, 10);
        do {
            dest = rng(1, 10);
        } while(dest == start);
        int ret = issue_processor(start, dest, type);
        printk(KERN_DEBUG "Issue (%d, %d, %d) returned %ld\n", start, dest, type, ret);
    }
    printk(KERN_DEBUG "out of testcase2(%d)\n", num);
}

void testcase3(int num){
    // Load elevator
    printk(KERN_DEBUG "in testcase3\n"); 
    int type;
    int start;
    int dest;
    int i;
    for(i = 0; i < num; i+=1)
    {
        type = rng(0,2);
        start = 1;
        do {
            dest = 2;
        } while(dest == start);
        int ret = issue_processor(start, dest, type);
        printk(KERN_DEBUG "Issue (%d, %d, %d) returned %ld\n", start, dest, type, ret);
    }
    while (!list_empty(&floors[0]) || !list_empty(&elevator_list)) {
        load_elevator(&floors[0]);
        FLOOR++;
        deload_elevator(FLOOR);
        printk(KERN_DEBUG "out of testcase3(%d)\n", num);
        FLOOR--;
    }
}
