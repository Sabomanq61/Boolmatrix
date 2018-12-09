#include "stdafx.h"
#include "boolvector.h"


boolvector::boolvector(char *str, int size)
{
	int i = strlen(str) - 1;
	if (size == -1)
	{
		len_bv = i + 1;
	}
	else {
		len_bv = size;
	}
	if (len_bv)
	{
		len_mas = (len_bv - 1) / 8 + 1;

		bv = new byte[len_mas];
		all0();

		byte mask = 1;

		for (int i1 = len_bv, i2 = len_mas - 1; i1 > 0 && i >= 0; i1--, i--, mask <<= 1)
		{
			if (!mask)
			{
				mask = 1;
				i2--;
			}
			if (str[i] == '1')
				bv[i2] |= mask;
		}
	}

}
boolvector::boolvector(unsigned int len)
{
	if (len > 0) {
		len_bv = len;

		len_mas = (len_bv - 1) / 8 + 1;

		bv = new byte[len_mas];

		//ZeroMemory(bv, len_mas);
		all0();
	}
	else
	{
		bv = NULL;
	}
}

boolvector::boolvector(const boolvector &t)
{
	len_bv = t.len_bv;
	len_mas = t.len_mas;
	bv = new byte[len_mas];

	for (int i = 0; i < len_mas; i++)
		bv[i] = t.bv[i];
}

boolvector::~boolvector()
{
	delete[]bv;
}

boolvector& boolvector::operator=(const boolvector &t)
{
	if (this != &t)
	{
		delete[]bv;
		len_bv = t.len_bv;
		len_mas = t.len_mas;
		bv = new byte[len_mas];

		for (int i = 0; i < len_mas; i++)
			bv[i] = t.bv[i];
	}
	return *this;
}

boolvector boolvector::operator&(const boolvector &t)
{
	/*int length;
	if (len_bv > t.len_bv)
	{
		length = len_bv;
	}
	else
	{
		length = t.len_bv;
	}

	boolvector temp(length);

	for (int i1 = len_mas - 1, i2 = t.len_mas - 1, i = temp.len_mas - 1; i1 >= 0 && i2 >= 0; i1--, i2--, i--) {
		temp.bv[i] = bv[i1] & t.bv[i2];
	}*/

	int len;
	if (len_bv > t.len_bv)
	{
		len = t.len_bv;
	}
	else
	{
		len = len_bv;
	}
	boolvector temp(len);
	for (int i1 = len_mas - 1, i2 = t.len_mas - 1, i = temp.len_mas - 1; i1 >= 0 && i2 >= 0; i1--, i2--, i--) {
		temp.bv[i] = bv[i1] & t.bv[i2];
	}
	return temp;
}

void boolvector::operator&=(const boolvector &t)
{
	int i1 = len_mas - 1;
	for (int i2 = t.len_mas - 1; i1 >= 0 && i2 >= 0; i1--, i2--)
		bv[i1] = bv[i1] & t.bv[i2];
	for (; i1 >= 0; i1--)
		bv[i1] = 0;
}

boolvector boolvector::operator|(const boolvector &t)
{
	int length;

	if (len_bv > t.len_bv) {
		length = len_bv;
	}
	else
	{
		length = t.len_bv;
	}

	boolvector temp(length);
	int i1, i2, i3;
	for (i1 = temp.len_mas - 1, i2 = len_mas - 1, i3 = t.len_mas - 1; i2 >= 0 && i3 >= 0; i1--, i2--, i3--) {
		temp.bv[i1] = bv[i2] | t.bv[i3];
	}

	for (; i2 >= 0; i2--)
		temp.bv[i1] = bv[i2];
	for (; i3 >= 0; i3--)
		temp.bv[i1] = t.bv[i3];

	return temp;
}

void boolvector::operator|=(const boolvector &t)
{
	for (int i = len_mas - 1, i1 = t.len_mas - 1; i >= 0 && i1 >= 0; i--, i1--) {
		bv[i] = bv[i] | t.bv[i1];
	}
}

boolvector boolvector::operator^(const boolvector &t)
{
	int length;

	if (len_bv > t.len_bv) {
		length = len_bv;
	}
	else
	{
		length = t.len_bv;
	}

	boolvector temp(length);
	int i1, i2, i3;
	for (i1 = temp.len_mas - 1, i2 = len_mas - 1, i3 = t.len_mas - 1; i2 >= 0 && i3 >= 0; i1--, i2--, i3--) {
		temp.bv[i1] = bv[i2] ^ t.bv[i3];
	}
	return temp;
}

