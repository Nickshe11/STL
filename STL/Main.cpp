#include<iostream>
#include<array>
#include<vector>
#include<list>
//using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define tab "\t"

template <typename T> void print(const std::vector<T>& vec);
void print(const std::list<int>& list);

//#define STL_ARRAY
//#define MY_EXCEPTION
//#define STL_VECTOR
#define STL_LIST

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
#ifdef MY_EXCEPTION
	try
	{
		for (int i = 0; i < vec.capacity(); i++)
		{
			//cout << vec[i] << tab;
			cout << vec.at(i) << tab;
		}
		cout << endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
#endif // MY_EXCEPTION

	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;

	for (std::vector<int>::reverse_iterator it = vec.rbegin(); it != vec.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;

	int index, value, number;
	do
	{
		cout << "Введите индекс добавляемого элемента "; cin >> index;
		if (index > vec.size()) cout << "Error: out of range";
	} while (index >= vec.size());
	cout << "Введите количество добавляемых значений "; cin >> number;
	cout << "Введите значение добавляемого элемента "; cin >> value;

	vec.insert(vec.begin() + index, number, value);
	print(vec);

#endif // STL_VECTOR

#ifdef STL_LIST
	std::list<int> list = { 0, 1, 1, 2, 3, 5, 8, 13, 21 };
	print(list);
	int index, value;
	cout << "Введите добавляемое значение: "; cin >> value;
	do
	{
		cout << "Введите индекс добавляемого значения: "; cin >> index;
		if (index > list.size())cout << "Error: out of range";
	} while (index > list.size());

	std::list<int>::const_iterator it = list.begin();
	for (int i = 0; i < index; i++) it++;
	list.insert(it, value);
	print(list);
#endif // STL_LIST


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
void print(const std::list<int>& list)
{
	for (std::list<int>::const_iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	cout << "Size: " << list.size() << endl;
	cout << "Max size: " << list.max_size() << endl;
}