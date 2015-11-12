#ifndef __QUEUE_H
#define __QUEUE_H

typedef struct Queue {
	List * head;
	List * last;
	unsigned size;
} Queue;

#endif