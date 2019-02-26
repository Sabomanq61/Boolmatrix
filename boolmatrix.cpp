#include "pch.h"
#include "boolmatrix.h"

boolmatrix::boolmatrix(int m1, int n1)
{
	m = m1;
	n = n1;
	if (m > 0)
	{
		bm = new boolvector[m];
		boolvector temp(n);
		for (int i = 0; i < m; i++)
			bm[i] = temp;
	}
	else
		bm = NULL;
}
boolmatrix::boolmatrix(char **t, int m1)
{
	m = m1;
	bm = new boolvector[m];
	n = strlen(t[0]);
	for (int i = 1, d; i < m; i++)
	{
		d = strlen(t[i]);
		if (n < d)
			n = d;
	}

	for (int i = 0; i < m; i++)
	{
		boolvector temp(t[i], n);
		bm[i] = temp;
	}
}

boolmatrix::boolmatrix(const boolmatrix &t)
{
	m = t.m;
	n = t.n;
	bm = new boolvector[m];
	for (int i = 0; i < m; i++)
		bm[i] = t.bm[i];
}

boolmatrix::~boolmatrix()
{
	delete[]bm;
}

boolmatrix boolmatrix::operator&(const boolmatrix &t)
{
	if (m != t.m)
		return *this;
	int size = 1;
	if (n < t.n)
		size = n;
	else
		size = t.n;
	boolmatrix temp(m, size);
	for (int i = 0; i < m; i++)
		temp.bm[i] = bm[i] & t.bm[i];
	return temp;
}

boolmatrix& boolmatrix::operator&=(const boolmatrix &t)
{
	*this = *this &t;
	return *this;
}

boolmatrix boolmatrix::operator|(const boolmatrix &t)
{
	if (m != t.m)
		return *this;
	int size;
	if (n > t.n)
		size = n;
	else
		size = t.n;
	boolmatrix temp(m, size);
	for (int i = 0; i < m; i++)
		temp.bm[i] = bm[i] | t.bm[i];
	return temp;
}

boolmatrix& boolmatrix::operator|=(const boolmatrix &t)
{
	*this = *this | t;
	return *this;
}


boolmatrix boolmatrix::operator^(const boolmatrix &t)
{
	if (m != t.m)
		return *this;
	int size;
	if (n > t.n)
		size = n;
	else
		size = t.n;
	boolmatrix temp(m, size);
	for (int i = 0; i < m; i++)
		temp.bm[i] = bm[i] ^ t.bm[i];
	return temp;
}
boolmatrix& boolmatrix::operator^=(const boolmatrix &t)
{
	*this = *this ^ t;
	return *this;
}

boolvector boolmatrix::or_all()
{
	boolvector temp(n);
	for (int i = 0; i < m; i++)
		temp |= bm[i];
	return temp;
}
boolvector boolmatrix::and_all()
{
	boolvector temp(n);
	temp.all1();
	for (int i = 0; i < m; i++)
		temp &= bm[i];
	return temp;
}
boolvector boolmatrix::exor()
{
	boolvector temp(bm[0]);

	for (int i = 1; i < m; i++)
		temp = temp ^ bm[i];
	return temp;
}

boolmatrix& boolmatrix::operator=(const boolmatrix &t)
{
	delete[]bm;
	m = t.m;
	n = t.n;
	bm = new boolvector[m];
	for (int i = 0; i < m; i++)
		bm[i] = t.bm[i];
	return *this;
}


boolvector& boolmatrix::operator[](int t)
{
	if (t >= 0 && t < m)
	{
		return bm[t];
	}
	return bm[0];
}

void boolmatrix::set1(int t)
{
	if (t >= 0 && t < m)
	{
		bm[t].all1();
	}
}
void boolmatrix::set0(int t)
{
	if (t >= 0 && t < m)
	{
		bm[t].all0();
	}
}
void boolmatrix::invert_string(int t)
{
	if (t >= 0 && t < m)
	{
		bm[t] = ~bm[t];
	}
}
void boolmatrix::set1fromto(int t, int index, int k)
{
	bm[t].set1from(index, k);
}
void boolmatrix::set0fromto(int t, int index, int k)
{
	bm[t].set0from(index, k);
}
void boolmatrix::invertfromto(int t, int p, int k)
{
	bm[t].invertFrom(p, k);
}


boolmatrix boolmatrix::operator<<(int t)
{
	boolmatrix temp(*this);
	temp <<= t;
	return temp;
}
boolmatrix boolmatrix::operator>>(int t)
{
	boolmatrix temp(*this);
	temp >>= t;
	return temp;
}
boolmatrix& boolmatrix::operator<<=(int t)
{
	for (int i = 0; i < m; i++)
		bm[i] <<= t;
	return *this;
}
boolmatrix& boolmatrix::operator>>=(int t)
{
	for (int i = 0; i < m; i++)
		bm[i] >>= t;
	return *this;
}

void boolmatrix::Show()
{
	for (int i = 0; i < m; i++)
	{
		bm[i].printBv();
	}
}

void boolmatrix::n1()
{
	cout << n << endl;
}

int boolmatrix::weight()
{
	int i = 0;
	for (int i1 = 0; i1 < m; i1++)
	{
		i += bm[i1].weight();
	}
	return i;
}
ostream& operator<<(ostream &r, boolmatrix &t)
{
	for (int i = 0; i < t.m; i++)
	{
		r << t.bm[i];
	}
	return r;
}

istream& operator>>(istream &r, boolmatrix &t)
{

	int m;
	cout << "enter m";
	r >> m;
	if (m > 0)
	{
		char ** s = new char *[m];

		for (int i = 0; i < m; i++)
		{
			s[i] = new char[50];

			r >> s[i];
		}

		t = boolmatrix(s, m);

		for (int i = 0; i < m; i++)
		{
			delete[]s[i];
		}
		delete[]s;
	}
	return r;
}

