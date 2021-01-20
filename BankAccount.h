#pragma once
class BankAccount
{
	private:
		double balance;
		double interest_rate;
	public:
		void set(int, int);
		void update();
		double get_balance();
		double get_rate();
		void set_rate(int);
};

