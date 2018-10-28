
#include "msgqueue.h"
#include <stdio.h>
#include <string.h>

#include <stdlib.h>

#define __compiler_offsetof(a,b) __builtin_offsetof(a,b)
 
#undef offsetof
#ifdef __compiler_offsetof
#define offsetof(TYPE,MEMBER) __compiler_offsetof(TYPE,MEMBER)
#else
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif
 
#define container_of(ptr, type, member) ({      \
    const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
    (type *)( (char *)__mptr - offsetof(type,member) );})


void free_msg(struct list *ptr)
{
	msgq_t *p = container_of(ptr, msgq_t, list);
	free(p->msg);
	p->msg = NULL;
	free(p);
	p = NULL;
}

struct list * malloc_msg(char *msg)
{
	if(NULL == msg)
	{
		return NULL;
	}
	int len = strlen(msg);
	msgq_t *onemsg = (msgq_t *)malloc(sizeof(msgq_t));
	if(NULL == onemsg)
	{
		printf("msg is nill\n");
		return NULL;
	}
	onemsg->list.next = NULL;
	onemsg->list.prv = NULL;
	char *onestr = (char *)malloc(len+1);
	if(NULL == onestr)
	{
		printf("str is nill\n");
		return NULL;
	}
	strcpy(onestr,msg);
	onestr[len+1] = 0;
	onemsg->msg = onestr;
	return &onemsg->list;
}

/*
参数1-head：链表的头
参数2-prv：链表的头的next;
*/
void Insert_Front(char * msg, struct list * head, struct list * next)
{
	struct list *tmp = malloc_msg(msg);
	Add_Front(tmp,head,next);
}


/*
参数1-head：链表的头
参数2-prv：链表的头的prv
*/
void Insert_Tail(char * msg, struct list * head, struct list * next)
{
	struct list *tmp = malloc_msg(msg);
	Add_Tail(tmp,head,next);
}

/*
参数1-head：链表的头
参数2-prv：链表的头的prv
*/
void Drop_Tail(struct list *head, struct list *prv)
{
	struct list *tmp = prv;
	Del_Tail(head,prv);
	free_msg(tmp);
}

void Foreach_Ele(struct list *head)
{
	struct list *tmp = head->next;

	do
	{
		msgq_t *p = container_of(tmp, msgq_t, list);
		printf("%s\n",p->msg);
		tmp = tmp->next;
	}while(tmp != head);

}

void Init_Listhead(struct list *head)
{
	Init_head(head);
}
