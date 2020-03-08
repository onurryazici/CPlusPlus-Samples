/// You need to send 3 arguments!!
/// Example student.txt academican.txt randezvous.txt 
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

/// Public erişimli elemanlar
int menuNumber;
fstream studentFile;
fstream academicianFile;
fstream randezvousFile;
string studentFileName;
string academicianFileName;
string randezvousFileName;
int student_size = 0;
bool firstRun = true;
/// Programın sınıf yapıları
class University
{
public:
	University() {}
	class Person
	{
	public:
		string number;
		string name;
		string surname;
		string department;
		string mail;
		string phone;
	};
	class Student : public Person
	{
	public:

		string registrationYear;
	};

	class Academician : public Person
	{
	public:
		string degree;
	};

	class Randezvous {
	public:
		string academicianNumber;
		string studentNumber;
		class Date {
		public:
			string day;
			string month;
			string year;
		}Date;
		class Hour {
		public:
			string startHour;
			string startMinute;
			string endHour;
			string endMinute;
		}Hour;

	};
	Student* student;
	Academician* academician;
	Randezvous* randezvous;

	// Menu structure
	struct MenuStruct {
	public:
		void printAllMenu();
		struct menu0 {
		public:
			void print();
			void showRandezvousByStudent(string studentNumber);
			void showRandezvousByAcademician(string registrationNumber);
		}menu0;
		struct menu1 {
		public:
			void showStudentClassData();
			void showAcademicianClassData();
		}menu1;
		struct menu2 {
		public:
			void print();
		private:
			bool insertStudent(string number, string name, string surname, string department, string registrationYear, string email, string phone);
		}menu2;
		struct menu3 {
		public:
			void print();
		private:
			bool insertAcademician(string registrationNumber, string name, string surname, string department, string email, string phone, string degree);
		}menu3;
		struct menu4 {
		public:
			void print();
		private:
			void deleteStudent(string studentNumber);
		}menu4;

		struct menu5 {
		public:
			void print();
		private:
			void deleteAcademician(string registrationNumber);
		}menu5;

		struct menu6 {
		public:
			void print();
			struct studentSubMenu {
			public:
				void printAndUpdate();
			}studentSubMenu;

			struct academicianSubMenu {
			public:
				void printAndUpdate();
			}academicianSubMenu;
		}menu6;

		struct menu7 {
		public:
			void print();
			bool isStudentHaveAnotherRandezvous(string studentNumber, string day, string month, string year, string hour, string minute);
			bool isRandezvousAvailableByAcademician(string academicianNumber, string day, string month, string year, string hour, string minute);
			bool isRandezvousAvailableByStudent(string studentNumber, string day, string month, string year, string hour, string minute);
			void showRandezvousTable(string academicianNumber, string studentNumber, string day, string month, string year);
		}menu7;

		struct menu8 {
		public:
			void print();
			struct subMenuEdit {
				void editRandezvousByStudent();
			}subMenuEdit;

			struct subMenuDelete {
				void print();
				void deleteRandezvousByStudent(string studentNumber, string day, string month, string year, string hour, string minute);
			}subMenuDelete;
		}menu8;

		struct menu9 {
		public:
			void saveStudents();
			void saveAcademicians();
			void saveRandezvous();
		}menu9;
	}Menu;

	// As it can be understood from their names, special functions that I created in order not to write code again and again ..

	// Initially fillStudentClass, fillAcademicianClass, fillRandezvousClass fonksiyonları and University functions are 
	// reading data from files and filling class structure.
	// You can quit with save data or not..

	// If you save data then class structure will write some files.

	// Randezvous conflict blocked

	// A student can make an appointment to a certain academician only once that day.

	// A student can't make an appointment on same times. You can find with 'studentHaveAnotherRandezvous' function.

	// You can't make an appointment for past tense.
	void fillStudentClass();
	void fillAcademicianClass();
	void fillRandezvousClass();
	int countDataFromFile(string fileName);
	int countStudentsFromClass();
	int countAcademiciansFromClass();
	int countRandezvousFromClass();
	bool doYouHaveThisAcademician(string registrationNumber);
	bool doYouHaveThisStudent(string studentNumber);
	bool isRandezvousDateTrue(string day, string month, string year);
	bool isRandezvousHourFormatTrue(string hour);
	string returnAcademicianNameAndDegree(string registrationNumber);
	string returnStudentNameAndSurname(string studentNumber);
	void clearStudentRandezvousByNumber(string studentNumber);
	void clearAcademicianRandezvousByNumber(string registrationNumber);
};

University university;
string* parseData(string line, int parseOfAmount);

int main(int argc, char* argv[])
{

	studentFileName = argv[1];
	academicianFileName = argv[2];
	randezvousFileName = argv[3];

	university.fillStudentClass();
	university.fillAcademicianClass();
	university.fillRandezvousClass();
	University::MenuStruct menu;
	menu.printAllMenu();

	return 0;
}

//// <PrivateMethods>-------------------------------------------------------------
int University::countDataFromFile(string fileName)
{
	fstream file;
	int count = 0;
	file.open(fileName, ios::in | ios::out | ios::app);
	if (file.good())
	{
		string temp;

		while (getline(file, temp))
		{
			count++;
			if (fileName == studentFileName && firstRun)
			{
				student_size++;
			}
		}
	}
	else
	{
		cout << "Can't access to file.." << endl;
		system("pause");
		return 0;

	}
	firstRun = false;
	file.close();
	return count;
}
int University::countAcademiciansFromClass()
{
	int amount = 0;
	for (int i = 0; i < 100; i++)
	{
		if (university.academician[amount].name != "")
		{
			amount++;
		}
	}
	return amount;
}
int University::countStudentsFromClass()
{
	int amount = 0;
	for (int i = 0; i < 100; i++)
	{
		if (university.student[amount].name != "")
		{
			amount++;
		}
	}
	return amount;
}
int University::countRandezvousFromClass()
{
	int amount = 0;
	for (int i = 0; i < 100; i++)
	{
		if (university.randezvous[amount].studentNumber != "")
		{
			amount++;
		}
	}
	return amount;
}
bool University::doYouHaveThisAcademician(string registrationNumber)
{
	bool result = false;
	for (int i = 0; i < 100; i++)
	{
		if (university.academician[i].number == registrationNumber)
		{
			result = true;
			break;
		}
	}
	return result;
}

string University::returnAcademicianNameAndDegree(string registrationNumber)
{
	string info;
	for (int i = 0; i < 100; i++)
	{
		if (university.academician[i].number == registrationNumber)
		{
			info = (university.academician[i].degree + " " + university.academician[i].name + " " + university.academician[i].surname);
			break;
		}
	}
	return info;
}
string University::returnStudentNameAndSurname(string studentNumber)
{
	string info;
	for (int i = 0; i < 100; i++)
	{
		if (university.student[i].number == studentNumber)
		{
			info = (university.student[i].name + " " + university.student[i].surname + " ");
			break;
		}
	}
	return info;
}
bool University::doYouHaveThisStudent(string studentNumber)
{
	bool result = false;
	for (int i = 0; i < 100; i++)
	{
		if (university.student[i].number == studentNumber)
		{
			result = true;
			break;
		}
	}
	return result;
}

void University::clearStudentRandezvousByNumber(string studentNumber)
{
	for (int i = 0; i < 100; i++)
	{
		if (university.randezvous[i].studentNumber == studentNumber)
		{
			university.randezvous[i].academicianNumber = "";
			university.randezvous[i].studentNumber = "";
			university.randezvous[i].Date.day = "";
			university.randezvous[i].Date.month = "";
			university.randezvous[i].Date.year = "";
			university.randezvous[i].Hour.startHour = "";
			university.randezvous[i].Hour.startMinute = "";
			university.randezvous[i].Hour.endHour = "";
			university.randezvous[i].Hour.endMinute = "";
		}
	}
}

