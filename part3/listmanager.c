void addAnimal(struct passenger* animal, struct list_head *head){
    list_add_tail(animal -> list_node, head);
}

struct passenger* floorAssigner(struct passenger* animal, int floor){
    animal -> dest = floor;
    return animal;
}

void getLizard(void){
    struct passenger* lizard = kmalloc(sizeof(struct passenger), GFP_KERNEL);
    lizard -> type = 'L';
    lizard -> weight = 5;
    return lizard;
}

void getCat(void){
    struct passenger* cat = kmalloc(sizeof(struct passenger), GFP_KERNEL);
    cat -> type = 'C';
    cat -> weight = 15;
    return cat;
}


void getDog(void){
    struct passenger* dog = kmalloc(sizeof(struct passenger), GFP_KERNEL);
    dog -> type = 'C';
    dog -> weight = 15;
    return cat;
}

struct passenger* animalReader(struct passenger* animal){
    if (animal -> type == 'L')
        return floorAssigner(getLizard(), animal -> dest);
    else if (animal -> type == 'C')
        return floorAssigner(getCat(), animal -> dest);
    else if (animal -> type == 'D')
        return floorAssigner(getDog(), animal -> dest);
}
