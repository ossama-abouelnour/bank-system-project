#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include <iomanip>

using namespace std;

class clsCurrenciesListScreen : protected clsScreen
{
private:

	static void _PrintCurrencyList(clsCurrency Currency)
	{
		cout << setw(8) << left << "" << "| " << setw(30) << left << Currency.Country();
		cout << "| " << setw(8) << left << Currency.CurrencyCode();
		cout << "| " << setw(45) << left << Currency.CurrencyName();
		cout << "| " << setw(10) << left << Currency.Rate();
	}


public:

	static void ShowCurrenciesListScreen()
	{
		vector <clsCurrency> vCurrency = clsCurrency::GetCurrenciesList();


		string Header = "\t\tCurrencies List Screen";
		_ScreenHeader(Header, "\t\t" + to_string(vCurrency.size()) + "Currency");

		cout << setw(8) << left << "" << "\n\t------------------------------------------------------------------------------------------------------\n";

		cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
		cout << "| " << left << setw(8) << "Code";
		cout << "| " << left << setw(45) << "Name";
		cout << "| " << left << setw(10) << "Rate/(1$)";
		cout << setw(8) << left << "" << "\n\t------------------------------------------------------------------------------------------------------\n";

		if (vCurrency.size() == 0)
		{
			cout << "\t\t\tNo currenices data available to show";
		}

		else
		{
			for (clsCurrency& C : vCurrency)
			{
				_PrintCurrencyList(C); 
				cout << endl;
			}
		}
	}
	
};

