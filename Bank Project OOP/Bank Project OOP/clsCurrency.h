#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "clsString.h"

using namespace std;

class clsCurrency
{
private:


	enum enMode{ EmptyMode = 0, UpdateMode = 1};

	enMode _Mode;

	string _Country, _CurrencyCode, _CurrencyName;
	float _Rate;

	static clsCurrency _ConvertLineToCurrencyObject(string Line, string Delim = "#//#")
	{
		vector <string> vCurrencyData; 

		vCurrencyData = clsString::Split(Line, Delim);

		return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2], stod(vCurrencyData[3]));
	}

	static vector <clsCurrency> _LoadCurrenciesDataFromFile()
	{
		fstream MyFile;

		vector <clsCurrency> vCurrency;

		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line = "";

			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				vCurrency.push_back(Currency);
			}

			MyFile.close();
		}
		return vCurrency;
	}

	static string _ConvertCurrencyObjectoToLine(clsCurrency Currency, string Delim = "#//#")
	{
		string stCurrency = "";
		
		stCurrency += Currency.Country() + Delim;
		stCurrency += Currency.CurrencyCode() + Delim;
		stCurrency += Currency.CurrencyName() + Delim;
		stCurrency += to_string(Currency.Rate());

		return stCurrency;
	}


	void _SaveCurrencyDataToFile(vector<clsCurrency>& _vCurrency)
	{
		fstream MyFile;

		MyFile.open("Currencies.txt", ios::out);

		string DataLine = "";

		if (MyFile.is_open())
		{
			for (clsCurrency& C : _vCurrency)
			{
				DataLine = _ConvertCurrencyObjectoToLine(C);
				MyFile << DataLine << endl;
			}
			MyFile.close();
		}
	}

	void _Update()
	{
		vector<clsCurrency> _vCurrency;

		_vCurrency = _LoadCurrenciesDataFromFile();

		for (clsCurrency& C : _vCurrency)
		{
			if (C.CurrencyCode() == _CurrencyCode)
			{
				C = *this;
				break;
			}
		}
		_SaveCurrencyDataToFile(_vCurrency);
	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

public:

	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrncyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrncyName;
		_Rate = Rate;
	}

	static vector <clsCurrency> GetAllUSDRates()
	{
		return _LoadCurrenciesDataFromFile();
	}

	bool IsEmpty()
	{
		return (_Mode = enMode::EmptyMode);
	}

	string Country()
	{
		return _Country;
	}

	string CurrencyCode()
	{
		return _CurrencyCode;
	}

	string CurrencyName()
	{
		return _CurrencyName;
	}

	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}

	float Rate()
	{
		return _Rate;
	}

	static clsCurrency FindByCode(string CurrencyCode)
	{
		CurrencyCode = clsString::UpperAllString(CurrencyCode);

		fstream MyFile;

		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

				if (Currency.CurrencyCode() == CurrencyCode)
				{
					MyFile.close();
					return Currency;
				}
			}
			
		}

	}

	static clsCurrency FindByCountry(string Country)
	{
		Country = clsString::UpperAllString(Country);

		fstream MyFile;

		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

				if (clsString::UpperAllString(Currency.Country()) == Country)
				{
					MyFile.close();
					return Currency;
				}
			}

		}
	}

	static bool DoesCurrencyExist(string CurrencyCode)
	{
		clsCurrency C1 = clsCurrency::FindByCode(CurrencyCode);
		return (!C1.IsEmpty());
	}

	static vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrenciesDataFromFile();
	}

	float ConvertToUSD(float Amount)
	{
		return (float)(Amount / Rate());
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency Currency2)
	{
		float AmountInUSD = ConvertToUSD(Amount);

		if (Currency2.CurrencyCode() == "USD")
		{
			return AmountInUSD;
		}

		return (float)(AmountInUSD * Currency2.Rate());
	}

};

