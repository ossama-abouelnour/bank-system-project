#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"

class clsWithdrawScreen : protected clsScreen
{
	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nPassword    : " << Client.Pin;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";

	}

	static string _ReadAccountNumber()
	{
		string AccountNumber = "";

		cout << "\nPlease enter account number? ";
		cin >> AccountNumber;
		return AccountNumber;
	}



public:

	static void ShowWithdrawScreen()
	{
		_ScreenHeader("\tWithdraw Screen");
		
		string AccountNumber = _ReadAccountNumber();

		while (!clsBankClient::DoesClientExist(AccountNumber))
		{
			cout << "Client with " << AccountNumber << " does not exist\n" << "Please enter a valid account: ";
			AccountNumber = _ReadAccountNumber();
		}

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);

		_PrintClient(Client1);

		double Amount = 0;
		cout << "Please enter the amount you would like to withdraw? ";
		cin >> Amount;

		while (Amount > Client1.AccountBalance)
		{
			cout << "Insuffienceint balance\nAccount Balance is " << Client1.AccountBalance << "\nPlease choose another amount\n";
			cin >> Amount;
		}

		cout << "\nAre you sure you want to perform this transaction? ";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			if (Client1.Withdraw(Amount)) {
				cout << "\nAmount Deposited Successfully.\nAccount Balance is: " << Client1.AccountBalance;
			}
			else
			{
				
				cout << "Insuffienceint balance\nAccount Balance is " << Client1.AccountBalance << "\nPlease choose another amount\n";
				cin >> Amount;
			}
		}

		else
		{
			cout << "\nTransaction was cancelled/\n";
		}
		

	}


};

