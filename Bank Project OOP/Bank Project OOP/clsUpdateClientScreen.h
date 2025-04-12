#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateClientScreen : protected clsScreen
{

private:

	static void _ReadClientInfo(clsBankClient& Client)
	{
		cout << "\nEnter First Name: ";
		Client.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter Last Name: ";
		Client.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		Client.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone: ";
		Client.Phone = clsInputValidate::ReadString();

		cout << "\nEnter PIN: ";
		Client.Pin = clsInputValidate::ReadString();

		cout << "\nEnter New Balance: ";
		Client.AccountBalance = clsInputValidate::ReadFloatNumber();
	}

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

	static void ShowUpdateClientScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::UpdateClients))
		{
			return;
		}
		_ScreenHeader("\t  Update Client Screen");
		cout << "\nPlease enter account number: ";
		    string AccountNumber = clsInputValidate::ReadString();
		
		    while (!clsBankClient::DoesClientExist(AccountNumber))
		    {
		        cout << "\nAccount does not exist, please enter a valid account number: ";
		        AccountNumber = clsInputValidate::ReadString();
		    }
		
		    clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		
			_PrintClient(Client1);
			cout << "\nAre you sure you want to update this client y/n? ";

			char Answer = 'n';
			cin >> Answer;

			if (Answer == 'y' || Answer == 'Y')
			{
				system("cls");
				cout << "\n\nUpdate Client Info:";
				cout << "\n----------------------\n";

				_ReadClientInfo(Client1);

				clsBankClient::enSaveResults SaveResult;

				SaveResult = Client1.Save();

				switch (SaveResult)
				{
				case clsBankClient::svFailedEmptyObject:
					cout << "\nERROR\nAccount was not saved, missing details";
					break;
				case clsBankClient::svSucceeded:
					cout << "Account Updated Successfully :)\n";
					break;
				}

			}
		    
	}




};

