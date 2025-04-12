#pragma once

#include <iostream>
#include "clsUser.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateUserScreen : protected clsScreen
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

	static void ShowUpdateUserScreen()
	{
		_ScreenHeader("\tUpdate User Screen");

		string UserName = "";

		cout << "\nPlease Enter User UserName: ";
		UserName = clsInputValidate::ReadString();

		while (!clsUser::DoesUserExist(UserName))
		{
			cout << "\nAccount number is not found, choose another one: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User1 = clsUser::Find(UserName);

		_PrintUser(User1);

		cout << "\nAre you sure you want to update this User y/n? ";

		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{

			cout << "\n\nUpdate User Info:";
			cout << "\n____________________\n";


			_ReadUserInfo(User1);

			clsUser::enSaveResult SaveResult;

			SaveResult = User1.Save();

			switch (SaveResult)
			{
			case  clsUser::enSaveResult::svSucceeded:
			{
				cout << "\nUser Updated Successfully :-)\n";

				_PrintUser(User1);
				break;
			}
			case clsUser::enSaveResult::svFailedEmptyObject:
			{
				cout << "\nError User was not saved because it's Empty";
				break;

			}


			}
			
		}
	}
};