void University::clearAcademicianRandezvousByNumber(string registrationNumber)
{
	for (int i = 0; i < 100; i++)
	{
		if (university.randezvous[i].academicianNumber == registrationNumber)
		{
			university.randezvous[i].academicianNumber = "";
			university.randezvous[i].studentNumber = "";
			university.randezvous[i].Date.day = "";
			university.randezvous[i].Date.month = "";
			university.randezvous[i].Date.year = "";
			university.randezvous[i].Hour.startHour = "";
			university.randezvous[i].Hour.startMinute = "";
			university.randezvous[i].Hour.endHour = "";
			university.randezvous[i].Hour.endMinute = "";
		}
	}
}
bool University::isRandezvousDateTrue(string day, string month, string year)
{
	bool result = true;
	time_t theTime = time(NULL);
	struct tm* date = localtime(&theTime);
	int currentDay = date->tm_mday;
	int currentMonth = (date->tm_mon + 1);
	int currentYear = (date->tm_year + 1900);

	int currentHour = date->tm_hour;
	int currentMinute = date->tm_min;

	int randezvousDay = atoi(day.c_str());
	int randezvousMonth = atoi(month.c_str());
	int randezvousYear = atoi(year.c_str());


	if ((randezvousDay < 1 || randezvousDay > 31) || (randezvousMonth < 1 || randezvousMonth > 12))
	{
		system("cls");
		cout << endl;
		cout << "  " << randezvousDay << ":" << randezvousMonth << ":" << randezvousYear << endl;
		cout << "  " << "The date format you entered is incorrect. Please try again.. " << endl;
		system("pause");
		return false;
	}

	if (randezvousDay == currentDay && randezvousMonth == currentMonth && randezvousYear == currentYear)
	{
		if (currentHour >= 18)
		{
			system("cls");
			cout << endl;
			cout << "  Appointment closed for today. Please choose the next days." << endl;
			system("pause");
			return false;
		}
	}

	if (randezvousDay < currentDay && randezvousMonth <= currentMonth && randezvousYear <= currentYear)
	{
		system("cls");
		cout << endl;
		cout << "  " << "You can't make an appointment process for past tense." << endl;
		system("pause");
		return false;
	}
	else if (randezvousDay > currentDay&& randezvousMonth < currentMonth && randezvousYear <= currentYear)
	{
		system("cls");
		cout << endl;
		cout << "  " << "You can't make an appointment process for past tense." << endl;
		system("pause");
		return false;
	}
	else if (randezvousMonth <= currentMonth && randezvousYear <= currentYear)
	{
		result = true;
	}
	return result;

}

bool University::isRandezvousHourFormatTrue(string hour)
{
	bool result = true;
	if (hour.length() != 5)
	{
		return false;
	}
	string* array = parseData(hour, 2);
	int hourValue = atoi(array[0].c_str());
	int minuteValue = atoi(array[1].c_str());

	if (hourValue > 17 || hourValue < 9 || (minuteValue % 30) != 0 || minuteValue > 59)
	{
		return false;
	}
	return result;
}

string* parseData(string line, int parseOfAmount)
{
	string* temp = new string[parseOfAmount];
	string word;
	int index = 0;
	int cursor = 0;
	for (auto x : line)
	{
		cursor++;
		if (x == ' ')
		{
			temp[index++] = word;
			word = "";
		}
		else if (x == ':')
		{
			temp[index++] = word;
			word = "";
		}
		else if (x == '/')
		{
			temp[index++] = word;
			word = "";
		}
		else if (cursor == line.length())
		{
			word = word + x;
			temp[index++] = word;
			word = "";
		}
		else
		{
			word = word + x;
		}

	}

	return temp;
}

//// </PrivateMethods> --------------------------------------------------------------
//// <InitInitializingClasses> ------------------------------------------------------

void University::fillStudentClass()
{
	studentFile.open(studentFileName, ios::in | ios::out | ios::app);
	if (studentFile.good())
	{
		string* array = new string[7];
		string line;
		int index = 0;
		int studentCount = countDataFromFile(studentFileName);
		student = new Student[100];
		while (getline(studentFile, line))
		{
			array = parseData(line, 7);
			student[index].number = array[0];
			student[index].name = array[1];
			student[index].surname = array[2];
			student[index].department = array[3];
			student[index].registrationYear = array[4];
			student[index].mail = array[5];
			student[index].phone = array[6];
			index++;
		}
	}
	else
	{
		cout << "Can't access to student file" << endl;
		system("pause");
		exit(0);
	}
	studentFile.close();

}

void University::fillAcademicianClass()
{
	academicianFile.open(academicianFileName, ios::in | ios::out | ios::app);
	if (academicianFile.good())
	{
		string* array = new string[6];
		string line;
		int index = 0;
		int academicianCount = countDataFromFile(academicianFileName);

		academician = new Academician[100];
		while (getline(academicianFile, line))
		{
			array = parseData(line, 7);
			academician[index].number = array[0];
			academician[index].name = array[1];
			academician[index].surname = array[2];
			academician[index].department = array[3];
			academician[index].mail = array[4];
			academician[index].phone = array[5];
			academician[index].degree = array[6];
			index++;
		}
	}
	else
	{
		cout << "Can't access to student file.." << endl;
		system("pause");
		exit(0);
	}
	academicianFile.close();
}

void University::fillRandezvousClass()
{
	randezvousFile.open(randezvousFileName, ios::in | ios::out | ios::app);
	if (randezvousFile.good())
	{
		string* array = new string[9];
		string line;
		int index = 0;
		int randezvousCount = countDataFromFile(randezvousFileName);

		randezvous = new Randezvous[100];
		while (getline(randezvousFile, line))
		{
			array = parseData(line, 9);
			randezvous[index].academicianNumber = array[0];
			randezvous[index].studentNumber = array[1];
			randezvous[index].Date.day = array[2];
			randezvous[index].Date.month = array[3];
			randezvous[index].Date.year = array[4];
			randezvous[index].Hour.startHour = array[5];
			randezvous[index].Hour.startMinute = array[6];
			randezvous[index].Hour.endHour = array[7];
			randezvous[index].Hour.endMinute = array[8];
			index++;
		}
	}
	else
	{
		cout << "Can't access to randezvous file.." << endl;
		system("pause");
		exit(0);
	}
	randezvousFile.close();
}


//// <MainMenu>------------------------------------------------------------------
void University::MenuStruct::printAllMenu()
{
	system("cls");
	cout << endl << "   " << "Academic Randezvous System" << endl << endl;
	cout << "  " << " [0]  " << "Show randezvous" << endl;
	cout << "  " << " [1]  " << "Show registered academics and students [OK]" << endl;
	cout << "  " << " [2]  " << "New Student[OK]" << endl;
	cout << "  " << " [3]  " << "New Academician[OK]" << endl;
	cout << "  " << " [4]  " << "Remove Student[OK]" << endl;
	cout << "  " << " [5]  " << "Remove Academician[OK]" << endl;
	cout << "  " << " [6]  " << "Update Student/Academician[OK]" << endl;
	cout << "  " << " [7]  " << "Create Randezvous[OK]" << endl;
	cout << "  " << " [8]  " << "Edit/Remove Randezvous" << endl;
	cout << "  " << " [9]  " << "Save and Quit[OK]" << endl;
	cout << "  " << " [10] " << "Quit without Save" << endl;
	cout << "  " << " [11] " << "Save all data" << endl << endl << endl;
	do
	{
		cout << " Menu seciniz : ";
		cin >> menuNumber;
		cout << endl;
	} while (menuNumber < 0 || menuNumber > 11);

	switch (menuNumber)
	{
	case 0:
		menu0.print();
		break;
	case 1:
		system("cls");
		menu1.showStudentClassData();
		menu1.showAcademicianClassData();
		system("pause");
		cout << endl;
		university.Menu.printAllMenu();
		break;

	case 2:
		menu2.print();
		break;

	case 3:
		menu3.print();
		break;

	case 4:
		menu4.print();
		break;

	case 5:
		menu5.print();
		break;

	case 6:
		menu6.print();
		break;

	case 7:
		menu7.print();
		break;

	case 8:
		menu8.print();
		break;

	case 9:
		university.Menu.menu9.saveStudents();
		university.Menu.menu9.saveAcademicians();
		university.Menu.menu9.saveRandezvous();
		exit(0);
		break;
	case 10:
		exit(0);
		break;
	case 11:
		system("cls");
		university.Menu.menu9.saveAcademicians();
		university.Menu.menu9.saveStudents();
		university.Menu.menu9.saveRandezvous();
		cout << "Data saved.." << endl;
		system("pause");
		university.Menu.printAllMenu();
		break;
	}
}
//// </MainMenu>-------------------------------------------------------

