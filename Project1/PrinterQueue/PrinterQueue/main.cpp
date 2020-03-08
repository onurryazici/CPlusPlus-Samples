#include <iostream>
#include <locale.h>
#include <fstream>
#include <string>
#include <Windows.h>
#include <time.h> 
#include <vector>
using namespace std;

enum colors {
	BLACK_BACKGROUND_WHITE_TEXT = 8,
	WHITE_BACKGROUND_BLACK_TEXT = 240,
	BLACK_BACKGROUND_YELLOW_TEXT = 14,
	BLACK_BACKGROUND_GREEN_TEXT = 10,
	BLACK_BACKGROUND_RED_TEXT = 12,
	WHITE_BACKGROUND_GREEN_TEXT = 250,
	WHITE_BACKGROUND_RED_TEXT = 252
};

enum parse_stage {
	DOCUMENT_PATH = 0,
	DOCUMENT_FILE_LENGTH = 1,
	DOCUMENT_PAGE_AMOUNT = 2,
	PERSON_NAME = 3,
	PERSON_SURNAME = 4,
	PERSON_USERNAME = 5,
	PERSON_MAIL = 6,
	DATE_YEAR = 7,
	DATE_MONTH = 8,
	DATE_DAY = 9,
	DATE_HOUR = 10,
	DATE_MINUTE = 11,
	DATE_SECONDS = 12,
	DOCUMENT_PRIORITY = 13,
};
struct Document {
	string documentPath;
	int documentFileLength;
	int documentPageAmount;
	bool havePriority = false;
	struct Person {
		string name;
		string surname;
		string username;
		string mail;
		bool havePriority;
	};

	struct Date {
		int year;
		int day;
		int month;
		int hour;
		int minute;
		int seconds;
	};

	Person person;
	Date date;
};

string parseStringByElement(string yourLine, enum parse_stage stage);
void printTableHeaders();	// Dosya içerikleri için basit table görünümü oluþturmak için..
void timer(vector<Document>& docList, const int printSpeed, const int queueSpeed); // kuyruk, yazma ve yazma zamanlama iþlemleri
bool addQueue(vector<Document>& docList); // Parametreye alýnan dökümaný kuyruða ekler.
void printQueueList();		// Kuyrukta bekleyen dökümanlarýn adýný yazdýrýr.
void printingQueueItems();	// Kuyrukta bekleyen dökümanlarý yazýcýya yazdrýr.
void leftShiftingQueue();	// Kuyruðu güncelledikten sonra oluþan boþluklarý önler.
int countQueueItems();		// Kuyrukta bulunan dökümanlarý sayar.
bool printCompleted(vector<Document>& docList); // Yazma iþleminin bitip bitmediðini kontrol eder
bool checkPriority(vector<Document>& docList);	// Öncelikli bulunan döküman varsa bu metod ile kuyruða ekler
string returnDocFileName(string docFilePath);	// Metin dosyasýnda konumu ve adýyla bulunun veriden sadece dosya adýný döndürür. (files/doc.docx --> doc.docx gibi)

