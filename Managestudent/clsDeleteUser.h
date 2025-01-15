#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsValidateInput.h"
class clsDeleteUser : protected clsScreen
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
    static void ShowDeleteUserScreen()
    {
        _DrawScreenHeader("\tDelete User Screen");
        string UserName = "";
        cout << "\nPlease Enter UserName: " << endl;
        UserName = clsValidateInput<string>::ReadString();
        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\nUser is not found, choose another one: ";
            UserName = clsValidateInput<string>::ReadString();
        }
        clsUser user = clsUser::Find(UserName);
        _PrintUser(user);
        char answer = 'n';
        cout << "\nAre you sure you want to delete this User y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            if (user.Delete())
            {
                cout << "\nUser Deleted Successfully :-)\n";
                _PrintUser(user);
            }
            else
            {
                cout << "\nError User Was not Deleted\n";
            }
        }
    }
};