#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void free_array(char **array, int count);
void display_words(char **array, int count);

int main() 
{
  int capacity = 2;
  int count = 0;
  char buffer[1000];
  char **words = malloc(capacity * sizeof(char*));
  
  if(words == NULL) {
    printf("Memory allocatoin for words failed.\n");
    return 1;
  }

  while(1) {
    printf("Enter name %d: ", count+1);
    fgets(buffer, sizeof(buffer), stdin);

    buffer[strcspn(buffer, "\n")] = '\0';

    if(strcmp(buffer, "q") == 0 || strcmp(buffer, "quit") == 0) {
      break;
    }

    if(count == capacity) {
      capacity *= 2;
      char **temp = realloc(words, capacity * sizeof(char*));
      if(temp == NULL) {
        printf("Memory reallocation for temp at %d failed.\n", count);
        free_array(words, count);
        free(words);
        words = NULL;

        return 1;
      }

      words = temp;
    }

    size_t word_len = strlen(buffer);

    *(words + count) = malloc((word_len+1) * sizeof(char));
    if(*(words + count) == NULL) {
      printf("Memory allocation for word at %d failed.\n", count);
      free_array(words, count);
      free(words);
      return 1;
    }

    strcpy(*(words + count), buffer);
    count++;

  }

  display_words(words, count);
  free_array(words, count);
  free(words);
  words = NULL;

  return 0;
}

void free_array(char **array, int count) {
  for(int i = 0; i < count; i++) {
    free(*(array + i));
  }
}

void display_words(char **array, int count) {
  printf("\nYour entered words:\n");
  if(count == 0) {
    printf("None\n");
    return;
  }

  for(int i = 0; i < count; i++) {
    printf("Word %d: %s\n", i+1, *(array + i));
  }
}
