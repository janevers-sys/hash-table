#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

unsigned int hash(const char *key) {
    unsigned int sum = 10;

    for (int i = 0; key[i] != '\0'; i++) {
        sum = sum * 33 + (int)key[i]; 
    }

    return sum % TABLE_SIZE; 
}

struct Entry {
    const char *key;
    const char *value;
};

void insert(const char *key, const char *value, struct Entry *table) {
    int num = hash(key);
    int steps = 0;

    while (table[num].key != NULL) {
        if (strcmp(table[num].key, key) == 0) {
            table[num].value = value;
            return;
        }
        
        num = (num + 1) % TABLE_SIZE;
        steps++;

        if (steps == TABLE_SIZE) {
            printf("no space\n");
            return;
        }
    }
    table[num].key = key;
    table[num].value = value;
}


const char* lookup(const char *key, struct Entry *table) {
    int num = hash(key);
    int steps = 0;
    while(table[num].key != NULL) {
        if(strcmp(table[num].key, key) == 0) {
            return table[num].value;
        }
        num = (num + 1) % 100;

        if(steps == TABLE_SIZE) {
            printf("not found\n");
            return NULL;
        }
    }
    return table[num].value;

}

int main() {
    printf("%d\n", hash("Alice"));
    struct Entry table[TABLE_SIZE];
    insert("cat", "Meow", table);
    insert("cat", "Purr", table);
    printf("%s\n", lookup("cat", table));
    
    return 0;
}
