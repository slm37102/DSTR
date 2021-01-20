#include<iostream>
#include<iomanip>
#include<string>
#include "StudentMark.h"
#include "CashRegister.h"
#include "BankAccount.h"
using namespace std;

int main() 
{
	/*
	// Q1
	int arrSize;
	float quizM, assignmentM, examM;
	bool isExceeded;
	
	float sum = 0.0f;

	cout << "Please specify the size of array: ";
	cin >> arrSize;

	StudentMark* ptrArr = new StudentMark[arrSize];
	
	cout << endl;
	for (int i = 0; i < arrSize; i++) 
	{
		cout << endl << "Student " << i + 1 << endl;
		do 
		{
			isExceeded = false;

			cout << "Quiz (10%): ";
			cin >> quizM;

			cout << "Assignment (30%): ";
			cin >> assignmentM;

			cout << "Final Exam (50%): ";
			cin >> examM;

			if (quizM > 20) 
			{
				cout << "Quiz marks exceeded!" << endl << endl;
				isExceeded = true;
			}

			if (assignmentM > 30) 
			{
				cout << "Assignment marks exceeded!" << endl << endl;;
				isExceeded = true;
			}

			if (examM > 50) 
			{
				cout << "Final exam marks exceeded!" << endl << endl;;
				isExceeded = true;
			}

		} while (isExceeded);

		// if for first-level (direct access), can straight away use ->
		// But here, we need to assign unique value to attributes based on different object instance, 
		// so we are accessing the object-level attribute value, not class-level attribute value
		// if straight away use -> we change the class value directly, this will cause all object to inherit the same attribute values.
		ptrArr[i].getMark(quizM, assignmentM, examM);
	}

	for (int j = 0; j < arrSize; j++) 
	{
		sum += ptrArr[j].calculateMark();
	}

	cout << endl << "The average student mark is " << (sum / arrSize) << endl;
	*/

	/*
	int arrSize2;
	cout << "Please specify the number of transaction: ";
	cin >> arrSize2;

	CashRegister* ptrArr2 = new CashRegister[arrSize2];
	
	for (int a = 0; a < arrSize2 - 1; a++) 
	{
		ptrArr2[a].updateAmount(a*10);
	}

	for (int b = 0; b < arrSize2; b++) 
	{
		int hold = ptrArr2[b].getBalance();
		cout << "Balance " << b + 1 << " : " << hold << endl;
	}
	*/

	/*
	//Q2
	int option;
	int deposit;
	int balance;
	char isContinue;

	CashRegister* transaction = new CashRegister();
	cout << "---CASH REGISTER---" << endl;
	do 
	{
		cout << endl <<"What do you want to do today?" << endl << endl;
		cout << "1. Deposit Cash" << endl;
		cout << "2. Check Balance" << endl;
		cout << "Option: ";
		cin >> option;

		switch (option) 
		{
			case 1:
				cout << "Please enter the amount you wanted to deposit: ";
				cin >> deposit;
				transaction->updateAmount(deposit);
				break;

			case 2:
				balance = transaction->getBalance();
				cout << "Your balance is: " << balance << endl;
				break;
			
			// if 'break' is absent, then this default statement will always executed.
			default:
				cout << "Invalid Input!" << endl << endl;
		}

		cout << "Do you wish to continue? (Y/N): ";
		cin >> isContinue;

	} while (isContinue == 'Y' || isContinue == 'y');
	*/

	
	// Q3
	BankAccount myAcc;
	myAcc.set(200, 520);
	myAcc.set_rate(3);
	
	// data type must be compatible in order to avoid data loss.
	double accBalance = myAcc.get_balance();
	double interestRate = myAcc.get_rate();

	cout << "Your account balance is: " << accBalance << endl;
	cout << "Your annual interest rate is: " << interestRate << endl;

	myAcc.update();
	accBalance = myAcc.get_balance();
	cout << "Your account balance is: " << accBalance << endl;

	return 0;
}