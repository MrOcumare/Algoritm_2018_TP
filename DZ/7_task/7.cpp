#include <iostream>



template <class T>
void PrintArray(int n, T*Array){
    for (int i = 0; i < n; i++){
        std::cout << Array[i] << " ";
    }
}
template <class T>
void MSD(int n,T* Array, int start_poz, int end_poz, int setter){
    if (setter < 0 || start_poz >= end_poz){
        return;
    }

    if (setter == 0){
        return;
    }
    int i = start_poz;
    int j = end_poz;
    while (i < j) {
        while (i < j && ((Array[i] >> setter) & 1) == 0) ++i;
        while (i < j && ((Array[j] >> setter) & 1 )== 1) --j;
        if(i < j){
            std::swap(Array[i],Array[j]);
        }

    }
    if (((Array[j] >> setter) & 1) == 0){
        ++j;
    }
    MSD(n, Array, start_poz, j-1, setter - 1);
    MSD(n, Array, j, end_poz, setter - 1);
}
int main(){
    int n = 0;
    std::cin >> n;
    int start_poz = 0;
    int end_poz = n-1;
    int  setter = 63;
    long long*Array = new long long [n];
    for (int i = 0; i < n; i++){
        std::cin >> Array[i];
    }

    MSD(n, Array, start_poz, end_poz, setter);

    PrintArray(n,Array);
    delete[] Array;
    return 0;
}

