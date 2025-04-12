#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsAddNewClient : protected clsScreen
{

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

        Client.AccountBalance = 0;
        cout << "\nEnter New Balance: ";
        Client.AccountBalance = clsInputValidate::ReadFloatNumber();
    }

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

    

public:


	static void ShowAddNewClientScreen()
	{
        if (CheckAccessRights(clsUser::enPermissions::AddNewClients))
        {
            return;
        }
        _ScreenHeader("\t  Add New Client Screen");

        string AccountNumber = "";

        cout << "Please enter account number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (clsBankClient::DoesClientExist(AccountNumber))
        {
            cout << "\nAccount Number Exists, Please Choose a Different One: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient NewClient = clsBankClient::AddNewClientObject(AccountNumber);

        _ReadClientInfo(NewClient);

        clsBankClient::enSaveResults SaveResult;

        SaveResult = NewClient.Save();

        switch (SaveResult)
        {
        case clsBankClient::svFailedEmptyObject:
            cout << "Failed, missing details\n";
            break;
        case clsBankClient::svSucceeded:
            system("cls");
            cout << "Account added successfully\n";
            _PrintClient(NewClient);
            break;
        case clsBankClient::svFailedAccountNumberExist:
            cout << "Failed, account number exists\n";
            break;
        }

	}

};

