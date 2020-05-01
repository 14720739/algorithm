#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define  queue_length 5000

typedef struct binary_tree_node {
  binary_tree_node *p_left;
  binary_tree_node *p_right;
  int data;

}
binary_tree_node;

int head=0;
int tail=0;
int insert_head=0;
int insert_tail=0;
int traversing_head=0;
int traversing_tail=0;
binary_tree_node *bt_queue[queue_length];
binary_tree_node *traversing_queue[queue_length];

int enqueue(binary_tree_node **array,binary_tree_node *p_bt_root)
{
int next_pos=(tail+1)%queue_length;
if(next_pos==head) return 0;
array[tail]=p_bt_root;
tail=next_pos;
return 1;
}

binary_tree_node *dequeue(binary_tree_node **array)
{
binary_tree_node *ret;
if(tail==head) return NULL;
ret=array[head];
head=(head+1)%queue_length;
return ret;
}

binary_tree_node *initiate_binary_tree(int height) {
int count;
binary_tree_node *p_node,*p_head;
srand(time(NULL));
int number_nodes=rand()%(int)(pow(2,height+1)-pow(2,height))+pow(2,height);
printf("number_nodes=%d\n",number_nodes);
count=0;
p_node=(binary_tree_node *)malloc(sizeof(binary_tree_node));
p_node->data=rand()%1000;
p_node->p_left=NULL;
p_node->p_right=NULL;
p_head=p_node;
count++;
head=insert_head;
tail=insert_tail;
printf("head=%d,tail=%d\n",head,tail);
if(!enqueue(bt_queue,p_node)) exit(0);
while(count<number_nodes)
{
p_node=dequeue(bt_queue);
if(!p_node) exit(0);
p_node->p_left=(binary_tree_node *)malloc(sizeof(binary_tree_node));
p_node->p_left->data=rand()%1000;
p_node->p_left->p_left=NULL;
p_node->p_left->p_right=NULL;
if(!enqueue(bt_queue,p_node->p_left)) exit(0);
count++;
p_node->p_right=(binary_tree_node *)malloc(sizeof(binary_tree_node));
p_node->p_right->data=rand()%1000;
p_node->p_right->p_left=NULL;
p_node->p_right->p_right=NULL;
if(!enqueue(bt_queue,p_node->p_right)) exit(0);
count++;
}
insert_head=head;
insert_tail=tail;
return p_head;
}

void print_binary_tree(binary_tree_node *p_head)
{
head=traversing_head;
tail=traversing_tail;
binary_tree_node *p;
if(!enqueue(traversing_queue,p_head)) exit(0);
while(head!=tail)
{
 p=dequeue(traversing_queue);
 printf("%d-->",p->data);
 if(p->p_left!=NULL) if(!enqueue(traversing_queue,p->p_left));
 if(p->p_right!=NULL) if(!enqueue(traversing_queue,p->p_right));
}

printf("END\n");

}

void destroy_binary_tree_c(binary_tree_node *pointer)
{
if(!pointer) return;
destroy_binary_tree_c(pointer->p_left);
destroy_binary_tree_c(pointer->p_right);
printf("%d-->",pointer->data);
free(pointer);
}

void destroy_binary_tree(binary_tree_node *p_head)
{
destroy_binary_tree_c(p_head);
}


main()
{
int height=4;
binary_tree_node *p_head;
p_head=initiate_binary_tree(height);
print_binary_tree(p_head);
destroy_binary_tree_c(p_head);
printf("Destroyed\n");
}

