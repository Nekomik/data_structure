#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int i,j;
    cin >> i >> j;

    // 我们让不同层的i，j找到同层的父节点。如果为同一个父节点，那么输出。
    int pos_i = i;
    int pos_j = j;
    int i_level = log2(pos_i);
    int j_level = log2(pos_j);
    
    if(arr[pos_i-1] == 0){
        cout << "ERROR: T[" << pos_i << "] is NULL" << endl;
        return 0;
    }

    if(arr[pos_j-1] == 0){
        cout << "ERROR: T[" << pos_j << "] is NULL" << endl;
        return 0;
    }



    while(i_level!= j_level){
        if(i_level > j_level){
            i_level--;
            pos_i = pos_i/2;
        }
        else{
            j_level--;
            pos_j = pos_j/2;
        }
    }

    while(pos_i!= pos_j && pos_i!= 0 && pos_j!= 0){
        pos_i = (pos_i/2);
        pos_j = (pos_j/2);
    }
    if(pos_i == pos_j){
        cout << pos_i <<" " << arr[pos_i-1] <<endl;
    }
    return 0;
}