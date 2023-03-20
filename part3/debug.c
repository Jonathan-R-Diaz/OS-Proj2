
void addLizard(struct passenger_list *list){
    struct passenger lizard = {.type = 'L', .weight = 5, .dest = 9, };
    struct passenger* curr = list -> first;
    curr = curr -> next;
    while (curr -> next -> type != 'E'){
        curr = curr -> next;
    }
    insert(curr, &lizard);
}
