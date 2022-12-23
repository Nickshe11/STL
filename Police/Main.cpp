#include<iostream>
#include<fstream>
#include<map>
#include<list>
#include<string>

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n----------------------------\n"

void load(std::ifstream& fin);

std::map<int, std::string> violation =
{
	{0, "Проезд на красный"},
	{1, "Превышение скорости"},
	{2, "Парковка в неположенном месте"},
	{3, "Езда по встречной полосе"},
	{4, "Оскорбление офицера"},
	{5, "Езда в нетрезвом состоянии"},
	{6, "Дрифт на перекрестке"}
};

class Crime
{
	int id;
	std::string place;
public:
	Crime(int violation, const std::string& place) :
		id(violation), place(place) {};
	Crime(const std::string& violation, const const std::string& place)
	{

	}
	~Crime() {};
	friend std::ostream& operator <<(std::ostream& os, const Crime& obj);
	friend void print(std::map<std::string, std::list<Crime>>& base);
	friend void save(std::map<std::string, std::list<Crime>>& base);
	friend void load(std::map<std::string, std::list<Crime>> base);
};
std::ostream& operator <<(std::ostream& os, const Crime& obj)
{
	return os << violation.at(obj.id) << ", " << obj.place;
}

//#define MAP_FROM_PC
#define MAP_FROM_FILE

void main()
{
	setlocale(LC_ALL, "");
#ifdef MAP_FROM_PC
	std::map <std::string, std::list <Crime>> base =
	{
		{"a777bb",{Crime(0, "Улица Ленина"), Crime(6, "Улица Космонавтов"), Crime(3, "Улица Октябрьская")}},
		{"m123ab", {Crime(2, "площадь Революции")}},
		{"a234bb", {Crime(5, "улица Ленина"), Crime(4, "улица Ленина")}}
	};
	print(base);
	//save(base);
#endif // MAP_FROM_PC

#ifdef MAP_FROM_FILE
	std::map<std::string, std::list<Crime>> base{};
	load(base);

#endif // MAP_FROM_FILE

}
void print(std::map<std::string, std::list<Crime>>& base)
{
	for (std::map<std::string, std::list<Crime>>::iterator it = base.begin(); it != base.end(); ++it)
	{
		cout << it->first << ":\n";
		for (std::list<Crime>::iterator jt = it->second.begin(); jt != it->second.end(); jt++)
		{
			cout << *jt << endl;
		}
		cout << delimiter << endl;
	}
}
void save(std::map<std::string, std::list<Crime>> base)
{
	std::ofstream fout;
	fout.open("Crime.txt", std::ios::app);
	for (std::map<std::string, std::list<Crime>>::iterator it = base.begin(); it != base.end(); ++it)
	{
		fout << it->first << ":\n";
		for (std::list<Crime>::iterator jt = it->second.begin(); jt != it->second.end(); jt++)
		{
			fout << *jt << endl;
		}
		fout << delimiter << endl;
	}
	fout.close();
}

void load(std::map<std::string, std::list<Crime>> base)
{
	std::ifstream fin("Crime.txt");
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			std::string car_number{};
			std::string crime{};
			std::string place{};
			int id;

			std::list <Crime> list;
			std::getline(fin, car_number);
			car_number.pop_back();

			//while (crime!=delimiter)
			//{
				std::getline(fin, crime,',');
				std::getline(fin, place);
				//if (crime == delimiter) break;
				//else
				//{
					for (std::map <int, std::string>::iterator it = violation.begin(); it != violation.end(); it++)
					{
						if (crime == it->second)
						{
							id = it->first;
							Crime car(id, place);
							list.push_back(car);
							break;
						}
					}
				//}
			//}


			//Crime crime(violation, place);
			//Crime crime ((std::getline(fin, violation, ',')), (std::getline(fin, place, ' ')))



		}
	}
}