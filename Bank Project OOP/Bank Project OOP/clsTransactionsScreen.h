#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsClientTransferHistory.h"



using namespace std;

class clsTransactions : protected clsScreen 
{
private:

	static void _ShowDepositScreen()
	{
		clsDepositScreen::ShowDepositScreen();
		system("cls");
	}

	static void _ShowWithdrawScreen()
	{
		clsWithdrawScreen::ShowWithdrawScreen();

		system("cls");
	}

	static void _ShowTotalBalancesScreen()
	{
		clsTotalBalancesScreen::ShowTotalBalancesScreen();
		system("cls");
	}

	static short _ReadTramsactionsMainMenuOption()
	{
		short Choice = 0;
		cout << "\n" << setw(37) << left << "" << "   Choose what you want to do (1-6)?";
		Choice = clsInputValidate::ReadShortNumberBetween(1,6);
		return Choice;
	}

	static void _ShowTransferScreen()
	{
		clsTransferScreen::TransferScreen();
	}

	static void _ShowTransferHistoryScreen()
	{
		clsClientTransferHistory::ShowTransferHistoryScreen();
	}

	enum enTransactionScreen { enDeposit = 1, enWithdraw = 2, enTotalBalances = 3, enTransfer = 4, enTransferHistory = 5, enMainMenu = 6 };

	static void _GoBackToTransactionsMenu()
	{
		cout << setw(37) << left << "" << "\nPress any key to go back to Main Menue...\n";

		system("pause>0");
		ShowTransactionsMenu();
	}

	static void _PerformTransactionsMainMenuOption(enTransactionScreen Choice)
	{
		switch (Choice)
		{
		case clsTransactions::enDeposit:
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionsMenu();
			break;

		case clsTransactions::enWithdraw:
			system("cls");
			_ShowWithdrawScreen();
			_GoBackToTransactionsMenu();
			break;

		case clsTransactions::enTotalBalances:
			system("cls");
			_ShowTotalBalancesScreen();
			_GoBackToTransactionsMenu();
			break;

		case clsTransactions::enTransfer:
			system("cls");
			_ShowTransferScreen();
			_GoBackToTransactionsMenu();
			break;

		case clsTransactions::enTransferHistory:
			system("cls");
			_ShowTransferHistoryScreen();
			_GoBackToTransactionsMenu();
			break;

		case clsTransactions::enMainMenu:
			system("cls");
			/*clsMainScreen::ShowMainMenu();*/
			break;
		}


	}


public:

	static void ShowTransactionsMenu()
	{
		
		if (!CheckAccessRights(clsUser::enPermissions::Transactions))
		{
			return;
		}
		system("cls");
		_ScreenHeader("\t  Transactions Screen");

		cout << setw(37) << left << "\n\t\t\t\t\t===============================\n";
		cout << setw(37) << left << "\t\t\t\t\t\tTransactions Menu";
		cout << setw(37) << left << "\n\t\t\t\t\t===============================\n";
		cout << setw(37) << left << "\t\t\t\t\t[1] Deposit\n";
		cout << setw(37) << left << "\t\t\t[2] Withdraw\n";
		cout << setw(37) << left << "\t\t\t[3] Total Balances\n";
		cout << setw(37) << left << "\t\t\t\t[4] Transfer\n";
		cout << setw(37) << left << "\t\t\t[5] Transfers History\n";
		cout << setw(37) << left << "\t\t\t\t[6] Main Menu\n";

		_PerformTransactionsMainMenuOption((enTransactionScreen)_ReadTramsactionsMainMenuOption());
	}


};

