#include <iostream>
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <process.h>
#include <fstream>			

using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

class account {
public:
	int sno;
	char name[100];
	char uname[100];
	char pass[100];
};

class stud : public account {
public:
	char clas[3];
};

class tchr : public account {
	public:
	char clas[3];
};

int login();
int signup();
int stud_win(stud stdtmp);
int tchr_win(tchr tchtmp);
int main_menu();

int main() {
	main_menu();
	cout << "Goodbye!";
	return 0;
}

int main_menu(){
	char per;
	cout << "\t /***********************************************************\\\n";
	cout << "\t|    __       ___  __     __   __   __    __    __     ___    |\n";
	cout << "\t|   /  \\ |  |  |  |  |   |    |  | |  \\  |        |   |   |   |\n";
	cout << "\t|   |--| |  |  |  |  |   |    |  | |  |  |--    --  @ |   |   |\n";
	cout << "\t|   |  | |__|  |  |__|   |__  |__| |_ /  |__   |__    |___|   |\n";
	cout << "\t \\___________________________________________________________/\n";

	cout << "\n\n\n\t\t\tPress any key to begin...";
	getch();
	//clrscr();
	system("cls");
	menu:
	cout << "Login(l)\nSign Up(s)\n>> ";
	cin >> per;
	//clrscr();
	system("cls");
	if(per == 'l')
		login();
	else if(per == 's')
		signup();
	else{
		cout << "Invalid option\n";
		goto menu;
	}
	return 0;
}

int signup(){
	char mod;
	sign:
	cout << "Select:\n";
	cout << "Student (s)\n";
	cout << "Teacher (t)\n";
	cout << ">> ";
	cin >> mod;
	//clrscr();
	system("cls");
	if(mod == 's') {							//Student Sign-up
		stud stud1;
		ofstream ofile("std.dat");
		int count = 0;
		char tmp;
		char spass[100];
		if(!ofile) {
			cout << "Fopen error!";
		}
		char tpass[100];
		cout << "Enter Real Name: ";
		cin.ignore();
		gets(stud1.name);
		cout << "Enter Username: ";
		gets(stud1.uname);
		signpass:
		cout << "Enter class (Eg:12A): ";
		gets(stud1.clas);
		cout << "Enter Password: ";
		do{
		tmp = getch();
		if(tmp == '\b' && count > 0){
			cout << "\b";
			count--;
		}
		else if( tmp != '\b' && tmp != '\r'){
			cout << '*';
			stud1.pass[count] = tmp;
			count++;
		}
	}while(tmp != '\r');
	stud1.pass[count] = '\0';
	cout << endl;
	count = 0;
	cout << "Confirm Password: ";
	do{
		tmp = getch();
		if(tmp == '\b' && count > 0){
			cout << "\b";
			count--;
		}
		else if( tmp != '\b' && tmp != '\r'){
			cout << '*';
			spass[count] = tmp;
			count++;
		}
	}while(tmp != '\r');
	spass[count] = '\0';
	cout << endl;
	if(strcmp(spass, stud1.pass) == 0)
		ofile.write((char*)&stud1, sizeof(stud1));
	else {
		cout << "Passwords not matching!\n";
		goto signpass;
	}
		ofile.close();
	}
	else if(mod == 't') {						//Teacher Sign-up
		tchr tchr1;
		ofstream ofile("tchr.dat");
		int count = 0;
		char tmp;

		if(!ofile) {
			cout << "Fopen error!";
		}
		char tpass[100];
		cout << "Enter Real Name: ";
		gets(tchr1.name);
		cout << "Enter Username: ";
		gets(tchr1.uname);
		cout << "Enter Password: ";
		do{
		tmp = getch();
		if(tmp == '\b' && count > 0){
			cout << "\b";
			count--;
		}
		else if( tmp != '\b' && tmp != '\r'){
			cout << '*';
			tchr1.pass[count] = tmp;
			count++;
		}
	}while(tmp != '\r');
	tchr1.pass[count] = '\0';
		cout << "Confirm Password: ";
		gets(tpass);

		ofile.write((char*)&tchr1, sizeof(tchr1));
		ofile.close();
	}
	else {
		cout << "Invalid Option\n";
		goto sign;
	}
	//clrscr();
	system("cls");
	cout << "Successful!";
	getch();
	//clrscr();
	system("cls");
	login();
	return 0;
}

