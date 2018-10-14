#include <iostream>

template <class T>
void swap(T& value1, T& value2)
{
	T tmp = value1;
	value1 = value2;
	value2 = tmp;
}


//template <class T>
//using TLess = bool (const T& value1, const T& value2);

template <class T, class TLess>
void BubbleSort(T* arr, int size, TLess less)
{
	for (int i = 0; i < size; i++) {
		for (int j = 1; j < size - i; j++) {
			if (!less(arr[j - 1], arr[j])) {
				swap(arr[j - 1], arr[j]);
			}
		}
	}
}

struct Point {
	int X;
	int Y;
};

bool x_sort(const Point& p1, const Point& p2)
{
	return p1.X != p2.X ? p1.X < p2.X : p1.Y < p2.Y;
}

class YSort {
public:
	bool operator() (const Point& p1, const Point& p2) const
	{
		return p1.Y != p2.Y ? p1.Y < p2.Y : p1.X < p1.X;
	}
};

int dist(const Point& p1, const Point& p2)
{
	const int dx = p1.X - p2.X;
	const int dy = p1.Y - p2.Y;

	return dx * dx + dy * dy;
}

class DistSort {
public:
	DistSort() = default;
	DistSort(const Point& _p0) : p0(_p0) {}

	bool operator() (const Point& p1, const Point& p2) const
	{
		return dist(p1, p0) < dist(p2, p0);
	}
private:
	Point p0 = { 0, 0 };
};

int main()
{
	Point* points = new Point[4];
	points[0] = { 1, 2 };
	points[1] = { 2, -1 };
	points[2] = { 0, 0 };
	points[3] = { 1, 1 };

	BubbleSort(points, 4, x_sort);

	for (int i = 0; i < 4; i++) {
		std::cout << "(" << points[i].X << ", " << points[i].Y << ") ";
	}
	std::cout << std::endl;

	BubbleSort(points, 4, YSort());

	for (int i = 0; i < 4; i++) {
		std::cout << "(" << points[i].X << ", " << points[i].Y << ") ";
	}
	std::cout << std::endl;

	BubbleSort(points, 4, DistSort());

	for (int i = 0; i < 4; i++) {
		std::cout << "(" << points[i].X << ", " << points[i].Y << ") ";
	}
	std::cout << std::endl;

	BubbleSort(points, 4, DistSort({ 2, 2 }));

	for (int i = 0; i < 4; i++) {
		std::cout << "(" << points[i].X << ", " << points[i].Y << ") ";
	}
	std::cout << std::endl;

	BubbleSort(points, 4, [](const Point& p1, const Point& p2) {
		return p1.X != p2.X ? p1.X < p2.X : p1.Y < p2.Y;
	});

	for (int i = 0; i < 4; i++) {
		std::cout << "(" << points[i].X << ", " << points[i].Y << ") ";
	}
	std::cout << std::endl;

	Point p0 = { -2, 1 };
	BubbleSort(points, 4, [p0](const Point& p1, const Point& p2) {
		return dist(p1, p0) < dist(p2, p0);
	});

	for (int i = 0; i < 4; i++) {
		std::cout << "(" << points[i].X << ", " << points[i].Y << ") ";
	}
	std::cout << std::endl;


	return 0;
}