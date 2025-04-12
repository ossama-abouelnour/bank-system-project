#pragma once
#include <iostream>
#include "clsScreen.h"
#include <fstream>

using namespace std;


class clsUsersLoginHistory : protected clsScreen
{
private:

	static void _PrintLoginHistoryRecordLine(clsUser::stLoginHistoryRecord LoginHistoryRecord)
	{
		cout << setw(8) << left << "" << "|" << setw(35) << LoginHistoryRecord.DateTime;
		cout << "| " << setw(20) << left << LoginHistoryRecord.Username;
		cout << "| " << setw(20) << left << LoginHistoryRecord.Password;
		cout << "| " << setw(10) << left << LoginHistoryRecord.Permissions;
	}



public:
	static void ShowUsersLoginHistory()
	{
		if (!CheckAccessRights(clsUser::enPermissions::UsersLoginHistory))
		{
			return;
		}
		vector <clsUser::stLoginHistoryRecord> vLoginHistoryRecord = clsUser::GetLoginHistoryList();

		string Title = "\tUsers Login History Screen";
		string SubTitle = "\t\t(" + to_string(vLoginHistoryRecord.size()) + ") Record(s).";

		_ScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
		cout << "| " << left << setw(20) << "UserName";
		cout << "| " << left << setw(20) << "Password";
		cout << "| " << left << setw(10) << "Permissions";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		if (vLoginHistoryRecord.size() == 0)
			cout << "\t\t\t\tNo Logins Available in the System!";
		else
			for (clsUser::stLoginHistoryRecord& Record : vLoginHistoryRecord)
			{
				_PrintLoginHistoryRecordLine(Record);
				cout << endl;
			}
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
	}

};

