/*Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел B[0..m-1]. 
Для каждого элемента массива B[i] найдите минимальный индекс k 
минимального элемента массива A, равного или превосходящего 
B[i]: A[k] >= B[i]. Если такого элемента нет, выведите n. 
Время работы поиска k для каждого элемента B[i]: O(log(k)). n, m ≤ 10000.

Формат ввода
В первой строчке записаны числа n и m. Во второй и третьей массивы 
A и B соответственно.
Ввод	Вывод
2 1¶
1 2¶
2¶        1¶

Ввод	            Вывод
4 3¶
2 4 5 7¶
4 6 1¶
                    1 3 0¶
*/
#include <iostream>



int prep_bin(int* Array, int sizeA, int num);
int find_binary(int* Array, int left, int right, int num);


int main()
{
    int sizeA = 0, sizeB = 0;
    std::cin >> sizeA >> sizeB;
    int* A = new int[sizeA];
    int* B = new int[sizeB];
    for (int i = 0; i < sizeA; i++){
        std::cin >> A[i];
    }
    for (int i = 0; i < sizeB; i++){
        std::cin >> B[i];
    }
    for(int i = 0; i < sizeB; i++)
    {
        std::cout << prep_bin(A, sizeA, B[i]) << ' ';
    }
    delete[] A;
    delete[] B;
	return 0;
}
int prep_bin(int* Array, int sizeA, int num){
    int i = 0;
    int l = 0;
    int r = 0;
    while(Array[1 << i] < num && (1 << i) < sizeA) i++;
    if (i == 0) {
        l = 0;
    } else {
        l = 1 << (i - 1);
    }
    if ((1 << i) < sizeA) {
        r = 1 << i;
    } else {
        r = sizeA;
    }
    return find_binary(Array, l, r, num);   
}
int find_binary(int* Array, int left, int right, int num)
{
    int first = left;
    int last = right; 
    int mid = 0;
    while( first < last ) 
    {
        mid = (first + last) / 2;
        if(num <= Array[mid]){
            last = mid;
        }
        else{
            first = mid + 1;
        }		
    }
    if (num <= Array[last]) {
        return last;
    } else { 
        return right;
    }
}