#ifndef QUOTE_H
#define QUOTE_H

#include <string>
#include <iostream>
using namespace std;

class Quote {
public:
	Quote() = default;
	Quote(const string& book, double sales_price) : bookNo(book), price(sales_price) {}
	virtual ~Quote() = default;

	string isbn() const { return bookNo; }
	virtual double net_price(size_t n) const { return price * n; }
	virtual ostream& debug(ostream&) const;

private:
	string bookNo = "";
protected:
	double price = 0.0;
};

class Disc_quote : public Quote {
public:
	Disc_quote() = default;
	Disc_quote(const string& book, double sales_price, double disc, size_t cnt) :
		Quote(book,sales_price), discount(disc), min_qty(cnt) {}

	double net_price(size_t n) const = 0;
	virtual ostream& debug(ostream&) const;

protected:
	double discount = 0.0;
	size_t min_qty = 0;
};

class Bulk_quote : public Disc_quote {
public:
	Bulk_quote() = default;
	Bulk_quote(const string& book, double sales_price, double disc, size_t cnt) : 
		Disc_quote(book,sales_price,disc,cnt) {}

	double net_price(size_t cnt) const override;
	ostream& debug(ostream&) const override;
};

class Limit_quote : public Bulk_quote {
public:
	Limit_quote() = default;
	Limit_quote(const string& book, double price, double disc, size_t min_cnt, size_t max_cnt ) :
		Bulk_quote(book,price,disc,min_cnt), max_qty(max_cnt) {}

	double net_price(size_t) const override;
	ostream& debug(ostream&) const override;

protected:
	size_t max_qty = 0;
};

double print_total(ostream&, const Quote&, size_t);

double print_total(ostream& os, const Quote& item, size_t n)
{
	double total = item.net_price(n);
	os << "ISBN: " << item.isbn() << " # sold: " << n << " Total price: " << total << endl;
	return total;
}

double Bulk_quote::net_price(size_t cnt) const
{
	if (cnt > min_qty) {
		return cnt * (1 - discount) * price;
	}
	return cnt * price;
}

double Limit_quote::net_price(size_t cnt) const
{
	if (cnt >= min_qty && cnt<=max_qty) {
		return cnt * (1 - discount) * price;
	}
	if (cnt > max_qty) {
		return max_qty * (1 - discount) * price + (cnt - max_qty) * price;
	}
	return cnt * price;
}

ostream& Quote::debug(ostream& os) const
{
	os << isbn() << price;
	return os;
}

ostream& Bulk_quote::debug(ostream& os) const
{
	Quote::debug(os) << discount << min_qty;
	return os;
}

ostream& Limit_quote::debug(ostream& os) const
{
	Bulk_quote::debug(os) << max_qty;
	return os;
}

#endif
