//该函数返回数x从低位开始的第d位数字，例如x=512，d=3时，返回512/100 = 5%10 = 5
int getdigit(int x, int d)
{
  //a数组的作用相当于pow(10,d-1)
	int a[3] = { 1,10,100 };
	return x / a[d-1] % 10;
}

//传入数组名相当于传入指针，所以在函数内可以直接对数组进行操作
void radix_sort(int a[], int len, int d)
{
	int count[10];
	for (int k = 1; k <= d; k++)
	{
		//根据第k位对数组进行计数排序，即算法导论中提到的稳定排序方法
		vector<int> bucket(len);
		int i;
		for (i = 0; i < 10; i++)
		{
			count[i] = 0;
		}

		for (i = 0; i < len; i++)
		{
			count[getdigit(a[i], k)]++;
		}

		for (i = 1; i < 10; i++)
		{
			count[i] += count[i - 1];
		}
    /*
    此处为了保证排序的有序性，必须从后往前遍历，例如：
    当数组中存在[87,86]，第一次按个位数排，变成了[86,87]，如果下一次按十位数从前往后遍历，
    在新数组中，86会占据count[8]的位置，而87则是count[8]-1的位置，即变成了[87,86]。
    而如果从后往前，在d+1位相同的情况下，先给位置的数一定是d位较大的，这样就不会破坏上一次排序的顺序。
    */
		for (i = len-1; i >= 0; i--)
		{
			int j = getdigit(a[i], k);
			bucket[count[j]-1] = a[i];
			count[j]--;
		}
    
		for (i = 0; i < len ; i++)
		{
			a[i] = bucket[i];
		}
	}
}
