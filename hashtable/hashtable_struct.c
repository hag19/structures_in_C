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
    items** array;   // Array of items
    int size;
    int capacity;
} hasharray;

typedef struct hashtable {
    hasharray** arrayP; // Array of hash arrays
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

    // Example insertions
    insert(&h, 5, "John", 25, true, 123456, "john@example.com");
    insert(&h, 15, "Alice", 30, false, 987654, "alice@example.com");
    insert(&h, 25, "Bob", 40, true, 111222, "bob@example.com");

    // Searching for some values
    search(&h, 5);
    search(&h, 15);
    search(&h, 25);
    search(&h, 100); // Non-existing value

    // Deleting a value
    delete(&h, 15);
    search(&h, 15); // Should print not found

    freeM(&h); // Free allocated memory
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
            printf("Found item: id: %d, name: %s, age: %d, verified: %d, phone: %d, email: %s\n",
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
        fprintf(stderr, "Error: Hash code out of bounds.\n");
        exit(EXIT_FAILURE);
    }
    hasharray *hashArr = h->arrayP[code];
    if (hashArr == NULL) {
        fprintf(stderr, "Error: hashArr is NULL at index %d.\n", code);
        exit(EXIT_FAILURE);
    }

    if (hashArr->size == hashArr->capacity) {
        hashArr->capacity *= 2;
        items **newArray = realloc(hashArr->array, hashArr->capacity * sizeof(items *));
        if (newArray == NULL) {
            fprintf(stderr, "Error: Failed to allocate memory.\n");
            exit(EXIT_FAILURE);
        }
        hashArr->array = newArray;
    }

    items *newitem = malloc(sizeof(items));
    if (newitem == NULL) {
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

    h->arrayP = malloc(sizeof(hasharray*) * capacity);
    if (h->arrayP == NULL) {
        return false;
    }

    h->capacity = capacity;

    for (int i = 0; i < capacity; i++) {
        h->arrayP[i] = malloc(sizeof(hasharray));
        if (h->arrayP[i] == NULL) {
            freeM(h);
            return false;
        }

        h->arrayP[i]->array = malloc(sizeof(items*) * capacity);
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

    printf("Couldn't find person with this ID: %d.\n", id);
}