//// <Menu0> ----------------------------------------------------------
void University::MenuStruct::menu1::showStudentClassData()
{
	cout << " " << "Students" << endl;
	int listNumber = 0;
	for (int i = 0; i < 100; i++)
	{
		if (university.student[i].number != "")
		{
			cout << ++listNumber << "- ";
			cout << university.student[i].number << " ";
			cout << university.student[i].name << " ";
			cout << university.student[i].surname << " ";
			cout << university.student[i].department << " ";
			cout << university.student[i].registrationYear << " ";
			cout << university.student[i].mail << " ";
			cout << university.student[i].phone << " " << endl;
		}
	}

	cout << endl << listNumber << " students were found" << endl;

}
//// <Menu0> ----------------------------------------------------------

void University::MenuStruct::menu0::print()
{
	system("cls");
	cout << " " << " [0] Student " << endl;
	cout << " " << " [1] Academician " << endl;
	int choice;
	do
	{
		cout << " Which person do you want to view appointments for? ";
		cin >> choice;
	} while (choice < 0 || choice > 1);


	string studentNumber;
	string academicianRegistrationNumber;
	bool finded;
	switch (choice)
	{
	case 0:
		finded = false;
		cout << " Enter the student number :";
		cin >> studentNumber;

		for (int i = 0; i < 100; i++)
		{
			if (university.student[i].number == studentNumber)
			{
				finded = true;
			}
		}
		if (finded)
		{
			showRandezvousByStudent(studentNumber);
		}
		else
		{
			cout << "There is no such student registered for this number ... " << endl;
			system("pause");
			university.Menu.menu0.print();
		}

		break;

	case 1:
		finded = false;
		cout << " Enter the academic's registration number:";
		cin >> academicianRegistrationNumber;

		if (university.doYouHaveThisAcademician(academicianRegistrationNumber))
		{
			showRandezvousByAcademician(academicianRegistrationNumber);
			system("pause");
			university.Menu.printAllMenu();
		}
		else
		{
			cout << "No academician registered with this registration number was found ..." << endl;
			system("pause");
			university.Menu.menu0.print();
		}
		break;
	}

}

void University::MenuStruct::menu0::showRandezvousByStudent(string studentNumber)
{
	system("cls");
	cout << "Student No : " << studentNumber << endl;
	cout << "Name Surname : " << university.returnStudentNameAndSurname(studentNumber) << endl;
	cout << endl << "Appointments for " << university.returnStudentNameAndSurname(studentNumber) << " student number" << studentNumber << endl << endl;

	time_t theTime = time(NULL);
	struct tm* date = localtime(&theTime);
	string currentDay = std::to_string(date->tm_mday);
	string currentMonth = std::to_string(date->tm_mon + 1);
	string currentYear = std::to_string(date->tm_year + 1900);
	int amount = 0;
	for (int i = 0; i < 100; i++)
	{

		if (university.randezvous[i].studentNumber == studentNumber)
		{
			amount++;
			// The past, expected, etc. to indicate the appointments before today.
			string lineDay = university.randezvous[i].Date.day;
			string lineMonth = university.randezvous[i].Date.month;
			string lineYear = university.randezvous[i].Date.year;

			if (lineDay.at(0) == '0')
			{
				lineDay = lineDay.at(1);
			}

			if (lineMonth.at(0) == '0')
			{
				lineMonth = lineMonth.at(1);
			}
			bool past_randezvous = false;
			// To determine whether appointments are in the past or future.
			if (atoi(lineMonth.c_str()) < atoi(currentMonth.c_str()) && atoi(lineYear.c_str()) <= atoi(currentYear.c_str()))
			{
				past_randezvous = true;
			}
			else if (atoi(lineMonth.c_str()) == atoi(currentMonth.c_str()) && atoi(lineYear.c_str()) == atoi(currentYear.c_str()))
			{
				if (atoi(lineDay.c_str()) < atoi(currentDay.c_str()))
				{
					past_randezvous = true;
				}
				else
				{
					past_randezvous = false;
				}
			}

			if (past_randezvous)
			{
				cout << university.returnAcademicianNameAndDegree(university.randezvous[i].academicianNumber) << " ";
				cout << university.randezvous[i].academicianNumber << " ";
				cout << university.randezvous[i].studentNumber << " ";
				cout << university.randezvous[i].Date.day << "/";
				cout << university.randezvous[i].Date.month << "/";
				cout << university.randezvous[i].Date.year << " ";
				cout << university.randezvous[i].Hour.startHour << ":";
				cout << university.randezvous[i].Hour.startMinute << " ";
				cout << university.randezvous[i].Hour.endHour << ":";
				cout << university.randezvous[i].Hour.endMinute << " ";
				cout << "Appointment History" << endl;
			}
			else
			{
				cout << university.returnAcademicianNameAndDegree(university.randezvous[i].academicianNumber) << " ";
				cout << university.randezvous[i].academicianNumber << " ";
				cout << university.randezvous[i].studentNumber << " ";
				cout << university.randezvous[i].Date.day << "/";
				cout << university.randezvous[i].Date.month << "/";
				cout << university.randezvous[i].Date.year << " ";
				cout << university.randezvous[i].Hour.startHour << ":";
				cout << university.randezvous[i].Hour.startMinute << " ";
				cout << university.randezvous[i].Hour.endHour << ":";
				cout << university.randezvous[i].Hour.endMinute << " ";
				cout << "Waiting" << endl;
			}
		}
	}

	cout << endl << endl << amount << " item listed." << endl;
	system("pause");
	university.Menu.printAllMenu();
}

void University::MenuStruct::menu0::showRandezvousByAcademician(string registrationNumber)
{
	system("cls");
	time_t theTime = time(NULL);
	struct tm* date = localtime(&theTime);
	string currentDay = std::to_string(date->tm_mday);
	string currentMonth = std::to_string(date->tm_mon + 1);
	string currentYear = std::to_string(date->tm_year + 1900);
	int amountOfRandezvous = 0;
	cout << "  " << university.returnAcademicianNameAndDegree(registrationNumber) << endl;
	cout << endl;
	for (int i = 0; i < 100; i++)
	{
		if (university.randezvous[i].academicianNumber == registrationNumber)
		{
			string lineDay = university.randezvous[i].Date.day;
			string lineMonth = university.randezvous[i].Date.month;
			string lineYear = university.randezvous[i].Date.year;

			if (lineDay.at(0) == '0')
			{
				lineDay = lineDay.at(1);
			}

			if (lineMonth.at(0) == '0')
			{
				lineMonth = lineMonth.at(1);
			}
			bool past_randezvous = false;
			// To determine whether appointments are in the past or future.
			if (atoi(lineMonth.c_str()) < atoi(currentMonth.c_str()) && atoi(lineYear.c_str()) <= atoi(currentYear.c_str()))
			{
				past_randezvous = true;
			}
			else if (atoi(lineMonth.c_str()) == atoi(currentMonth.c_str()) && atoi(lineYear.c_str()) == atoi(currentYear.c_str()))
			{
				if (atoi(lineDay.c_str()) < atoi(currentDay.c_str()))
				{
					past_randezvous = true;
				}
				else
				{
					past_randezvous = false;
				}
			}

			if (past_randezvous)
			{
				cout << "  ";
				cout << university.randezvous[i].studentNumber << " ";
				cout << university.randezvous[i].Hour.startHour << ":";
				cout << university.randezvous[i].Hour.startMinute << " ";
				cout << university.randezvous[i].Date.day << "/";
				cout << university.randezvous[i].Date.month << "/";
				cout << university.randezvous[i].Date.year << " ";
				cout << "Appointment History" << endl;
			}
			else
			{
				cout << "  ";
				cout << university.randezvous[i].studentNumber << " ";
				cout << university.randezvous[i].Hour.startHour << ":";
				cout << university.randezvous[i].Hour.startMinute << " ";
				cout << university.randezvous[i].Date.day << "/";
				cout << university.randezvous[i].Date.month << "/";
				cout << university.randezvous[i].Date.year << " ";
				cout << "Waiting" << endl;
			}
			amountOfRandezvous++;
		}
	}
	cout << endl;
	cout << "  " << amountOfRandezvous << " randezvous found" << endl << " ";
}
//// </Menu0> ---------------------------------------------------------


