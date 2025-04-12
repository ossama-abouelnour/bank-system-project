#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"


using namespace std;

class clsTransferScreen : protected clsScreen
{
	static string _ReadAccountNumbersForTransfer(string FromOrTo)
	{
		string Account = "";

		cout << "Please enter account number to transfer " << FromOrTo << ": ";
		Account = clsInputValidate::ReadString();

		while (!clsBankClient::DoesClientExist(Account))
		{
			cout << "Account number does not exist, please enter a valid account\n";
			Account = clsInputValidate::ReadString();
		}

		return Account;
	}

	static float _ReadAmount(clsBankClient SourceClient)
	{
		float Amount;

		cout << "Enter transfer amount: ";
		Amount = clsInputValidate::ReadDblNumber();

		while (Amount > SourceClient.AccountBalance)
		{
			cout << "Amount exceeds available balance, please enter another amount: ";
			Amount = clsInputValidate::ReadDblNumber();
		}


		return Amount;
	}

	static void _PrintClientCard(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";

	}


public:

	static void TransferScreen()
	{
		
		_ScreenHeader("\t\tTransfer Screen");
		
		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumbersForTransfer("From"));

		_PrintClientCard(SourceClient);

		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumbersForTransfer("To"));
		
		_PrintClientCard(DestinationClient);

		float Amount = _ReadAmount(SourceClient);

		char Answer = 'n';
		cout << "Are you sure you would like to complete this transfer? (y/n)";
		cin >> Answer;
		
		if (Answer == 'y' || 'Y')
		{
			if (SourceClient.Transfer(Amount, DestinationClient, CurrentUser.UserName))
			{
				cout << "\nTransfer completed successfully\n";
			}

			else
			{
				cout << "\nTransfer Faild \n";
			}
			
		}

		_PrintClientCard(SourceClient);
		_PrintClientCard(DestinationClient);
		system("pause>0");
	}

};

