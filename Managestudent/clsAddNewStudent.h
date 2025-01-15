#pragma once
#include <iostream>
#include "clsValidateInput.h"
#include "clsScreen.h"
#include "clsStudent.h"
class clsAddNewStudent : public clsScreen
{
private:
	static void _ReadNewPerson(clsStudent& Person, string NumberStudent)
	{
		Person.NumberStudent = NumberStudent;
	    cout << "Enter Your First Name : " << endl;
	    Person.FirstName = clsValidateInput<string>::ReadString();
	    cout << "Enter Your Last Name : " << endl;
	    Person.LastName = clsValidateInput<string>::ReadString();
	    cout << "Enter Your Email : " << endl;
	    Person.Email = clsValidateInput<string>::ReadString();
	    cout << "Enter Your Phone Number : " << endl;
	    Person.Phone = clsValidateInput<string>::ReadString();
	}
public:
	static void ShowAddNewStudent()
	{
		if (!CheckRightAccesPermitions(clsUser::enPermissions::pAddNewStudent))
		{
			return;
		}
		_DrawScreenHeader("\t Add New Student Screen");
		cout << "Please Enter New NumberStudent :" << endl;
		string NumberStudent = clsValidateInput<string>::ReadString();
		while (clsStudent::isStudentExist(NumberStudent))
		{
			cout << "Student is Already Exist Choose Another one :" << endl;
			NumberStudent = clsValidateInput<string>::ReadString();
		}
		clsStudent Student = clsStudent::Find(NumberStudent);
		_ReadNewPerson(Student, NumberStudent);
		char anwser = 'n';
		cout << "Do You Want Add Student Y/N : " << endl;
		cin >> anwser;
		if (anwser == 'y' || anwser == 'Y')
		{
			Student.addNewStudent(Student);
			cout << "Student Added Successfully :-)" << endl;
		}
	}
};

