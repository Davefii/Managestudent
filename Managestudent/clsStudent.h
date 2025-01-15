#pragma once
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>
#include <string>
#include "clsDate.h"
using namespace std;
class clsPerson;
class clsStudent : public clsPerson
{
private:
    string _DateRegister;
    string _NumberStudent;
    bool _MarkForDeleted = false;
    static clsStudent _ConvertRecordLineToObject(string Line, string Seperator = "#//#")
    {
        vector<string> vStudentData;
        vStudentData = clsString::Split(Line, Seperator);
        if (vStudentData.size() < 4) {
            throw runtime_error("Invalid data format in line: " + Line);
        }
        return clsStudent(vStudentData[0], vStudentData[1], vStudentData[2],vStudentData[3],vStudentData[4],vStudentData[5]);
    }
    static string _ConverStudentObjectToLine(clsStudent Student, string Seperator = "#//#")
    {
        string stStudentRecord = "";
        stStudentRecord += clsDate::GetSystemDate().DateToString() + Seperator;
        stStudentRecord += Student.NumberStudent + Seperator;
        stStudentRecord += Student.FirstName + Seperator;
        stStudentRecord += Student.LastName + Seperator;
        stStudentRecord += Student.Email + Seperator;
        stStudentRecord += Student.Phone;
        return stStudentRecord;
    }
    static vector <clsStudent> _LoadStudentFromFile()
    {
        vector <clsStudent> vStudent;
        fstream StuFile;
        StuFile.open("student.txt", ios::in);
        if (StuFile.is_open())
        {
            string Line;
            while (getline(StuFile, Line))
            {
                clsStudent student = _ConvertRecordLineToObject(Line);
                vStudent.push_back(student);
            }
            StuFile.close();
        }
        return vStudent;
    }
    static void _SaveStudentsDataToFile(vector <clsStudent> &vStudents)
    {
        fstream StuFile;
        StuFile.open("student.txt", ios::out);//overwrite
        string DataLine;
        if (StuFile.is_open())
        {
            for (clsStudent& C : vStudents)
            {
                if (C.MarkedForDeleted() == false)
                {
                    //we only write records that are not marked for delete.  
                    DataLine = _ConverStudentObjectToLine(C);
                    StuFile << DataLine << endl;
                }
            }
            StuFile.close();
        }
    }
    void _AddDataLineToFile(string stDataLine)
    {
        fstream StuFile;
        StuFile.open("Clients.txt", ios::out | ios::app);
        if (StuFile.is_open())
        {
            StuFile << stDataLine << endl;
            StuFile.close();
        }
    }
    static clsStudent _GetEmptyStudent()
    {
        return clsStudent("", "", "", "", "", "");
    }
public:
    clsStudent()
    {

    }
    clsStudent(string DateRegister,string NumberStudent ,string SFirstName, string SLastName, string SEmail, string SPhone)
    {
        _DateRegister = DateRegister;
        _NumberStudent = NumberStudent;
        FirstName = SFirstName;
        LastName = SLastName;
        Email = SEmail;
        Phone = SPhone;
    }
    void setNumberStudent(string NumberStudent)
    {
        _NumberStudent = NumberStudent;
    }
    string getnumberStudent()
    {
        return _NumberStudent;
    }
    __declspec(property(get = getnumberStudent, put = setNumberStudent))string NumberStudent;
    string DateRegister()
    {
        return _DateRegister;
    }
    bool MarkedForDeleted()
    {
        return _MarkForDeleted;
    }
    bool Delete(string NumberStudent)
    {
        vector <clsStudent> _vStudnets = _LoadStudentFromFile();
        bool StudentFound = false;// Track if the client is found
        for (clsStudent& stu : _vStudnets)
        {
            // Check if the current student matches the identifier
            if (stu.NumberStudent == NumberStudent)
            {
                stu._MarkForDeleted = true;// Mark the client for deletion
                StudentFound = true;
                break;
            }
        }
        if (StudentFound)
        {
            _SaveStudentsDataToFile(_vStudnets);// Save updated client data
            *this = _GetEmptyStudent();// Clear the current client object
            return true;// Return success
        }
        return false;// Return false if no matching client was found
    }
    static vector <clsStudent> GetListStudent()
    {
        return _LoadStudentFromFile();
    }
    static void addNewStudent(clsStudent Student)
    {
        fstream StuFile;
        StuFile.open("student.txt", ios::out | ios::app);
        if (StuFile.is_open())
        {
            string Line = _ConverStudentObjectToLine(Student);
            StuFile << Line << endl;
            StuFile.close();
        }
    }
    static clsStudent Find(string NumberStudent)
    {
        vector <clsStudent> vStudents;
        fstream BankFile;
        BankFile.open("student.txt", ios::in);
        if (BankFile.is_open())
        {
            string Line;
            while (getline(BankFile, Line))
            {
                clsStudent Student = _ConvertRecordLineToObject(Line);
                if (Student.NumberStudent == NumberStudent)
                {
                    BankFile.close();
                    return Student;
                }
                vStudents.push_back(Student);
            }
        }
        return _GetEmptyStudent();
    }
    static bool isStudentExist(string NumberStudent)
    {
        vector <clsStudent> vStudents = _LoadStudentFromFile();
        for (clsStudent student : vStudents)
        {
            if (student.NumberStudent == NumberStudent)
            {
                return true;
            }
        }
        return false;
    }
    void Update(string NumberStudent)
    {
        vector <clsStudent> vStudents = _LoadStudentFromFile();
        for (clsStudent& c : vStudents)
        {
            if (c.NumberStudent == NumberStudent)
            {
                c = *this;
                break;
            }
        }
        _SaveStudentsDataToFile(vStudents);
    }
};