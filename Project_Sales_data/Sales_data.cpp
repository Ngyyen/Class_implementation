#include <iostream>
#include <fstream>
#include "Sales_data.h"
#include "Quote.h"
using namespace std;
int main()
{
	Sales_data total("12sd", 1, 20000);
	Sales_data temp;
	temp = Sales_data("12sd", 1, 20001);
	ifstream input("C:/Users/Nguyen Le/OneDrive/Máy tính/CPP/Class/Project_Sales_data/transaction.txt");
	ofstream output("C:/Users/Nguyen Le/OneDrive/Máy tính/CPP/Class/Project_Sales_data/output.txt", ofstream::app);
	
	if (input>>total)
	{
		Sales_data trans;
		while (!input.eof() && input>>trans)
			if (total.isbn() == trans.isbn())
				total+=trans;
			else
			{
				output << total << endl;
				total = trans;
			}
		output << total << endl;
	}
	output << temp << endl;

	Bulk_quote item2("12sd", 50000, 0.2, 3);
	Limit_quote item3("12sd", 50000, 0.2, 3, 5);
	Quote& item1 = item3;
	item1.debug(cout) << endl;
	item2.debug(cout) << endl;
	item3.debug(cout) << endl;
	print_total(cout, item2, 5);
	print_total(cout, item2, 6);
	print_total(cout, item3, 5);
	print_total(cout, item3, 6);
	print_total(cout, item1, 6);
	Disc_quote obj;
	return 0;
}