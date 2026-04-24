#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Vector {
  size_t len;
  size_t cap;
  char **data;
};

int append(struct Vector *vec, const char *str);
void free_items(struct Vector *vec);
void display_items(const struct Vector vec);
int remove_at(struct Vector *vec, const size_t index);
char *get(const struct Vector vec, const size_t index);
int search(const struct Vector vec, const char *str);
int insert(struct Vector *vec, const size_t index, const char *str);
void clear(struct Vector *vec);
int sort(struct Vector *vec);
int replace(struct Vector *vec, const size_t index ,const char* str);

int main(void) {
  struct Vector vec = {0};
  append(&vec, "Jack");
  append(&vec, "Harold");
  append(&vec, "Word");
  append(&vec, "Toilet");
  append(&vec, "Lol");

  int index = 3;
  char *word = get(vec, 2);
  printf("Removing element %s at index %d: %s\n", word, search(vec, word),
         get(vec, index));

  remove_at(&vec, search(vec, word));
  insert(&vec, 2, "Inserted");
  sort(&vec);
  replace(&vec, 0, "Barry");

  display_items(vec);

  clear(&vec);

  printf("\n");
  display_items(vec);

  // memory for pointer "data" is already free'd since i called the clear() method
  // free_items(&vec);
  // free(vec.data);
  // vec.data = NULL;

  return 0;
}

int append(struct Vector *vec, const char *str) {
  char *str_copy = malloc(strlen(str) + 1);

  if (str_copy == NULL)
    return 1;

  strcpy(str_copy, str);

  if (vec->len == vec->cap) {
    size_t temp_cap = vec->cap == 0 ? 2 : vec->cap * 2;
    char **temp = realloc(vec->data, temp_cap * sizeof(char *));

    if (temp == NULL) {
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

void display_items(const struct Vector vec) {
  if (vec.len == 0)
    printf("None\n");

  for (size_t i = 0; i < vec.len; i++) {
    printf("%s\n", *(vec.data + i));
  }
}

void free_items(struct Vector *vec) {
  for (size_t i = 0; i < vec->len; i++) {
    free(*(vec->data + i));
    *(vec->data + i) = NULL;
  }
}

int remove_at(struct Vector *vec, const size_t index) {
  if (index >= vec->len)
    return 1;

  free(*(vec->data + index));

  for (size_t i = index; i < vec->len - 1; i++) {
    *(vec->data + i) = *(vec->data + (i + 1));
  }
  *(vec->data + vec->len - 1) = NULL;
  vec->len--;

  return 0;
}

char *get(struct Vector vec, const size_t index) {
  if (index >= vec.len)
    return NULL;

  return *(vec.data + index);
}

int search(const struct Vector vec, const char *str) {
  for (size_t i = 0; i < vec.len; i++) {
    if (strcmp(*(vec.data + i), str) == 0) {
      return i;
    }
  }
  return -1;
}

int insert(struct Vector *vec, const size_t index, const char *str) {
  if (index > vec->len)
    return 1;

  char *str_copy = malloc(strlen(str) + 1);

  if (str_copy == NULL) {
    return 1;
  }
  strcpy(str_copy, str);

  if (vec->cap == vec->len) {
    size_t temp_cap = vec->cap == 0 ? 2 : vec->cap * 2;
    char **temp = realloc(vec->data, temp_cap * sizeof(char *));

    if (temp == NULL) {
      free(str_copy);
      return 1;
    }
    vec->data = temp;
    vec->cap = temp_cap;
  }

  for (size_t i = vec->len; i > index; i--) {
    *(vec->data + i) = *(vec->data + (i - 1));
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

int sort(struct Vector *vec) {
  if(vec->len < 2)
    return 1;

  for (size_t i = 0; i < vec->len - 1; i++) {
    for (size_t j = 0; j < vec->len - 1; j++) {
      if (strlen(*(vec->data + j)) > strlen(*(vec->data + (j + 1)))) {
        char *temp = *(vec->data + j);
        *(vec->data + j) = *(vec->data + (j + 1));
        *(vec->data + (j + 1)) = temp;
      }
    }
  }
  return 0;
}

int replace(struct Vector *vec, const size_t index ,const char* str) {
  if(vec->len == 0 || index >= vec->len)
    return 1;

  if(remove_at(vec, index) != 0)
    return 1;

  if(insert(vec, index, str) != 0)
    return 1;

  return 0;
}
