#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsValidateInput.h"
#include "clsAddNewStudent.h"
#include "clsListStudent.h";
#include "clsDeleteStudent.h"
#include "clsUpdateStudent.h"
#include "clsFindStudnet.h"
#include "clsManageUsersScreen.h"
#include "clsShowLoginRegisterScreen.h"
#include <iomanip>
class clsMainMenuScreen : protected clsScreen
{
    enum enMainMenuOption 
    {
        eShowStudent = 1, eAddNewStudent = 2,
        eDeleteStudent = 3, eUpdateStudent = 4,
        eFindStudent = 5, eManageUsers = 6,
        LoginRegister = 7, eExit = 8
    };
    static short ReadMainMenuOption()
    {
        short choise = 0;
        cout << setw(37) << left << "" << "Choose Another one 1 To 8 : ";
        choise = clsValidateInput<short>::ReadNumberBetween(1, 8);
        return choise;
    }
    static  void _GoBackToMainMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";
        system("pause>0");
        ShowMainMenuScreen();
    }
    static void _ShowAllStudentScreen()
    {
        clsListStudent::ShowStudentList();
    }
    static void _ShowAddNewStudentScreen()
    {
        clsAddNewStudent::ShowAddNewStudent();
    }
    static void _ShowDeleteStudentScreen()
    {
        clsDeleteStudent::ShowDeleteStudentScreen();
    }
    static void _ShowUpdateStudentScreen()
    {
        clsUpdateStudent::ShowUpdateStudentScreen();
    }
    static void _ShowFindStudentScreen()
    {
        clsFindStudnet::ShowFindStudentScreen();
    }
    //static void _ShowCalculatePointStudentMenue()
    //{
    //}
    static void _ShowUserManagerMenue()
    {
        clsManageUsersScreen::ShowManageUsersMenue();
    }
    static void _ShowLoginRegisterScreen()
    {
        clsShowLoginRegisterScreen::ShowLoginRegisterScreen();
    }
    static void _ShowEndScreen()
    {
        //cout << "\nEnd Screen Will be here...\n";
    }
    static void PerfomenceMainMenuScreen(enMainMenuOption MainMenuOption)
    {
        switch (MainMenuOption)
        {
        case clsMainMenuScreen::eShowStudent:
            system("cls");
            _ShowAllStudentScreen();
            _GoBackToMainMenue();
            break;
        case clsMainMenuScreen::eAddNewStudent:
            system("cls");
            _ShowAddNewStudentScreen();
            _GoBackToMainMenue();
            break;
        case clsMainMenuScreen::eDeleteStudent:
            system("cls");
            _ShowDeleteStudentScreen();
            _GoBackToMainMenue();
            break;
        case clsMainMenuScreen::eUpdateStudent:
            system("cls");
            _ShowUpdateStudentScreen();
            _GoBackToMainMenue();
            break;
        case clsMainMenuScreen::eFindStudent:
            system("cls");
            _ShowFindStudentScreen();
            _GoBackToMainMenue();
            break;
        /*case clsMainMenuScreen::eCalculatePointStudent:
            system("cls");
            _ShowCalculatePointStudentMenue();
            _GoBackToMainMenue();
            break;*/
        case clsMainMenuScreen::eManageUsers:
            system("cls");
            _ShowUserManagerMenue();
            _GoBackToMainMenue();
            break;
        case clsMainMenuScreen::LoginRegister:
            system("cls");
            _ShowLoginRegisterScreen();
            _GoBackToMainMenue();
            break;
        case clsMainMenuScreen::eExit:
            
            break;
        }
    }
public:
	static void ShowMainMenuScreen()
	{
        system("cls");
        _DrawScreenHeader("\t\tMain Menu");
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Student List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Student.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Student.\n";
        cout << setw(37) << left << "" << "\t[4] Update Student.\n";
        cout << setw(37) << left << "" << "\t[5] Find Student.\n";
        cout << setw(37) << left << "" << "\t[6] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[7] Login Register.\n";
        //cout << setw(37) << left << "" << "\t[5] Calculate Point Student.\n";
        cout << setw(37) << left << "" << "\t[8] Exit.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        PerfomenceMainMenuScreen((enMainMenuOption)ReadMainMenuOption());
	}
};