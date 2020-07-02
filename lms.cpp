#include <iostream>
#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <iomanip> //for using setw()
#include <string.h>
using namespace std;
class book
{
	char bno[6];
	char bname[50];
	char aname[20];

public:
	void createbook()
	{
		cout << endl
			 << "New Book Entry" << endl;
		cout << endl
			 << "Enter the Book No.";
		cin >> bno;
		cout << endl
			 << "Enter the Book Name" << endl;
		gets(bname);
		cout << endl
			 << "Enter the Book Author Name" << endl;
		gets(aname);
		cout << endl
			 << endl
			 << endl
			 << "Book created";
	}
	void showbook()
	{
		cout << endl
			 << "Book Number : " << bno;
		cout << endl
			 << "Book Name :";
		puts(bname);
		cout << endl
			 << "Author Name :";
		cout << aname;
	}

	void modifybook()
	{
		cout << endl
			 << "Enter Number : " << bno;
		cout << endl
			 << "Modify Book Name :";
		gets(bname);
		cout << endl
			 << "Modify Author's Name :";
		gets(aname);
	}

	char *retbno()
	{
		return bno;
	}

	void report()
	{
		cout << bno << setw(30) << bname << setw(30) << aname << endl;
	}
};
class student
{
	char admno[6];
	char name[20];
	char stbno[6]; //which book student has issued
	int token;	   //total no. of books issued by students
public:
	void createstudent()
	{
		system("cls");
		cout << endl
			 << "New Student Entry" << endl;
		cout << endl
			 << "Enter the Admission number";
		cin >> admno;
		cout << endl
			 << "Enter the Student Name";
		gets(name);
		token = 0;
		stbno[0] = '\0';
		cout << endl
			 << endl
			 << "Student Record Created";
	}
	void showstudent()
	{
		cout << endl
			 << "Admission Number :" << admno;
		cout << endl
			 << "Student Name : ";
		puts(name);
		cout << endl
			 << "No of Book Issued :" << token;
		if (token == 1) // only one book issued by the student
		{
			cout << endl
				 << "Book number " << stbno;
		}
	}
	void modifystudent()
	{
		cout << endl
			 << "Admission No." << admno;
		cout << endl
			 << "Modify Student Name :";
		gets(name);
	}
	char *retadmno()
	{
		return admno;
	}
	char *retstbo()
	{
		return stbno;
	}
	int rettoken()
	{
		return token;
	}
	void addtoken()
	{
		token = 1;
	}
	void resettoken()
	{
		token = 0;
	}
	void getstbno(char t[])
	{
		strcpy(stbno, t);
	}
	void report()
	{
		cout << "\t" << admno << setw(20) << name << setw(10) << token << endl;
	}
};
fstream fp, fp1;
book bk;
student st;

void writebook() //function to write on a book using file handling..
{
	char ch;
	fp.open("book.txt", ios ::out | ios ::app);
	do
	{
		system("cls");
		bk.createbook();
		fp.write((char *)&bk, sizeof(book));
		cout << endl
			 << endl
			 << "Do you want to add more record (y/n)?";
		cin >> ch;
	} while (ch == 'y' || ch == 'Y');
	fp.close();
}

void writestudent() //function to write on a student using file handling..
{
	char ch;
	fp.open("student.txt", ios ::out | ios ::app);
	do
	{
		system("cls");
		st.createstudent();
		fp.write((char *)&st, sizeof(student));
		cout << endl
			 << endl
			 << "Do you want to add more record (y/n)?";
		cin >> ch;
	} while (ch == 'y' || ch == 'Y');
	fp.close();
}

void displayspb(char n[]) //searching book
{
	cout << endl
		 << "Book Details" << endl;
	int flag = 0;
	fp.open("book.txt", ios::in);
	while (fp.read((char *)&bk, sizeof(book)))
	{
		if (strcmpi(bk.retbno(), n) == 0) //strcmpi ignores casesenstive
		{
			bk.showbook();
			flag = 1;
		}
	}
	fp.close();
	if (flag == 0)
	{
		cout << endl
			 << endl
			 << "Book does not exist";
		getch();
	}
}
void displaysps(char n[]) //searching student
{
	cout << endl
		 << "Student Details" << endl;
	int flag = 0;
	fp.open("student.txt", ios::in);
	while (fp.read((char *)&st, sizeof(student)))
	{
		if (strcmpi(st.retadmno(), n) == 0) //strcmpi ignores casesenstive
		{
			st.showstudent();
			flag = 1;
		}
	}
	fp.close();
	if (flag == 0)
	{
		cout << endl
			 << endl
			 << "Student does not exist";
		getch();
	}
}