//// <Menu1> ----------------------------------------------------------
void University::MenuStruct::menu1::showAcademicianClassData()
{
	cout << endl << " " << "Academicians " << endl;
	int amount = 0;
	int listNumber = 1;
	for (int i = 0; i < 100; i++)
	{
		if (university.academician[i].name != "")
		{
			amount++;
			cout << listNumber++ << "- ";
			cout << university.academician[i].number << " ";
			cout << university.academician[i].name << " ";
			cout << university.academician[i].surname << " ";
			cout << university.academician[i].department << " ";
			cout << university.academician[i].mail << " ";
			cout << university.academician[i].phone << " ";
			cout << university.academician[i].degree << " " << endl;
		}
	}

	cout << endl << amount << " academicians found." << endl;
}



///// </Menu1>---------------------------------------------------------OK

///// <Menu2>----------------------------------------------------------
void University::MenuStruct::menu2::print()
{
	string studentNumber;
	string name;
	string surname;
	string department;
	string registrationYear;
	string email;
	string phone;
	University::MenuStruct menu;

	bool studentAlreadyRegistered;
	do
	{
		studentAlreadyRegistered = false;
		system("cls");
		cout << endl << " " << "New Student" << endl;
		cout << " Student number : ";
		cin >> studentNumber;
		if (university.doYouHaveThisStudent(studentNumber))
		{
			studentAlreadyRegistered = true;
			cout << endl << "The student with this number already exists." << endl;
			system("pause");
		}
		cout << endl;
	} while (studentNumber.length() != 6 || studentAlreadyRegistered == true);

	cout << " Name : ";
	cin >> name;

	cout << endl;
	cout << " Surname : ";
	cin >> surname;

	cout << endl;
	cout << " Department : ";
	cin >> department;


	cout << endl;
	cout << " Registration Year : ";
	cin >> registrationYear;


	cout << endl;
	cout << " E-mail : ";
	cin >> email;

	do
	{
		cout << endl;
		cout << " Phone : ";
		cin >> phone;
	} while (phone.front() != '+' || phone.length() != 13);


	if (insertStudent(studentNumber, name, surname, department, registrationYear, email, phone))
	{
		int amount = university.countStudentsFromClass();
		university.student[amount].number = studentNumber;
		university.student[amount].name = name;
		university.student[amount].surname = surname;
		university.student[amount].department = department;
		university.student[amount].registrationYear = registrationYear;
		university.student[amount].mail = email;
		university.student[amount].phone = phone;

		system("cls");
		cout << endl << endl;
		cout << " Data added ";
		cout << " Student number : " << studentNumber << endl;
		cout << " Name : " << name << endl;
		cout << " Surname : " << surname << endl;
		cout << " Department : " << department << endl;
		cout << " Registration year : " << registrationYear << endl;
		cout << " E-mail : " << email << endl;
		cout << " Phone : " << phone << endl;
		system("pause");
		student_size++;
		menu.printAllMenu();
	}
	else
	{
		system("cls");
		cout << "This student is already exist.." << endl;

		char select;
		do {
			cout << "Do you want to add again (y/n) : ";
			cin >> select;
		} while (select != 'y' && select != 'n' && select != 'Y' && select != 'N');

		if (select == 'y' || select == 'Y')
		{
			menu.menu2.print();
		}
		else if (select == 'n' || select == 'N')
		{
			menu.printAllMenu();
		}

	}

}
bool University::MenuStruct::menu2::insertStudent(string number, string name, string surname, string department, string registrationYear, string email, string phone)
{
	bool result = false;
	studentFile.open(studentFileName, ios::in | ios::out | ios::app);
	if (studentFile.good())
	{
		result = true;
		string lineHolder;
		while (getline(studentFile, lineHolder))
		{
			string selectedNumber = lineHolder.substr(0, 6);
			if (number == selectedNumber)
			{
				studentFile.close();
				return false;
			}
		}
		studentFile.clear();
		studentFile.seekg(0, studentFile.beg);

	}
	else
	{
		result = false;
		cout << "Can't access to students file.. " << endl;
	}
	studentFile.close();
	return result;
}
///// </Menu 2>-----------------------------------------------------


///// <Menu3>-------------------------------------------------------
void University::MenuStruct::menu3::print()
{
	string registrationNumber;
	string name;
	string surname;
	string department;
	string email;
	string phone;
	string degree;
	University::MenuStruct menu;

	bool academicianAlreadyRegistered;
	do
	{
		academicianAlreadyRegistered = false;
		system("cls");
		cout << endl << " " << "New Academician" << endl;
		cout << " Academician Registration Year : ";
		cin >> registrationNumber;
		if (university.doYouHaveThisAcademician(registrationNumber))
		{
			// Yes he's mine ..
			academicianAlreadyRegistered = true;
			cout << endl << "The academic with this registration number is already registered." << endl;
			system("pause");
		}
		cout << endl;
	} while (registrationNumber.length() != 8 || academicianAlreadyRegistered == true);

	cout << " Name : ";
	cin >> name;

	cout << endl;
	cout << " Surname : ";
	cin >> surname;

	cout << endl;
	cout << " Department : ";
	cin >> department;

	cout << endl;
	cout << " E-mail : ";
	cin >> email;

	do
	{
		cout << endl;
		cout << " Phone : ";
		cin >> phone;
	} while (phone.front() != '+' || phone.length() != 13);

	cout << endl;
	cout << " Degree : ";
	cin >> degree;

	if (insertAcademician(registrationNumber, name, surname, department, email, phone, degree))
	{
		int amount = university.countAcademiciansFromClass();
		university.academician[amount].number = registrationNumber;
		university.academician[amount].name = name;
		university.academician[amount].surname = surname;
		university.academician[amount].department = department;
		university.academician[amount].mail = email;
		university.academician[amount].phone = phone;
		university.academician[amount].degree = degree;

		system("cls");
		cout << endl << endl;
		cout << " Data added";
		cout << " Academician registration number : " << registrationNumber << endl;
		cout << " Name : " << name << endl;
		cout << " Surname : " << surname << endl;
		cout << " Department : " << department << endl;
		cout << " E-mail : " << email << endl;
		cout << " Phone : " << phone << endl;
		cout << " Degree : " << degree << endl;
		system("pause");
		menu.printAllMenu();
	}
	else
	{
		system("cls");
		cout << "This academician is already exist.." << endl;

		char select;
		do {
			cout << "Do you want to add again (y/n) : ";
			cin >> select;
		} while (select != 'y' && select != 'n' && select != 'Y' && select != 'N');

		if (select == 'y' || select == 'Y')
		{
			menu.menu3.print();
		}
		else if (select == 'n' || select == 'N')
		{
			menu.printAllMenu();
		}

	}
}

bool University::MenuStruct::menu3::insertAcademician(string registrationNumber, string name, string surname, string department, string email, string phone, string degree)
{
	bool result = false;
	academicianFile.open(academicianFileName, ios::in | ios::out | ios::app | fstream::out);
	if (academicianFile.good())
	{
		result = true;
		string lineHolder;
		while (getline(academicianFile, lineHolder))
		{
			string selectedNumber = lineHolder.substr(0, 8);
			if (registrationNumber == selectedNumber)
			{
				return false;
			}
		}
		academicianFile.clear();
		academicianFile.seekg(0, academicianFile.beg);

	}
	else
	{
		cout << "Akademisyen dosyasina ulasilamiyor.. " << endl;
		system("pause");
		exit(0);
	}
	academicianFile.close();
	return result;
}
//// </Menu3>-----------------------------------------------------------


