#pragma once
#include "clsUser.h"
#include <iomanip>
#include <vector>
#include <fstream>
#include "clsMainMenuScreen.h"

class clsLoginScreen : protected clsScreen
{
private:
	static string _PerpareRegister(clsUser User, string Seperator = "#//#")
	{
		string UserRecord = "";
		UserRecord += clsDate::DateToString(clsDate()) + Seperator;
		UserRecord += User.UserName + Seperator;
		UserRecord += clsUtil::EncryptText(User.Password) + Seperator;
		UserRecord += to_string(User.Permissions);
		return UserRecord;
	}
	static void _SaveLoginRegister(string DataLine)
	{
		fstream LogFile;
		LogFile.open("Log.txt", ios::out | ios::app);
		if (LogFile.is_open())
		{
			LogFile << DataLine << endl;
			LogFile.close();
		}
	}
	static void _saveLoginregister()
	{
		_SaveLoginRegister(_PerpareRegister(CurrentUser));
	}
	static bool _Login()
	{
		short FaildLoginCount = 0;
		bool LoginFaild = false;
		do
		{
			string userName, passWord;
			if (LoginFaild)
			{
				FaildLoginCount++;
				cout << "\nInvalid Username/Password!" << endl;
				cout << "\nYou have " << (3 - FaildLoginCount)
					<< " Trial(s) to login.\n\n";
			}
			if (FaildLoginCount == 3)
			{
				cout << "Login is Locked" << endl;
				return false;
			}
			cout << "Enter Username? ";
			cin >> userName;
			cout << "Enter Password? ";
			cin >> passWord;
			CurrentUser = clsUser::Find(userName, passWord);
			LoginFaild = CurrentUser.IsEmpty();
		} while (LoginFaild);
		_saveLoginregister();
		clsMainMenuScreen::ShowMainMenuScreen();
		return true;
	}
public:
	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t Login Screen");
		return _Login();
	}
};