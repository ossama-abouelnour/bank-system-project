#pragma once
#include <iostream>
#include "clsUser.h"
#include "clsInputValidate.h"

using namespace std;

class clsAddNewUsersScreen : protected clsScreen
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

	static void _ReadUserInfo(clsUser& User)
	{
		cout << "\nEnter FirstName: ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName: ";
		User.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		User.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone: ";
		User.Phone = clsInputValidate::ReadString();

		cout << "\nEnter Permissions: ";
		User.Permissions = _ReadPermissionsToSet();
	}

	static int _ReadPermissionsToSet()
	{
		int Permissions = 0;
		char Answer = 'n';

		cout << "Do you want to give full access: (y/n)? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			return -1;
		}

		cout << "Do want to give access to: \n";
		cout << "Show client list: (y/n)? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::ListClients;
		}

		cout << "\nAdd new client: (y/n)? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::AddNewClients;
		}

		cout << "\nDelete clients: (y/n)? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::DeleteClients;
		}

		cout << "\nUpdate clients: (y/n)? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::UpdateClients;
		}


		cout << "\nFind clients: (y/n)? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::FindClients;
		}


		cout << "\nTransactions: (y/n)? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::Transactions;
		}

		cout << "\nManage Users: (y/n)? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::ManagerUsers;
		}

		cout << "\nUsers Login History: (y/n)? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::UsersLoginHistory;
		}

		return Permissions;
	}



public:

	static void ShowAddNewUserScreen()
	{
		

		_ScreenHeader("\t  Add New User Screen");

		string UserName = "";

		cout << "\nPlease Enter UserName: ";
		UserName = clsInputValidate::ReadString();
		while (clsUser::DoesUserExist(UserName))
		{
			cout << "\nUserName Is Already Used, Choose another one: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser NewUser = clsUser::GetAddNewUserObject(UserName);

		_ReadUserInfo(NewUser);

		clsUser::enSaveResult SaveResult;

		SaveResult = NewUser.Save();

		switch (SaveResult)
		{
		case  clsUser::enSaveResult::svSucceeded:
		{
			cout << "\nUser Addeded Successfully :-)\n";
			_PrintUser(NewUser);
			break;
		}
		case clsUser::enSaveResult::svFailedEmptyObject:
		{
			cout << "\nError User was not saved because it's Empty";
			break;

		}
		case clsUser::enSaveResult::svFailedUserExists:
		{
			cout << "\nError User was not saved because UserName is used!\n";
			break;

		}


		}

	}

};