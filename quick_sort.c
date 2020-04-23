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

int partition(data_node *array,int p, int r)
{
   int pivot=array[r].data;
   int i=p,j;
   data_node tmp;
   for(j=p;j<=r-1;j++)
    {
     if(array[j].data<=pivot) 
        {
          tmp=array[j];
          array[j]=array[i];
          array[i]=tmp;
          i++;
        }
     }
      tmp=array[i];
      array[i]=array[r];
      array[r]=tmp;
      return i;
}

void quick_sort_c(data_node *array,int p,int r)
{
  int q;
  if(p>=r) return;
  q=partition(array,p,r);
  quick_sort_c(array,p,q-1);
  quick_sort_c(array,q+1,r);
}

void quick_sort(data_node *array,int n)
{
  quick_sort_c(array,0,n-1);
}


int  main()
{
    int array_length=50,scope=300;
    data_node initial_array[array_length];
    initiate_array(initial_array,array_length,scope);
    printf("Initial Array:");
    array_print(initial_array,array_length);
    quick_sort(initial_array,array_length);
    printf("After sorted:");
    array_print(initial_array,array_length);
}
