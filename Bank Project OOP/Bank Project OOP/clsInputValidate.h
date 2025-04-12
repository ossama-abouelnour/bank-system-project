#pragma once
#include <iostream>
#include "clsDate.h"
#include "clsUtil.h"


using namespace std;

class clsInputValidate
{

public:

	static bool IsNumberBetween(short Number, short From, short To)
	{
		return (Number >= From && Number <= To);
	}

	static bool IsNumberBetween(int Number, int From, int To)
	{
		return (Number >= From && Number <= To);
	}

	static bool IsNumberBetween(float Number, float From, float To)
	{
		return (Number >= From && Number <= To);
	}

	static bool IsNumberBetween(double Number, double From, double To)
	{
		return (Number >= From && Number <= To);
	}

	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
	{
		return (Date.Year > From.Year ||
			(Date.Year == From.Year && Date.Month > From.Month) ||
			(Date.Year == From.Year && Date.Month == From.Month && Date.Day > From.Day))

			&&

			(Date.Year < To.Year ||
				(Date.Year == To.Year && Date.Month < To.Month) ||
				(Date.Year == To.Year && Date.Month == To.Month && Date.Day < To.Day));
	}

	static int ReadIntNumber(string ErrorMessage = "Invalid Entry, please try again\n")
	{
		int Number;

		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static short ReadShortNumber(string ErrorMessage = "Invalid Entry, please try again\n")
	{
		short Number;

		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static short ReadShortNumberBetween(short From, short To, string ErrorMessage = "Invalid Entry, please try again\n")
	{
		short Number = ReadIntNumber();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			short Number = ReadShortNumber();
		}
		return Number;
	}


	static int ReadIntNumberBetween(int From, int To, string ErrorMessage = "Invalid Entry, please try again\n")
	{
		int Number = ReadIntNumber();

		while(!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			int Number = ReadIntNumber();
		}
		return Number;
	}

	static double ReadDblNumber(string ErrorMessage = "Invalid Entry, please try again\n")
	{
		double Number;

		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static double ReadDblNumberBetween(double From, double To, string ErrorMessage = "Invalid Entry, please try again\n")
	{
		double Number = ReadDblNumber();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			double Number = ReadDblNumber();
		}
		return Number;
	}

	static double ReadFloatNumber(string ErrorMessage = "Invalid Entry, please try again\n")
	{
		float Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static bool IsValidDate(clsDate Date)
	{
		return clsDate::IsValidDate(Date);
	}

	static string ReadString()
	{
		string S1 = "";

		getline(cin >> ws, S1);
		return S1;
	}

};

