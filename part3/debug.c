
void addLizard(struct list_head *head){
    struct passenger* lizard = kmalloc(sizeof(struct passenger*), GFP_KERNEL);
    lizard -> type = 'L';
    lizard -> dest = 100;
    lizard -> weight = 5;
    list_add_tail(&lizard -> list_node, head);
}

void testcase1(void){
    for (int i = 0; i < MAX_FLOORS; i++){
        addLizard(&floors[i]);
    }
}