//// <Menu4>------------------------------------------------------------
void University::MenuStruct::menu4::deleteStudent(string studentNumber)
{
	bool studentFound = false;
	bool randezvousFound = false;
	int amountOfRandezvous = 0;
	int studentIndex = 0;
	int randezvousIndex = 0;
	for (; studentIndex < 100; studentIndex++)
	{
		if (university.student[studentIndex].number == studentNumber)
		{
			studentFound = true;
			break;
		}
	}

	if (studentFound)
	{
		for (; randezvousIndex < 100; randezvousIndex++)
		{
			if (university.randezvous[randezvousIndex].studentNumber == studentNumber)
			{
				randezvousFound = true;
				amountOfRandezvous++;
			}
		}
		if (randezvousFound)
		{
			char choice;
			do
			{
				system("cls");
				cout << "There are " << amountOfRandezvous << " appointments for this student you want to delete";
				cout << endl << "Are you sure you want to delete ? (y/n) ";
				cin >> choice;
			} while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N');

			if (choice == 'y' || choice == 'Y')
			{
				university.student[studentIndex].number = "";
				university.student[studentIndex].name = "";
				university.student[studentIndex].surname = "";
				university.student[studentIndex].department = "";
				university.student[studentIndex].registrationYear = "";
				university.student[studentIndex].mail = "";
				university.student[studentIndex].phone = "";

				university.clearStudentRandezvousByNumber(studentNumber);
				cout << "Student removed." << endl;
				system("pause");
				university.Menu.printAllMenu();
			}
			else
			{
				cout << "Process canceled." << endl;
				system("pause");
				university.Menu.printAllMenu(); // refreshing menu
			}
		}
		else
		{
			university.student[studentIndex].number = "";
			university.student[studentIndex].name = "";
			university.student[studentIndex].surname = "";
			university.student[studentIndex].department = "";
			university.student[studentIndex].registrationYear = "";
			university.student[studentIndex].mail = "";
			university.student[studentIndex].phone = "";

			cout << "Student removed." << endl;
			system("pause");
			university.Menu.printAllMenu();
		}
	}
	else
	{
		cout << "The student you want to delete could not be found.." << endl;
		system("pause");
		university.Menu.printAllMenu();
	}
}

void University::MenuStruct::menu4::print()
{
	system("cls");
	cout << " " << "Remove Student" << endl << endl;
	string number;
	do
	{
		cout << " " << "Enter the number of the student you want to delete : ";
		cin >> number;
	} while (number.length() != 6);
	if (university.doYouHaveThisStudent(number))
	{
		deleteStudent(number);
		cout << "Student removed.." << endl;
		system("pause");
		university.Menu.printAllMenu();
	}
	else
	{
		cout << "The student you want to delete could not be found.." << endl;
		system("pause");
		university.Menu.menu4.print();
	}
}
//// </Menu4>------------------------------------------------

//// <Menu5>-------------------------------------------------
void University::MenuStruct::menu5::print()
{
	system("cls");
	string registrationNumber;
	do
	{
		cout << "The registration number of the academician you want to delete: ";
		cin >> registrationNumber;
	} while (registrationNumber.length() != 8);
	deleteAcademician(registrationNumber);
}
void University::MenuStruct::menu5::deleteAcademician(string registrationNumber)
{
	bool academicianFound = false;
	bool randezvousFound = false;
	int amountOfRandezvous = 0;
	int academicianIndex = 0;
	int randezvousIndex = 0;
	for (; academicianIndex < 100; academicianIndex++)
	{
		if (university.academician[academicianIndex].number == registrationNumber)
		{
			academicianFound = true;
			break;
		}
	}

	if (academicianFound)
	{
		for (; randezvousIndex < 100; randezvousIndex++)
		{
			if (university.randezvous[randezvousIndex].academicianNumber == registrationNumber)
			{
				randezvousFound = true;
				amountOfRandezvous++;
			}
		}
		if (randezvousFound)
		{
			char choice;
			do
			{
				system("cls");
				cout << amountOfRandezvous << " appointments found for this academic you want to delete";
				cout << endl << "Are you sure you want to delete ? (y/n) ";
				cin >> choice;
			} while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N');

			if (choice == 'y' || choice == 'Y')
			{
				university.academician[academicianIndex].number = "";
				university.academician[academicianIndex].name = "";
				university.academician[academicianIndex].surname = "";
				university.academician[academicianIndex].department = "";
				university.academician[academicianIndex].mail = "";
				university.academician[academicianIndex].phone = "";
				university.academician[academicianIndex].degree = "";

				university.clearAcademicianRandezvousByNumber(registrationNumber);
				cout << "Academician removed." << endl;
				system("pause");
				university.Menu.printAllMenu();
			}
			else
			{
				cout << "Process canceled." << endl;
				system("pause");
				university.Menu.printAllMenu(); // refreshing menu
			}
		}
		else
		{
			university.academician[academicianIndex].number = "";
			university.academician[academicianIndex].name = "";
			university.academician[academicianIndex].surname = "";
			university.academician[academicianIndex].department = "";
			university.academician[academicianIndex].mail = "";
			university.academician[academicianIndex].phone = "";
			university.academician[academicianIndex].degree = "";
			cout << "Akademician removed." << endl;
			system("pause");
			university.Menu.printAllMenu();
		}
	}
	else
	{
		cout << "The academician you want to delete could not be found." << endl;
		system("pause");
		university.Menu.printAllMenu();
	}
}
//// </Menu5>-----------------------------------------------------------

//// <Menu6>------------------------------------------------------------
void University::MenuStruct::menu6::print()
{
	system("cls");
	cout << endl;
	cout << "[0] Student" << endl;
	cout << "[1] Academician" << endl << endl;
	int choice;
	do
	{
		cout << "Select the area you want to update : ";
		cin >> choice;
	} while (choice != 0 && choice != 1);

	switch (choice)
	{
	case 0:
		studentSubMenu.printAndUpdate();
		break;
	case 1:
		academicianSubMenu.printAndUpdate();
		break;
	}

}

void University::MenuStruct::menu6::studentSubMenu::printAndUpdate()
{
	string oldStudentNumber;
	bool studentAlreadyRegistered = false;
	int index;
	do
	{
		index = 0;
		cout << "Number of the student you want to update : ";
		cin >> oldStudentNumber;

		for (; index < 100; index++)
		{
			if (university.student[index].number == oldStudentNumber)
			{
				studentAlreadyRegistered = true;
				break;
			}
		}
		if (studentAlreadyRegistered == false)
		{
			cout << endl << "Student number " << oldStudentNumber << " was not found." << endl;
			system("pause");
			system("cls");
		}
	} while (oldStudentNumber.length() != 6 || studentAlreadyRegistered == false);


	string newStudentNumber;
	string name;
	string surname;
	string department;
	string registrationYear;
	string email;
	string phone;
	University::MenuStruct menu;

	studentAlreadyRegistered = false;
	do
	{
		system("cls");
		studentAlreadyRegistered = false;
		cout << endl << " " << "Enter new information for student number " << oldStudentNumber << endl;
		cout << " Student number : ";
		cin >> newStudentNumber;
		cout << endl;
		for (int i = 0; i < 100; i++)
		{
			if (university.student[i].number == newStudentNumber && oldStudentNumber != newStudentNumber)
			{
				studentAlreadyRegistered = true;
				break;
			}
		}
		if (studentAlreadyRegistered)
		{
			cout << "Student number " << oldStudentNumber << " has already exist.";
			system("pause");
		}
	} while (newStudentNumber.length() != 6 || studentAlreadyRegistered);

	cout << " Name : ";
	cin >> name;

	cout << endl;
	cout << " Surname : ";
	cin >> surname;

	cout << endl;
	cout << " Department : ";
	cin >> department;

	cout << endl;
	cout << " Registration Year : ";
	cin >> registrationYear;


	cout << endl;
	cout << " E-mail : ";
	cin >> email;

	do
	{
		cout << endl;
		cout << " Phone : ";
		cin >> phone;
	} while (phone.front() != '+' || phone.length() != 13);


	university.student[index].number = newStudentNumber;
	university.student[index].name = name;
	university.student[index].surname = surname;
	university.student[index].department = department;
	university.student[index].registrationYear = registrationYear;
	university.student[index].mail = email;
	university.student[index].phone = phone;
	cout << endl << "The student has successfully updated." << endl << endl;
	system("pause");
	menu.printAllMenu();
}

