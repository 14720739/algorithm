#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define  queue_length 5000

#define rand_range 100

typedef struct binary_search_tree_node {
  binary_search_tree_node *p_left;
  binary_search_tree_node *p_right;
  int data;
  int level;
}
binary_search_tree_node;

int head=0;
int tail=0;
int insert_head=0;
int insert_tail=0;
int traversing_head=0;
int traversing_tail=0;
binary_search_tree_node *bt_queue[queue_length];
binary_search_tree_node *traversing_queue[queue_length];

int enqueue(binary_search_tree_node **array,binary_search_tree_node *p_bt_root)
{
int next_pos=(tail+1)%queue_length;
if(next_pos==head) return 0;
array[tail]=p_bt_root;
tail=next_pos;
return 1;
}

binary_search_tree_node *dequeue(binary_search_tree_node **array)
{
binary_search_tree_node *ret;
if(tail==head) return NULL;
ret=array[head];
head=(head+1)%queue_length;
return ret;
}

int insert_node_2_bstree(binary_search_tree_node *head,int data)
{
int level;
binary_search_tree_node *pointer,*new_pointer;
pointer=head;
printf("heander=%d-",head);
while(pointer!=NULL)
{
  if(data<pointer->data) 
   {
    if(pointer->p_left==NULL) 
     {
       new_pointer=(binary_search_tree_node *)malloc(sizeof(binary_search_tree_node));
       new_pointer->level=(pointer->level)+1;
       new_pointer->data=data;
       new_pointer->p_left=NULL;
       new_pointer->p_right=NULL;
       pointer->p_left=new_pointer;
       printf("pointer->p_left->level=%d data=%d ",pointer->p_left->level,pointer->p_left->data);
       return 1;
     }
    pointer=pointer->p_left;
    }
  else if(data>=pointer->data)
   {
     if(pointer->p_right==NULL)
     {
      pointer->p_right=(binary_search_tree_node *)malloc(sizeof(binary_search_tree_node));
      pointer->p_right->level=(pointer->level)+1;
      pointer->p_right->data=data;
      pointer->p_right->p_left=NULL;
      pointer->p_right->p_right=NULL;
      printf("pointer->p_right->level=%d data=%d ",pointer->p_right->level,pointer->p_right->data);
      return 1;
     }
    pointer=pointer->p_right;
   }
   else pointer=pointer->p_right;
}
putchar('\n');
return 1;
}

binary_search_tree_node *initiate_binary_search_tree(int height) {
int count,insert_data;
binary_search_tree_node *p_node,*p_head;
srand(time(NULL));
int number_nodes=rand()%(int)(pow(2,height+1)-pow(2,height))+pow(2,height);
printf("number_nodes=%d\n",number_nodes);
count=0;
p_node=(binary_search_tree_node *)malloc(sizeof(binary_search_tree_node));
insert_data=rand()%rand_range;
p_node->data=insert_data;
p_node->p_left=NULL;
p_node->p_right=NULL;
p_node->level=0;
p_head=p_node;
count++;
while(count<number_nodes)
{
if(!insert_node_2_bstree(p_head,rand()%rand_range)) exit(0);
count++;
}

return p_head;
}

void print_binary_tree(binary_search_tree_node *p_head)
{
head=traversing_head;
tail=traversing_tail;
binary_search_tree_node *p;
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

void destroy_binary_tree_c(binary_search_tree_node *pointer)
{
if(!pointer) return;
destroy_binary_tree_c(pointer->p_left);
destroy_binary_tree_c(pointer->p_right);
printf("%d-%d-->",pointer->level,pointer->data);
free(pointer);
}

void destroy_binary_tree(binary_search_tree_node *p_head)
{
destroy_binary_tree_c(p_head);
}

void inorder_traversing(binary_search_tree_node *p1)
{
if(p1==NULL) return;
inorder_traversing(p1->p_left);
printf("%d-->",p1->data);
inorder_traversing(p1->p_right);
}



main()
{
int height=4;
binary_search_tree_node *p_head;
p_head=initiate_binary_search_tree(height);
print_binary_tree(p_head);
inorder_traversing(p_head);
printf("Inorder Traversing Complted\n");
destroy_binary_tree(p_head);
printf("Destroyed\n");
}

