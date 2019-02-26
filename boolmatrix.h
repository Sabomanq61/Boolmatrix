#pragma once
#include "boolvector.h"
class boolmatrix
{
private:
	boolvector *bm;
	int m, n;
public:
	boolmatrix(int m1 = 1, int n1 = 1);
	boolmatrix(char **, int);
	boolmatrix(const boolmatrix&);
	~boolmatrix();
	/*logic operations*/
	boolmatrix operator&(const boolmatrix &);
	boolmatrix& operator&=(const boolmatrix &);
	boolmatrix operator|(const boolmatrix &);
	boolmatrix& operator|=(const boolmatrix &);
	boolmatrix operator^(const boolmatrix &);
	boolmatrix& operator^=(const boolmatrix &);
	boolvector or_all();
	boolvector and_all();
	boolvector exor();
	boolmatrix& operator=(const boolmatrix&);
	boolvector& operator[](int);
	void set1(int);
	void set0(int);
	void invert_string(int);
	void set1fromto(int, int k, int p);
	void set0fromto(int, int k, int p);
	void invertfromto(int, int p, int k);
	/*Сдвиги */
	boolmatrix operator<<(int);
	boolmatrix operator>>(int);
	boolmatrix& operator<<=(int);
	boolmatrix& operator>>=(int);

	/*Ввод вывод */
	void Show();
	void n1();
	int weight();
	friend ostream& operator<<(ostream &r, boolmatrix &t);
	friend istream& operator>>(istream &r, boolmatrix &t);
};

