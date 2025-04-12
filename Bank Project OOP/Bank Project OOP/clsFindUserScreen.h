#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindUserScreen : private clsScreen
{
private:

	static void _PrintUser(clsUser User)
	{
		cout << "\nUser Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << User.FirstName;
		cout << "\nLastName    : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUser Name   : " << User.UserName;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n___________________\n";

	}


public:

	static void ShowFindUserScreen()
	{

		_ScreenHeader("Find User Screen");

		string UserName = "";
		cout << "Please enter a username: ";
		UserName = clsInputValidate::ReadString();

		while (!clsUser::DoesUserExist(UserName))
		{
			cout << "User does not exist, please enter a valid username.\n";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);
		
		if (!User.IsEmpty())
		{
			cout << "\nUser Found :)\n";
		}

		else
		{
			cout << "\nUser Not Found :(\n";
		}

		_PrintUser(User);

		

	}
};

