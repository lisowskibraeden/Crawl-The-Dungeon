#ifndef ENTITY_H
#define ENTITY_H

static int ID_COUNT = 0;

class Entity {
    public:
        Entity() {
            id = ID_COUNT;
            ID_COUNT++;
        }
        int getId() {
            return id;
        }        
    private: 
        int id;
};

#endif