void University::MenuStruct::menu6::academicianSubMenu::printAndUpdate()
{
	string oldRegistrationNumber;
	bool academicianAlreadyRegistered = false;
	int index = 0;
	do
	{
		cout << "The registration number of the academic to be updated : ";
		cin >> oldRegistrationNumber;

		for (; index < 100; index++)
		{
			if (university.academician[index].number == oldRegistrationNumber)
			{
				academicianAlreadyRegistered = true;
				break;
			}
		}
		if (academicianAlreadyRegistered == false)
		{
			cout << endl << " No academician number" << oldRegistrationNumber << " was found" << endl;
			system("pause");
			system("cls");
		}
	} while (oldRegistrationNumber.length() != 8 || academicianAlreadyRegistered == false);



	string newRegistrationNumber;
	string name;
	string surname;
	string department;
	string email;
	string phone;
	string degree;
	University::MenuStruct menu;

	do
	{
		system("cls");
		academicianAlreadyRegistered = false;
		cout << "Enter new information for academician with " << oldRegistrationNumber << " registration numbers" << endl << endl;
		cout << " Akademisyen sicil numarasi : ";
		cin >> newRegistrationNumber;
		cout << endl;
		for (int i = 0; i < 100; i++)
		{
			if (university.academician[i].number == newRegistrationNumber && oldRegistrationNumber != newRegistrationNumber)
			{
				academicianAlreadyRegistered = true;
				break;
			}
		}
		if (academicianAlreadyRegistered)
		{
			cout << "Academician with " << newRegistrationNumber << " registration numbers already exists";
			system("pause");
		}
	} while (newRegistrationNumber.length() != 8 || academicianAlreadyRegistered);

	cout << " Name : ";
	cin >> name;

	cout << endl;
	cout << " Surname : ";
	cin >> surname;

	cout << endl;
	cout << " Department : ";
	cin >> department;


	cout << endl;
	cout << " E-mail : ";
	cin >> email;

	do
	{
		cout << endl;
		cout << " Phone : ";
		cin >> phone;
	} while (phone.front() != '+' || phone.length() != 13);

	cout << endl;
	cout << " Degree: ";
	cin >> degree;

	university.academician[index].number = newRegistrationNumber;
	university.academician[index].name = name;
	university.academician[index].surname = surname;
	university.academician[index].department = department;
	university.academician[index].mail = email;
	university.academician[index].phone = phone;
	university.academician[index].degree = degree;
	cout << endl << "Academician successfully updated" << endl << endl;
	system("pause");
	menu.printAllMenu();
}
//// </Menu6>-----------------------------------------------------------

//// <Menu7>------------------------------------------------------------
void University::MenuStruct::menu7::print()
{
	system("cls");
	university.Menu.menu1.showAcademicianClassData();
	string academicianNumber;
	string studentNumber;
	bool academicianFound = false;
	bool studentFound = false;
	do
	{
		cout << "Enter the registration number of the academic you want to make an appointment with : ";
		cin >> academicianNumber;
		if (university.doYouHaveThisAcademician(academicianNumber))
		{
			academicianFound = true;
		}
	} while (academicianNumber.length() != 8 || academicianFound == false);

	do
	{
		cout << "Enter the number of the student you want to book an appointment with:";
		cin >> studentNumber;
		if (university.doYouHaveThisStudent(studentNumber))
		{
			studentFound = true;
		}
	} while (studentNumber.length() != 6 || studentFound == false);

	string randezvousDay;
	string randezvousMonth;
	string randezvousYear;
	string dateData;

	string* array = new string[3];
	time_t theTime = time(NULL);
	struct tm* date = localtime(&theTime);
	string currentDay = std::to_string(date->tm_mday);
	string currentMonth = std::to_string(date->tm_mon + 1);
	string currentYear = std::to_string(date->tm_year + 1900);
	bool studentAlreadyRandezvousReceived = false;
	do
	{
		studentAlreadyRandezvousReceived = false;
		cout << "Set an appointment date etc. \"dd:MM:yyyy\" >>";
		cin >> dateData;
		array = parseData(dateData, 7);
		randezvousDay = array[0];
		randezvousMonth = array[1];
		randezvousYear = array[2];

		for (int i = 0; i < 100; i++)
		{
			if (university.randezvous[i].academicianNumber == academicianNumber && university.randezvous[i].studentNumber == studentNumber)
			{
				if (university.randezvous[i].Date.day == randezvousDay && university.randezvous[i].Date.month == randezvousMonth && university.randezvous[i].Date.year == randezvousYear)
				{
					studentAlreadyRandezvousReceived = true;
					cout << "This student has already made an appointment to the academic you want to make an appointment .." << endl;
					cout << "A student can only make an appointment once a day to a certain academician." << endl;
					system("pause");
					break;
				}
			}
		}

	} while (dateData.size() != 10 || studentAlreadyRandezvousReceived == true);




	if (university.isRandezvousDateTrue(randezvousDay, randezvousMonth, randezvousYear))
	{
		showRandezvousTable(academicianNumber, studentNumber, randezvousDay, randezvousMonth, randezvousYear);
	}
	else
	{
		system("cls");
		cout << "No appointment was made. Please try again" << endl;
		system("pause");
		university.Menu.menu7.print();
	}

}



