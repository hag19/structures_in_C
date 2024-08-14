#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

typedef struct items {
    int id;
    char *name;
    int age;
    bool verified;
    int number;
    char *email;
} items;

typedef struct hasharray {
    struct items** array;
    int size;
    int capacity;
} hasharray;

typedef struct hashtable {
    struct hasharray** arrayP;
    int capacity;
} hashtable;

bool create(hashtable *h, int capacity);
void insert(hashtable *h, int id, char *name, int age, bool verified, int number, char *email);
void freeM(hashtable* h);
int hashcode(int id, int size);
void search(hashtable *h, int id);
void freeitem(items *item);
void delete(hashtable *h, int id);

int main() {
    hashtable h;
    int capacity = 10;
    if (!create(&h, capacity)) {
        fprintf(stderr, "Failed to create hashtable.\n");
        return EXIT_FAILURE;
    }
 
    search(&h, 5);
    search(&h, 15);
    search(&h, 25);
    search(&h, 12);
    search(&h, 66);
    search(&h, 3);
    search(&h, 99);

    freeM(&h);
    return EXIT_SUCCESS;
}

int hashcode(int id, int size) {
    if (size <= 0) {
        return -1;
    }
    return id % size;
}

void search(hashtable *h, int id) {
    int c = 0;
    int code = hashcode(id, h->capacity);
    if (code < 0 || code >= h->capacity) {
        printf("Invalid hash code.\n");
        return;
    }

    hasharray *hashArr = h->arrayP[code];
    if (hashArr == NULL || hashArr->array == NULL) {
        printf("No items in this hasharray.\n");
        return;
    }

    for (int i = 0; i < hashArr->size; i++) {
        if (hashArr->array[i]->id == id) {
            items *person = hashArr->array[i];
            printf("address of the structure hasharray %p, then address of the array %p, then the hashcode %d, then address of the structure of this person %p, then index itself %d, your value %d\n",
                &hashArr, hashArr->array, code, &hashArr->array[i], i, id);
            printf("id: %d, name: %s, age: %d, verified: %d, phone: %d, email: %s\n",
                person->id, person->name, person->age, person->verified, person->number, person->email);
            c++;
        }
    }
    if (c == 0) {
        printf("Value %d doesn't exist in the hashtable.\n", id);
    } else {
        printf("Value %d found %d times in the hashtable.\n", id, c);
    }
}

void insert(hashtable *h, int id, char *name, int age, bool verified, int number, char *email) {
    if (h == NULL) {
        fprintf(stderr, "Error: Hashtable is NULL.\n");
        exit(EXIT_FAILURE);
    }
    int code = hashcode(id, h->capacity);
    if (code < 0 || code >= h->capacity) {
        freeM(h);
        fprintf(stderr, "Error: Hash code out of bounds.\n");
        exit(EXIT_FAILURE);
    }
    hasharray *hashArr = h->arrayP[code];
    if (hashArr == NULL) {
        freeM(h);
        fprintf(stderr, "Error: hashArr is NULL at index %d.\n", code);
        exit(EXIT_FAILURE);
    }

    if (hashArr->size == hashArr->capacity) {
        hashArr->capacity *= 2;
        struct items **newArray = realloc(hashArr->array, hashArr->capacity * sizeof(struct items *));
        if (newArray == NULL) {
            freeM(h);
            fprintf(stderr, "Error: Failed to allocate memory.\n");
            exit(EXIT_FAILURE);
        }
        hashArr->array = newArray;
    }

    items *newitem = malloc(sizeof(items));
    if (newitem == NULL) {
        freeM(h);
        fprintf(stderr, "Error: Failed to allocate memory for the item struct.\n");
        exit(EXIT_FAILURE);
    }
    newitem->age = age;
    newitem->id = id;
    newitem->number = number;
    newitem->verified = verified;
    newitem->name = strdup(name);
    newitem->email = strdup(email);

    hashArr->array[hashArr->size++] = newitem;
}

void freeM(hashtable* h) {
    if (h->arrayP != NULL) {
        for (int i = 0; i < h->capacity; i++) {
            if (h->arrayP[i] != NULL) {
                hasharray *hashArr = h->arrayP[i];
                if (hashArr->array != NULL) {
                    for (int j = 0; j < hashArr->size; j++) {
                        freeitem(hashArr->array[j]);
                    }
                    free(hashArr->array);
                }
                free(hashArr);
            }
        }
        free(h->arrayP);
    }
}

bool create(hashtable *h, int capacity) {
    if (h == NULL || capacity <= 0) {
        return false;
    }

    h->arrayP = malloc(sizeof(struct hasharray*) * capacity);
    if (h->arrayP == NULL) {
        return false;
    }

    h->capacity = capacity;

    for (int i = 0; i < capacity; i++) {
        h->arrayP[i] = malloc(sizeof(struct hasharray));
        if (h->arrayP[i] == NULL) {
            freeM(h);
            return false;
        }
        
        h->arrayP[i]->array = malloc(sizeof(struct items*) * capacity);
        if (h->arrayP[i]->array == NULL) {
            freeM(h);  
            return false;
        }
        
        h->arrayP[i]->size = 0;
        h->arrayP[i]->capacity = capacity;
        
        for (int j = 0; j < capacity; j++) {
            h->arrayP[i]->array[j] = NULL;
        }
    }

    return true;
}

void freeitem(items *item) {
    if (item != NULL) {
        free(item->email);
        free(item->name);
        free(item);
    }
}

void delete(hashtable *h, int id) {
    if (h == NULL) {
        return;
    }

    int code = hashcode(id, h->capacity);
    if (code < 0 || code >= h->capacity) {
        printf("Invalid hash code.\n");
        return;
    }

    hasharray *hashArr = h->arrayP[code];
    if (hashArr == NULL) {
        printf("No items in this hasharray.\n");
        return;
    }

    for (int j = 0; j < hashArr->size; j++) {
        if (hashArr->array[j] && hashArr->array[j]->id == id) {
            freeitem(hashArr->array[j]);
            hashArr->array[j] = hashArr->array[--hashArr->size];
            hashArr->array[hashArr->size] = NULL;
            return;
        }
    }
printf("Couldn't find person with this ID: %D.\n",id);
}
