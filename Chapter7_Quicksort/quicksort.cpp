#include <iostream>
#include <array>
#include <ctime>
#include <cstdlib>

#define ARRAY_SIZE 20

using namespace std;

//初始化array
void init_array(array <int,ARRAY_SIZE> &A,int s,int e)
{
    srand((unsigned) time(0));
    for(int i = 0; i < ARRAY_SIZE; i++)
    {
        A[i] = s+(e-s)*rand()/RAND_MAX;
    }
}

void my_swap(int &a,int &b)
{
    int t = a;
    a = b;
    b = t;
}

//主要函数
int q_part(array <int,ARRAY_SIZE> &A,int p,int r)
{
    //哨兵值，用来与其他元素比较，比它大的放它右边，比它小的或相等的放它左边
    int pivot = A[r];
    //A[p]到A[i]均不大于哨兵值，A[i+1]到A[j]大于哨兵值，A[j]到A[r]尚未比较，i的初始值为p-1
    int i = p-1;
    for(int j = p; j < r; j++)
    {
        //i始终不大于j，且只在发现比pivot值小的元素时才会增加，以便将A[i]重新设为不大于Pivot的值A[j]
        if(A[j]<=pivot)
        {
            i++;
            my_swap(A[i],A[j]);
        }
    }
    my_swap(A[i+1],A[r]);
    return i+1;
}

void quicksort(array <int,ARRAY_SIZE> &A,int p,int r)
{
    //分治算法的Conquer步骤，不需要额外的Combine，因为这一步已经使每一个子数组都有序了
    if(p < r)
    {
        int q = q_part(A,p,r);
        quicksort(A,p,q-1);
        quicksort(A,q+1,r);
    }
}

int main()
{
    array<int,ARRAY_SIZE> a;
    init_array(a,5,40);
    for(int i = 0; i<20; i++)
    {
        cout<<a[i]<<" ";
    }
    cout<<endl;
    quicksort(a,0,19);
    for(int i = 0; i<20; i++)
    {
        cout<<a[i]<<" ";
    }
}


