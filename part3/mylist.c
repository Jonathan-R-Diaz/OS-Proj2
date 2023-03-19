static void insert(struct passenger* prev, struct passenger* newNode){
    struct passenger* ptr = prev -> next;
    prev -> next = newNode;
    newNode -> next = ptr;
}

void remove(struct passenger* prev, struct passenger* del){
    prev -> next = del -> next;
    del = del -> next;
}

void unloadAll(struct passenger* head, int level){
    struct passenger* prev = head;
    struct passenger* curr = head -> next;
    while (curr != NULL && curr -> type != 'E'){
        if (curr -> dest == level){
            remove(prev, curr);
        }
        curr = curr -> next;
    }
}

int size(struct passenger_list* list){
    int size = 0;
    struct passenger* curr = list -> first;
    curr = curr -> next;
    while (curr != NULL && curr -> type != 'E'){
        size++;
        curr = curr -> next;
    }
    return size;
}

void list_init(struct passenger_list* node){ 
    struct passenger start = {
        .type = 'F',
        .dest = -1,
        .weight = 0,
    };
    struct passenger end = {
         .type = 'E', 
         .dest = -1,
         .weight = 0,
    };

    node -> first = &start;
    node -> first -> next = &end;
}
