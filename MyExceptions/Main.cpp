#include<iostream>
using namespace std;

void main()
{
	setlocale(LC_ALL, "");
	int a, b;
	cout << "¬ведите два числа: "; cin >> a >> b;
	try
	{
		cout << a / b << endl;
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
	catch(...)
	{
		cout << "Error: something happened" << endl;
	}
}