#pragma once
#include <iostream>
#include "clsValidateInput.h"
#include "clsScreen.h"
#include "clsStudent.h"
#include <iomanip>
class clsListStudent : public clsScreen
{
private:
	static void PrintStudentRecordLine(clsStudent Student)
	{
		cout << "|" << setw(12) << left << Student.DateRegister();
		cout << "|" << setw(12) << left << Student.NumberStudent;
		cout << "|" << setw(12) << left << Student.FirstName;
		cout << "|" << setw(12) << left << Student.LastName;
		cout << "|" << setw(30) << left << Student.Email;
		cout << "|" << setw(20) << left << Student.Phone;
	}
public:
	static void ShowStudentList()
	{
		if (!CheckRightAccesPermitions(clsUser::enPermissions::pListStudents))
		{
			return;
		}
		vector <clsStudent> vStudents = clsStudent::GetListStudent();
		string title = "\tStudent List ";
		string subtitle = "\t(" + to_string(vStudents.size()) + ") Student(s).";
		_DrawScreenHeader(title, subtitle);
		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		cout << "| " << left << setw(12) << "Date Joined";
		cout << "| " << left << setw(12) << "Number Student";
		cout << "| " << left << setw(12) << "First Name";
		cout << "| " << left << setw(12) << "Last Name";
		cout << "| " << left << setw(12) << "Email";
		cout << "| " << left << setw(12) << "Phone";
		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		if (vStudents.size() == 0)
		{
			cout << "\t\t\t\tNo Student Available In the System!";
		}
		else
		{
			for (clsStudent Stu : vStudents)
			{

				PrintStudentRecordLine(Stu);
				cout << endl;
			}
		}
		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;
	}
};