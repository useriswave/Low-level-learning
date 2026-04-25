#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next_ptr;
} node_t;

typedef struct LinkedList {
    node_t *head;
    node_t *tail;
    size_t size;
} LinkedList;

void ll_init(LinkedList *ll);
void display_ll(LinkedList ll);
void free_ll(LinkedList *ll);
node_t *create_node(int x);
int ll_push_back(LinkedList *ll, int x);
int ll_push_front(LinkedList *ll, int x);
int ll_peak_front(LinkedList ll);
int ll_peak_back(LinkedList ll);
int ll_pop_front(LinkedList *ll);
int ll_pop_back(LinkedList *ll);
int ll_remove(LinkedList *ll, int target);
node_t *get_node(LinkedList ll, int target);
int reverse(LinkedList *ll);

int main() 
{
    LinkedList ll;
    ll_init(&ll);

    ll_push_front(&ll, 1);
    ll_push_front(&ll, 5);
    ll_push_front(&ll, 9);
    ll_push_front(&ll, 2);
    ll_push_front(&ll, 0);

    ll_pop_back(&ll);
    ll_pop_front(&ll);
    display_ll(ll);

    reverse(&ll);
    printf("\n\n");
    display_ll(ll);
    printf("Front element: %d\n", ll_peak_front(ll));
    printf("Back element: %d\n", ll_peak_back(ll));
    node_t *target = get_node(ll, 9);
    printf("Target node:\n");
    printf("Data: %d\nAddress: %p\nnext_ptr: %p\n--------------------\n", target->data, target, target->next_ptr);
    free_ll(&ll);
    display_ll(ll);
    return 0;
}

void ll_init(LinkedList *ll) {
    ll->head = NULL;
    ll->tail = NULL;
    ll->size = 0;
}

void display_ll(LinkedList ll) {
    if(ll.size == 0) {
        printf("No nodes.\n");
        return;
    }
    while(ll.head != NULL) {
        printf("Data: %d\nAddress: %p\nnext_ptr: %p\n--------------------\n", ll.head->data, ll.head, ll.head->next_ptr);
        ll.head = ll.head->next_ptr;
    }
        printf("Total size: %zu\n", ll.size);
}

void free_ll(LinkedList *ll) {
    while(ll->head != NULL) {
        node_t *temp = ll->head->next_ptr;
        free(ll->head);
        ll->head = temp;
    }
    ll->tail = NULL;
    ll->size = 0;
}

node_t *create_node(int x) {
    node_t *node = (node_t*) malloc(sizeof(node_t));
    if(!node)
        return NULL;

    node->data = x;
    node->next_ptr = NULL;

    return node;
}

int ll_push_back(LinkedList *ll, int x) {
  node_t *node = create_node(x);
  if(node == NULL) return -1;

    if(ll->head == NULL) {
        ll->head = node;
        ll->tail = node;
    }
    else {
        // previous node's next POINTS to new node, the tail BECOMES the new node.
        ll->tail->next_ptr = node;
        ll->tail = node;
    }

  ll->size++;
  return 0;
}

int ll_push_front(LinkedList *ll, int x) {
    node_t *node = create_node(x);
    if(!node) return -1;

    if(ll->head == NULL) {
        ll->head = node;
        ll->tail = node;
    }
    else {
        node->next_ptr = ll->head;
        ll->head = node;
    }
    
    ll->size++;
    return 0;
}

int ll_peak_front(LinkedList ll) {
    if(ll.head == NULL) return -1;

    return ll.head->data;
}

int ll_peak_back(LinkedList ll) {
    if(ll.tail == NULL) return -1;

    return ll.tail->data;
}

int ll_remove(LinkedList *ll, int target) {
    node_t *curr = ll->head;
    node_t *prev = NULL;

    while(curr != NULL && curr->data != target) {
        prev = curr;
        curr = curr->next_ptr;
    }

    if(curr == NULL) return -1;

    if(curr == ll->tail) {
        ll->tail = prev;
    }

    if(prev == NULL) {
        ll->head = curr->next_ptr;
    }
    else {
        prev->next_ptr = curr->next_ptr;
    }

    free(curr);
    ll->size--;
    return 0;
}

node_t *get_node(LinkedList ll, int target) {
    node_t *curr = ll.head;

    while(curr != NULL && curr->data != target) {
        curr = curr->next_ptr;
    }

    if(curr == NULL) return NULL;

    return curr;
}

int ll_pop_front(LinkedList *ll) {
    if(ll->size == 0) return -1;
    
    node_t *temp = ll->head;
    ll->head = ll->head->next_ptr;

    // head is null if theres 1 node (next_ptr is null)

    if(ll->head == NULL) {
        ll->tail = NULL;
    }
    free(temp);
    ll->size--;
    return 0;
}

int ll_pop_back(LinkedList *ll) {
    if(ll->size == 0) return -1;

    node_t *prev = NULL;
    node_t *curr = ll->head;

    // we check for the tail if next_ptr is null
    while(curr->next_ptr != NULL) {
        prev = curr;
        curr = curr->next_ptr;
    }

    if(curr == NULL) return -1;

    if(prev == NULL) {
        ll->head = NULL;
        ll->tail = NULL;
    }
    else {
        prev->next_ptr = NULL;
        ll->tail = prev;
    }
    

    free(curr);
    ll->size--;
    return 0;
}

int reverse(LinkedList *ll) {
    if(ll->size == 0) return 1;
    node_t *prev = NULL;
    node_t *curr = ll->head;

    while(curr != NULL) {
        node_t *next = curr->next_ptr;
        curr->next_ptr = prev;

        prev = curr;
        curr = next;
    }
    ll->head = prev;

    return 0;
}