int login() {
	int count = 0, flag = 0;
	stud stud1;
	tchr tchr1;
	char uname[100], pass[100], mod, tmp;

	login:
	pass[0] = '\0';
	count = 0;
	cout << "Login:\n";
	cin.ignore();
	cout << "Username: ";
	gets(uname);
	cout << "Password: ";
	do{
		tmp = getch();
		if(tmp == '\b' && count > 0){
			cout << "\b";
			count--;
		}
		else if( tmp != '\b' && tmp != '\r'){
			cout << '*';
			pass[count] = tmp;
			count++;
		}
	}while(tmp != '\r');
	pass[count] = '\0';

	cout << "\nSelect:\n";
	cout << "Student (s)\n";
	cout << "Teacher (t)\n";
	cout << ">> ";
	cin >> mod;
	cout << "Logging in...\n";
	if(mod == 's') {							//Student Login
		ifstream ifile("std.dat", ios::binary);

		if(!ifile) {
			cout << "Fopen error!";
		}
		while(ifile.read((char*)&stud1,sizeof(stud1)) && flag == 0) {
			if(strcmp(stud1.uname, uname) == 0 && strcmp(pass, stud1.pass) == 0)
				flag = 1;
		}
		ifile.close();
	}
	else if (mod == 't'){						//Teacher Login
		ifstream ifile("tchr.dat", ios::binary);

		if(!ifile) {
			cout << "Fopen error!";
		}
		while(ifile.read((char*)&tchr1,sizeof(tchr1)) && flag  == 0) {
			if(strcmp(tchr1.uname, uname) == 0 && strcmp(pass, tchr1.pass))
				flag = 2;
		}
		ifile.close();
	}
	if(flag == 0) {
		//clrscr();
		system("cls");
		cout << "Invalid Username or Password\n";
		goto login;
	}
	if(flag == 1) {
		stud_win(stud1);
	}
	else if(flag == 2) {
		tchr_win(tchr1);
	}
	return 0;
}

int stud_win(stud stdtmp) {
	system("cls");
	//clrscr();
	cout << "Welcome, " << stdtmp.name << endl;
	int count = 0;
	char com = 'y';
	do {
		if (count > 0) {
			cout << "Press any key to continue...";
			getch();
			//clrscr();
			system("cls");
		}
		cout << "\t\tMenu:\n";
		cout << "Submit: (s)\n";
		cout << "Back: (b)\n";
		cout << "Exit: (e)\n";
		cout << "Enter Command: ";
		cin >> com;
		//clrscr();
		system("cls");
		switch (com) {
		case 's':
			break;
		case 'b':
			main_menu();
			break;
		case 'e':
			return 0;
			break;
		}
		count++;
	} while (com != 'e');
	return 0;
}

int tchr_win(tchr tchtmp) {
	system("cls");
	//clrscr();
	cout << "Welcome, " << tchtmp.name << endl;
	int count = 0;
	char com = 'y';
	do {
		if (count > 0) {
			cout << "Press any key to continue...";
			getch();
			//clrscr();
			system("cls");
		}
		cout << "\t\tMenu:\n";
		cout << "Display Student Details: (d)\n";
		cout << "Back: (b)\n";
		cout << "Exit: (e)\n";
		cout << "Enter Command: ";
		cin >> com;
		//clrscr();
		system("cls");
		switch (com) {
		case 'b':
			main_menu();
			break;
		case 'd':
			break;
		case 'e':
			return 0;
			break;
		}
		count++;
	} while (com != 'e');
	return 0;
}
