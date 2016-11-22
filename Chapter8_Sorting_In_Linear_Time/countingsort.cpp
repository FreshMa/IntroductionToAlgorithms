//计数排序
void countingsort(vector<int> &A)
{
    int max_num = INT_MIN;
    for(int x:A)
    {
        if(max_num < x)
        {
            max_num = x;
        }
    }
    //B中元素个数等于A中最大元素值加一
    vector<int> B(max_num+1,0);
    for (int x:A)
    {
        //B[x]记录了A中等于x的元素的个数
        B[x] = B[x]+1;
    }

    for(int i = 1;i<B.size();i++)
    {
        //此时B[x]代表A中小于等于x元素的个数
        B[i] += B[i-1];
        //cout<<B[i]<<endl;
    }

    vector<int> C(A.size());
    //C中存放排好序的数组
    for(int i = A.size()-1;i>=0;i--)
    {
        /*
        B[i]是小于等于i的元素个数，所以当A中元素都不相同时，C[B[i]-1]就是i在排好序数组中的位置；
        当A中有相同元素时，即有相同的i时，每次赋值完成之后都要将B[i]减一，以免重复放置；
        例如，如果i = 5，B[i] = 3，意味着在原数组A中，有三个数小于等于5，那么i在新数组中的位置就是3-1=2，即C[2] = 5
        */
        C[B[A[i]]-1] = A[i];
        B[A[i]] -= 1;
    }
    //将新数组值赋给原数组
    A = C;
}
