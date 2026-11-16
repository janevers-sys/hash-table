#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100
struct Entry {
    const char *key;
    const char *value;
};

struct hashtable {
    struct Entry *entries; 
    int capacity;          
    int count;             
};
void resize(struct hashtable *ht);


unsigned int hash(const char *key, int capacity) {
    unsigned int sum = 10;

    for (int i = 0; key[i] != '\0'; i++) {
        sum = sum * 33 + (int)key[i]; 
    }

    return sum % capacity; 
}

const char* lookup(const char *key, struct hashtable *ht) {
    int num = hash(key, ht->capacity);
    int steps = 0;
    while(ht->entries[num].key != NULL) {
        if(strcmp(ht->entries[num].key, key) == 0) {
            return ht->entries[num].value;
        }
        num = (num + 1) % 100;

        if(steps == TABLE_SIZE) {
            printf("not found\n");
            return NULL;
        }
    }
    return ht->entries[num].value;

}
struct hashtable create_table(int cap) {
    struct hashtable ht;
    ht.entries = calloc(cap, sizeof(struct Entry));
    ht.capacity = cap;
    ht.count = 0;
    return ht;
}

void insert(const char *key, const char *value, struct hashtable *ht) {
    if (ht->count * 2 >= ht->capacity) {
        resize(ht);
    }
    int num = hash(key, ht->capacity);
    while (ht->entries[num].key != NULL) {
        if (strcmp(ht->entries[num].key, key) == 0) {
            ht->entries[num].value = value;
            return;
        }
        num = (num + 1) % ht->capacity;
    }

    ht->entries[num].key = key;
    ht->entries[num].value = value;
    ht->count += 1;
}
void resize(struct hashtable *ht) {

    struct hashtable new_ht = create_table(ht->capacity * 2);

    for (int i = 0; i != ht->capacity; i++) {
        if (ht->entries[i].key != NULL) {
            insert(ht->entries[i].key, ht->entries[i].value, &new_ht);
        }
    }

    free(ht->entries);

    *ht = new_ht;
    return;
}
int main() {
    
    return 0;
}
