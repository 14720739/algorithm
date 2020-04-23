#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct data_node {
  int id;
  int data;
} data_node;

void initiate_array(data_node *array,int n,int scope)
{
  srand(time(NULL));
  for(int i=0;i<n;i++)
    {
       array[i].data=rand()%scope;
       array[i].id=i;
    }

}

void array_print(data_node *array,int n)
{
    int i;
    for(i=0;i<n;i++)  printf("(%d,%d) ",array[i].id,array[i].data);
    printf("\n");

}

/* 依次从最小单位（一个元素分组）开始排序merge各个组，直至整个数组全部merge成功 */
void merge(data_node *array,int p,int q, int r)
{
int length=r-p+1;
int i=p;
int j=q+1;
int k=0;
int start,end;
data_node tmp[length];
while(i<=q && j<=r)
{
if(array[i].data<=array[j].data)
  {
     tmp[k].data=array[i].data;
     tmp[k++].id=array[i++].id;
  }
else
  {
    tmp[k].data=array[j].data;
    tmp[k++].id=array[j++].id;
  }
}
if(j<=r) {start=j; end=r;}
else {start=i;end=q; }  

while(start<=end) 
  {
   tmp[k].id=array[start].id;
   tmp[k++].data=array[start++].data;
  }


for(i=0;i<r-p+1;i++) 
  {
    array[p+i].data=tmp[i].data;
    array[p+i].id=tmp[i].id;
  }
 
}


void merge_sort_c(data_node *array,int p, int r)
{
 int q;
 q=(p+r)/2;
 if(p>=r) return;
 q=(p+r)/2;
 merge_sort_c(array,p,q);
 merge_sort_c(array,q+1,r);
 merge(array,p,q,r);

}

void merge_sort(data_node *array,int n)
{
  merge_sort_c(array,0,n-1);

}

int  main()
{
    int array_length=50,scope=300;
    data_node initial_array[array_length];
    initiate_array(initial_array,array_length,scope);
    printf("Initial Array:");
    array_print(initial_array,array_length);
    merge_sort(initial_array,array_length);
    printf("After sorted:");
    array_print(initial_array,array_length);
}
