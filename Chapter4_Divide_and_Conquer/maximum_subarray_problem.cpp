#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

//定义结构体，结构体代表最大和的信息。
//low代表左下标，high代表右下标，sum代表数组左下标到右下标元素之和
struct r_tuple{
    int low;
    int high;
    int sum;
};

//最大和子数组跨过了mid下标
r_tuple* find_cross_max(vector<int> A,int low,int mid,int high){
    int max_left = INT_MIN;
    int max_right = INT_MIN;

    int left_pos,right_pos;
    r_tuple* temp = (r_tuple*)malloc(sizeof(r_tuple));

    int sum_left = 0;
    int sum_right = 0;
    //分别计算mid下标左右两边且包含A[mid]的最大连续元素和
    for(int i = mid;i >= low;i--){
        sum_left += A[i];

        if(sum_left>max_left){
            max_left = sum_left;
            left_pos = i;
        }
    }

    for(int j = mid+1;j<=high;j++){
        sum_right += A[j];
        if(sum_right>max_right){
            max_right = sum_right;
            right_pos = j;
        }
    }
    //将左右两边最大和相加即得包含A[mid]元素的最大和子数组
    int sum = sum_left+sum_right;
    
    temp->low = left_pos;
    temp->high = right_pos;
    temp->sum = sum;
    return temp;
}
//生成[s,e]的随机数
int randInt(int s,int e){
    return s+(int)(e-s)*rand()/(RAND_MAX);
}
//用随机数初始化vector
void initVector(vector<int> & v){
    int len = v.size();
    srand((int)time(0));
    for(int i =0;i<len;i++){
        v[i] = randInt(-20,30);
    }
    cout<<"vector init done;"<<endl;
}

/*
主方法，运用了分治法，最大和序列只有三种情况：
1.该序列出现在数组mid下标左侧；
2.该序列跨过了mid下标，也就是一部分在mid左侧，另一部分在mid右侧，且包含A[mid]；
3.该序列出现在数组A mid下标右侧
当左右下标相等，说明该子数组只有一个元素，最大和即是该元素。
*/
r_tuple* find_max_subarray(vector<int> v,int l,int h){
    r_tuple *t1 = (r_tuple*)malloc(sizeof(r_tuple));
    r_tuple *t2 = (r_tuple*)malloc(sizeof(r_tuple));
    r_tuple *t3 = (r_tuple*)malloc(sizeof(r_tuple));

    if(l == h){
        t1->low = l;
        t1->high = h;
        t1->sum = v[l];
        return t1;
    }
    else{
        int mid = (l+h)/2;
        t1 = find_max_subarray(v,l,mid);
        t2 = find_max_subarray(v,mid+1,h);
        t3 = find_cross_max(v,l,mid,h);
        //比较三个和谁大，谁大就返回谁，可以用嵌套三目运算符减少代码长度
        // return t1->sum>t2->sum&&t1->sum>t3->sum?t1:(t2->sum>t1->sum&&t2->sum>t3->sum?t2:t3);
        if(t1->sum>t2->sum&&t1->sum>t3->sum){
            return t1;
        }
        else if(t2->sum>t1->sum&&t2->sum>t3->sum){
            return t2;
        }
        else{
            return t3;
        }
    }
}

int main()
{
    r_tuple *p = NULL;
    vector<int> v(30);
    initVector(v);
    for(vector<int>::iterator it = v.begin();it!=v.end();it++){
        cout<<*it<<" ";
    }
    cout<<endl;
    p = find_max_subarray(v,0,29);
    cout<<p->sum<<endl;
    return 0;
}
