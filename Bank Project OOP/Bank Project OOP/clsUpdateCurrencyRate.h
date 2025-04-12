#pragma once
#include "clsScreen.h"
#include <iostream>
#include "clsCurrency.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateCurrencyRate : private clsScreen
{
private:

    static float _ReadRate()
    {
        float NewRate = 0;
        cout << "Enter New Rate: ";
        NewRate = clsInputValidate::ReadFloatNumber();
        
        return NewRate;
    }

	static void _PrintCurrencyCard(clsCurrency Currency)
	{
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();

        cout << "\n_____________________________\n";
	}



public:


    static void ShowUpdateCurrencyRateScreen()
    {
        _ScreenHeader("\tUpdate Currency Screen");
        string CurrencyCode = "";

      

        cout << "Please enter currency code: ";
        CurrencyCode = clsString::UpperAllString(clsInputValidate::ReadString());

        while (!clsCurrency::DoesCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency is not found; choose another one: ";
            CurrencyCode = clsString::UpperAllString(clsInputValidate::ReadString());
        }

        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
        _PrintCurrencyCard(Currency);

        

        cout << "Are you sure you want to update the rate of this currency (y/n)?/n";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            cout << "\nUpdate Currency Rate:";
            cout << "\n----------------------\n";
            Currency.UpdateRate(_ReadRate());

            cout << "\nCurrency Rate updated Successfully :)";
            _PrintCurrencyCard(Currency);
        }
        


    }


};

