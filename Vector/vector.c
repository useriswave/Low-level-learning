#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Vector {
  size_t len;
  size_t cap;
  char **data;
};

int append(struct Vector *vec, char* str);
void free_items(struct Vector *vec);
void display_items(struct Vector vec);
int remove_at(struct Vector *vec, size_t index);
char *get(struct Vector vec, size_t index);
int search(struct Vector vec, char* str);
int insert(struct Vector *vec, size_t index, char* str);
void clear(struct Vector *vec);

int main()
{
  struct Vector vec = {0};
  append(&vec, "Jack");
  append(&vec, "Harold");
  append(&vec, "Word");
  append(&vec, "Toilet");
  append(&vec, "Lol");

  int index = 3;
  char* word = get(vec, 3);
  printf("Removing element %s at index %d: %s\n", word, search(vec, word), get(vec, index));

  remove_at(&vec, search(vec, word));
  insert(&vec, 3, "Inserted");

  display_items(vec);

  clear(&vec);

  printf("\n");
  display_items(vec);
}

int append(struct Vector *vec, char* str) {
  char* str_copy = malloc(strlen(str) + 1);

  if(str_copy == NULL)
    return 1;

  strcpy(str_copy, str);

  if(vec->len == vec->cap) {
    size_t temp_cap = vec->cap == 0 ? 2 : vec->cap * 2;
    char **temp = realloc(vec->data, temp_cap * sizeof(char *));

    if(temp == NULL) {
      free(str_copy);
      return 1;
    }

    vec->data = temp;
    vec->cap = temp_cap;
  }

  *(vec->data + vec->len) = str_copy;

  vec->len++;
  return 0;
}

void display_items(struct Vector vec) {
  if(vec.len == 0)
    printf("None\n");

  for(size_t i = 0; i < vec.len; i++) {
    printf("%s\n", *(vec.data + i));
  }
}

void free_items(struct Vector *vec) {
  for(size_t i = 0; i < vec->len; i++)  {
    free(*(vec->data + i));
    *(vec->data + i) = NULL;
  }
}

int remove_at(struct Vector *vec, size_t index) { // should i return 1 or -1
  if(index >= vec->len)
    return 1;
  
  free(*(vec->data + index));

  for(size_t i = index; i < vec->len - 1; i++) {
    *(vec->data + i) = *(vec->data + (i+1));
  }
  *(vec->data + vec->len -1) = NULL;
  vec->len--;

  return 0;
}

char *get(struct Vector vec, size_t index) {
  if(index >= vec.len)
    return NULL;

  return *(vec.data + index);
}

int search(struct Vector vec, char* str) {
  for(size_t i = 0; i < vec.len; i++) {
    if(strcmp(*(vec.data + i), str) == 0) {
      return i;
    }
  }
  return -1;   // should i return 1 or -1
}

int insert(struct Vector *vec, size_t index, char* str) {
  if(index > vec->len)
    return 1;

  char *str_copy = malloc(strlen(str)+1);

  if(str_copy == NULL) {
    return 1;
  }
  strcpy(str_copy, str);

  if(vec->cap == vec->len) {
    size_t temp_cap = vec->cap == 0 ? 2 : vec->cap * 2;
    char **temp = realloc(vec->data, temp_cap * sizeof(char*));

    if(temp == NULL) {
      free(str_copy);
      return 1;
    }
  vec->data = temp;
  vec->cap = temp_cap;

  }

  for(size_t i = vec->len; i > index; i--) {
    *(vec->data + i) = *(vec->data + (i-1));
  }

  *(vec->data + index) = str_copy;
  ++vec->len;

  return 0;
}
void clear(struct Vector *vec) {
  free_items(vec);
  free(vec->data);
  vec->data = NULL;
  vec->cap = 0;
  vec->len = 0;
}