void boolvector::operator^=(const boolvector &t)
{
	for (int i = len_mas - 1, i1 = t.len_mas - 1; i >= 0 && i1 >= 0; i--, i1--) {
		bv[i] = bv[i] ^ t.bv[i1];
	}
}

boolvector boolvector::operator~()
{
	boolvector temp(*this);

	for (int i = len_mas - 1; i >= 0; i--)
		temp.bv[i] = ~temp.bv[i];
	return temp;
}

int boolvector::operator[](int index)
{
	if (index < len_bv && index >= 0)
	{
		int i = len_mas - 1 - index / 8;
		int bit = index % 8;

		byte mask = 1 << bit;

		if (bv[i] & mask)
		{
			return 1;
		}

		return 0;
	}
	return 0;
}

boolvector boolvector::operator<<(int t)
{
	boolvector temp(*this);
	temp <<= t;

	return temp;
}

boolvector boolvector::operator>>(int t)
{
	boolvector temp(*this);
	temp >>= t;

	return temp;
}
void boolvector::operator<<=(int t)
{

	for (int i = len_bv - 1; (i - t) >= 0; i--)
	{
		if (this->operator[](i - t))
			set1(i);
		else
			set0(i);
	}
	set0from(0, t);
}

void boolvector::operator>>=(int t)
{
	for (int i = 0; (i + t) <= len_bv - 1; i++)
	{
		if (this->operator[](i + t))
			set1(i);
		else
			set0(i);
	}
	set0from(len_bv - t, t);
}


void boolvector::printBv()
{
	byte mask;

	for (int i = 0; i < len_mas; i++)
	{
		for (mask = 1 << 7; mask; mask >>= 1)
		{
			if (bv[i] & mask)
				cout << '1';
			else
				cout << '0';
		}
	}
	cout << endl;
}

void boolvector::set1(int index)
{
	if (index < len_bv)
	{
		int index_byte = len_mas - index / 8 - 1;
		bv[index_byte] |= (1 << index % 8);
	}
}

void boolvector::set0(int index)
{
	if (index < len_bv)
	{
		int index_byte = len_mas - index / 8 - 1;
		bv[index_byte] &= ~(1 << index % 8);
	}
}

void boolvector::all0()
{
	for (int i = 0; i < len_mas; i++)
		bv[i] = 0;
}

void boolvector::all1()
{
	this->set1from(0, len_bv);
}
void boolvector::set0from(int index, int k)
{
	if (len_bv - index >= k) {
		byte mask = 1 << (index % 8);
		int index_byte = len_mas - index / 8 - 1;

		for (int i = 0; i < k; i++, mask <<= 1)
		{
			if (!mask)
			{
				mask = 1;
				index_byte--;
			}
			bv[index_byte] &= ~mask;
		}
	}
}
void boolvector::set1from(int index, int k)
{
	if (len_bv - index >= k) {
		byte mask = 1 << (index % 8);
		int index_byte = len_mas - index / 8 - 1;

		for (int i = 0; i < k; i++, mask <<= 1)
		{
			if (!mask)
			{
				mask = 1;
				index_byte--;
			}
			bv[index_byte] |= mask;
		}
	}
}

void boolvector::invert(int index)
{
	if (index < len_bv && index >= 0)
	{
		int index_byte = len_mas - index / 8 - 1;

		if (bv[index_byte] & (1 << (index % 8)))
			bv[index_byte] &= ~(1 << index % 8);
		else
			bv[index_byte] |= (1 << index % 8);
	}
}

void boolvector::invertFrom(int index, int k)
{
	int index_byte = len_mas - index / 8 - 1;
	byte mask = 1 << (index % 8);
	for (int i = 0; i < k; i++, mask <<= 1)
	{
		if (!mask)
		{
			index_byte--;
			mask = 1;
		}
		if (bv[index_byte] & mask)
			bv[index_byte] &= ~mask;
		else
			bv[index_byte] |= mask;
	}
}

int boolvector::size()
{
	return this->len_bv;
}

int boolvector::size_bv()
{
	return this->len_mas;
}

int boolvector::weight()
{
	byte mask;
	int w = 0;
	for (int i = len_mas - 1; i >= 0; i--)
	{
		for (mask = 1; mask; mask <<= 1)
		{
			if (bv[i] & mask)
				w++;
		}
	}
	return w;
}