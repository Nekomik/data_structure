#include <iostream> 
#include <vector> 
#include <queue>
#include <cstdio>
#include <iomanip>
using namespace std; 


// 用俩个队列来存储降落飞机，和起飞飞机。
// 用一个数组来表示跑道是否占用。
// 如果队列内存在飞机,并且跑道没有被占用,则可以降落.降落优先级高于起飞.

int total_fly_wait_time = 0; // 总飞行等待时间
int total_load_wait_time = 0; // 总降落等待时间





// 起飞飞机类, 用来存储飞机信息
class FlyPlane{
    public:
        int id; // 飞机id
        int time; // 飞机塞入队列时间
        int wait_time = 0; // 飞机等待时间
        FlyPlane(int id, int time):id(id), time(time){};
        
        void wait(){
            total_fly_wait_time++;
        }

    
};

class LoadPlane{
    public:
        int id; // 飞机id
        int time; // 飞机出队列时间
        int wait_time = 0; // 飞机等待时间
        LoadPlane(int id, int time):id(id), time(time){};
        
        void wait(){
            wait_time++;
            total_load_wait_time ++;
        }

};


// 遍历并对 LoadPlane 队列中所有飞机调用 wait() 方法
void waitForLoadPlanes(queue<LoadPlane>& load_queue) {
    size_t size = load_queue.size(); // 获取队列大小

    for (size_t i = 0; i < size; i++) {
        LoadPlane plane = load_queue.front(); // 获取前端元素
        plane.wait(); // 调用wait()方法
        load_queue.pop(); // 移除前端元素
        load_queue.push(plane); // 重新入队
    }
}

// 遍历并对 FlyPlane 队列中所有飞机调用 wait() 方法
void waitForFlyPlanes(queue<FlyPlane>& fly_queue) {
    size_t size = fly_queue.size(); // 获取队列大小

    for (size_t i = 0; i < size; i++) {
        FlyPlane plane = fly_queue.front(); // 获取前端元素
        plane.wait(); // 调用wait()方法
        fly_queue.pop(); // 移除前端元素
        fly_queue.push(plane); // 重新入队
    }
}




int main(){
    int runway_num, load_time, fly_time;
    cin >> runway_num >> load_time >> fly_time;
    vector<int> runway(runway_num, 0); // 跑道是否被占用
    vector<int> buy_time(runway_num, 0); // 飞机信息
    queue<LoadPlane> load_queue;
    queue<FlyPlane> fly_queue;
    
    int time = 0; // 当前时间

    int load_id = 5001;
    int fly_id = 1;

    // 主循环
    int load_num = 0; // 载入飞机数量
    int fly_num = 0; // 起飞飞机数量
    int total_load = 0;
    int total_fly = 0;


    int free_runway[runway_num];
    for(int i = 0; i < runway_num; i++){
        free_runway[i] = 0;
    }

    int lock = 0; // 锁定标志位, 用于判断是否结束输入
    int plane_on_runway = 0; 


    while(true){
         

        //  如果跑道为0，lock=1，栈为空，则结束循环
        if(lock == 1 && load_queue.empty() && fly_queue.empty() && plane_on_runway == 0){
            break;
        }
        plane_on_runway = 0;

        // 播报当前时间
        printf("Current Time: %4d\n",time);

        // 处理飞机跑道空闲播报
        for(int i = 0; i < runway_num; i++){
            if(free_runway[i] == 1){ 
                printf("runway %02d is free\n", i+1);
                free_runway[i] = 0;
            }
        }


        // 处理载入飞机
        if (lock!=1) {
            cin >> load_num >> fly_num; // 输入载入和起飞飞机数量
            if(load_num != -1 && fly_num != -1){
                total_load += load_num;
                total_fly += fly_num;
            }
        }

        if(load_num == -1 && fly_num == -1){
            lock = 1;
        }
        if(lock != 1){
            for(int i = 0; i < load_num; i++){
                load_queue.push(LoadPlane(load_id++, time)); // 载入飞机
            }
            for(int i = 0; i < fly_num; i++){
                fly_queue.push(FlyPlane(fly_id++, time)); // 起飞飞机
            }
        }






        for(int i = 0; i < runway_num; i++){
            if(runway[i] == 0 && load_queue.size() > 0){
                // 跑道空闲, 载入飞机
                runway[i] = load_time;
                buy_time[i] += load_time;   
                printf("airplane %04d is ready to land on runway %02d\n", load_queue.front().id, i+1);
                load_queue.pop();
            }
            // 跑道无空闲，我们什么都不做
        }

        for(int i = 0; i < runway_num; i++){
            if(runway[i] == 0 && fly_queue.size() > 0){
                // 跑道空闲, 载入飞机
                runway[i] = fly_time;
                buy_time[i] += fly_time;
                printf("airplane %04d is ready to takeoff on runway %02d\n", fly_queue.front().id, i+1);
                fly_queue.pop();
            }
        }   

        // 此时，队列内所有的飞机需要计算等待时间
        waitForLoadPlanes(load_queue);
        waitForFlyPlanes(fly_queue);




        // 播报当前时间
        
        // 播报跑道空闲情况
        int *used_runway = new int[runway_num]; // 跑道是否被占用
        for(int i = 0; i < runway_num; i++){

            used_runway[i] = 0; 


            if(runway[i] > 0){
                runway[i]--; // 跑道时间减一分钟
                used_runway[i] = 1; // 跑道被占用
                plane_on_runway ++;
            }

            // 跑道时间为0, 并且跑道之前被占用
            if(runway[i] == 0 && used_runway[i] == 1){
                free_runway[i] = 1; // 跑道空闲
            }

            

        }

        time++;
    }

    time--; // 减去最后一次循环的1分钟

      // 计算平均等待时间
    printf("simulation finished\n");
    printf("simulation time: %4d\n", time);


    // // 测试用
    // cout << "total_load_wait_time: " << total_load_wait_time <<"  total_load: " << total_load << endl;
    // cout << "total_fly_wait_time: " << total_fly_wait_time <<"  total_fly: " << total_fly <<endl;

    if(total_load == 0){
        printf("average waiting time of landing: %4.1f\n",0.0);
    }else{
        printf("average waiting time of landing: %4.1f\n", (float)total_load_wait_time/(float)total_load);
    }    
	if(total_fly == 0){
        printf("average waiting time of takeoff: %4.1f\n",0.0);
    }
    else{
        printf("average waiting time of takeoff: %4.1f\n", (float)total_fly_wait_time/(float)total_fly);
    }

   
    

    int busy_time = 0; 
    for(int i = 0; i < runway_num; i++){
        if(buy_time[i] > 0){  
            printf("runway %02d busy time: %4d\n", i+1, buy_time[i]);
            busy_time += buy_time[i];
        }
    }   
    double avg_busy_time = (double)busy_time/((double)runway_num*(double)time);

	printf("runway average busy time percentage: %4.1f%%\n", avg_busy_time*100);
    return 0;


}