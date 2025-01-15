#pragma once
#include <iostream>
#include "clsValidateInput.h"
#include "clsScreen.h"
#include "clsStudent.h"
#include "clsUser.h"
class clsUpdateStudent : protected clsScreen
{
private:
	static void _ReadUpdatePerson(clsStudent& Person)
	{
		cout << "Enter Your First Name : " << endl;
		Person.FirstName = clsValidateInput<string>::ReadString();
		cout << "Enter Your Last Name : " << endl;
		Person.LastName = clsValidateInput<string>::ReadString();
		cout << "Enter Your Email : " << endl;
		Person.Email = clsValidateInput<string>::ReadString();
		cout << "Enter Your Phone Number : " << endl;
		Person.Phone = clsValidateInput<string>::ReadString();
	}
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
	static void ShowUpdateStudentScreen()
	{
		if (CheckRightAccesPermitions(clsUser::enPermissions::pUpdateStudents))
		{
			return;
		}
		_DrawScreenHeader("\t Update Student");
		cout << "Enter Number Student : " << endl;
		string NumberStudent = clsValidateInput<string>::ReadString();
		while (!clsStudent::isStudentExist(NumberStudent))
		{
			cout << "NumberStudent Doesn't Exist Choose Another one : " << endl;
			NumberStudent = clsValidateInput<string>::ReadString();
		}
		clsStudent Student = clsStudent::Find(NumberStudent);
		_PrintStudent(Student);
		cout << "Do You Want Update This Student :" << endl;
		char anwser = 'n';
		cin >> anwser;
		if (anwser == 'y' || anwser == 'Y')
		{
			_ReadUpdatePerson(Student);
			Student.Update(NumberStudent);
			cout << "Student Deleted Successfully........." << endl;
			_PrintStudent(Student);
		}
	}
};