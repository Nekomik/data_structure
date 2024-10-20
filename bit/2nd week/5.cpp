#include <iostream>
using namespace std;

int main() {
    // 出栈序列中的每个数后面的比它小的数，是按递减排列的。

    int n,m;
    int lock = 0;
    while(true){
        cin>>n>>m;
        int a[n];

        if(n==0&&m==0) break;
        if(lock) cout<<endl;
        for(int i=0;i<m;i++){
            lock = 1;
            for(int j = 0;j<n;j++){
                cin >> a[j];
            }
            // 判断是否为出栈序列
            bool flag = true;
            for(int i=0;i<n-1;i++){
                for(int j=i+1;j<n;j++){
                    if(a[i]>a[j]){
                        for(int k=j;k<n-1;k++){
                            if(a[k]<a[k+1] && a[k] < a[i] && a[k+1] < a[i]){
                                flag = false;
                                break;
                            }
                        }
                    }
                }
            }
            if(flag) cout<<"Yes"<<endl;
            else cout<<"No"<<endl;
        }
        
    }
}