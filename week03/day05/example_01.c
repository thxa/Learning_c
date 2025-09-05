#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct student_t student_t;

struct student_t
{
    /* Data */
    int id;
    int age;
    /* Links */
    student_t *next;
    student_t *previous;
};

student_t *create_student(int id, int age)
{
    student_t *std = malloc(sizeof(student_t));
    if (std == NULL)
        return NULL;

    std->id = id;
    std->age = age;

    std->next = NULL;
    std->previous = NULL;

    return std;
}

void destroy_node(student_t *node)
{
    if (node != NULL)
    {
        node->id = 0;
        node->age = 0;
        node->next = NULL;
        node->previous = NULL;
        free(node);
    }
}

void destroy_all(student_t *node)
{
    student_t *ptr = node;
    student_t *tmp = NULL;

    while (ptr != NULL)
    {
        tmp = ptr;
        ptr = ptr->next;
        destroy_node(tmp);
        printf("node destroyed\n");
    }
}


student_t* insert_first(student_t *node, student_t *target)
{
    if (node == NULL)
        return false;

    student_t *ptr = node;
    while (ptr->previous != NULL)
    {
        ptr = ptr->previous;
    }

    ptr->previous = target;
    target->next = ptr;
    return target;
}

bool insert_last(student_t *node, student_t *target)
{
    if (node == NULL)
        return false;

    student_t *ptr = node;
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }

    ptr->next = target;
    target->previous = ptr;
    return true;
}

bool insert_after(student_t *node, student_t *target)
{
    if (node == NULL || target == NULL)
        return false;

    student_t *ptr = node;
    if(ptr->next == NULL) {
        ptr ->next = target;
        return true;
    }
    student_t *tmp = ptr ->next;
    ptr -> next = target;
    tmp ->previous = target;
    target ->next = tmp;

    return true;
}

bool insert_before(student_t *node, student_t *target)
{
    if (node == NULL || target == NULL)
        return false;

    student_t *ptr = node;
    if(ptr->previous == NULL) {
        ptr ->previous = target;
        return true;
    }
    student_t *tmp = ptr ->previous;
    ptr -> previous = target;
    tmp ->next = target;
    target ->previous = tmp;

    return true;
}

void print(student_t *node)
{
    if (node == NULL)
    {
        printf("Empty list\n");
        return;
    }

    student_t *ptr = node;
    int count = 1;
    while (ptr != NULL)
    {
        printf("node[%d]: id->%d, age->%d\n",
               count++, ptr->id, ptr->age);
        ptr = ptr->next;
    }
}

int main()
{
    student_t *root;
    root = create_student(10, 20);

    root = insert_first(root, create_student(6, 17));
    insert_last(root, create_student(5, 13));
    insert_last(root, create_student(30, 88));
    insert_after(root, create_student(50, 2));
    insert_last(root, create_student(9, 17));

    print(root);
    destroy_all(root);

    return 0;
}
