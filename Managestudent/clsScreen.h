#pragma once
#include <iostream>
#include "clsDate.h"
#include "Global.h"
using namespace std;
class clsScreen
{
protected:
    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";
        time_t t = time(0); // get time now
        tm* now = localtime(&t);
        //cout << "\n\t\t\t\t\tUser:" << CurrentUser.UserName << "\n";
        cout << "\t\t\t\t\tDate:" << clsDate::DateToString(clsDate()) << "\n\n";
    }
    static bool CheckRightAccesPermitions(clsUser::enPermissions Permission)
    {
        if (!CurrentUser.CheckAccesPermition(Permission))
        {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;
        }
        else
        {
            return true;
        }
    }
};
