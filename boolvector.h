#pragma once
#include <iostream>

using namespace std;

typedef unsigned char byte;



class boolvector
{
public:
	boolvector(char *str, int size = -1);
	boolvector(unsigned int len = 0);
	boolvector(const boolvector &);
	~boolvector();

	boolvector& operator=(const boolvector&);
	boolvector operator&(const boolvector&);
	void operator&=(const boolvector&);
	boolvector operator|(const boolvector&);
	void operator|=(const boolvector&);
	boolvector operator^(const boolvector&);
	void operator^=(const boolvector&);
	boolvector operator~();
	boolvector operator<<(int);
	boolvector operator>>(int);
	void operator<<=(int);
	void operator>>=(int);
	int operator[](int);
	/*Ввод вывод*/
	void printBv();
	friend istream& operator>>(istream &r, boolvector &t)
	{
		char buf[80];
		cout << "Enter the vector" << endl;
		gets_s(buf);
		boolvector temp(buf);
		t = buf;
		return r;
	}
	friend ostream& operator<<(ostream &r, boolvector &t)
	{
		if (t.bv != NULL) {
			byte mask = 1;
			for (int index = 0; index < t.len_mas; index++)
			{
				for (mask = 1 << 7; mask; mask >>= 1)
				{
					if (t.bv[index] & mask)
						r << '1';
					else
						r << '0';
				}
			}
			r << endl;
		}
		return r;
	}
	/*Установка в 1 или 0*/
	void set0(int);
	void set1(int);
	void all0();
	void all1();
	void set0from(int, int);
	void set1from(int, int);
	void invert(int);
	void invertFrom(int, int);
	int size();
	int size_bv();
	int weight();
private:
	int len_bv, len_mas;
	byte *bv;
};

