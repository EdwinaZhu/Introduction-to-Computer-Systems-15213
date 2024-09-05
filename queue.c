/**
 * @file queue.c
 * @brief Implementation of a queue that supports FIFO and LIFO operations.
 *
 * This queue implementation uses a singly-linked list to represent the
 * queue elements. Each queue element stores a string value.
 *
 * Assignment for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Extended to store strings, 2018
 *
 * @author Yingzhu <yingzhu3@andrew.cmu.edu>
 */

#include "queue.h"
#include "harness.h"

#include <stdlib.h>
#include <string.h>

/**
 * @brief Allocates a new queue
 * @return The new queue, or NULL if memory allocation failed
 */
queue_t *queue_new(void) {
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if(q==NULL) return q;

    q->head = NULL;
    q->size=0;
    q->tail= q->head;
    return q;
}

/**
 * @brief Frees all memory used by a queue
 * @param[in] q The queue to free
 */
void queue_free(queue_t *q) {
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if(q==NULL) return;
    while(q->size>0){
        list_ele_t* ele_remove = q->head;
        q->head= ele_remove->next;
        q->size--;
        if(ele_remove->value!=NULL){
            free(ele_remove->value);
            ele_remove->value=NULL;
        }
        free(ele_remove);
        ele_remove=NULL;
    }
    free(q);
    q=NULL;
}

/**
 * @brief Attempts to insert an element at head of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_head(queue_t *q, const char *s) {
    list_ele_t *newh;
    char* s_c;
    /* What should you do if the q is NULL? */
    if(q==NULL) return false;

    newh = malloc(sizeof(list_ele_t));
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    if(newh==NULL) return false;

    s_c = (char*)malloc(strlen(s)+1);
    if(s_c==NULL){
        free(newh);
        newh=NULL;
        return false;
    } 

    strcpy(s_c,s);
    newh->value=s_c;
    newh->next = q->head;
    q->head = newh;
    q->size++;
    
    /*initial queue tail*/
    if(q->size==1) q->tail=q->head;
    return true;
}

/**
 * @brief Attempts to insert an element at tail of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_tail(queue_t *q, const char *s) {
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    list_ele_t *newt;
    char* s_c;
    /* What should you do if the q is NULL? */
    if(q==NULL) return false;

    newt = malloc(sizeof(list_ele_t));
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    if(newt==NULL) return false;

    s_c = (char*)malloc(strlen(s)+1);
    if(s_c==NULL) {
        free(newt);
        newt=NULL;
        return false;
    }

    strcpy(s_c,s);
    newt->value=s_c;
    if(q->size==0){
        q->tail=newt;
        q->head=q->tail;
        newt->next=NULL;
    }
    else{
        newt->next=q->tail->next;
        q->tail->next=newt;
        q->tail=newt;
    }
    q->size++;
    return true;
}

/**
 * @brief Attempts to remove an element from head of a queue
 *
 * If removal succeeds, this function frees all memory used by the
 * removed list element and its string value before returning.
 *
 * If removal succeeds and `buf` is non-NULL, this function copies up to
 * `bufsize - 1` characters from the removed string into `buf`, and writes
 * a null terminator '\0' after the copied string.
 *
 * @param[in]  q       The queue to remove from
 * @param[out] buf     Output buffer to write a string value into
 * @param[in]  bufsize Size of the buffer `buf` points to
 *
 * @return true if removal succeeded
 * @return false if q is NULL or empty
 */
bool queue_remove_head(queue_t *q, char *buf, size_t bufsize) {
    list_ele_t* ele_remove;
    /*false if q is NULL or empty. */
    if(q==NULL||q->size==0) return false;
    
    /*buf is non-NULL, copy queue head*/
    if(buf!=NULL){
        /*false if queue head doesn't contain char*/
        if(q->head->value==NULL) return false;

        strncpy(buf, q->head->value,bufsize-1);
        buf[bufsize-1]='\0';
    }

    /*free queue head*/
    ele_remove=q->head;
    q->head = q->head->next;
    q->size--;
    free(ele_remove->value);
    ele_remove->value=NULL;
    free(ele_remove);
    ele_remove=NULL;
    return true;
}

/**
 * @brief Returns the number of elements in a queue
 *
 * This function runs in O(1) time.
 *
 * @param[in] q The queue to examine
 *
 * @return the number of elements in the queue, or
 *         0 if q is NULL or empty
 */
size_t queue_size(queue_t *q) {
    /* Remember: It should operate in O(1) time */
    if(q==NULL) return 0;
    return q->size;
}

/**
 * @brief Reverse the elements in a queue
 *
 * This function does not allocate or free any list elements, i.e. it does
 * not call malloc or free, including inside helper functions. Instead, it
 * rearranges the existing elements of the queue.
 *
 * @param[in] q The queue to reverse
 */
void queue_reverse(queue_t *q) {
    list_ele_t* cur;
    list_ele_t* prev;
    list_ele_t* next;

    /*no operation if q is NULL*/
    if(q==NULL) return;
    
    cur=q->head;
    prev=NULL;
    // next=cur->next;
    while(prev!=q->tail){
        next=cur->next;
        cur->next=prev;
        prev=cur;
        cur=next;
    }
    q->tail=q->head;
    q->head=prev;
}
