#include <stdlib.h>
#include <string.h>

#include "assert.h"

typedef struct list_node list_node_t;
typedef struct list      list_t;

struct list_node
{
    void *data;
    int position;
    struct list_node *next;
};

struct list
{
    list_node_t *first;
    size_t data_size;
    unsigned int length;
};

list_t list_create(size_t data_size);

void list_add   (list_t *list, void *next_data);
void list_append(list_t *list, list_node_t *next);
void list_extend(list_t *list, list_t *extend);

void list_delete(list_t *list);
void list_delete_node(list_node_t *node);

list_node_t * list_at(list_t *list, int pos);

void * list_to_array(list_t *list);