void modifybook() //updating book
{
	char n[6];
	int found = 0;
	clrscr();
	cout << endl<< endl<< "Modify Book Record ";
	cout << endl<< endl<< "Enter the Book Number ";
	cin >> n;
	fp.open("book.txt", ios::in | ios::out);
	while (fp.read((char *)&bk, sizeof(book)) && found == 0)
	{
		if (strcmpi(bk.retbno(), n) == 0)
		{
			bk.showbook();
			cout<<endl<<"Enter the new details of the book "<<endl;
			bk.modifybook();
			int pos = -1*sizeof(bk);
			fp.write((char*)&bk,sizeof(book));
			fp.seekp(pos,ios::cur);
			cout<<endl<<end<<"Record Updated";
			found=1;

		}
	}
	fp.close();
	if(found == 0)
	{
		cout<<endl<<endl<<"Record not found";
	}
	getch();
}


void modifystudent() //updating student
{
	char n[6];
	int found = 0;
	clrscr();
	cout << endl<< endl<< "Modify Student Record ";
	cout << endl<< endl<< "Enter Admission  Number ";
	cin >> n;
	fp.open("student.txt", ios::in | ios::out);
	while (fp.read((char *)&st, sizeof(student)) && found == 0)
	{
		if (strcmpi(st.retadmno(), n) == 0)
		{
			st.showstudent();
			cout<<endl<<"Enter the new details of the Student "<<endl;
			st.modifystudent();
			int pos = -1*sizeof(st);
			fp.write((char*)&st,sizeof(student));
			fp.seekp(pos,ios::cur);
			cout<<endl<<end<<"Record Updated";
			found=1;

		}
	}
	fp.close();
	if(found == 0)
	{
		cout<<endl<<endl<<"Record not found";
	}
	getch();
}





void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void start()
{

	gotoxy(35, 11);
	cout << "LIBRARY MANAGEMENT SYSYTEM" << endl
		 << endl;
	gotoxy(35, 13);
	cout << "Developer : Nitesh Prasad";
	getch();
}
void adminmenu()
{
	system("cls");
	int ch2;
	cout << endl
		 << endl
		 << endl
		 << "\tAdminstrator Menu";
	cout << endl
		 << endl
		 << endl
		 << "\t1.Create Student Record";
	cout << endl
		 << endl
		 << endl
		 << "\t2.Display All Student Record";
	cout << endl
		 << endl
		 << endl
		 << "\t3.Display Specific Student Record";
	cout << endl
		 << endl
		 << endl
		 << "\t4.Modify Student Record";
	cout << endl
		 << endl
		 << endl
		 << "\t5.Delete Student Record";
	cout << endl
		 << endl
		 << endl
		 << "\t6.Create Book";
	cout << endl
		 << endl
		 << endl
		 << "\t7.Display ALL Book";
	cout << endl
		 << endl
		 << endl
		 << "\t8.Display Specific Book";
	cout << endl
		 << endl
		 << endl
		 << "\t9.Modify Book Record";
	cout << endl
		 << endl
		 << endl
		 << "\t10.Delete Book Record";
	cout << endl
		 << endl
		 << endl
		 << "\t11.Back to Main Menu";
	cout << endl
		 << endl
		 << endl
		 << "\tPlease Enter Your Choice(1-11)";
	cin >> ch2;
	switch (ch2)
	{
	case 1:

		break;
	case 2:

		break;
	case 3:
		char num[6];
		system("cls");
		cout << endl
			 << endl
			 << "\t Please Enter the Admission No.";
		cin >> num;

		break;
	case 4:

		break;

	case 5:
		break;
	case 6:
		break;

	case 7:

		break;
	case 8:
	{

		char num[6];
		cin >> num;
	}
	break;
	case 9:

		break;
	case 10:
		break;
	case 11:

		return;
	default:
		cout << "Invalid Choice, try again";
	}
	adminmenu();
}

int main()
{
	start();
	char ch;

	do
	{
		system("cls");
		cout << endl
			 << endl
			 << "\tMAIN MENU";
		cout << endl
			 << endl
			 << "\t1.Book Issue";
		cout << endl
			 << endl
			 << "\t2.Book Deposit";
		cout << endl
			 << endl
			 << "\t3.Admnistrator Menu";
		cout << endl
			 << endl
			 << "\t4.EXIT";
		cout << endl
			 << endl
			 << "\tPlease Select Your Option between 1-4";
		ch = getche();
		switch (ch)
		{
		case '1':
			//bookissue();

		case '2':
			break;
		case '3':
			adminmenu();
			break;
		case '4':
			exit(0);
			break;
		default:
			cout << "Invalid choice, Choose valid option";
		}
	} while (ch != 4);
}
