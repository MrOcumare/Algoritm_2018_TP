#include <iostream>
#include <algorithm>
#include <string>

struct Bounds {
	int Min;
	int Max;
};

template <class T>
using TKey = int (const T&);

template <class T>
Bounds findMinMaxKey(const T* arr, int size, TKey<T> getKey)
{
	int min = INT_MAX;
	int max = INT_MIN;
	for (int i = 0; i < size; i++) {
		min = std::min(min, getKey(arr[i]));
		max = std::max(max, getKey(arr[i]));
	}

	return { min, max };
}

template <class T>
void CountSort(T* arr, int size, TKey<T> getKey)
{
	auto bounds = findMinMaxKey(arr, size, getKey);

	const int binsCount = bounds.Max - bounds.Min + 1;
	int* bins = new int[binsCount];
	memset(bins, 0, binsCount * sizeof(int));
	for (int i = 0; i < size; i++) {
		bins[getKey(arr[i]) - bounds.Min]++;
	}

	for (int i = 1; i < binsCount; i++) {
		bins[i] += bins[i - 1];
	}

	T* tmp = new T[size];
	for (int i = 0; i < size; i++) {
		tmp[i] = arr[i];
	}

	for (int i = size - 1; i >= 0; i--) {
		int& bin = bins[getKey(tmp[i]) - bounds.Min];
		arr[--bin] = tmp[i];
	}

	delete[] tmp;
	delete[] bins;
}

int key(const int& v)
{
	return v;
}

int length(const std::string& str)
{
	return str.size();
}

int main()
{
	int size = -1;
	std::cin >> size;
	
	std::string* arr = new std::string[size];
	for (int i = 0; i < size; i++) {
		std::cin >> arr[i];
	}

	CountSort(arr, size, length);

	for (int i = 0; i < size; i++) {
		std::cout << arr[i] << " ";
	}

	delete[] arr;
	return 0;
}