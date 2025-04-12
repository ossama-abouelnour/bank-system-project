#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include "clsUtil.h"

using namespace std;

class clsUser : public clsPerson
{

private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;
	string _UserName, _Password;
	int _Permissions;

	bool _MarkedForDeletion = false;


	string _PrepareLoginRecord(string Delim = "#//#")
	{
		string LoginRecord = "";

		LoginRecord += clsDate::GetSystemDateTimeString() + Delim;
		LoginRecord += UserName + Delim;
		LoginRecord += clsUtil::EncryptText(Password) + Delim;
		LoginRecord += to_string(Permissions);
		return LoginRecord;
	}

	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static string _ConvertObjectToLine(clsUser User, string Seperator = "#//#")
	{
		string UserRecord = "";
		UserRecord += User.FirstName + Seperator;
		UserRecord += User.LastName + Seperator;
		UserRecord += User.Email + Seperator;
		UserRecord += User.Phone + Seperator;
		UserRecord += User.UserName + Seperator;
		UserRecord += clsUtil::EncryptText(User.Password) + Seperator;
		UserRecord += to_string(User.Permissions);

		return UserRecord;
	}

	static clsUser _ConvertLineToUserObject(string Line , string Seperator = "#//#")
	{
		vector<string> vUserData;

		vUserData = clsString::Split(Line, Seperator);

		return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
			vUserData[3], vUserData[4], clsUtil::DecryptText(vUserData[5]) , stoi(vUserData[6]));
	}

	static vector <clsUser> _LoadUsersDataFromFile()
	{
		fstream MyFile;
		vector <clsUser> vUsers;

		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				vUsers.push_back(User);
			}
			MyFile.close();
		}
		return vUsers;
	}

	void _SaveUsersDataToFile(vector <clsUser>& vUsers)
	{
		fstream MyFile;
		string DataLine;
		MyFile.open("Users.txt", ios::out);

		if (MyFile.is_open())
		{
			for (clsUser& User : vUsers)
			{
				if (User.MarkedForDeletion() == false)
				{
					DataLine = _ConvertObjectToLine(User);
					MyFile << DataLine << endl;
				}
			}
			MyFile.close();
		}

	}

	void _Update()
	{
		vector <clsUser> _vUsers;

		_vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : _vUsers)
		{
			if (U.UserName == UserName)
			{
				U = *this;
				break;
			}
		}
		_SaveUsersDataToFile(_vUsers);
	}

	void _AddDataLineToFile(string Line)
	{
		 fstream MyFile;

		 MyFile.open("Users.txt", ios::out | ios::app);

		 if (MyFile.is_open())
		 {
			 MyFile << Line << endl;
		 }
		 MyFile.close();
	}


	void _AddNew()
	{
		_AddDataLineToFile(_ConvertObjectToLine(*this));
	}

	struct stLoginHistoryRecord;

	static stLoginHistoryRecord _ConvertLoginHistoryLineToRecord(string DataLine)
	{
		stLoginHistoryRecord LoginHistoryRecord;

		vector<string> LoginHistoryDataLine = clsString::Split(DataLine, "#//#");

		LoginHistoryRecord.DateTime = LoginHistoryDataLine[0];
		LoginHistoryRecord.Username = LoginHistoryDataLine[1];
		LoginHistoryRecord.Password = clsUtil::DecryptText(LoginHistoryDataLine[2]);
		LoginHistoryRecord.Permissions = stoi(LoginHistoryDataLine[3]);

		return LoginHistoryRecord;
	}
	

public:

	enum enPermissions {
		All = -1, ListClients = 1, AddNewClients = 2, DeleteClients = 4, 
		UpdateClients = 8, FindClients = 16, Transactions = 32, ManagerUsers = 64, UsersLoginHistory = 128
	};

	struct stLoginHistoryRecord
	{
		string DateTime;
		string Username;
		string Password;
		int Permissions;
	};


	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password, int Permissions) :
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}


	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDeletion()
	{
		return _MarkedForDeletion;
	}

	string GetUserName()
	{
		return _UserName;
	}

	void SetUserName(string UserName)
	{
		_UserName = UserName;
	}

	_declspec(property(get = GetUserName, put = SetUserName)) string UserName;
	

	string GetPassword()
	{
		return _Password;
	}

	void SetPassword(string Password)
	{
		_Password = Password;
	}

	_declspec(property(get = GetPassword, put = SetPassword)) string Password;

	int GetPermissions()
	{
		return _Permissions;
	}

	void SetUserName(int Permissions)
	{
		_Permissions = Permissions;
	}

	_declspec(property(get = GetPermissions, put = SetUserName)) int Permissions;

	

	static clsUser Find(string UserName)
	{
		fstream MyFile;

		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);

				if (User.UserName == UserName)
				{
					MyFile.close();
					return User;
				}
			}

			MyFile.close();
		}

		return _GetEmptyUserObject();
	}

	static clsUser Find(string UserName, string Password)
	{
		fstream MyFile;

		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);

				if (User.UserName == UserName && User.Password == Password)
				{
					MyFile.close();
					return User;
				}
			}

			MyFile.close();
		}

		return _GetEmptyUserObject();
	}

	static bool DoesUserExist(string UserName)
	{
		clsUser User = clsUser::Find(UserName);

		return (!User.IsEmpty());
	}

	bool Delete()
	{
		vector<clsUser> vClients = _LoadUsersDataFromFile();

		for (clsUser& C : vClients)
		{
			if (C.UserName == _UserName)
			{
				C._MarkedForDeletion = true;
				break;
			}

		}
		_SaveUsersDataToFile(vClients);

		*this = _GetEmptyUserObject();
		return true;
	}


	enum enSaveResult{ svFailedEmptyObject = 0, svSucceeded = 1, svFailedUserExists = 2 };


	enSaveResult Save()
	{
		switch (_Mode)
		{
		case clsUser::EmptyMode:
			if (IsEmpty())
			{
				return enSaveResult::svFailedEmptyObject;
			}

		case clsUser::UpdateMode:
			_Update();
			enSaveResult::svSucceeded;
			break;

		case clsUser::AddNewMode:

			if (DoesUserExist(_UserName))
			{
				return enSaveResult::svFailedUserExists;
			}

			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResult::svSucceeded;
			}
			break;
		}
	}

	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	static vector <clsUser> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}

	bool CheckAccessPermissions(enPermissions Permission)
	{
		if (this->Permissions == enPermissions::All)
			return true;

		if ((Permission & this->Permissions) == Permission)
			return true;
		else
			return false;

	}


	void LoginHistory()
	{
		string stDataLine = _PrepareLoginRecord();

		fstream MyFile;

		MyFile.open("LoginHistory.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;
		}
		MyFile.close();
	}

	static vector<stLoginHistoryRecord> GetLoginHistoryList()
	{
		fstream MyFile;

		vector <stLoginHistoryRecord> vLoginHistoryRecords;

		MyFile.open("LoginHistory.txt", ios::in);



		if (MyFile.is_open())
		{
			string DataLine = "";
			stLoginHistoryRecord LoginHistoryRecord;

			while (getline(MyFile, DataLine))
			{
				LoginHistoryRecord = _ConvertLoginHistoryLineToRecord(DataLine);
				
				vLoginHistoryRecords.push_back(LoginHistoryRecord);
			}
			MyFile.close();
		}
		return vLoginHistoryRecords;
	}

};

