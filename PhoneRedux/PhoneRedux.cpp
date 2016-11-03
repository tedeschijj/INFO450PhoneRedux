// PhoneRedux.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;

class phoneBook
{
	char name[50];
	char homeNumber[50];
	char cellNumber[50];

public:
	phoneBook();
	void setPhoneBook(char b1[], char b2[], char b3[]);
	void display();
	friend class phonelist;
};

phoneBook::phoneBook()
{
	strcpy_s(name, "");
	strcpy_s(homeNumber, "");
	strcpy_s(cellNumber, "");
}

void phoneBook::setPhoneBook(char b1[], char b2[], char b3[])
{
	strcpy_s(name, b1);
	strcpy_s(homeNumber, b2);
	strcpy_s(cellNumber, b3);
}

void phoneBook::display()
{
	printf("--------------------------------------\n");
	printf("Full Name: %s Home Number: %s Cell Number: %s", name, homeNumber, cellNumber);
	printf("--------------------------------------\n");
}

class phonelist
{
	char filename[100];
	int phoneCount;
	phoneBook **mylist;
public:
	phonelist();
	~phonelist();
	void setFilename(char f[]);
	int getCount();
	void addToList(phoneBook *b);
	void showList();
	int saveList();
	void readList();
};

phonelist::phonelist()
{
	mylist = new phoneBook*[100];
	phoneCount = 0;
}

phonelist::~phonelist()
{
	delete mylist;
}

void phonelist::setFilename(char f[])
{
	strcpy_s(filename, f);
}

void phonelist::addToList(phoneBook *b)
{
	mylist[phoneCount] = b;
	phoneCount++;
	//could use a second ; above
}

int phonelist::getCount()
{
	return phoneCount;
}

void phonelist::showList()
{
	for (int i = 0; i < phoneCount; i++)
	{
		mylist[i]->display();

	}
}

int phonelist::saveList()
{
	ofstream output(filename);
	if (!output)
	{
		cout << "Failure saving..." << endl;
		return -1;
	}
	for (int i = 0; i < phoneCount; i++)
	{
		output << mylist[i]->name << ",";
		output << mylist[i]->homeNumber << ",";
		output << mylist[i]->cellNumber << ",";
	}
	output.close();
	return 0;
}

void phonelist::readList()
{
	ifstream infile(filename);
	if (!infile)
	{
		return;
	}
	while (!infile.eof())
	{
		phoneBook *ptr;
		char name[50];
		char homeNumber[50];
		char cellNumber[50];

		infile.getline(name, 50, ',');
		if (strlen(name))
		{
			infile.getline(homeNumber, 50, ',');
			infile.getline(cellNumber, 50, ',');
			ptr = new phoneBook();
			ptr->setPhoneBook(name, homeNumber, cellNumber);
			addToList(ptr);
		}
	}
	infile.close();
}

int main()
{
	char anwser = 'y';
	char name[50];
	char homeNumber[50];
	char cellNumber[50];
	char filename[50];

	phonelist *bList = new phonelist();

	cout << "Please enter full path filename" << endl;
	gets_s(filename);
	bList->setFilename(filename);

	bList->readList();
	if (bList->getCount() == 0)
	{
		cout << "Your list is empty, enter records" << endl;
	}
	else
	{
		cout << "You have: " << bList->getCount() << " in your list" << endl;
	}

	cout << "Would you like to enter new user? Enter Y to add; any other key to quit" << endl;
	cin >> anwser;

	while (anwser == 'Y' || anwser == 'y')
	{
		cin.ignore();
		cin.clear();

		cout << "Enter Name" << endl;
		gets_s(name);
		cout << "Enter Home Phone Number" << endl;
		gets_s(homeNumber);
		cout << "Enter Cell Phone Number" << endl;
		gets_s(cellNumber);

		phoneBook *myphoneBook = new phoneBook();
		myphoneBook->setPhoneBook(name, homeNumber, cellNumber);
		bList->addToList(myphoneBook);

		cout << "Another ?" << endl;
		cin >> anwser;
	}
	cout << cellNumber << endl;
	bList->showList();
	bList->saveList();
	return 0;
}

