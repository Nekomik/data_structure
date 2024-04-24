#include <stdio.h>
#include <time.h>

void Calculate_running_time(){
    // clock是clock()返回的变量类型
    clock_t start,stop;
    // 记录被测函数的时间，以ms为单位
    double duration;

    start = clock();
    MyFunction();
    stop = clock();
    duration = (double)(stop-start);

    printf("运行的时间为%.5fms",duration);
}
int main(){
    return 0;
}