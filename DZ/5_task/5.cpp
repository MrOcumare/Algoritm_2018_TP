/* 
На числовой прямой окрасили N отрезков.
Известны координаты левого и правого концов каждого отрезка [Li, Ri]. Найти длину окрашенной части числовой прямой.
N ≤ 10000. Li, Ri — целые числа в диапазоне [0, 109].
Ввод	Вывод
3
1 4
7 8
2 5
        5
*/

#include <iostream>

struct P{
    int val;
    bool flag;
    P(){
        val = 0;
        flag = false;
    }
};

void Merge(P*, int, int, int);
void MergeSort(P*, int, int);
int drow_line(int , P*);
void Print_array(P*, int);


int main() {
    int count_of_split = 0,
            count_of_points = 0,
            first_point = 0,
            second_point = 0;
    std::cin >> count_of_split;
    count_of_points = count_of_split * 2;
    P* Array_of_pints = new P[count_of_points];
    for (int i = 0; i < count_of_points; i++){
        std::cin >> first_point >> second_point;
        Array_of_pints[i].val = first_point;
        Array_of_pints[i].flag = true;
        Array_of_pints[++i].val = second_point;
    }
    std::cout << drow_line(count_of_points, Array_of_pints);
    delete[] Array_of_pints;
    return 0;
}

void Merge(P* Array_of_pints, int left, int right, int medium)
{
    int j = left;
    int k = medium + 1;
    int count = right - left + 1;

    if (count <= 1) return;
    P *tmp = new P [count];
    for (int i = 0; i < count; ++i) {
        if (j <= medium && k <= right) {
            if (Array_of_pints[j].val < Array_of_pints[k].val)
                tmp[i] = Array_of_pints[j++];
            else
                tmp[i] = Array_of_pints[k++];
        } else {
            if (j <= medium)
                tmp[i] = Array_of_pints[j++];
            else
                tmp[i] = Array_of_pints[k++];
        }
    }
    j = 0;
    for (int i = left; i <= right; ++i) {
        Array_of_pints[i] = tmp[j++];
    }
    delete[] tmp;
}


void MergeSort(P *Array_of_pints, int first, int last)
{
    int middle = 0;
    if(first >= last) return;
    middle = first + (last - first) / 2;
    MergeSort(Array_of_pints, first, middle);
    MergeSort(Array_of_pints, middle + 1, last);
    Merge(Array_of_pints, first, last, middle);

};


int drow_line(int count_of_points, P *Array_of_pints){
    MergeSort(Array_of_pints, 0 , count_of_points - 1);
    int begin = Array_of_pints[0].val;
    int result = 0;
    int tol = 0;
    for (int i = 0; i < count_of_points; ++i){
        if (Array_of_pints[i].flag == true) tol++;
        if (Array_of_pints[i].flag == false) tol--;
        if (tol == 0){
            result = result + Array_of_pints[i].val - begin;
            if (i  < count_of_points - 1){
                begin = Array_of_pints[i + 1].val;
            }
        }
    }
    //Print_array(Array_of_pints, count_of_points);
    return result;
}

void Print_array(P* Array_of_pints, int count_of_points){
    for (int i = 0; i < count_of_points; ++i) {
        std::cout << Array_of_pints[i].val << " ";
    }
    std::cout << '\n';
}