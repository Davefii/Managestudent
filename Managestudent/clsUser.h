#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsUntility.h"
#include <vector>
#include <fstream>
#include "clsDate.h"
class clsUser : public clsPerson
{
    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permissions;

    bool _MarkedForDelete = false;
    struct stLoginRegister;
    static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> vUserData;
        vUserData = clsString::Split(Line, Seperator);

        return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
            vUserData[3], vUserData[4], clsUtil::DecryptText(vUserData[5]), stoi(vUserData[6]));

    }

    static string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#")
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
    
    static string _ConverRegisterUserToLine(clsUser User, string Seperator = "#//#")
    {
    	string UserRecord = "";
    	UserRecord += clsDate::DateToString(clsDate()) + " - ";
    	UserRecord += User.UserName + Seperator;
    	UserRecord += User.Password + Seperator;
    	UserRecord += to_string(User.Permissions);
    	return UserRecord;
    }
    
    static stLoginRegister _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
    {
        stLoginRegister LoginRegisterRecord;
        vector <string> LoginRegisterDataLine = clsString::Split(Line, Seperator);
        LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
        LoginRegisterRecord.userName = LoginRegisterDataLine[1];
        LoginRegisterRecord.Password = clsUtil::DecryptText(LoginRegisterDataLine[2]);
        LoginRegisterRecord.Permitions = stoi(LoginRegisterDataLine[3]);
        return LoginRegisterRecord;
    }

    static vector <clsUser> _LoadUsersDataLineToFile()
    {
        vector <clsUser> vUsers;
        fstream UserFile;
        UserFile.open("Users.txt",ios::in);
        if (UserFile.is_open())
        {
            string Line;

            while (getline(UserFile, Line))
            {
                clsUser Usr = _ConvertLinetoUserObject(Line);
                vUsers.push_back(Usr);
            }
            UserFile.close();
        }
        return vUsers;
    }
    static void _SaveUsersDataToFile(vector <clsUser> vUsers)
    {

        fstream MyFile;
        MyFile.open("Users.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsUser U : vUsers)
            {
                if (U.MarkedForDeleted() == false)
                {
                    //we only write records that are not marked for delete.  
                    DataLine = _ConverUserObjectToLine(U);
                    MyFile << DataLine << endl;

                }

            }

            MyFile.close();

        }

    }
    void _Update()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataLineToFile();

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
    void _AddNew()
    {
        _AddDataLineToFile(_ConverUserObjectToLine(*this));
    }
    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }
    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }
public:
    enum enPermissions {
        eAll = -1, pListStudents = 1, pAddNewStudent = 2, pDeleteStudent = 4, pUpdateStudents = 8,
        pFindStudents = 16, pManageUsers = 32, pListRegister = 64
    };
    struct stLoginRegister
    {
        string DateTime;
        string userName;
        string Password;
        int Permitions;
    };
    clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password,
        int Permissions) : clsPerson(FirstName, LastName, Email, Phone)
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
    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }
    string GetUserName()
    {
        return _UserName;
    }
    void SetUserName(string UserName)
    {
        _UserName = UserName;
    }
    __declspec(property(get = GetUserName, put = SetUserName)) string UserName;
    void SetPassword(string Password)
    {
        _Password = Password;
    }
    string GetPassword()
    {
        return _Password;
    }
    __declspec(property(get = GetPassword, put = SetPassword)) string Password;
    void SetPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }
    int GetPermissions()
    {
        return _Permissions;
    }
    __declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;
    static clsUser Find(string UserName)
    {
        fstream UserFile;
        UserFile.open("Users.txt",ios::in);
        if (UserFile.is_open())
        {
            string Line;
            while (getline(UserFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName == UserName)
                {
                    UserFile.close();
                    return User;
                }
            }
            UserFile.close();
        }
        return _GetEmptyUserObject();
    }
    static clsUser Find(string UserName, string Password)
    {
        fstream UserFile;
        UserFile.open("Users.txt", ios::in);
        if (UserFile.is_open())
        {
            string Line;
            while (getline(UserFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName == UserName && User.Password == Password)
                {
                    UserFile.close();
                    return User;
                }
            }
            UserFile.close();
        }
        return _GetEmptyUserObject();
    }
    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };
    enSaveResults Save()
    {

        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (IsEmpty())
            {
                return enSaveResults::svFaildEmptyObject;
            }
        }

        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;

            break;
        }

        case enMode::AddNewMode:
        {
            //This will add new record to file or database
            if (clsUser::IsUserExist(_UserName))
            {
                return enSaveResults::svFaildUserExists;
            }
            else
            {
                _AddNew();
                //We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

            break;
        }
        }

    }
    static bool IsUserExist(string UserName)
    {
        clsUser User = clsUser::Find(UserName);
        return (!User.IsEmpty());
    }
    bool Delete()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataLineToFile();
        bool UserFond = false;
        for (clsUser& U : _vUsers)
        {
            if (U.UserName == _UserName)
            {
                U._MarkedForDelete = true;
                UserFond = true;
                break;
            }

        }
        if (UserFond)
        {
            _SaveUsersDataToFile(_vUsers);
            *this = _GetEmptyUserObject();
            return true;
        }
        return false;
    }
    static clsUser GetAddNewUserObject(string UserName)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }
    static vector <clsUser> GetUsersList()
    {
        return _LoadUsersDataLineToFile();
    }
    bool CheckAccesPermition(enPermissions Permission)
    {
        if (this->Permissions == enPermissions::eAll)
        {
            return true;
        }
        if ((Permission & this->Permissions) == Permission)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    static vector <stLoginRegister> GetLoginRegister()
    {
        vector <stLoginRegister> vLoginRegisterRecord;
        fstream LogFile;
        LogFile.open("Log.txt", ios::in);
        if (LogFile.is_open())
        {
            string Line;
            stLoginRegister LoginRegisterRecord;
            while (getline(LogFile, Line))
            {
                LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);
                vLoginRegisterRecord.push_back(LoginRegisterRecord);
            }
            LogFile.close();
        }
        return vLoginRegisterRecord;
    }
};