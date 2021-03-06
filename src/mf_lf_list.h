#ifndef MF_LF_LIST_H__
#define MF_LF_LIST_H__

#include "Openflow/types.h"

#define OFFSETOF(type, member) (size_t)&(((type*)0)->member)

#define container_of(ptr, type, member) ({const typeof( ((type *)0)->member ) *__mptr = (ptr);(type *)((char *)__mptr - OFFSETOF(type,member));})

struct lf_list
{
	struct lf_list * next;  
	uint32_t cache_padding;
	char mark;
};

typedef int (*compare)(void*, struct lf_list*);

void lf_list_insert(struct lf_list* i, struct lf_list* l);
struct lf_list * lf_list_pop(struct lf_list *l);
struct lf_list * lf_list_delete(struct lf_list* i, struct lf_list* l);
struct lf_list * lf_list_search_node(struct lf_list* l, compare, void*);
#endif
