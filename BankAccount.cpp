#include "BankAccount.h"

void BankAccount::set(int dollar, int cent) 
{
	// must out d.p for '100'
	// If d.p is missing, then it is an int-int division that will only return an integer value. 
	balance = dollar + (cent / 100.00);
}

void BankAccount::set_rate(int rate) 
{
	interest_rate = (rate / 100.00);
}

double BankAccount::get_balance() 
{
	return balance;
}

double BankAccount::get_rate() 
{
	return interest_rate;
}

void BankAccount:: update() 
{
	balance = balance * (1 + interest_rate);
}
