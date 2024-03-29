void addAnimal(struct passenger* animal, struct list_head *head){
    list_add_tail(&animal -> list_node, head);
}

struct passenger* floorAssigner(struct passenger* animal, int floor){
    animal -> dest = floor;
    return animal;
}

struct passenger* getLizard(void){
    struct passenger* lizard = kmalloc(sizeof(struct passenger), GFP_KERNEL);
    lizard -> type = 'L';
    lizard -> weight = 5;
    return lizard;
}

struct passenger* getCat(void){
    struct passenger* cat = kmalloc(sizeof(struct passenger), GFP_KERNEL);
    cat -> type = 'C';
    cat -> weight = 15;
    return cat;
}

struct passenger* getDog(void){
    struct passenger* dog = kmalloc(sizeof(struct passenger), GFP_KERNEL);
    dog -> type = 'D';
    dog -> weight = 45;
    return dog;
}

struct passenger* animalReader(struct passenger* animal){
    if (animal == NULL){
        printk(KERN_DEBUG "animal null in animalReader\n");
        return NULL;
    }
    if (animal -> type == 'L')
        return floorAssigner(getLizard(), animal -> dest);
    else if (animal -> type == 'C')
        return floorAssigner(getCat(), animal -> dest);
    else if (animal -> type == 'D')
        return floorAssigner(getDog(), animal -> dest);
    else {
        printk(KERN_DEBUG "NULL in animalReader detected\n");
        return NULL;
    }
}

struct passenger* int_to_passenger(int type){
    if (type == 0)
        return getLizard();
    if (type == 1)
        return getCat();
    if (type == 2)
        return getDog();
    printk(KERN_DEBUG "RETURNING NULL ANIMAL int_to_passenger\n");
    return NULL;
}

int issue_processor(int start, int dest, int type){
    struct passenger* animal = int_to_passenger(type);
    floorAssigner(animal, dest);
    
    struct list_head *list;
    if (start == 0)
        list = &elevator_list;
    else {
        list = &floors[--start];
    } 

    if (animal != NULL && list != NULL){
        addAnimal(animal, list);
    }
    else
        printk(KERN_DEBUG "animal or list null\n");
    return 0;
}

void load_elevator(struct list_head* floor){
    struct passenger *animal, *tmp;
    list_for_each_entry_safe(animal, tmp, floors, list_node){
        if (WEIGHT + animal -> weight <= 100 && PASSENGERS < 10){
            WEIGHT += animal -> weight;
            PASSENGERS++;
            list_del(&animal -> list_node);
            addAnimal(animal, &elevator_list);
            printk(KERN_DEBUG "Animal added, type: %c, WEIGHT: %d\n", animal -> type, WEIGHT);
        }
    }
}

void deload_elevator(int floor){
    floor++; //index to floor
    struct passenger *animal, *tmp;
    list_for_each_entry_safe(animal, tmp, &elevator_list, list_node){
        printk(KERN_DEBUG "animal -> dest: %d\n", animal -> dest);
        printk(KERN_DEBUG "floor: %d\n", floor);
        if (animal -> dest == floor){
            WEIGHT -= animal -> weight;
            PASSENGERS--;
            list_del(&animal -> list_node);
            printk(KERN_DEBUG "Animal dropped off, Type: %c, Destination: %d\n", animal -> type, animal -> dest);
            SERVICED++;
            kfree(animal);
        }
    }
}
