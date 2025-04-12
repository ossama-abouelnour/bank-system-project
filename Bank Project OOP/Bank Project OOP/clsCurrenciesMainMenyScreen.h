#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsCurrency.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRate.h"
#include "clsCurrencyCalculator.h"

using namespace std;


class clsCurrenciesMainMenuScreen : protected clsScreen
{
private:

	enum enCurrencyExchangeMenu { enListCurrencies = 1, enFindCurrency = 2, enUpdateRate = 3, enCurrencyCalculator = 4, enMainMenu = 5 };

	static short _ReadCurrencyExchangeOption()
	{
		short Choice = 0;
		cout << setw(40) << left << "" << "Choose what you want to do? [1 to 5] ";
		Choice = clsInputValidate::ReadShortNumberBetween(1, 5);

		return Choice;
	}

	static void _ShowCurrenciesList()
	{
		clsCurrenciesListScreen::ShowCurrenciesListScreen();
	}

	static void _ShowFindCurrencyScreen()
	{
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}

	static void _ShowUpdateRateScreen()
	{
		clsUpdateCurrencyRate::ShowUpdateCurrencyRateScreen();
	}

	static void _ShowCurrencyCalculator()
	{
		clsCurrencyCalculator::ShowCurrencyCalculatorScreen();
	}

	static void _GoBackToExchangeMenu()
	{
		cout << "\n\nPress any key to go back to Currencies Menue...";
		system("pause>0");
		ShowCurrencyExchangeScreen();
	}

	static void _PerformCurrencyExchangeOption(enCurrencyExchangeMenu Choice)
	{
		switch (Choice)
		{
		case clsCurrenciesMainMenuScreen::enListCurrencies:
			system("cls");
			_ShowCurrenciesList();
			_GoBackToExchangeMenu();
			break;

		case clsCurrenciesMainMenuScreen::enFindCurrency:
			system("cls");
			_ShowFindCurrencyScreen();
			_GoBackToExchangeMenu();
			break;

		case clsCurrenciesMainMenuScreen::enUpdateRate:
			system("cls");
			_ShowUpdateRateScreen();
			_GoBackToExchangeMenu();
			break;

		case clsCurrenciesMainMenuScreen::enCurrencyCalculator:
			system("cls");
			_ShowCurrencyCalculator();
			_GoBackToExchangeMenu();
			break;

		case clsCurrenciesMainMenuScreen::enMainMenu:
			break;

		}
	}

public:

	static void ShowCurrencyExchangeScreen()
	{
		system("cls");
		_ScreenHeader("\t  Currency Exchange Main Screen");

		cout << setw(40) << left << "" << "======================================\n";
		cout << setw(40) << left << "" << "\t\tCurrency Exchange\n";
		cout << setw(40) << left << "" << "======================================\n";
		cout << setw(40) << left << "" << "\t(1) List Currencies.\n";
		cout << setw(40) << left << "" << "\t(2) Find Currency.\n";
		cout << setw(40) << left << "" << "\t(3) Update Rate.\n";
		cout << setw(40) << left << "" << "\t(4) Currency Calculator.\n";
		cout << setw(40) << left << "" << "\t(5) Main Menu.\n";
		cout << setw(40) << left << "" << "======================================\n";
		_PerformCurrencyExchangeOption((enCurrencyExchangeMenu)_ReadCurrencyExchangeOption());

	}



};

