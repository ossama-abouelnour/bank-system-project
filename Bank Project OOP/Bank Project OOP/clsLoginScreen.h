#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsGlobal.h"
#include "clsMainScreen.h"

class clsLoginScreen : protected clsScreen
{



	static bool _Login()
	{
		bool LoginFailed = false;
		short FailedLoginCount = 0;

		string UserName , Password ;

		do
		{
			if (LoginFailed)
			{
				FailedLoginCount++;

				cout << "\nInvalid Username/Passowrd!\n\n";
				cout << "\nYou have " << (3 - FailedLoginCount) << " left attempt(s) to login.\n\n";
			}

			if (FailedLoginCount == 3)
			{
				cout << "\nYou are locked after 3 failed attempts\n\n";
				return false;
			}


			cout << "USERNAME: ";
			cin >> UserName;
			cout << "\nPASSWORD: ";
			cin >> Password;

			CurrentUser = clsUser::Find(UserName, Password);
			LoginFailed = CurrentUser.IsEmpty();

		} while (LoginFailed);
		CurrentUser.LoginHistory();
		clsMainScreen::ShowMainMenu();
		return true;
	}




public:

	static bool ShowLoginScreen()
	{
		system("cls");
		_ScreenHeader("\t      Login Screen");
		return _Login();
	}
};

