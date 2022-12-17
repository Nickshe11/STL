#include<iostream>
#include<array>
#include<vector>
//using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define tab "\t"

template <typename T> void print(const std::vector<T>& vec);

//#define STL_ARRAY
#define STL_VECTOR

void main()
{
	setlocale(LC_ALL, "");
#ifdef STL_ARRAY
	//array - это контейнер, который хранит данные в виде статического массива
	const int SIZE = 5;
	std::array<int, SIZE> arr = { 3,5,8,13,21 };
	for (int i = 0; i < arr.size(); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;
#endif // STL_ARRAY
#ifdef STL_VECTOR
	//vector - это контейнер, который хранит данные в виде динамического массива
	std::vector<int>vec = { 0,1,1,2,3,5,8,13,21,34 };
	print(vec);
	vec.push_back(123);
	print(vec);
	vec.resize(7);
	//vec.shrink_to_fit();
	//print(vec);
	vec.reserve(12);
	print(vec);
#endif // STL_VECTOR	
}
template<typename T>void print(const std::vector<T>& vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << tab;
	}
	cout << endl;
	cout << "Size: " << vec.size() << endl;
	cout << "Max size: " << vec.max_size() << endl;
	cout << "Capacity: " << vec.capacity() << endl;
}