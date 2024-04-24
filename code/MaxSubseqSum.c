#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>




// 给定一个N个整数的序列，求子序列的最大值

// 暴力循环法
int MaxSubseqSum1(int A[],int N);

// 分治法
int MaxSubseqSum2(int A[],int left,int right);
int FindMaxCrossingSeq(int A[],int left,int right);
int MaxOfThree(int a,int b,int c);


// 动态规划
// dp[i]代表以A[i]结尾的最大子数组和
// 动态转移方程为if dp[i] > 0: dp[i+1] = dp[i] + A[i+1]
//              else; dp[i+1] = A[i+1]
int MaxSubseqSum3(int A[],int N);

int MaxOfThree(int a,int b,int c){
    int max;
    if (a>b){max = a;}
    else{max=b;}
    if (max<c){max=c;}
    return max;
}

int MaxSubseqSum1(int A[],int N){
    // 时间复杂度为O(N**3)，空间复杂度为O(1)
    int maxsum = 0;
    int i,j,k;
    for (i = 0;i < N;i++){
        for(j = i+1;j < N;j++){
            int seqsum = 0;
            for (k = i;k<=j;k++){
                seqsum += A[k];
                if (seqsum > maxsum) {maxsum = seqsum;}
            }
        }
    }
    return maxsum;
}

int FindMaxCrossingSeq(int A[],int left,int right){
    int mid = (left + right) / 2 ;
    int N = right - left + 1;
    int i,j;
    int left_sum = 0,right_sum = 0,left_maxsum = 0,right_maxsum = 0;
    for (i = mid-1;i>=0;i--){
        left_sum += A[i];
        if (left_maxsum < left_sum) {left_maxsum = left_sum;}
    }
    for (j = mid;j < N;j ++){
        right_sum += A[j];
        if (right_maxsum < right_sum) {right_maxsum = right_sum;}
    }
    return right_maxsum + left_maxsum;
}
int MaxSubseqSum2(int A[],int left,int right){
    int max_sum = 0;
    int mid,left_max,right_max;
    int N = right - left;
    if (N <= 1) {max_sum = A[left];}
    else{
        mid = (left + right)/2;
        left_max = MaxSubseqSum2(A,left,mid);
        right_max = MaxSubseqSum2(A,mid+1,right);
        max_sum = MaxOfThree(left_max,right_max,FindMaxCrossingSeq(A,left,right));
    }
    return(max_sum);
}


int MaxSubseqSum3(int A[],int N){
    // 创建一个长度为N的数组
    // calloc 适合为数组申请空间，要注意释放空间
    int sum_max = 0;
    int *dp = (int *)calloc(N,sizeof(int));
    dp[0] = A[0];
    for (int i = 1;i < N;i++){
        if (dp[i-1] > 0){
            dp[i] = dp[i-1] + A[i];
        }
        else{
            dp[i] = A[i];
        }
        sum_max = MaxOfThree(sum_max,dp[i],0);
    }
    free(dp);
    dp = NULL;
    return sum_max;
    


}


void Calculate_running_time1(int A[],int N,int t){
    // clock是clock()返回的变量类型
    clock_t start,stop;
    // 记录被测函数的时间，以ms为单位
    int duration;
    start = clock();
    for (int i = 0;i < t-1;i++){MaxSubseqSum1(A,N);}
    printf("MaxSubseqSum1暴力算法的结果为%d\n",MaxSubseqSum1(A,N));
    stop = clock();
    duration = (int)(stop-start) ;
    printf("运行的时间为%dms\n",duration);
}
void Calculate_running_time2(int A[],int N,int t){
    // clock是clock()返回的变量类型
    clock_t start,stop;
    // 记录被测函数的时间，以ms为单位
    int duration;
    start = clock();
    for (int i = 0;i < t-1;i++){MaxSubseqSum2(A,0,N-1);}
    printf("MaxSubseqSum2分治法的结果为%d\n",MaxSubseqSum2(A,0,N-1));
    stop = clock();
    duration = (int)(stop-start);
    printf("运行的时间为%dms\n",duration);
}

void Calculate_running_time3(int A[],int N,int t){
    // clock是clock()返回的变量类型
    clock_t start,stop;
    // 记录被测函数的时间，以ms为单位
    int duration;
    start = clock();
    for (int i = 0;i < t-1;i++){MaxSubseqSum3(A,N);}
    printf("MaxSubseqSum3动态规划法的结果为%d\n",MaxSubseqSum3(A,N));
    stop = clock();
    duration = (int)(stop-start);
    printf("运行的时间为%dms\n",duration);
}

int main()
{
    int array[50] = {0};
    srand(time(0));
    for(int i=0;i<50;i++)
    {
        array[i]=rand()%10;
    }
    int N;
    int t = 10000;
    N = sizeof(array)/sizeof(array[0]);
    Calculate_running_time1(array,N,t);
    Calculate_running_time2(array,N,t);
    Calculate_running_time3(array,N,t);
    
    
    return 0;
}