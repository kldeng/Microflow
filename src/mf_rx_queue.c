#include "mf_rx_queue.h"
#include <stdio.h>
#include <stdlib.h>

struct q_node* q_node_init(void* packet_buffer, uint16_t length){
	struct q_node* q = (struct q_node*)malloc(sizeof(struct q_node));
	q->rx_packet = packet_buffer;
	q->packet_length = length;
	q->priority = 0;
	q->next_node = NULL;
	q->previous_node = NULL;
	return q;
}

struct mf_rx_queue* mf_rx_queue_init(){
	printf("--malloc starts---");
	struct mf_rx_queue* q = (struct mf_rx_queue*)malloc(sizeof(struct mf_rx_queue));
	if(q == NULL){
		printf("\nmalloc memory failed\n");
		return NULL;
	}else{
	q->queue_length = 0;
	q->head = NULL;
	q->tail = NULL;
	return q;
	}
}

uint8_t push_q_node(struct q_node* n, struct mf_rx_queue* q){
	uint8_t success_flag = 0;
	if(n == NULL || q == NULL)
		return success_flag;
	if(!q->queue_length){
		q->head = n;
		q->tail = n;
		q->queue_length = 1;
		success_flag = 1;
		return success_flag;
	}else{
		q->tail->next_node = n;
		n->previous_node = q->tail;
		n->next_node = NULL;
		q->tail = n;
		q->queue_length++;
		success_flag = 1;
		return success_flag;
	}
	return success_flag;
}

struct q_node* pop_q_node(struct mf_rx_queue* q){
	if(q->queue_length)
		return NULL;
	else{
		struct q_node* tmp = NULL;
		tmp = q->head;
		q->head = tmp->next_node;
		q->head->previous_node = NULL;
		tmp->next_node = NULL;
		q->queue_length--;
		return tmp;
	}
}

void destory_q_node(struct q_node* n){
	if(n != NULL)
		free(n);
}

void destory_queue(struct mf_rx_queue* q){
	uint64_t i;
	struct q_node* tmp;
	while(q->head){
		tmp = q->head;
		q->head = tmp->next_node;
		free(q->head);
	}
	free(q);
}

static void print_q_node(struct q_node* n){
	char* content = (char*)(n->rx_packet);
	content[n->packet_length] = '\0';
	printf("\nPacket content:%s\n", content);
}

void print_queue(struct mf_rx_queue* q){
	struct q_node* tmp;
	tmp = q->head;
	while(tmp){
		print_q_node(tmp);
		tmp = tmp->next_node;
	}

}
