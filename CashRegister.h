#pragma once
class CashRegister
{
	private:
		int cashOnHand;

	public:
		CashRegister();
		void updateAmount(int);
		int getBalance();
};

