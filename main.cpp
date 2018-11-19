#include <iostream>
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <fstream>

#define	DEBUG	printf

#define COMP_FILE	"submit\\tmp\\a.exe"
#define TC_FILE		"submit\\tmp\\tc.txt"
#define OUT_FILE	"submit\\tmp\\output.txt"
#define EXP_FILE	"submit\\tmp\\expected.txt"

using namespace std;

class account {
public:
	int sno;
	char name[100];
	char uname[100];
	char pass[100];

	account() {
		name[0] = '\0';
		uname[0] = '\0';
		pass[0] = '\0';
	}
};

class questc{
public:
	char quest[500];
	char ans[100];
	char tc[100];

	questc() {
		quest[0] = '\0';
		ans[0] = '\0';
		tc[0] = '\0';
	}
};

class stud : public account {
public:
	char clas[5];
	char path[100];
	int score;

	stud(){
		clas[0] = '\0';
		path[0] = '\0';
		score = 0;
	}
};

class tchr : public account {
public:
	char clas[3];

	tchr(){
		clas[0] = '\0';
	}
};

int login();
int signup();
int stud_win(stud stdtmp);
int tchr_win(tchr tchtmp);
int main_menu();
int submit(char *tmpath, questc qtmp);
int adquest(char *path);

int main() {
	main_menu();
	cout << "Goodbye!\n\n\n";
	return 0;
}

