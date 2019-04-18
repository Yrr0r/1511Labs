#include "Queue.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct queue {
	int size;
	int *queue;
};
// Empty: -32768

Queue queueCreate(int maxSize){
	Queue q = malloc(maxSize*sizeof(int));
	q->queue = calloc(maxSize, sizeof(int));
	for(int i=0; i<maxSize; i++){
		q->queue[i] = '\0';
	}
	q->size = maxSize;
	return q;
}

void enqueue(Queue q, int item){
	for(int i=0; i<(q->size); i++){
		if(q->queue[i] == '\0'){
			q->queue[i] = item;
			return;
		}
	}
	fprintf(stderr, "Queue is full.");
}

int queueFront(Queue q){
	return q->queue[0];
}

int dequeue(Queue q){
	int i = q->queue[0];
	for(int i=1; i<(q->size); i++){
		q->queue[i-1] = q->queue[i];
	}
	q->queue[q->size-1] = '\0';
	return i;
}

int queueSize(Queue q){
	int i=0;
	while(q->queue[i] != '\0'){
		i++;
		if(i>(q->size)){
			break;
		}
	}
	return i;
}

void queueDestroy(Queue q){
	free(q->queue);
}
