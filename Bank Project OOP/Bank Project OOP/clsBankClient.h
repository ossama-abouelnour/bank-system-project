#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>

using namespace std;

class clsBankClient : public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;

	string _AccountNumber;
	string _Pin;
	float _AccountBalance;
	bool _MarkForDeletion = false;

	static clsBankClient _ConvertLineToClientObject(string Line, string Separator = "#//#")
	{
		vector<string> vClients = clsString::Split(Line, Separator);

		if (vClients.size() < 7)
		{
			return _GetEmptyClientObject();
		}

		return clsBankClient(enMode::UpdateMode, vClients[0], vClients[1], vClients[2], vClients[3], vClients[4], vClients[5], stod(vClients[6]));
	}

	static string _ConvertClientObjectToLine(clsBankClient & Client, string Separator = "#//#")
	{
		string ClientRecordLine = "";

		ClientRecordLine = Client.FirstName + Separator;
		ClientRecordLine += Client.LastName + Separator;
		ClientRecordLine += Client.Email + Separator;
		ClientRecordLine += Client.Phone + Separator;
		ClientRecordLine += Client.AccountNumber() + Separator;
		ClientRecordLine += Client.Pin + Separator;;
		ClientRecordLine += to_string(Client.AccountBalance);

		return ClientRecordLine;
	}

	static clsBankClient _GetEmptyClientObject()
	{

		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector <clsBankClient> _LoadClientsDataFromFile()
	{
		fstream MyFile;
		vector <clsBankClient> vClients;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				vClients.push_back(Client);
			}
			MyFile.close();
		}

		return vClients;
	}

	static void _SaveClientsDataToFile( vector<clsBankClient>& vClients )
	{
		fstream MyFile;

		MyFile.open("Clients.txt", ios::out);

		if (MyFile.is_open());
		{
			for (clsBankClient& C : vClients)
			{
				if (C._MarkForDeletion == false)
				{
					string Line = _ConvertClientObjectToLine(C);

					MyFile << Line << endl;
				}

				
			}
			MyFile.close();
		}

		
	}

	void _Update()
	{
		vector <clsBankClient> _vClients;

		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}
		_SaveClientsDataToFile(_vClients);
	}

	void _AddDataLineToFile(string DataLine)
	{
		fstream MyFile;

		MyFile.open("Clients.txt", ios::out | ios::app);

		if(MyFile.is_open())
		{
			MyFile << DataLine << endl;
			MyFile.close();
		}
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	string _PrepareTransferLogRecord(float Amount, clsBankClient DestinationClient, string Username ,string Delim = "#//#")
	{
		string TransferRecord = "";

		TransferRecord += clsDate::GetSystemDateTimeString() + Delim;
		TransferRecord += AccountNumber() + Delim;
		TransferRecord += DestinationClient.AccountNumber() + Delim;
		TransferRecord += to_string(Amount) + Delim;
		TransferRecord += to_string(AccountBalance) + Delim;
		TransferRecord += to_string(DestinationClient.AccountBalance) + Delim;
		TransferRecord += Username;

		return TransferRecord;
	}

	void _RegisterTransferLog(float Amount, clsBankClient DestinationClient, string Username)
	{
		fstream MyFile;

		MyFile.open("TransfersLog.txt", ios::out | ios::app);

		string DataLine = _PrepareTransferLogRecord(Amount, DestinationClient, Username);

		if (MyFile.is_open())
		{
			MyFile << DataLine << endl;
		}

		MyFile.close();
	}

	struct stTransferHistory;

	static stTransferHistory _ChangeTransferLogLineToRecord(string DataLine, string Delim = "#//#")
	{
		vector<string> vTransferHistory = clsString::Split(DataLine, Delim);
		stTransferHistory TransferHistory;

		TransferHistory.DateTime = vTransferHistory[0];
		TransferHistory.SourceAccountNumber = vTransferHistory[1];
		TransferHistory.DestinationAccountNumber = vTransferHistory[2];
		TransferHistory.Amount = stod(vTransferHistory[3]);
		TransferHistory.srcBalanceAfterTransfer = stod(vTransferHistory[4]);
		TransferHistory.destAccountBalanceAfter = stod(vTransferHistory[5]);
		TransferHistory.Username = vTransferHistory[6];

		return TransferHistory;
	}

public:

	struct stTransferHistory {
		string DateTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		float Amount;
		float srcBalanceAfterTransfer;
		float destAccountBalanceAfter;
		string Username;
	};

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string Pin, float AccountBalance) :
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_Pin = Pin;
		_AccountBalance = AccountBalance;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	string AccountNumber()
	{
		return _AccountNumber;
	}

	void SetPin(string Pin)
	{
		_Pin = Pin;
	}

	string GetPin()
	{
		return _Pin;
	}
	__declspec(property(get = GetPin, put = SetPin)) string Pin;

	void SetBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	float GetAccountBalance()
	{
		return _AccountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = SetBalance)) float AccountBalance;

	static clsBankClient Find(string AccountNumber)
	{
		vector<clsBankClient> vClients;

		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);

				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}
				vClients.push_back(Client);
			}

			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string Pin)
	{
		vector<clsBankClient> vClients;

		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);

				if (Client.AccountNumber() == AccountNumber && Client.Pin == Pin)
				{
					MyFile.close();
					return Client;
				}
				vClients.push_back(Client);
			}

			MyFile.close();
		}
		return _GetEmptyClientObject();

	}

	static bool DoesClientExist(string AccountNumber)
	{
		clsBankClient Client = clsBankClient::Find(AccountNumber);

		return (!Client.IsEmpty());
	}

	enum enSaveResults { svFailedEmptyObject = 0, svSucceeded = 1, svFailedAccountNumberExist = 2 };

	enSaveResults Save()
	{
	

		switch (_Mode)
		{
		case clsBankClient::EmptyMode:

			return enSaveResults::svFailedEmptyObject;

		case clsBankClient::UpdateMode:
			
			_Update();
			return enSaveResults::svSucceeded;

		case clsBankClient::AddNewMode:

			if (clsBankClient::DoesClientExist(_AccountNumber))
			{
				return enSaveResults::svFailedAccountNumberExist;
			}

			else
			{
				_AddNew();
				_Mode = clsBankClient::UpdateMode;
				return enSaveResults::svSucceeded;
			}

			break;
		}
	}

	static clsBankClient AddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	bool Delete()
	{
		vector<clsBankClient> vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : vClients)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkForDeletion = true;
				break;
			}

		}
		_SaveClientsDataToFile(vClients);

		*this = _GetEmptyClientObject();
		return true;
	}

	static vector <clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	static double GetTotalBalances()
	{
		vector <clsBankClient> vClients = _LoadClientsDataFromFile();

		double TotalBalances = 0;

		for (clsBankClient& Client : vClients)
		{
			TotalBalances += Client.AccountBalance;
		}
		return TotalBalances;
	}

	void Deposit(double Amount)
	{
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount)
	{
		if (Amount > _AccountBalance)
		{
			return false;
		}
		else 
		{
			_AccountBalance -= Amount;
			Save();
		}
		
	}

	bool Transfer(float Amount, clsBankClient& DestinationClient, string Username)
	{
		if (Amount > AccountBalance)
		{
			return false;
		}

		Withdraw(Amount);
		DestinationClient.Deposit(Amount);
		_RegisterTransferLog(Amount, DestinationClient, Username);
		return true;
	}

	static vector<stTransferHistory> GetTransferLogHistory()
	{
		vector<stTransferHistory> vTransferHistoryLog;

		fstream MyFile;

		MyFile.open("TransfersLog.txt", ios::in);

		if (MyFile.is_open())
		{
			string DataLine; 
			stTransferHistory TransferRecord;

			while (getline(MyFile, DataLine))
			{
				TransferRecord = _ChangeTransferLogLineToRecord(DataLine);
				vTransferHistoryLog.push_back(TransferRecord);
			}
			MyFile.close();
		}
		return vTransferHistoryLog;
	}


};