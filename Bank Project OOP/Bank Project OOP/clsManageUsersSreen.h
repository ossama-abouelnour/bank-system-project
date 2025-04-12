#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUsersScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

using namespace std;

class clsManageUsersSreen : protected clsScreen
{
private:

    enum enManageUsers {
        enListUsers = 1,
        enAddNewUsers = 2,
        enDeleteUsers = 3,
        enUpdateUsers = 4,
        enFindUsers = 5,
        enMainMenu = 6
    };

    static short _ReadManageUsersOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short choice = clsInputValidate::ReadShortNumberBetween(1, 6);
        return choice;
    }

    static void _ShowListUsersScreen()
    {
        clsListUsersScreen::ShowUsersList();
        
    }

    static void _ShowAddNewUsersScreen()
    {
        clsAddNewUsersScreen::ShowAddNewUserScreen();
       
    }

    static void _ShowDeleteUsersScreen()
    {
        clsDeleteUserScreen::ShowDeleteUserScreen();
       
    }

    static void _ShowUpdateUsersScreen()
    {
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }

    static void _ShowFindUsersScreen()
    {
        clsFindUserScreen::ShowFindUserScreen();
       
    }

    static void _PerformManagerUsersMenu(enManageUsers Choice)
    {
        switch (Choice)
        {
        case clsManageUsersSreen::enListUsers:
            system("cls");
            _ShowListUsersScreen();
            _GoBackToManageUsersMenu();
            break;
        case clsManageUsersSreen::enAddNewUsers:
            system("cls");
            _ShowAddNewUsersScreen();
            _GoBackToManageUsersMenu();
            break;
        case clsManageUsersSreen::enDeleteUsers:
            system("cls");
            _ShowDeleteUsersScreen();
            _GoBackToManageUsersMenu();
            break;
        case clsManageUsersSreen::enUpdateUsers:
            system("cls");
            _ShowUpdateUsersScreen();
            _GoBackToManageUsersMenu();
            break;
        case clsManageUsersSreen::enFindUsers:
            system("cls");
            _ShowFindUsersScreen();
            _GoBackToManageUsersMenu();
            break;

        case clsManageUsersSreen::enMainMenu:
        {
            
        }
            break;
        }



    }


    static void _GoBackToManageUsersMenu()
    {

        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

        system("pause>0");
        ShowManageUsersMenu();
    }

public:

	static void ShowManageUsersMenu()
	{
        system("cls");
        if (!CheckAccessRights(clsUser::enPermissions::ManagerUsers))
        {
            return;
        }
        _ScreenHeader("\t Manage Users Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Manage Users Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Users.\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _PerformManagerUsersMenu((enManageUsers)_ReadManageUsersOption());
	}

};