int main()
{
	setlocale(LC_ALL, "turkish");

	cout << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE_BACKGROUND_BLACK_TEXT);
	for (int i = 0; i < 27; i++)
	{
		cout << "-";
	}

	cout << "Print Process";
	for (int k = 0; k < 27; k++)
	{
		cout << "-";
	}
	cout << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK_BACKGROUND_WHITE_TEXT);
	cout << endl << "Files reading..." << endl;
	Sleep(100);

	bool fileAccessed = false;
	ifstream dataFile("documentFileContexts.txt");
	if (dataFile.good())
	{
		Sleep(500);
		fileAccessed = true;
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK_BACKGROUND_RED_TEXT);
		cout << "[XX]" << endl;
		cout << "Can't access to file..\n";
		fileAccessed = false;
	}


	int amountOfDocuments = 0;
	if (fileAccessed)
	{
		cout << "File access successful.\t\t";
		cout << "[OK]" << endl;
		string dataString;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK_BACKGROUND_WHITE_TEXT);
		printTableHeaders();
		while (getline(dataFile, dataString))
		{
			amountOfDocuments++;
			// Count only documents
		}
		dataString = "";
		dataFile.clear();					// We need these 2 lines to bring the file cursor to the top
		dataFile.seekg(0, dataFile.beg);	// again..

		vector<Document> documentList(amountOfDocuments);

		int loop = 0;

		int zebraLines = 0;
		while (getline(dataFile, dataString))
		{
			zebraLines++;
			if (zebraLines % 2 == 0)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK_BACKGROUND_WHITE_TEXT);
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE_BACKGROUND_BLACK_TEXT);
			}
			documentList[loop].documentPath = parseStringByElement(dataString, DOCUMENT_PATH);
			documentList[loop].documentFileLength = atoi(parseStringByElement(dataString, DOCUMENT_FILE_LENGTH).c_str());
			documentList[loop].documentPageAmount = atoi(parseStringByElement(dataString, DOCUMENT_PAGE_AMOUNT).c_str());
			documentList[loop].person.name = parseStringByElement(dataString, PERSON_NAME);
			documentList[loop].person.surname = parseStringByElement(dataString, PERSON_SURNAME);
			documentList[loop].person.username = parseStringByElement(dataString, PERSON_USERNAME);
			documentList[loop].person.mail = parseStringByElement(dataString, PERSON_MAIL);
			documentList[loop].date.year = atoi(parseStringByElement(dataString, DATE_YEAR).c_str());
			documentList[loop].date.month = atoi(parseStringByElement(dataString, DATE_MONTH).c_str());
			documentList[loop].date.day = atoi(parseStringByElement(dataString, DATE_DAY).c_str());
			documentList[loop].date.hour = atoi(parseStringByElement(dataString, DATE_HOUR).c_str());
			documentList[loop].date.minute = atoi(parseStringByElement(dataString, DATE_MINUTE).c_str());
			documentList[loop].date.seconds = atoi(parseStringByElement(dataString, DATE_SECONDS).c_str());





			cout.width(30);
			cout << left << documentList[loop].documentPath << '\t';
			std::cout.width(10);
			cout << documentList[loop].documentFileLength << "\t";
			std::cout.width(10);
			cout << documentList[loop].documentPageAmount << "\t";

			string priority = parseStringByElement(dataString, DOCUMENT_PRIORITY);
			if (priority == "*")
			{
				documentList[loop].havePriority = true;
				cout.width(9);

				if (zebraLines % 2 == 0)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK_BACKGROUND_RED_TEXT);
					cout << right << "YES";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK_BACKGROUND_WHITE_TEXT);
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE_BACKGROUND_RED_TEXT);
					cout << right << "YES";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK_BACKGROUND_WHITE_TEXT);
				}
			}
			else
			{
				documentList[loop].havePriority = false;
				cout.width(9);
				if (zebraLines % 2 == 0)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK_BACKGROUND_WHITE_TEXT);
					cout << right << "NO";
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE_BACKGROUND_BLACK_TEXT);
					cout << right << "YES";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK_BACKGROUND_WHITE_TEXT);
				}


			}



			cout << endl;
			Sleep(20);
			loop++;
		}


		int printSpeed, queueSpeed;
		cout << endl << "How many seconds do you send a document to the computer queue? :";
		cin >> queueSpeed;

		cout << endl << "How many seconds do you print document? :";
		cin >> printSpeed;

		Sleep(300);
		cout << endl << "Print process starting..." << endl << endl;
		timer(documentList, printSpeed, queueSpeed);
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);// black line
		cout << "Can't access the file";
	}
	dataFile.close();
	system("pause");
}


int seconds = 0;
vector<Document> queue(5);
int queueLocation = 0; // Provides DOCUMENT by accessing the indexes of the vector array.
int printLocation = 0; // Accesses the indexes of the DOCUMENTS vector array, bypassing the order.
int printedPageHolder = 0;
void timer(vector<Document>& docList, const int printSpeed, const int queueSpeed)
{
	if (!printCompleted(docList))
	{
		cout << endl;
		clock_t endwait;
		endwait = clock() + 1 * CLOCKS_PER_SEC;
		while (clock() < endwait) {}
		seconds++;
		cout << seconds << ".seconds ";


		if (seconds % queueSpeed == 0)
		{
			if (checkPriority(docList))
			{

			}
			else
			{
				if (addQueue(docList))
				{
					// Sadece addQueue methodu sadece eklenebilirliði test etmez. Eklenebilirlik var ise kuyruða ekler
				}
				else
				{
					if (queueLocation != (int)docList.size())
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK_BACKGROUND_RED_TEXT);
						cout << "The queue is full. Please wait!!\t";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
					}
					printQueueList();
				}
			}
		}


		if (seconds % printSpeed == 0 && countQueueItems() != 0)
		{
			printingQueueItems();
			timer(docList, printSpeed, queueSpeed);
		}
		else
		{
			// for first loop
			timer(docList, printSpeed, queueSpeed);
		}
	}
	else
	{
		cout << "Queue ended. << endl";
	}
}

bool printCompleted(vector<Document>& docList)
{
	bool value;
	if (queueLocation < (int)(docList.size()))
	{
		value = false; // Is print process ended ?
	}
	else
	{
		if (countQueueItems() == 0)
		{
			value = true;
		}
		else
		{
			value = false;
		}

	}

	return value;
}

int countQueueItems()
{
	int value = 0;
	for (size_t index = 0; index < queue.size(); index++)
	{
		if (queue.at(index).documentPath != "")
		{
			value++;
		}
	}
	return value;
}

