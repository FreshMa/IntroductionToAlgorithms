void Merge(vector<int> &A,int p, int q, int r){
    //左右半部分的个数
    int n1 = q-p+1;
    int n2 = r-q;
    vector<int> L(n1+1);
    vector<int> R(n2+1);
    //分别将左右半部分数组复制到新数组中
    for(int i = 0;i<n1;i++){
        L[i] = A[p+i];
    }
    for(int j = 0;j<n2;j++){
        R[j] = A[q+j+1];
    }
    //设立了哨兵值，其实没必要，比较指针有没有到达尾部就可以了
    L[n1] = INT_MAX;
    R[n2] = INT_MAX;

    int i = 0;
    int j = 0;
    int k = p;
    while(k <= r){
        //分别给给左右数组赋值
        if(L[i]<=R[j]){
            A[k++] = L[i++];
        }
        else{
            A[k++] = R[j++];
        }
    }
    //把剩余的元素逐个赋给原数组
    while(L[i]!=INT_MAX){
        A[k++] = L[i++];
    }
    while(R[j]!=INT_MAX){
        A[k++] = R[j++];
    }
}

void MergeSort(vector<int> & A,int s,int e){
    //在s和e不相等的时候循环
    if(e > s){
        int mid = (e+s)/2;
        //不断划分左右数组
        MergeSort(A,s,mid);
        MergeSort(A,mid+1,e);
        //上面两步执行完之后，返回的数组A[s,mid],A[mid+1,e]各自都是有序的，用Merge合并
        Merge(A,s,mid,e);
    }
}
