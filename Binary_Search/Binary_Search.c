#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct data_node {
  int id;
  int data;
} data_node;

/* 使用rand()生成数组，srand()每次运行函数的时候重新生成种子，time(NULL)表示种子根据当前时间生成 */
void initiate_array(data_node *array,int n,int scope)
{
  srand(time(NULL));
  for(int i=0;i<n;i++)
    {
       array[i].data=rand()%scope;
       array[i].id=i;
    }

}

/* 打印数组 */
void array_print(data_node *array,int n)
{
    int i;
    for(i=0;i<n;i++)  printf("i=%d-(%d,%d) ",i,array[i].id,array[i].data);
    printf("\n");

}

/* 分区函数，用于对传入的数组进行分区，p-r指分区的范围，从下标为p到下标为r的位置进行分区 */
int partition(data_node *array,int p, int r)
{
   int pivot=array[r].data;
   int i=p,j;
   /* 指针i指向的是小于pivot的位置，通过置换，让指针i以左的元素全部小于pivot，然后把pivot移动到指针i指向的位置*/
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

/* 通过递归不断对数组进行分化处理，q的左边都是小数，右边都是大数，通过迭代递归，直至每个分组只有一个元素，说明全部都被处理 */
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

/* method=1 查找第一个等于value的值
 * method=2 查找最后一个等于value的值
 * method=3 查找第一个大于等于value的值
 * method=4 查找最后一个小于等于value的值 */
int binary_search(data_node *array,int n,int value,int method)
{
int p=0;
int r=n-1;
int mid;
printf("value=%d\n",value);
while(p<=r)
{
 int init_mid;
 mid = p + (r-p)/2;
 printf("p=%d,r=%d ",p,r);
 printf("mid=%d\n",mid);
 init_mid=mid;
 if(method==1) while(array[mid].data==value) mid--; 
 else if(method==2) while(array[mid].data==value) mid++;
 else if(method==3) while(array[mid].data>=value) mid--;
 else if(method==4) while(array[mid].data<=value) mid++;
 if(mid!=init_mid) 
    if(method==1 || method==3) return ++mid;
    else if(method==2 || method==4) return --mid;
 
 if(array[mid].data>value)   r=mid-1;
 else p=mid+1;
} 
}

int  main()
{
    int value,location;
    int array_length=50,scope=30;
    data_node initial_array[array_length];
    /* 初始化生成数组 */
    initiate_array(initial_array,array_length,scope);
    printf("Initial Array:");
    array_print(initial_array,array_length);
    /* 对数组进行快速排序 */
    quick_sort(initial_array,array_length);
    /* 打印排序以后的结果 */
    printf("After sorted:");
    array_print(initial_array,array_length);
    /* 输入要查找的数据 */
    printf("Please input the data you want to search:");
    scanf("%d", &value); 
    printf("You have inputed the value:%d\n",value);
    location=binary_search(initial_array,array_length,value,4);
    /* 打印 */
    printf("location=%d, value=%d\n",location,initial_array[location].data);
}
