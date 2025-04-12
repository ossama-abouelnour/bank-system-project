#pragma once
#include "clsScreen.h"
#include <iostream>
#include "clsBankClient.h"

using namespace std;

class clsClientTransferHistory : protected clsScreen
{

private:

	static void _PrintTransferHistory(clsBankClient::stTransferHistory TransferHistory)
	{
		cout << setw(8) << left << "" << "| " << setw(23) << left << TransferHistory.DateTime;
		cout << "| " << setw(8) << left << TransferHistory.SourceAccountNumber;
		cout << "| " << setw(8) << left << TransferHistory.DestinationAccountNumber;
		cout << "| " << setw(8) << left << TransferHistory.Amount;
		cout << "| " << setw(10) << left << TransferHistory.srcBalanceAfterTransfer;
		cout << "| " << setw(10) << left << TransferHistory.destAccountBalanceAfter;
		cout << "| " << setw(8) << left << TransferHistory.Username;
		cout << endl;
	}


public:

	static void ShowTransferHistoryScreen()
	{
		vector<clsBankClient::stTransferHistory> vTransferHistory = clsBankClient::GetTransferLogHistory();

		_ScreenHeader("\tTransfer History Screen", "\t      (" + to_string(vTransferHistory.size()) + ") Records");

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
		cout << "| " << left << setw(8) << "s.Acct";
		cout << "| " << left << setw(8) << "d.Acct";
		cout << "| " << left << setw(8) << "Amount";
		cout << "| " << left << setw(10) << "s.Balance";
		cout << "| " << left << setw(10) << "d.Balance";
		cout << "| " << left << setw(8) << "User";

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		if (vTransferHistory.size() == 0)
		{
			cout << "\t\t\t\tNo Transfers Available In the System!";
		}

		else
		{
			for (clsBankClient::stTransferHistory& TransferHistory : vTransferHistory)
			{
				_PrintTransferHistory(TransferHistory);
			}
		}
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
	}



};