int main_menu(){								//Main menu window
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

int signup(){								//Sign up window
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
		ofstream ofile("std.dat", ios::binary);
		stud stud1;
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
		cout << "Enter class(E.g.: 12A): ";
		gets(stud1.clas);
		signpass:
		cout << "Enter Password: ";
		do{
			tmp = getch();
			if(tmp == '\b' && count > 0){
				cout << "\b";
				count--;
			}
			else if( tmp != '\b' && tmp != '\r' && tmp != '\n'){
				cout << '*';
				stud1.pass[count] = tmp;
				count++;
			}
		}while(tmp != '\r' && tmp != '\n');
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
			else if( tmp != '\b' && tmp != '\r' && tmp != '\n'){
				cout << '*';
				spass[count] = tmp;
				count++;
			}
		}while(tmp != '\r' && tmp != '\n');
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
		ofstream ofile("tchr.dat", ios::binary);
		tchr tchr1;
		int count = 0;
		char tmp;
		if(!ofile) {
			cout << "Fopen error!";
		}
		char tpass[100];
		cout << "Enter Real Name: ";
		cin.ignore();
		gets(tchr1.name);
		cout << "Enter Username: ";
		gets(tchr1.uname);
		cout << "Enter class teaching(E.g.: 12A): ";
		gets(tchr1.clas);
		cout << "Enter Password: ";
		do{
			tmp = getch();
			if(tmp == '\b' && count > 0){
				cout << "\b";
				count--;
			}
			else if( tmp != '\b' && tmp != '\r' && tmp != '\n'){
				cout << '*';
				tchr1.pass[count] = tmp;
				count++;
			}
		}while(tmp != '\r' && tmp != '\n');
		tchr1.pass[count] = '\0';
		cout << endl;
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

int login() {										//Login Window
	int count = 0, flag = 0;
	stud stud1;
	tchr tchr1;
	char uname[100], pass[100], mod, tmp;

	login:
	pass[0] = '\0';
	count = 0;
	cout << "Login:\n Press a key to login...\n";
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
		else if( tmp != '\b' && tmp != '\r' && tmp != '\n'){
			cout << '*';
			pass[count] = tmp;
			count++;
		}
	}while(tmp != '\r' && tmp != '\n');
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
			if(strcmp(tchr1.uname, uname) == 0 && strcmp(pass, tchr1.pass) == 0)
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

int stud_win(stud stdtmp) {						//Student Window
	system("cls");
	//clrscr();
	cout << "Welcome, " << stdtmp.name << endl;
	int count = 0, res = 0;
	char com = 'y', fpath[100];
	questc squest;
	snprintf(fpath, 100, "Assignments/%s.dat", stdtmp.clas);
	snprintf(stdtmp.path, 8, "submit");
	do{
		ifstream ifile(fpath, ios::binary);
		if(!ifile){
			cout << "Missing assignment file!\n Check path: " << fpath << endl;
		}
		for(int cnt = 0; cnt <= stdtmp.score; ifile.read((char*)&squest, sizeof(squest))){cnt++;}
		ifile.close();
		cout << "Score: " << stdtmp.score << endl;
		cout << "Question: " << squest.quest << endl;
		if (count > 0) {
			cout << "Press any key to continue...";
			getch();
			getch();
			//clrscr();
			system("cls");
		}
		cout << "Place the main.cpp file in " << stdtmp.path << " before submitting.\n";
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
			res = submit(stdtmp.path, squest);
			if(res == 0)
				stdtmp.score++;
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

int tchr_win(tchr tchtmp) {						//Teacher Window
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
		cout << "Add question: (a)\n";
		cout << "Remove question: (r)\n";
		cout << "Back: (b)\n";
		cout << "Exit: (e)\n";
		cout << "Enter Command: ";
		cin >> com;
		//clrscr();
		system("cls");
		switch (com) {
			case 'a':
			adquest(tchtmp.clas);
			break;
			case 'b':
			main_menu();
			break;
			case 'd':
			break;
			case 'r':
			return 0;
			break;
		}
		count++;
	} while (com != 'e');
	return 0;
}

int submit(char *tmpath, questc qtmp) {					//Compiles and checks submitted program
	int res;
	char stat[500];
	cout << "Compiling your program ...\n";
	snprintf(stat, 500, "g++ -o %s %s/main.cpp -L /MinGW64/lib32 -L /MinGW64/x86_64-w64-mingw32/lib32 -static-libgcc -m32", COMP_FILE, tmpath);
	DEBUG("Dbg> Executing %s\n", stat);
	res = system(stat);
	if(res == 1) {
		cout << "Error compiling.\n";
		return -1;
	}
	else {
		ofstream ofile(TC_FILE, ios::binary);
		if(!ofile) {
			cout << "Fopen error!";
		}
		ofile.write((char *)qtmp.tc, strlen(qtmp.tc)+1);
		ofile.close();
		ofstream ofile2(EXP_FILE, ios::binary);
		if(!ofile2) {
			cout << "Fopen error!";
		}
		ofile2.write((char *)qtmp.ans, strlen(qtmp.ans)+1);
		ofile2.close();
		cout << "Compiled. Executing your program with test case ...\n";
		snprintf(stat, 100, "%s > %s < %s", COMP_FILE, OUT_FILE, TC_FILE);
		DEBUG("Dbg> Executing %s\n", stat);
		res = system(stat);
		cout << "Executed. Comparing the output ...\n";
		ifstream ifile(OUT_FILE);
		ifstream ifile2(EXP_FILE);
		if(!ifile || !ifile2) {
			cout << "Open file error\n";
			return -1;
		}
		char ans[100], exp[100];
		res = 0;
		while(ifile && ifile2) {
			ifile.getline(ans, 100, '\n');
			ifile2.getline(exp, 100, '\0');
			if(strcmpi(ans, exp) != 0)
				res = 1;
		}
		if (res == 0) {
			cout << "Matches !!\n";
			return 0;
		} 
		else {
			cout << "Did not match !\n";
			return -1;
		}
	}
	return 0;
}

int adquest(char *path) {						//add question
	char fpath[100];
	snprintf(fpath, 100, "Assignments/%s.dat", path);
	ofstream ofile(fpath, ios::app | ios::binary);
	questc qtmp;
	cout << "Enter a question: ";
	cin.ignore();
	gets(qtmp.quest);
	cout << "Enter the testcases: ";
	gets(qtmp.tc);
	cout << "Enter expected answer: ";
	gets(qtmp.ans);
	ofile.write((char*)&qtmp, sizeof(qtmp));
	ofile.close();
	return 0;
}
