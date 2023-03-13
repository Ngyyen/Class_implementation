#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
#include <vector>
using namespace std;
class Account
{
public:
    double new_amount() { return amount += amount * interest_rate; }
    static double rate() { return interest_rate; }
    static void rate(double new_rate);
private:
    static constexpr int size = 10;
    static vector<double> vec;
    static constexpr double arr[size] = { 1,2,3 };
    static double interest_rate;
    std::string owner = "";
    double amount = 0;
};
constexpr int Account::size;
vector<double> Account::vec(size, 5);
double Account::interest_rate = 0.2;
void Account::rate(double new_rate)
{
    interest_rate = new_rate;
}
#endif