#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;


class clsDeleteClientScreen : protected clsScreen
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

    static void DeleteClient()
    {
        if (!CheckAccessRights(clsUser::enPermissions::DeleteClients))
        {
            return;
        }
        _ScreenHeader("\t  Delete Client");
        string AccountNumber = "";

        cout << "Please enter account number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::DoesClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, please enter a correct one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        _PrintClient(Client1);
        cout << "\nAre you sure you want to delete this client? ";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            if (Client1.Delete())
            {
                system("cls");
                cout << "\nClient deleted successfully :)\n";
                _PrintClient(Client1);
            }

            else
            {
                cout << "\nError, Client was not deleted\n";
            }

        }
    }



};

