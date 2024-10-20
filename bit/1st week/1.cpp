#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

int main() {
    int n, k, m;
    scanf("%d,%d,%d", &n, &k, &m);

    if (n < 1 || k < 1 || m < 1) {
        cout << "n,m,k must bigger than 0." << endl;
    } else if (k > n) {
        cout << "k should not bigger than n." << endl;
    } else {
        vector<int> a(n);
        for (int i = 1; i <= n; i++) {
            a[i - 1] = i; 
        }

        int index = k - 1; 
        int count = 0;     
        while (!a.empty()) {
            index = (index + m - 1) % a.size();  
            cout << a[index];  
            a.erase(a.begin() + index);  

            count++; 
            if (count % 10 == 0) {  
                cout << endl;
            } else if (!a.empty()) {
                cout << " "; 
            }
        }
    
        if (count % 10 != 0) {
            cout << endl;
        }
    }
    
    return 0;
}