void University::MenuStruct::menu7::showRandezvousTable(string academicianNumber, string studentNumber, string day, string month, string year)
{
	system("cls");

	time_t theTime = time(NULL);
	struct tm* date = localtime(&theTime);

	int currentHour = date->tm_hour;
	int currentMinute = date->tm_min;

	int currentDay = date->tm_mday;
	int currentMonth = (date->tm_mon + 1);
	int currentYear = (date->tm_year + 1900);

	cout << " Academician : " << university.returnAcademicianNameAndDegree(academicianNumber) << endl;
	cout << " " << "Appoint table for " << day << "/" << month << "/" << year << endl;
	cout << endl << endl;
	int hour = 9;
	int tempMinute = 0;
	int k = 0;
	for (int i = 0; i < 100; i++)
	{

		if (k % 5 == 0)
		{
			cout << endl;
		}

		if (hour < 18)
		{

			if (hour < 10 && tempMinute == 0)
			{
				cout << "0" << hour << ":" << "00" << " ";
				if (currentHour >= hour && currentMinute >= tempMinute && atoi(day.c_str()) == currentDay)
				{
					cout << "[----]" << "\t";
				}
				else if (currentHour >= hour && currentMinute <= tempMinute && atoi(day.c_str()) == currentDay)
				{
					cout << "[----]" << "\t";
				}
				else
				{
					if (isRandezvousAvailableByAcademician(academicianNumber, day, month, year, ("0" + to_string(hour)), "00"))
					{
						cout << "[BOS ]" << "\t";
					}
					else
					{
						cout << "[DOLU]" << "\t";
					}
				}

				tempMinute = 30;
			}
			else if (hour < 10 && tempMinute != 0)
			{

				cout << "0" << hour << ":" << "30" << " ";
				if (currentHour >= hour && currentMinute >= tempMinute && atoi(day.c_str()) == currentDay)
				{
					cout << "[----]" << "\t";
				}
				else if (currentHour >= hour && currentMinute <= tempMinute && atoi(day.c_str()) == currentDay)
				{
					cout << "[----]" << "\t";
				}
				else
				{
					if (isRandezvousAvailableByAcademician(academicianNumber, day, month, year, ("0" + to_string(hour)), "30"))
					{
						cout << "[NULL]" << "\t";

					}
					else
					{
						cout << "[FULL]" << "\t";
					}
				}
				hour++;
				tempMinute = 0;
			}
			else if (hour >= 10 && tempMinute == 0)
			{
				cout << hour << ":" << "00" << " ";
				if (currentHour >= hour && currentMinute >= tempMinute && atoi(day.c_str()) == currentDay)
				{
					cout << "[----]" << "\t";
				}
				else if (currentHour >= hour && currentMinute <= tempMinute && atoi(day.c_str()) == currentDay)
				{
					cout << "[----]" << "\t";
				}
				else
				{
					if (isRandezvousAvailableByAcademician(academicianNumber, day, month, year, to_string(hour), "00"))
					{
						cout << "[NULL]" << "\t";
					}
					else
					{
						cout << "[FULL]" << "\t";
					}
				}
				tempMinute = 30;
			}
			else if (hour >= 10 && tempMinute != 0)
			{
				cout << hour << ":" << "30" << " ";
				if (currentHour >= hour && currentMinute >= tempMinute && atoi(day.c_str()) == currentDay)
				{
					cout << "[----]" << "\t";
				}
				else if (currentHour >= hour && currentMinute <= tempMinute && atoi(day.c_str()) == currentDay)
				{
					cout << "[----]" << "\t";
				}
				else
				{
					if (isRandezvousAvailableByAcademician(academicianNumber, day, month, year, to_string(hour), "30"))
					{
						cout << "[NULL]" << "\t";
					}
					else
					{
						cout << "[FULL]" << "\t";
					}
				}
				tempMinute = 0;
				hour++;
			}
		}
		else
		{
			break;
		}
		k++;
	}
	cout << endl << endl;

	string randezvousValue;
	string hourValue;
	string minuteValue;
	bool result = false;
	string* array;
	do
	{
		cout << "Enter the time you want to make an appointment etc. \"hh:MM\" >>";
		cin >> randezvousValue;
		if (university.isRandezvousHourFormatTrue(randezvousValue))
		{
			array = parseData(randezvousValue, 2);
			hourValue = array[0];
			minuteValue = array[1];
			if (isStudentHaveAnotherRandezvous(studentNumber, day, month, year, hourValue, minuteValue))
			{
				string academician = university.returnAcademicianNameAndDegree(academicianNumber.c_str());
				cout << "The student has already made an appointment with the academician " << academician << " at this time.." << endl;
				result = false;
			}
			else
			{
				if (isRandezvousAvailableByAcademician(academicianNumber, day, month, year, hourValue, minuteValue))
				{
					result = true;
				}
				else
				{
					cout << endl << "Please enter a different time. Because the appointment is full at the selected time." << endl;
					result = false;
				}
			}

		}
	} while (result == false);

	if (result)
	{
		for (int i = 0; i < 100; i++)
		{
			if (university.randezvous[i].academicianNumber == "")
			{
				university.randezvous[i].academicianNumber = academicianNumber;
				university.randezvous[i].studentNumber = studentNumber;
				university.randezvous[i].Date.day = day;
				university.randezvous[i].Date.month = month;
				university.randezvous[i].Date.year = year;
				university.randezvous[i].Hour.startHour = hourValue;
				university.randezvous[i].Hour.startMinute = minuteValue;
				if (university.randezvous[i].Hour.startMinute == "00")
				{
					university.randezvous[i].Hour.endHour = hourValue;
					university.randezvous[i].Hour.endMinute = "30";
				}
				else
				{
					int temp = atoi(hourValue.c_str()) + 1;
					university.randezvous[i].Hour.endHour = to_string(temp);
					university.randezvous[i].Hour.endMinute = "00";
				}
				cout << endl << "Randezvous created.. " << endl;
				break;
			}
		}
		system("pause");
		university.Menu.printAllMenu();
	}
}


bool University::MenuStruct::menu7::isRandezvousAvailableByAcademician(string academicianNumber, string day, string month, string year, string hour, string minute)
{
	bool result = true;
	for (int i = 0; i < 100; i++)
	{
		if (university.randezvous[i].academicianNumber == academicianNumber)
		{
			if (university.randezvous[i].Date.day == day && university.randezvous[i].Date.month == month && university.randezvous[i].Date.year == year)
			{
				if (university.randezvous[i].Hour.startHour == hour && university.randezvous[i].Hour.startMinute == minute)
				{
					result = false;
					break;
				}
			}
		}
	}
	return result;
}
bool University::MenuStruct::menu7::isRandezvousAvailableByStudent(string studentNumber, string day, string month, string year, string hour, string minute)
{
	bool result = true;
	for (int i = 0; i < 100; i++)
	{
		if (university.randezvous[i].studentNumber == studentNumber)
		{
			if (university.randezvous[i].Date.day == day && university.randezvous[i].Date.month == month && university.randezvous[i].Date.year == year)
			{
				if (university.randezvous[i].Hour.startHour == hour && university.randezvous[i].Hour.startMinute == minute)
				{
					result = false;
					break;
				}
			}
		}
	}
	return result;
}

bool University::MenuStruct::menu7::isStudentHaveAnotherRandezvous(string studentNumber, string day, string month, string year, string hour, string minute)
{
	bool result = false;
	for (int i = 0; i < 100; i++)
	{
		if (university.randezvous[i].studentNumber == studentNumber)
		{
			if (university.randezvous[i].Date.day == day && university.randezvous[i].Date.month == month && university.randezvous[i].Date.year == year)
			{
				if (university.randezvous[i].Hour.startHour == hour && university.randezvous[i].Hour.startMinute == minute)
				{
					result = true;
					break;
				}
			}
		}
	}
	return result;
}
//// </Menu7>-----------------------------------------------------------

//// <Menu8>------------------------------------------------------------
void University::MenuStruct::menu8::print()
{
	system("cls");
	cout << endl;
	cout << " [0] Edit Randezvous" << endl;
	cout << " [1] Remove Randezvous" << endl;
	int choice;
	do
	{
		cout << " Choose the action you want to do" << endl;
		cin >> choice;
	} while (choice != 0 && choice != 1);

	switch (choice)
	{
	case 0:
		university.Menu.menu8.subMenuEdit.editRandezvousByStudent();
	case 1:
		university.Menu.menu8.subMenuDelete.print();
		break;
	}
}


