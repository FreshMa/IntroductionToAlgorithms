#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

/*
heapify函数的前置条件是，i节点的左右孩子都是一个良好的堆
该函数的目的是将i节点作为这两个堆的父节点之后，以i为根的堆仍然能维持堆的属性
len是数组大小，从1开始，而数组下标则从0开始，这样的话，左孩子坐标为2i+1，右孩子坐标为2i+2
*/
void heapify(int *A,int i,int len)
{
	int l = 2*i+1;
	int r = 2*i+2;
	int max;
	if(l < len && A[i] < A[l])
		max = l;
	else
		max = i;
	if(r < len && A[max] < A[r])
		max = r;
	if(i!=max)
	{
		int t = A[i];
		A[i] = A[max];
		A[max] = t;
		//调换了a[i]和a[max]的位置之后，可能会使新的a[max]不符合堆属性，继续调用heapify
		heapify(A,max,len);
	}
}

void build_heap(int *A,int len)
{
	for(int i = len/2-1;i>=0;i--)
	{
		heapify(A,i,len);
	}
}


void init(int *A,int len)
{
    srand((unsigned)time(0));
    for(int i = 0;i < len;i++)
    {
        A[i] = 2+198*rand()/RAND_MAX;
    }
}

void heap_sort(int *A,int len)
{
    //建好堆之后最大值是A[0]
    build_heap(A,len);
    /*
    用一个临时变量tl来确定heapify的边界，在tl之前（包括tl）的都是待heapify的元素，在tl之后的都是曾经的A[0]，即极大值们。
    建立递增数组，将每次循环产生的A[0]放到A[tl]上，tl每次减1，代表heapify的边界越来越小，一直到tl=1为止。此时的数组已经是一个有序数组了。
    堆排序使用了n次heapify，所以它的复杂度是O(nlg(n))
    */
    int tl = len;
    for(int i = 0;i<len;i++)
    {
        int temp = A[tl-1];
        A[tl-1] = A[0];
        A[0] = temp;
        tl--;
        //要保证A[0]始终是数组中的最大值
        heapify(A,0,tl);
    }
}

void display(int *A,int len)
{
    for(int i = 0;i<len;i++)
    {
        cout<<A[i]<<" ";
    }
    cout<<endl;
}

int main()
{
    int a[20] = {0};
    init(a,20);
    display(a,20);
    cout<<"******************"<<endl;
    heap_sort(a,20);
    display(a,20);
    //main函数中没有显式return语句的话，默认添加return 0，不过仅仅在main函数中
}

