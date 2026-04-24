#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Numbers {
  size_t cap;
  size_t size;
  int *list;
};

int append(struct Numbers *ns, int n);
int getEven(struct Numbers ns);
int getOdd(struct Numbers ns);
void displayItems(struct Numbers ns);

int main()
{
  struct Numbers nums = {0};
  srand(time(NULL));

  for(int i = 0; i < 5; i++) {
   if(append(&nums, rand() % 21) == 1) {
     free(nums.list);
     nums.list = NULL;
     return 1;
   }
  }

  displayItems(nums);

  printf("Even count: %d\n", getEven(nums));
  printf("Odd count: %d\n", getOdd(nums));

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
    ns->cap*=2;
    int *temp = realloc(ns->list, ns->cap * sizeof(*(ns->list)));
    
    if(temp == NULL)
      return 1;

    ns->list = temp;
  }
    
  *(ns->list + ns->size) = n;
  ns->size++;

  return 0;
}

int getEven(struct Numbers ns) {
  int count = 0;
  for(size_t i = 0; i < ns.size; i++) {
    if(*(ns.list + i) % 2 == 0)
      count++;
  }
  return count;
}
int getOdd(struct Numbers ns) {
int count = 0;
  for(size_t i = 0; i < ns.size; i++) {
    if(*(ns.list + i) % 2 != 0)
      count++;
  }
  return count;
}

void displayItems(struct Numbers ns) {
  if(ns.size == 0)  {
    printf("None\n");
    return;
  }

  for(size_t i = 0; i < ns.size; i++)
    printf("Number %zu: %d\n", i, *(ns.list + i));

  printf("\n\n");
}