void University::MenuStruct::menu8::subMenuEdit::editRandezvousByStudent()
{
	string studentNumber;
	do
	{
		cout << endl;
		cout << " Enter the number of the student whose randezvous you want to update :";
		cin >> studentNumber;
		if (university.doYouHaveThisStudent(studentNumber) == false)
		{
			cout << "Student number " << studentNumber << " was not found";
			system("pause");
		}
	} while (studentNumber.length() != 6 || university.doYouHaveThisStudent(studentNumber) == false);

	string date;
	string day;
	string month;
	string year;
	string hour;
	string minute;
	string* dateArray;
	bool wrongFormat = true;
	do
	{
		system("cls");
		cout << "Set the date you want to update etc. \"dd:MM:yyyy hh:mm\" >>";
		cin >> ws; // Çoklu sözcük için "first second"
		getline(std::cin, date);
		dateArray = parseData(date, 5);
		day = dateArray[0];
		month = dateArray[1];
		year = dateArray[2];
		hour = dateArray[3];
		minute = dateArray[4];
		if (university.isRandezvousDateTrue(day, month, year) == true && university.isRandezvousHourFormatTrue(hour + ":" + minute))
		{
			wrongFormat = false;
		}
		else
		{
			wrongFormat = true;
		}

	} while (wrongFormat == true);

	if (university.Menu.menu7.isRandezvousAvailableByStudent(studentNumber, day, month, year, hour, minute) == false)
	{
		// Randevu bulamıyorsa demek ki o an randevusu vardır o yüzden fonksiyonun false deger döndürmesini istedim
		// Çünkü bu fonksiyon sadece randevu ALABİLİYOR mu onu kontrol eder. Alamıyorsa randevusu vardır belirtilen tarihte
		string newDate;
		string newDay;
		string newMonth;
		string newYear;
		string newHour;
		string newMinute;
		string* newDateArray;
		do
		{
			cout << "Set the new date and time you want to update orn \"dd:MM:yyyy hh:mm\" >>";
			cin >> ws;
			getline(cin, newDate);
			newDateArray = parseData(newDate, 5);
			newDay = newDateArray[0];
			newMonth = newDateArray[1];
			newYear = newDateArray[2];
			newHour = newDateArray[3];
			newMinute = newDateArray[4];
			if (university.isRandezvousDateTrue(day, month, year) == true && university.isRandezvousHourFormatTrue(newHour + ":" + newMinute))
			{
				if (university.Menu.menu7.isStudentHaveAnotherRandezvous(studentNumber, newDay, newMonth, newYear, newHour, newMinute))
				{
					cout << "You have another randezvous at this time you want to update" << endl;
					system("pause");
					university.Menu.menu8.subMenuEdit.editRandezvousByStudent();
				}
				else
				{
					if (university.Menu.menu7.isRandezvousAvailableByStudent(studentNumber, newDay, newMonth, newYear, newHour, newMinute))
					{
						int k = 0;
						bool finded = false;
						for (; k < 100; k++)
						{
							if (university.randezvous[k].studentNumber == studentNumber)
							{
								if (university.randezvous[k].Date.day == day && university.randezvous[k].Date.month == month && university.randezvous[k].Date.year == year)
								{
									if (university.randezvous[k].Hour.startHour == hour && university.randezvous[k].Hour.startMinute == minute)
									{
										finded = true;
										break;
									}
								}
							}
						}
						if (finded)
						{
							university.randezvous[k].Date.day = newDay;
							university.randezvous[k].Date.month = newMonth;
							university.randezvous[k].Date.year = newYear;
							university.randezvous[k].Hour.startHour = newHour;
							university.randezvous[k].Hour.startMinute = newMinute;
							int tempHour;
							tempHour = atoi(university.randezvous[k].Hour.startHour.c_str());
							if (newMinute == "30")
							{
								tempHour++;
								university.randezvous[k].Hour.endHour = to_string(tempHour);
								university.randezvous[k].Hour.endMinute = "00";
							}
							else
							{
								university.randezvous[k].Hour.endHour = to_string(tempHour);
								university.randezvous[k].Hour.endMinute = "30";
							}

							cout << "Update randezvous successfull..";
							system("pause");
						}

					}
				}
			}
			else
			{
				cout << endl << "The appointment time format entered is incorrect. Please write the format accordingly" << endl;
				system("pause");
			}

		} while (university.isRandezvousDateTrue(day, month, year) != true || university.isRandezvousHourFormatTrue(newHour + ":" + newMinute) != true);

		// Buraya kadar gelirse zaten randevu güncelleme başarılı olmuştur..
		university.Menu.printAllMenu();
	}
	else
	{
		cout << endl << "No appointment for the student was found at this time.";
		system("pause");
		university.Menu.menu0.showRandezvousByStudent(studentNumber);
	}

}
void University::MenuStruct::menu8::subMenuDelete::print()
{
	string studentNumber;
	string day;
	string month;
	string year;
	string hour;
	string minute;
	string date;
	do
	{

		system("cls");
		cout << endl << " Set the randezvous you want to delete. etc. \"ogrenciNo dd:MM:yyyy hh:mm\" >>";
		cin >> ws;
		getline(cin, date);
		string* array = parseData(date, 6);
		studentNumber = array[0];
		day = array[1];
		month = array[2];
		year = array[3];
		hour = array[4];
		minute = array[5];

	} while (university.isRandezvousDateTrue(day, month, year) == false || university.isRandezvousHourFormatTrue(hour + ":" + minute) == false);

	bool randezvousFound = false;
	for (int i = 0; i < 100; i++)
	{
		if (university.randezvous[i].studentNumber == studentNumber)
		{
			if (university.randezvous[i].Date.day == day && university.randezvous[i].Date.month == month && university.randezvous[i].Date.year == year)
			{
				if (university.randezvous[i].Hour.startHour == hour && university.randezvous[i].Hour.startMinute == minute)
				{
					randezvousFound = true;
					break;
				}
			}
		}
	}
	if (randezvousFound)
	{
		deleteRandezvousByStudent(studentNumber, day, month, year, hour, minute);
		cout << "Randezvous deleted.." << endl;
		system("pause");
		university.Menu.printAllMenu();
	}
	else
	{
		cout << "The appointment you want to delete could not be found.." << endl;
		system("pause");
		university.Menu.printAllMenu();
	}

}

void University::MenuStruct::menu8::subMenuDelete::deleteRandezvousByStudent(string studentNumber, string day, string month, string year, string hour, string minute)
{
	for (int i = 0; i < 100; i++)
	{
		if (university.randezvous[i].studentNumber == studentNumber)
		{
			if (university.randezvous[i].Date.day == day && university.randezvous[i].Date.month == month && university.randezvous[i].Date.year == year)
			{
				if (university.randezvous[i].Hour.startHour == hour && university.randezvous[i].Hour.startMinute == minute)
				{
					university.randezvous[i].academicianNumber = "";
					university.randezvous[i].studentNumber = "";
					university.randezvous[i].Date.day = "";
					university.randezvous[i].Date.month = "";
					university.randezvous[i].Date.year = "";
					university.randezvous[i].Hour.startHour = "";
					university.randezvous[i].Hour.startMinute = "";
					university.randezvous[i].Hour.endHour = "";
					university.randezvous[i].Hour.endMinute = "";
					break;
				}
			}
		}
	}
}
//// </Menu8>-----------------------------------------------------------

//// <Menu9>------------------------------------------------------------
//// <Menu9>------------------------------------------------------------
void University::MenuStruct::menu9::saveStudents()
{
	studentFile.open(studentFileName, std::ofstream::out);
	for (int i = 0; i < 100; i++)
	{
		if (university.student[i].number != "")
		{
			studentFile << university.student[i].number << " ";
			studentFile << university.student[i].name << " ";
			studentFile << university.student[i].surname << " ";
			studentFile << university.student[i].department << " ";
			studentFile << university.student[i].registrationYear << " ";
			studentFile << university.student[i].mail << " ";
			studentFile << university.student[i].phone << endl;

		}
	}
	studentFile.close();
}
void University::MenuStruct::menu9::saveAcademicians()
{
	academicianFile.open(academicianFileName, std::ofstream::out);
	int amount = university.countAcademiciansFromClass();
	if (amount != 0)
	{
		for (int i = 0; i < 100; i++)
		{
			if (university.academician[i].number != "")
			{
				academicianFile << university.academician[i].number << " ";
				academicianFile << university.academician[i].name << " ";
				academicianFile << university.academician[i].surname << " ";
				academicianFile << university.academician[i].department << " ";
				academicianFile << university.academician[i].mail << " ";
				academicianFile << university.academician[i].phone << " ";
				academicianFile << university.academician[i].degree << endl;
			}
		}
	}
	academicianFile.close();
}
void University::MenuStruct::menu9::saveRandezvous()
{
	randezvousFile.open(randezvousFileName, std::ofstream::out);
	int amount = university.countRandezvousFromClass();
	if (amount != 0)
	{
		for (int i = 0; i < 100; i++)
		{
			if (university.randezvous[i].academicianNumber != "")
			{
				randezvousFile << university.randezvous[i].academicianNumber << " ";
				randezvousFile << university.randezvous[i].studentNumber << " ";
				randezvousFile << university.randezvous[i].Date.day << "/";
				randezvousFile << university.randezvous[i].Date.month << "/";
				randezvousFile << university.randezvous[i].Date.year << " ";
				randezvousFile << university.randezvous[i].Hour.startHour << ":";
				randezvousFile << university.randezvous[i].Hour.startMinute << " ";
				randezvousFile << university.randezvous[i].Hour.endHour << ":";
				randezvousFile << university.randezvous[i].Hour.endMinute << " " << endl;
			}
		}
	}

}
//// </Menu9>--------------------------------------------------------------