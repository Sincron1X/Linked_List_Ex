#include <stddef.h>
#include <stdio.h>

#define MY_LIST(ptr) (ptr)

#define MY_LIST_CAST(ptr) ((struct my_list_item*)(ptr))
#define MY_INT_ITEM_CAST(ptr) ((struct my_int_item*)(ptr))

struct my_list_item
{
    struct my_list_item* next;
    unsigned int count;
};

struct my_int_item
{
    struct my_list_item list_item; // it's like his parent
    int value;
};

struct my_list_item* my_list_get_tail(struct my_list_item* head)
{
    if (!head)
    {
        return NULL;
    }

    struct my_list_item* current_item = head;
    struct my_list_item* last_item = NULL;

    while (current_item)
    {
        last_item = current_item;
        current_item = current_item->next;
    }

    return last_item;
}

struct my_list_item* my_list_append(struct my_list_item** head, struct my_list_item* item)
{
    struct my_list_item* tail = my_list_get_tail(*head);

    if (!(tail))
    {
        *head = item;
        (*head)->count = 1;
    }
    else
    {
        tail->next = item;
        (*head)->count++;
    }

    item->next = NULL;
    return item;
}

struct my_list_item* my_list_pop(struct my_list_item** head)
{
    if (!(*head))
    {
        return NULL;
    }

    struct my_list_item* current_head = *head;
    const unsigned int current_count = (*head)->count;
    *head = (*head)->next;
    if (*head)
    {
        (*head)->count = current_count - 1;
    }

    current_head->next = NULL;
    return current_head;
}

void my_list_remove(struct my_list_item** head, struct my_list_item* item)
{
    if (!(*head) || !item)
    {
        return;
    }

    struct my_list_item* current_item = *head;
    struct my_list_item* prev_item = NULL;

    while (current_item && current_item != item)
    {
        prev_item = current_item;
        current_item = current_item->next;
    }

    if (!current_item)
    {
        return; // Item not found
    }

    if (prev_item)
    {
        prev_item->next = current_item->next;
        (*head)->count--;
    }
    else
    {
        *head = current_item->next;
    }

    current_item->next = NULL;
}

unsigned int my_list_length(struct my_list_item* head)
{
    return head->count;
}

void print_my_list(struct my_list_item* head)
{
    printf("Linked List: ");
    struct my_list_item* current_item = head;

    while (current_item != NULL)
    {
        struct my_int_item* int_item = MY_INT_ITEM_CAST(current_item);
        printf("%d ", int_item->value);
        current_item = current_item->next;
    }

    printf("\n");
}

int main(int argc, char** argv)
{

    struct my_list_item* head = NULL;

    struct my_int_item first_int_item;
    first_int_item.value = 0;
    my_list_append(&head, MY_LIST(&first_int_item.list_item));

    struct my_int_item second_int_item;
    second_int_item.value = 10;
    my_list_append(&head, MY_LIST(&second_int_item.list_item));

    struct my_int_item third_int_item;
    third_int_item.value = 20;
    my_list_append(&head, MY_LIST(&third_int_item.list_item));

    struct my_int_item fourth_int_item;
    fourth_int_item.value = 30;
    my_list_append(&head, MY_LIST(&fourth_int_item.list_item));

    struct my_int_item fifth_int_item;
    fifth_int_item.value = 40;
    my_list_append(&head, MY_LIST(&fifth_int_item.list_item));

    // Remove an item from the list
    my_list_remove(&head, MY_LIST(&first_int_item.list_item));

    print_my_list(head);

    return 0;
}
