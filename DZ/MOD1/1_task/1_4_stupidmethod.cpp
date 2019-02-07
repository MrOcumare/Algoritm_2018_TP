#include <iostream>


int kill(int n, int k) {
 
     int res = 0;
     for (int i=1; i<=n; ++i)
         res = (res + k) % i;
     return ++res;
 }
 
int main(){
    int n,k;

    std::cin >> n, k;
    if (n==1) {
        std::cout << 1;
    }
    else {
        std::cout << kill(n,k);
    }
    return 0;
}