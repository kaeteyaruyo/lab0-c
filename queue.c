/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = (queue_t *) malloc(sizeof(queue_t));
    if (q != NULL) {
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* Remove head element until empty */
    while (q_size(q) > 0) {
        q_remove_head(q, NULL, 0);
    }

    /* Free queue structure */
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /* If q is NULL, return false */
    if (q == NULL)
        return false;

    list_ele_t *newh = create_node(s);
    if (newh == NULL)
        return false;

    /* Maintain queue information */
    newh->next = q->head;
    q->head = newh;
    ++(q->size);
    if (q_size(q) == 1)
        q->tail = newh;
    return true;
}

/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* If q is NULL, return false */
    if (q == NULL)
        return false;

    list_ele_t *newt = create_node(s);
    if (newt == NULL)
        return false;

    /* Maintain queue information */
    q->tail->next = newt;
    newt->next = NULL;
    q->tail = newt;
    ++(q->size);

    if (q_size(q) == 1)
        q->head = newt;
    return true;
}

list_ele_t *create_node(char *s)
{
    /* Create a new element of queue */
    /* If failed, return NULL */
    list_ele_t *new;
    new = (list_ele_t *) malloc(sizeof(list_ele_t));
    if (new == NULL)
        return NULL;

    /* Allocate space for string copy */
    /* If failed, free space fot element and return NULL */
    new->value = (char *) malloc(sizeof(char) * (strlen(s) + 1));
    if (new->value == NULL) {
        free(new);
        return NULL;
    }

    /* Copy string and return element */
    strcpy(new->value, s);
    return new;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* If q is NULL or empty, return false */
    if (q_size(q) == 0)
        return false;

    /* Remove head element for queue*/
    list_ele_t *tmp = q->head;
    q->head = q->head->next;
    --(q->size);
    if (q_size(q) == 0)
        q->tail = NULL;

    /* If sp is not NULL, copy data stored in head to it */
    if (sp != NULL) {
        strncpy(sp, tmp->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }

    /* Free space for element */
    free(tmp->value);
    free(tmp);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (q == NULL)
        return 0;
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (q_size(q) == 0)
        return;

    list_ele_t *prev = q->head;
    list_ele_t *curr = q->head->next;
    list_ele_t *next = NULL;
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    q->head->next = NULL;
    curr = q->head;
    q->head = q->tail;
    q->tail = curr;
}
