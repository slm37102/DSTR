#include "CashRegister.h"

CashRegister::CashRegister() 
{
	cashOnHand = 500;
}

void CashRegister::updateAmount(int deposit) 
{
	cashOnHand += deposit;
}

int CashRegister::getBalance() 
{
	return cashOnHand;
}