void printingQueueItems()
{
	int page = queue.at(printLocation).documentPageAmount;
	printedPageHolder++;
	if (printedPageHolder == page)
	{
		cout << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		cout << seconds << ".second " << queue.at(printLocation).documentPath << " writed. ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
		Document nullDoc;
		queue.at(printLocation) = nullDoc;
		leftShiftingQueue();
		printedPageHolder = 0;
		printQueueList();
	}
}
void leftShiftingQueue()
{
	for (size_t index = 0; index < queue.size(); index++)
	{
		if (queue.at(index).documentPath == "")
		{
			if ((index + 1) < queue.size())
			{
				Document nullDoc;
				queue.at(index) = queue.at(index + 1);
				queue.at(index + 1) = nullDoc;
			}

		}
	}
}

bool addQueue(vector<Document>& docList)
{
	bool isItCanBeAdded = true;
	for (size_t index = 0; index < queue.size(); index++)
	{
		if (queue.at(index).documentPath == "")// if queue index is empty
		{
			if (queueLocation < (int)(docList.size())) // for overflowing
			{
				queue.at(index) = docList[queueLocation];
				cout << "PC " << returnDocFileName(queue.at(index).documentPath) << " sended. ";
				printQueueList();
				queueLocation++;
				isItCanBeAdded = true;
				return true;
			}
		}
		else
		{
			isItCanBeAdded = false;
		}
	}

	return isItCanBeAdded;
}

bool checkPriority(vector<Document>& docList)
{
	bool priorityAvailable = false;
	for (size_t index = 0; index < docList.size(); index++)
	{
		if (docList.at(index).havePriority)
		{
			// filling to queue
			for (size_t i = 0; i < queue.size(); i++)
			{
				if (queue.at(i).documentPath == "")// Kuyrukta boþ yer bulursa döküman kuyruða atanýr
				{
					queue.at(i) = docList[index];
					cout << "PC " << returnDocFileName(queue.at(i).documentPath) << " sended with PRIORITY. ";
					printQueueList();
					docList.erase(docList.begin() + index);
					priorityAvailable = true;
					return true;
				}
			}
		}
	}
	return priorityAvailable;
}

void printQueueList()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK_BACKGROUND_YELLOW_TEXT);
	cout << "Queue : ";
	for (size_t index = 0; index < queue.size(); index++)
	{
		if (queue.at(index).documentPath != "")
		{
			cout << " " << returnDocFileName(queue.at(index).documentPath) << " ";
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK_BACKGROUND_RED_TEXT);
	cout << ">> " << countQueueItems() << " <<";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK_BACKGROUND_WHITE_TEXT);

}
string returnDocFileName(string docFilePath)
{
	int index = docFilePath.find_last_of('/');
	string value = docFilePath.erase(0, index + 1);
	return value;
}

string parseStringByElement(string yourLine, enum parse_stage stage)
{
	string result;

	int arrayIndex = 0;
	string arrayOfParse[14];
	yourLine += "\n";
	string word;
	for (auto x : yourLine)
	{
		if (x == '\n')
		{
			arrayOfParse[arrayIndex++] = word;
			word = "";
		}
		else if (x == '\t')
		{
			arrayOfParse[arrayIndex++] = word;
			word = "";
		}
		else
		{
			word = word + x;
		}
	}


	switch (stage)
	{
	case DOCUMENT_PATH:
	{
		result = arrayOfParse[DOCUMENT_PATH];
		break;
	}
	case DOCUMENT_FILE_LENGTH:
	{
		result = arrayOfParse[DOCUMENT_FILE_LENGTH];
		break;
	}
	case DOCUMENT_PAGE_AMOUNT:
	{
		result = arrayOfParse[DOCUMENT_PAGE_AMOUNT];
		break;
	}
	case PERSON_NAME:
	{
		result = arrayOfParse[PERSON_NAME];
		break;
	}
	case PERSON_SURNAME:
	{
		result = arrayOfParse[PERSON_SURNAME];
		break;
	}
	case PERSON_USERNAME:
	{
		result = arrayOfParse[PERSON_USERNAME];
		break;
	}
	case PERSON_MAIL:
	{
		result = arrayOfParse[PERSON_MAIL];
		break;
	}
	case DATE_YEAR:
	{
		result = arrayOfParse[DATE_YEAR];
		break;
	}
	case DATE_MONTH:
	{
		result = arrayOfParse[DATE_MONTH];
		break;
	}
	case DATE_DAY:
	{
		result = arrayOfParse[DATE_DAY];
	}
	case DATE_HOUR:
	{
		result = arrayOfParse[DATE_HOUR];
		break;
	}
	case DATE_MINUTE:
	{
		result = arrayOfParse[DATE_MINUTE];
		break;
	}
	case DATE_SECONDS:
	{
		result = arrayOfParse[DATE_SECONDS];
		break;
	}
	case DOCUMENT_PRIORITY:
	{
		result = arrayOfParse[DOCUMENT_PRIORITY];
		break;
	}
	}
	return result;
}

void printTableHeaders()
{
	cout << endl << " File\t\t\t\t" << "Sİze\t\t" << "Page\t\t" << "Priority" << endl;
	for (int i = 0; i < 73; i++)
	{
		cout << "_";
	}
	cout << endl << endl;
}
