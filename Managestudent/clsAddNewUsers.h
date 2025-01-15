#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsValidateInput.h"
#include <iomanip>
using namespace std;
class clsAddNewUsers : protected clsScreen
{
private:
    static void _ReadUserInfo(clsUser& User)
    {
        cout << "\nEnter FirstName: ";
        User.FirstName = clsValidateInput<string>::ReadString();
    
        cout << "\nEnter LastName: ";
        User.LastName = clsValidateInput<string>::ReadString();
    
        cout << "\nEnter Email: ";
        User.Email = clsValidateInput<string>::ReadString();
    
        cout << "\nEnter Phone: ";
        User.Phone = clsValidateInput<string>::ReadString();
    
        cout << "\nEnter Password: ";
        User.Password = clsValidateInput<string>::ReadString();
    
        cout << "\nEnter Permission: ";
        User.Permissions = _ReadPermissionsToSet();
    }
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
    static int _ReadPermissionsToSet()
    {
        int Permissions = 0;
        char Answer = 'n';
        cout << "\nDo you want to give full access? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            return -1;
        }
        cout << "\nDo you want to give access to : \n ";
        cout << "\nShow Client List? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
    
    
            Permissions += clsUser::enPermissions::pListStudents;
        }
        cout << "\nAdd New Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pAddNewStudent;
        }
        cout << "\nDelete Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pDeleteStudent;
        }
        cout << "\nUpdate Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pUpdateStudents;
        }
        cout << "\nFind Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pFindStudents;
        }
        cout << "\nManage Users? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pManageUsers;
        }
        cout << "\nShow Register List? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pListRegister;
        }
        return Permissions;
    }
public:
    static void ShowAddNewUser()
    {
        _DrawScreenHeader("\t Add New User Screen");
        string userName = "";
        cout << "Enter User Name :" << endl;
        userName = clsValidateInput<string>::ReadString();
        while (clsUser::IsUserExist(userName))
        {
            cout << "User Name is Already Used Choose Another one :" << endl;
            userName = clsValidateInput<string>::ReadString();
        }
        clsUser NewUser = clsUser::GetAddNewUserObject(userName);
        _ReadUserInfo(NewUser);
        clsUser::enSaveResults  SaveResults;
        SaveResults = NewUser.Save();
        switch (SaveResults)
        {
        case clsUser::svFaildEmptyObject:
            cout << "\nError User was not saved because it's Empty";
            break;
        case clsUser::svSucceeded:
            cout << "\nUser Addeded Successfully :-)\n";
            _PrintUser(NewUser);
            break;
        case clsUser::svFaildUserExists:
            cout << "\nError User was not saved because UserName is used!\n";
            break;
        }
    }
};