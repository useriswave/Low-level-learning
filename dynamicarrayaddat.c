#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Numbers {
  size_t cap;
  size_t size;
  int *list;
};

int append(struct Numbers *ns, int n);
int insert(struct Numbers *ns, size_t index, int n);
void displayItems(struct Numbers ns);

int main()
{
  struct Numbers nums = {0};

  srand(time(NULL));

  for(int i = 0; i < 5; i++) {
    append(&nums, rand() & 21);
  }

  displayItems(nums);

  for(int i = 0; i < 3; i++) {
    insert(&nums, rand() % 6, rand() % 80);
  }

  displayItems(nums);
  
  free(nums.list);
  nums.list = NULL;

  return 0;
}

int append(struct Numbers *ns, int n) {
  if(ns->cap == 0)
    ns->cap = 2;

  if(ns->size == 0) {
    ns->list = malloc(ns->cap * sizeof(*(ns->list)));

    if(ns->list == NULL)
      return 1;
  }

  if(ns->size == ns->cap) {
    ns->cap *= 2;
    int *temp = realloc(ns->list, ns->cap * sizeof(*(ns->list)));

    if(temp == NULL)
      return 1;

    ns->list = temp;
  }

  *(ns->list + ns->size) = n;
  ns->size++;
  return 0;
}

int insert(struct Numbers *ns, size_t index, int n) {
  if(index > ns->size)
    return 1;
  int *temp = realloc(ns->list, ++ns->cap * sizeof(*(ns->list)));
  if(temp == NULL)
    return 1;
  ns->list = temp;
  ns->size++;

  for(size_t i = ns->size - 1; i > index; i--) {
    *(ns->list + i) = *(ns->list + (i-1));
  }

  *(ns->list + index) = n;
  return 0;
}

void displayItems(struct Numbers ns) {
  if(ns.size == 0)
    printf("None.\n");

  for(size_t i = 0; i < ns.size; i++) {
    printf("Item %zu: %d\n", i+1, *(ns.list + i));
  }
  printf("\n");
}
