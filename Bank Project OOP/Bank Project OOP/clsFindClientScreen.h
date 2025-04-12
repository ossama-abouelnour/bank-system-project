#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

using namespace std;


class clsFindClientScreen : protected clsScreen
{
private:

	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n______________________________";
		cout << "\nFirstName   :" << Client.FirstName;
		cout << "\nLastName    :" << Client.LastName;
		cout << "\nFullName    :" << Client.FullName();
		cout << "\nEmail       :" << Client.Email;
		cout << "\nPhone       :" << Client.Phone;
		cout << "\nAcc. Number :" << Client.AccountNumber();
		cout << "\nPIN         :" << Client.Pin;
		cout << "\nBalance     :" << Client.AccountBalance;
		cout << "\n______________________________";
	}


public:

	static void ShowFindClientScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::FindClients))
		{
			return;
		}
		_ScreenHeader("Find Client Screen");
		cout << "\n\nPlease enter the account number: ";
		string AccountNumber = clsInputValidate::ReadString();

		

		

		while (!clsBankClient::DoesClientExist(AccountNumber))
		{
			cout << "\nAccount number not found, please enter a different one: ";
			AccountNumber = clsInputValidate::ReadString();
		}


		clsBankClient Client1 = clsBankClient::Find(AccountNumber);

		if (!Client1.IsEmpty())
		{
			cout << "\nClient Found\n";
		}

		else
		{
			cout << "\nClient Not Found\n";
		}

		_PrintClient(Client1);

	}
	








};

