#ifndef SALES_DATA_H
#define SALES_DATA_H
#include <string>
#include <iostream>
using namespace std;

class Sales_data
{
	friend Sales_data operator+ (const Sales_data&, const Sales_data&);
	friend ostream& operator<< (ostream&, const Sales_data&);
	friend istream& operator>> (istream&, Sales_data&);
	friend bool operator== (const Sales_data&, const Sales_data&);
	friend bool operator!= (const Sales_data&, const Sales_data&);
public:
	Sales_data& operator+= (const Sales_data&);
		
	string isbn() const { return bookNo; }
	Sales_data& combine(const Sales_data& rhs);

	Sales_data() = default;
	Sales_data(const string& s, unsigned u, double p) : bookNo(s), unit_sold(u), revenue(p* u) { }
private:
	double avg_price() const { return revenue / unit_sold; }
	string bookNo = "";
	unsigned unit_sold = 0;
	double revenue = 0;
};

ostream& operator<< (ostream& os, const Sales_data& item)
{
	os << item.isbn() << " " << item.unit_sold << " " << item.revenue << " " << item.avg_price();
	return os;
}

istream& operator>> (istream& is, Sales_data& item)
{
	double price = 0;
	is >> item.bookNo >> item.unit_sold >> price;
	if (is) {
		item.revenue = item.unit_sold * price;
	}	 
	else {
		item = Sales_data();
	}
	return is;
}

Sales_data operator+ (const Sales_data& lhs, const Sales_data& rhs)
{
	Sales_data sum = lhs;
	sum += rhs;
	return sum;
}

Sales_data& Sales_data::operator+= (const Sales_data& rhs)
{
	unit_sold += rhs.unit_sold;
	revenue += rhs.revenue;
	return *this;
}

bool operator== (const Sales_data& lhs, const Sales_data& rhs)
{
	return lhs.bookNo == rhs.bookNo 
		&& lhs.revenue == rhs.revenue 
		&& lhs.unit_sold == rhs.unit_sold;
}

bool operator!= (const Sales_data& lhs, const Sales_data& rhs)
{
	return !(lhs == rhs);
}

Sales_data& Sales_data::combine(const Sales_data& rhs)
{
	unit_sold += rhs.unit_sold;
	revenue += rhs.revenue;
	return *this;
}

#endif