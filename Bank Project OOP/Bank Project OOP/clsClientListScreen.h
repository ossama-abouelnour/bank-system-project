#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>

using namespace std;

class clsClientListScreen :protected clsScreen
{
private:

    static void _PrintClientRecord(clsBankClient Client)
    {
        cout << "| " << left << setw(15) << Client.AccountNumber();
        cout << "| " << left << setw(20) << Client.FullName();
        cout << "| " << left << setw(15) << Client.Phone;
        cout << "| " << left << setw(30) << Client.Email;
        cout << "| " << left << setw(10) << Client.Pin;
        cout << "| " << left << setw(12) << Client.AccountBalance << "|";
    }

public:

	static void ShowClientsList()
	{
        if (!CheckAccessRights(clsUser::enPermissions::ListClients))
        {
            return;
        }
        vector <clsBankClient> vClients = clsBankClient::GetClientsList();

        string Title = "\t Client List Screen";
        string SubTitle = "\t (" + to_string(vClients.size()) + ") Client(s)";
        _ScreenHeader(Title, SubTitle);

        cout << "\n_______________________________________________________";
        cout << "________________________________________________________\n" << endl;

        cout << "| " << left << setw(15) << "Account Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(15) << "Phone";
        cout << "| " << left << setw(30) << "Email";
        cout << "| " << left << setw(10) << "PIN";
        cout << "| " << left << setw(12) << "Balance |";
        cout << "\n_______________________________________________________";
        cout << "________________________________________________________\n" << endl;


        if (vClients.size() == 0)
        {
            cout << "\n\t\t\t\t\tNo clients available in the system";
        }

        else
        {
            for (clsBankClient& Client : vClients)
            {
                _PrintClientRecord(Client);
                cout << endl;
            }
            cout << "\n_______________________________________________________";
            cout << "________________________________________________________\n" << endl;
        }
	}

};

