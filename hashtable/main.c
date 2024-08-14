#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct hasharray {
    int *array;
    int size;
    int capacity;
} hasharray;

typedef struct hashtable {
    struct hasharray** arrayP;
    int capacity;
} hashtable;
bool create(hashtable *h, int capacity);
void insert(hashtable *h, int value);
void freeM(hashtable* h, int capacity);
int hashcode(int value, int size);
void search(hashtable *h, int value);

int main() {
    hashtable h;
    if (!create(&h, 10)) {
        fprintf(stderr, "Failed to create hashtable.\n");
        return EXIT_FAILURE;
    }

    insert(&h, 5);
    insert(&h, 15);
    insert(&h, 25);
    insert(&h,12);
    insert(&h, 66); 
    insert(&h,3);
    search(&h, 5);
    search(&h, 15);
    search(&h, 25);
    search(&h, 12);
    search(&h, 66);
    search(&h, 3);
    search(&h, 99);

    freeM(&h, h.capacity);
    return EXIT_SUCCESS;
}

int hashcode(int value, int size) {
    if (size <= 0) {
        return -1;
    }
    return value % size;
}

void search(hashtable *h, int value) {
    int c = 0;
    int code = hashcode(value, h->capacity);
    if (code < 0 || code >= h->capacity) {
        printf("Invalid hash code.\n");
        return;
    }

    hasharray *hashArr = h->arrayP[code];
    for (int i = 0; i < hashArr->size; i++) {
        if (hashArr->array[i] == value) {
      printf("address of the structure %p, then address of the array %p,then the hashcode %d then address of the value %p, then index itself %d, youre value %d\n"
            ,&hashArr,&hashArr->array,code, &hashArr->array[i],i,value);
            c++;
        }
    }
    if (c == 0) {
        printf("Value %d doesn't exist in the hashtable.\n", value);
    } else {
        printf("Value %d found %d times in the hashtable.\n", value, c);
    }
}

void insert(hashtable *h, int value) {
    if (h == NULL) {
        fprintf(stderr, "Error: Hashtable is NULL.\n");
        exit(EXIT_FAILURE);
    }
    int code = hashcode(value, h->capacity);
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
        int *newArray = realloc(hashArr->array, hashArr->capacity * sizeof(int));
        if (newArray == NULL) {
            fprintf(stderr, "Error: Failed to allocate memory.\n");
            exit(EXIT_FAILURE);
        }
        hashArr->array = newArray;
    }
    hashArr->array[hashArr->size++] = value;
}

void freeM(hashtable* h, int capacity) {
    if (h->arrayP != NULL) {
        for (int i = 0; i < capacity; i++) {
            if (h->arrayP[i] != NULL) {
                free(h->arrayP[i]->array);
                free(h->arrayP[i]);
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
            freeM(h, i);  // Free already allocated memory
            return false;
        }
        
        h->arrayP[i]->array = malloc(sizeof(int) * capacity);
        if (h->arrayP[i]->array == NULL) {
            freeM(h, i);  // Free already allocated memory
            return false;
        }
        
        h->arrayP[i]->size = 0;
        h->arrayP[i]->capacity = capacity;
        
        // Initialize the array elements to some default value (e.g., -1)
        for (int j = 0; j <capacity; j++) {
            h->arrayP[i]->array[j] = -1;
        }
    }

    return true;
}
