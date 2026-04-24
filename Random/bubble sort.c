#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct Numbers {
  size_t cap;
  size_t size;
  int *list;
};

int append(struct Numbers *ns, int n);
void displayItems(struct Numbers ns);
int sort(struct Numbers *ns);

int main()
{
  struct Numbers nums = {0};
  
  srand(time(NULL));
  for(int i = 1; i <= 5; i++) {
    if(append(&nums, rand() % 11) != 0) {
      free(nums.list);
      nums.list = NULL;
      return 1;
    }

  }
  
  printf("Before sort:\n");

  displayItems(nums);

  printf("After sort:\n");

  if(sort(&nums) != 0) {
      free(nums.list);
      nums.list = NULL;
      return 1;
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
    ns->cap *=2;
    int *temp = realloc(ns->list, ns->cap * sizeof(*(ns->list)));

    if(temp == NULL)
      return 1;

    ns->list = temp;
  }

  *(ns->list + ns->size) = n;
  ns->size++;

  return 0;
}

void displayItems(struct Numbers ns) {
  if(ns.size == 0) {
    printf("None\n");
    return;
  }

  for(size_t i = 0; i < ns.size; i++) {
    printf("Item %zu: %d\n", i+1, *(ns.list + i));
  }
}

int sort(struct Numbers *ns) {
  if(ns->size == 0)
    return 0;

  for(size_t i = 0; i < ns->size - 1; i++) {
    for(size_t j = 0; j < ns->size - 1; j++) {
      if(*(ns->list + j) > *(ns->list + (j+1))) {
        int temp = *(ns->list + j);
        *(ns->list + j) = *(ns->list + (j + 1));
        *(ns->list + (j+1)) = temp;
      }
    }
  }
  return 0;
}
