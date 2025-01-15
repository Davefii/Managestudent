#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsValidateInput.h"
class clsUpdateUser : protected clsScreen
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
        cout << "\nManage Users? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pListRegister;
        }
        return Permissions;

    }
public:
    static void  ShowUpdateUserScreen()
    {
        _DrawScreenHeader("\t Update User");
        string userName = "";
        cout << "\nPlease Enter User UserName: ";
        userName = clsValidateInput<string>::ReadString();
        while (!clsUser::IsUserExist(userName))
        {
            cout << "\nAccount number is not found, choose another one: ";
            userName = clsValidateInput<string>::ReadString();
        }
        clsUser user = clsUser::Find(userName);
        _PrintUser(user);

        cout << "\nAre you sure you want to update this User y/n? ";

        char Answer = 'n';
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            cout << "\n\nUpdate User Info:";
            cout << "\n____________________\n";
            _ReadUserInfo(user);
            clsUser::enSaveResults SaveResult;
            SaveResult = user.Save();
            switch (SaveResult)
            {
            case clsUser::svFaildEmptyObject:
                cout << "\nError User was not saved because it's Empty";
                break;
            case clsUser::svSucceeded:
                cout << "\nUser Updated Successfully :-)\n";
                _PrintUser(user);
                break;
            }
        }
    }
};