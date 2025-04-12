#pragma once
#include "iostream"
#include "clsBankClient.h"
#include "clsUtil.h"

using namespace std;


class clsTotalBalancesScreen : protected clsScreen
{

private:

    static void _PrintClientRecordBalanceLine(clsBankClient Client)
    {
        cout << setw(25) << left << "" << "| " << setw(15) << left << Client.AccountNumber();
        cout << "| " << setw(40) << left << Client.FullName();
        cout << "| " << setw(12) << left << Client.AccountBalance;
    }



public:

	static void ShowTotalBalancesScreen()
	{
        
       
            vector <clsBankClient> vClients = clsBankClient::GetClientsList();

            string Title = "\t Balances Screen";
            string SubTitle = "\t (" + to_string(vClients.size()) + ") Client(s)";
            
            _ScreenHeader(Title, SubTitle);

            cout << "\n_______________________________________________________";
            cout << "________________________________________________________\n" << endl;

            cout << setw(25) << left << "" << "| " << setw(15) << left << "Account Number";
            cout << "| " << setw(40) << left << "Client Name";
            cout << "| " << setw(12) << left << "Balance |";
            cout << "\n_______________________________________________________";
            cout << "________________________________________________________\n" << endl;

            double TotalBalances = clsBankClient::GetTotalBalances();

            if (vClients.size() == 0)
            {
                cout << "\n\t\t\t\t\tNo clients available in the system";
            }

            else
            {
                for (clsBankClient& Client : vClients)
                {
                    _PrintClientRecordBalanceLine(Client);
                    cout << endl;
                }
                cout << "\n_______________________________________________________";
                cout << "________________________________________________________\n" << endl;
            }

            cout << "Total Balances = " << TotalBalances << endl;
            cout  << clsUtil::NumberToText(TotalBalances) << " Pounds";
            cout << "\nPress any key to go back to Main Menu...";
            system("pause>0");
	}

};

