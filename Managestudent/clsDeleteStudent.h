#pragma once
#include <iostream>
#include "clsValidateInput.h"
#include "clsScreen.h"
#include "clsStudent.h"
class clsDeleteStudent : protected clsScreen
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
	static void ShowDeleteStudentScreen()
	{
		if (CheckRightAccesPermitions(clsUser::enPermissions::pDeleteStudent))
		{
			return;
		}
		_DrawScreenHeader("\t Delete Student");
		cout << "Enter Number Student : " << endl;
		string NumberStudent = clsValidateInput<string>::ReadString();
		while (!clsStudent::isStudentExist(NumberStudent))
		{
			cout << "NumberStudent Doesn't Exist Choose Another one : " << endl;
			NumberStudent = clsValidateInput<string>::ReadString();
		}
		clsStudent Student = clsStudent::Find(NumberStudent);
		_PrintStudent(Student);
		cout << "Do You Want Delete This Student :" << endl;
		char anwser = 'n';
		cin >> anwser;
		if (anwser == 'y' || anwser == 'Y')
		{
			if (Student.Delete(Student.NumberStudent))
			{
				cout << "Student Deleted Successfully........." << endl;
				_PrintStudent(Student);
			}
			else
			{
				cout << "\nError Delete Student..." << endl;
			}
		}
	}
};