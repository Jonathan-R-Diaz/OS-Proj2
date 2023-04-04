int rng(int lower, int upper){
    int num;
    get_random_bytes(&num, sizeof(num));
    return ((num % ++upper) + lower);
}

void testcase2(int num){
    
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
        long ret = issue_processor(start, dest, type);
        printk(KERN_DEBUG "Issue (%d, %d, %d) returned %ld\n", start, dest, type, ret);
    }
    printk(KERN_DEBUG "out of testcase(%d)\n", num);
}
