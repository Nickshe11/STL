#define _CRT_SECURE_NO_WARNINGS

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



const std::map<int, std::string> violation =
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
	~Crime() {};
	friend std::ostream& operator <<(std::ostream& os, const Crime& obj);
	friend std::ofstream& operator<<(std::ofstream& ofs, const Crime& obj);
};
std::ostream& operator <<(std::ostream& os, const Crime& obj)
{
	return os << violation.at(obj.id) << ", " << obj.place;
}

std::ofstream& operator<<(std::ofstream& ofs, const Crime& obj)
{
	ofs << obj.id << " " << obj.place;
	return ofs;
}
void print(const std::map< std::string, std::list<Crime>>& base);
void save(const std::map<std::string, std::list<Crime>>& base, const std::string& filename);
void load(std::map<std::string, std::list<Crime>>& base, const std::string& filename);

#define MAP_FROM_PC
#define STD_STRING_PARSE


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
	save(base, "base.txt");
	system("notepad base.txt");

#endif // MAP_FROM_PC
}

void print(const std::map<std::string, std::list<Crime>>& base)
{
	for (std::map<std::string, std::list<Crime>>::const_iterator it = base.begin(); it != base.end(); ++it)
	{
		cout << it->first << ":\n";
		for (std::list<Crime>::const_iterator jt = it->second.begin(); jt != it->second.end(); jt++)
		{
			cout << *jt << endl;
		}
		cout << delimiter << endl;
	}
}
void save(const std::map<std::string, std::list<Crime>>& base, const std::string& filename)
{
	std::ofstream fout(filename.c_str());
	//fout.open("Crime.txt", std::ios::app);
	for (std::map<std::string, std::list<Crime>>::const_iterator it = base.begin(); it != base.end(); ++it)
	{
		fout << it->first << ":\n";
		for (std::list<Crime>::const_iterator jt = it->second.begin(); jt != it->second.end(); ++jt)
		{
			fout << *jt << endl;
		}
		fout << endl;
	}
	fout.close();
}

void load(std::map<std::string, std::list<Crime>>& base, const std::string& filename)
{
	std::ifstream fin(filename.c_str());
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			std::string license_plate;
			std::getline(fin, license_plate, ':');
			if (license_plate.empty())continue;
			std::string all_crimes;
			std::getline(fin, all_crimes);
			all_crimes.erase(0, 1);
#ifdef STD_STRING_PARSE
			/*size_t start = 0;
			size_t end = 0;*/
			for (
				int start = 0, end = all_crimes.find(',');
				/*end != std::string::npos*/;
				start = end + 1, end = all_crimes.find(',', end + 1)
				)
			{
				std::string place = all_crimes.substr(start, end - start);
				if (place[place.size() - 1] == ';')place[place.size() - 1] = 0;
				int id = std::stoi(place);
				place[0] = ' ';//удаляем цифру в начале строки
				place.erase(0, place.find_first_not_of(' '));
				//Crime crime(id, place);
				base[license_plate].push_back(Crime(id, place));
				if (end == std::string::npos)break;
			}
#endif // STD_STRING_PARSE
#ifndef STD_STRING_PARSE
			int size = all_crimes.size() + 1;
			char* szbuffer = new char[size] {};
			strcpy_s(szbuffer, size, all_crimes.c_str());

			char delimiters[] = ",;";
			for (char* pch = strtok(szbuffer, delimiters); pch; pch = strtok(NULL, delimiters))
			{
				int id = std::atoi(pch);
				pch[0] = ' ';
				while (pch[0] == ' ')
				{
					for (int i = 0; pch[i]; i++)pch[i] = pch[i + 1];
				}
				Crime crime(id, pch);
				base[license_plate].push_back(crime);
			}
			delete[]szbuffer;
#endif // !STD_STRING_PARSE				
		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: file not found" << endl;
	}


}


