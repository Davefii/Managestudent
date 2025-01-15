#pragma once
#include <iostream>
#include "clsValidateInput.h"
#include "clsScreen.h"
#include "clsStudent.h"
#include "clsUser.h"
class clsFindStudnet : protected clsScreen
{
private:
	static void _PrintStudent(clsStudent Student)
	{
		cout << "\nStudent Card:";
		cout << "\n___________________";
		cout << "\nUser Name   : " << Student.NumberStudent;
		cout << "\nFirstName   : " << Student.FirstName;
		cout << "\nLastName    : " << Student.LastName;
		cout << "\nEmail       : " << Student.Email;
		cout << "\nPhone       : " << Student.Phone;
		cout << "\n___________________\n";
	}
public:
	static void ShowFindStudentScreen()
	{
		if (!CheckRightAccesPermitions(clsUser::enPermissions::pFindStudents))
		{
			return;
		}
		_DrawScreenHeader("\t Find Student");
		cout << "Enter Number Student : " << endl;
		string NumberStudent = clsValidateInput<string>::ReadString();
		while (!clsStudent::isStudentExist(NumberStudent))
		{
			cout << "NumberStudent Doesn't Exist Choose Another one : " << endl;
			NumberStudent = clsValidateInput<string>::ReadString();
		}
		clsStudent Student = clsStudent::Find(NumberStudent);
		cout << "Student is Found " << endl;
		_PrintStudent(Student);
	}
};