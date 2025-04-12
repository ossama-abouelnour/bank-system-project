#pragma once
#include <iomanip>
#include "clsScreen.h"
#include "clsClientListScreen.h"
#include "clsInputValidate.h"
#include "clsAddNewClient.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersSreen.h"
#include "clsGlobal.h"
#include "clsUsersLoginHistory.h"
#include "clsCurrenciesMainMenyScreen.h"


using namespace std;

class clsMainScreen : protected clsScreen
{
private:

	enum enMainMenu{
		enShowClients = 1, enAddNewClient = 2, enDeleteClient = 3, enUpdateClient = 4, 
		enFindClient = 5, enTransactions = 6, enManageUsers = 7, enUsersLoginHistory = 8 , enCurrencyExchange = 9 ,enLogout = 10
	};

	static short _RedMainMenuOption()
	{
		cout << setw(40) << left << "" << "Please enter your selection from 1 - 10? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 10);
		return Choice;
	}

	static void _GoBackToMainMenuScreen()
	{
		cout << setw(40) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

		system("pause>0");
		ShowMainMenu();
	}

	static void _ShowAllClientsScreen()
	{
		clsClientListScreen::ShowClientsList();
		system("pause>0");
	}

	static void _ShowAddNewClientsScreen()
	{
		clsAddNewClient::ShowAddNewClientScreen();
		system("pause>0");
	}

	static void _ShowDeleteClientScreen()
	{
		clsDeleteClientScreen::DeleteClient();
		system("pause>0");
	}

	static void _ShowUpdateClientScreen()
	{
		clsUpdateClientScreen::ShowUpdateClientScreen();
		system("pause>0");
	}

	static void _ShowFindClientScreen()
	{
		clsFindClientScreen::ShowFindClientScreen();
		system("pause>0");
	}

	static void _ShowTransactionsScreen()
	{
		clsTransactions::ShowTransactionsMenu();
		system("pause>0");
	}

	static void _ShowManageUsersScreen()
	{
		clsManageUsersSreen::ShowManageUsersMenu();
		system("pause>0");
	}

	/*static void _ShowEndScreen()
	{
		cout << "Here will be the end screen";
		system("pause>0");
	}*/

	static void _ShowUsersLoginHistory()
	{
		clsUsersLoginHistory::ShowUsersLoginHistory();
	}

	static void _ShowCurrencyExchangeScreen()
	{
		clsCurrenciesMainMenuScreen::ShowCurrencyExchangeScreen();
	}

	static void _Logout()
	{
		CurrentUser = clsUser::Find("", "");
	}

	static void _PerformMainMenuOption(enMainMenu Entry)
	{
		switch (Entry)
		{
		case clsMainScreen::enShowClients:
			system("cls");
			_ShowAllClientsScreen();
			_GoBackToMainMenuScreen();
			break;

		case clsMainScreen::enAddNewClient:
			system("cls");
			_ShowAddNewClientsScreen();
			_GoBackToMainMenuScreen();
			break;

		case clsMainScreen::enDeleteClient:
			system("cls");
			_ShowDeleteClientScreen();
			_GoBackToMainMenuScreen();
			break;

		case clsMainScreen::enUpdateClient:
			system("cls");
			_ShowUpdateClientScreen();
			_GoBackToMainMenuScreen();
			break;

		case clsMainScreen::enFindClient:
			system("cls");
			_ShowFindClientScreen();
			_GoBackToMainMenuScreen();
			break;

		case clsMainScreen::enTransactions:
			system("cls");
			_ShowTransactionsScreen();
			_GoBackToMainMenuScreen();
			break;

		case clsMainScreen::enManageUsers:
			system("cls");
			_ShowManageUsersScreen();
			_GoBackToMainMenuScreen();
			break;

		case clsMainScreen::enUsersLoginHistory:
			system("cls");
			_ShowUsersLoginHistory();
			_GoBackToMainMenuScreen();
			break;

		case clsMainScreen::enCurrencyExchange:
			system("cls");
			_ShowCurrencyExchangeScreen();
			_GoBackToMainMenuScreen();
			break;

		case clsMainScreen::enLogout:
			system("cls");
			//_ShowEndScreen();
			_Logout();
			break;
		
		}
	}

public:

	static void ShowMainMenu()
	{
		system("cls");
		_ScreenHeader("\t\tMain Screen");

		cout << setw(40) << left << "" << "======================================\n";
		cout << setw(40) << left << "" << "\t\tMain Menu\n";
		cout << setw(40) << left << "" << "======================================\n";
		cout << setw(40) << left << "" << "\t(1) Show Client List.\n";
		cout << setw(40) << left << "" << "\t(2) Add a New Client.\n";
		cout << setw(40) << left << "" << "\t(3) Delete a Client.\n";
		cout << setw(40) << left << "" << "\t(4) Update Client Details.\n";
		cout << setw(40) << left << "" << "\t(5) Find a Client.\n";
		cout << setw(40) << left << "" << "\t(6) Transactions.\n";
		cout << setw(40) << left << "" << "\t(7) Manage Users.\n";
		cout << setw(40) << left << "" << "\t(8) Users Login History.\n";
		cout << setw(40) << left << "" << "\t(9) Currency Exchange.\n";
		cout << setw(40) << left << "" << "\t(10) Logout.\n";
		cout << setw(40) << left << "" << "======================================\n";

		_PerformMainMenuOption((enMainMenu)_RedMainMenuOption());
	}


};

