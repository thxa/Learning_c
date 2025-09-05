#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include <stdbool.h>

typedef struct node_t  node_t;
struct node_t {
    char* left;
    char* right;
    node_t *next;
    node_t *previous;
};

typedef struct {
    node_t* first;
    node_t* current;
    node_t* last;
    int cnt;
} node_list_t;


// insert
// delete
// update
// search

node_t* insert_first(node_list_t *list, node_t *node)
{

    if (list == NULL || node == NULL)
        return false;

    node_t *ptr = list->first;
    if(ptr->previous == NULL) {
        ptr ->previous = node;
        ptr = ptr->previous;
        list->first = ptr;
        return true;
    }
    node_t *tmp = list->first;
    // ptr -> previous = target;
    // tmp ->next = target;
    // target ->previous = tmp;


    // node_t *ptr = node;
    // while (ptr->previous != NULL)
    // {
    //     ptr = ptr->previous;
    // }
    // ptr->previous = target;
    // target->next = ptr;
    // return target;

}



// bool update(node_t *node, node_t *target, )
// {
//     if (node == NULL)
//         return false;

//     node_t *ptr = node;
//     while (ptr->next != NULL)
//     {
//         ptr = ptr->next;
//     }

//     ptr->next = target;
//     target->previous = ptr;
//     return true;
// }

// bool search(node_t *node) {
// }




bool insert_last(node_t *node, node_t *target)
{
    if (node == NULL)
        return false;

    node_t *ptr = node;
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }

    ptr->next = target;
    target->previous = ptr;
    return true;
}

bool insert_after(node_t *node, node_t *target)
{
    if (node == NULL || target == NULL)
        return false;

    node_t *ptr = node;
    if(ptr->next == NULL) {
        ptr ->next = target;
        return true;
    }
    node_t *tmp = ptr ->next;
    ptr -> next = target;
    tmp ->previous = target;
    target ->next = tmp;

    return true;
}

bool insert_before(node_t *node, node_t *target)
{
    if (node == NULL || target == NULL)
        return false;

    node_t *ptr = node;
    if(ptr->previous == NULL) {
        ptr ->previous = target;
        return true;
    }
    node_t *tmp = ptr ->previous;
    ptr -> previous = target;
    tmp ->next = target;
    target ->previous = tmp;

    return true;
}

void print(node_t *node)
{
    if (node == NULL)
    {
        printf("Empty list\n");
        return;
    }

    node_t *ptr = node;
    int count = 1;
    while (ptr != NULL)
    {
        printf("%s <-- node[%d] --> %s \n",
               ptr->left, count++,ptr->right);
        ptr = ptr->next;
    }
}

node_t *create_node(char* operation_left, char* operation_right)
{
    node_t *std = malloc(sizeof(node_t));
    if (std == NULL)
        return NULL;

    std->left = operation_left;
    std->right = operation_right;

    std->next = NULL;
    std->previous = NULL;

    return std;
}





void destroy_node(node_t *node)
{
    if (node != NULL)
    {
        node->right = 0;
        node->left = 0;
        node->next = NULL;
        node->previous = NULL;
        free(node);
    }
}

void destroy_all(node_t *node)
{
    node_t *ptr = node;
    node_t *tmp = NULL;

    while (ptr != NULL)
    {
        tmp = ptr;
        ptr = ptr->next;
        destroy_node(tmp);
        printf("node destroyed\n");
    }
}

int
main(int argc, char ** args)
{

    node_t *root;
    root = create_node("1+2", "3+3");
    insert_before(root, create_node("5+3", "1+2"));
    root = insert_first(root, create_node("1+4", "1+3"));
    insert_last(root, create_node("2+5", "4+2"));
    insert_before(root, create_node("5+3", "1+2"));
    insert_last(root, create_node("5+3", "1+2"));
    insert_after(root, create_node("5+3", "1+2"));
    insert_last(root, create_node("4+5", "4+2"));
    insert_before(root, create_node("5+3", "1+2"));
    insert_last(root, create_node("2+3", "2+2"));

    print(root);
    destroy_all(root);

   return 0;
}
