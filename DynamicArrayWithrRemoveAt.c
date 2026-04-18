#include <stdio.h>
#include <stdlib.h>

struct Numbers {
  size_t cap;
  size_t size;
  int *list;
};

int append(struct Numbers *ns, const int n);
void displayItems(struct Numbers ns);
int removeAt(struct Numbers *ns, size_t index);

int main()
{
  struct Numbers nums = {0};
  int c = 0;
  while(1) {
    int n;
    printf("Enter number %d: ", ++c);
    scanf("%d", &n);
    
    if(n == -999)
      break;
    
    if(append(&nums, n) == 1) {
      printf("Problem with memory occured.\nProgram terminated.\n");
      free(nums.list);
      nums.list = NULL;
      return 1;
    }
  }

  displayItems(nums);

  char input;
  while(1) {
    printf("Remove an item? (y/n): ");
    scanf(" %c", &input);
    if(input != 'y' && input != 'n')
      printf("Invalid entry.\n");

    if(input == 'n')
      break;
    
    size_t index;
    printf("Which index? ");
    scanf(" %zu", &index);

    if(removeAt(&nums, index) == 1) {
      printf("Index out of bounds.\nProgram terminated.\n");
      free(nums.list);
      nums.list = NULL;
      return 1;
    }

    printf("Removed item from index %zu\n", index);
    displayItems(nums);
  }
  
  printf("Program closed.\n");
  free(nums.list);
  nums.list = NULL;

  return 0;
}

int append(struct Numbers *ns, const int n) {
  if(ns->cap == 0)
    ns->cap = 2;
  if(ns->size == 0) {
    ns->list = malloc(ns->cap * sizeof(*(ns->list)));
    if(ns->list == NULL) {
      return 1;
    }
  }
  if(ns->cap == ns->size) {
    ns->cap *= 2;
    int *temp = realloc(ns->list, ns->cap * sizeof(*(ns->list)));
    if(temp == NULL) {
      return 1;
    }
     ns->list = temp;
  }

  *(ns->list + ns->size) = n;
  ns->size++;
  return 0;
}

int removeAt(struct Numbers *ns, size_t index) {
  if(index >= ns->size)
    return 1;

  for(size_t i = index; i < ns->size - 1; i++) {
    *(ns->list + i) = *(ns->list + (i+1));
  }
  ns->size--;
  return 0;
}

void displayItems(struct Numbers ns) {
  if(ns.size == 0)
    printf("None\n");

  for(size_t i = 0; i < ns.size; i++) {
    printf("Item %zu: %d\n", i+1, *(ns.list + i));
  }
}
