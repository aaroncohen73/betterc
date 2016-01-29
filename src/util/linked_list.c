#include "linked_list.h"

list_t list_create(size_t data_size)
{
    list_t list = {.first = NULL, .data_size = data_size, .length = 0};
    
    return list; 
}

void list_add(list_t *list, void *next_data)
{
    list_node_t *next;

    next = malloc(sizeof(list_node_t));
    next->data = malloc(list->data_size);
    next->position = 0;
    next->next = NULL;
    assert_not_null("list_add", 2, list, next);

    memcpy(next->data, next_data, list->data_size);
    next->position = list->length;

    list_append(list, next);
}

void list_append(list_t *list, list_node_t *next)
{
    list_node_t *last;

    assert_not_null("list_append", 2, list, next);

    if (list->length == 0)
    {
        list->first = next;
    }
    else
    {
        last = list_at(list, list->length - 1);
        
        assert_not_null("list_append", 1, last);

        last->next = next;
    }

    list->length += 1;
}

void list_extend(list_t *list, list_t *extend)
{
    list_node_t *linking;

    assert_not_null("list_extend", 2, list, extend);

    if (list->data_size != extend->data_size)
    {
        return;
    }

    if (list->length == 0)
    {
        list->first = extend->first;
        list->length = extend->length;
    }
    else if (extend->length == 0)
    {
        return;
    }
    else
    {
        linking = list_at(list, list->length - 1);

        assert_not_null("list_extend", 1, linking);

        linking->next = extend->first;

        list->length += extend->length;
    }
}

void list_delete(list_t *list)
{
    list_node_t *current;

    assert_not_null("list_delete", 1, list);

    list_delete_node(list->first);
    list->length = 0;
}

void list_delete_node(list_node_t *node)
{
    assert_not_null("list_delete_node", 1, node);

    if (node->next != NULL)
    {
        list_delete_node(node->next);
    }

    if (node->data != NULL)
    {
        free(node->data);
    }

    free(node);
}

list_node_t * list_at(list_t *list, int pos)
{
    list_node_t *current_node;
    int current_index;

    assert_not_null("list_at", 1, list);

    if (list->length == 0)
    {
        return NULL;
    }
    
    current_node = list->first;
    for(current_index = 0; current_index < pos; current_index++)
    {
        if (current_node->next == NULL) 
        {
            return NULL;
        }

        current_node = current_node->next;
    }

    return current_node;
}

void * list_to_array(list_t *list)
{
    void *data;
    void *array;
    list_node_t *current_node;
    int i;

    assert_not_null("list_to_array", 1, list);

    if (list->length == 0 || list->data_size == 0)
    {
        return NULL;
    }

    array = malloc(list->data_size * list->length);

    current_node = list->first;
    for (i = 0; i < list->length; i++)
    {
        memcpy(data, current_node->data, list->data_size);

        assert_not_null("list_to_array", 1, data);

        memcpy(array + (i * list->data_size), data, list->data_size);

        current_node = current_node->next;
    }

    return array;
}
