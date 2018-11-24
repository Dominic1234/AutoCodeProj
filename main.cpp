#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <fstream>

#define COMP_FILE	"submit\\tmp\\a.exe"
#define TC_FILE		"submit\\tmp\\tc.txt"
#define OUT_FILE	"submit\\tmp\\output.txt"
#define EXP_FILE	"submit\\tmp\\expected.txt"
#define CFLAGS		"-L /MinGW64/lib32 -L /MinGW64/x86_64-w64-mingw32/lib32 -static-libgcc -m32"

#include <conio.h>

using namespace std;

class account {
public:
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
	char clas[4];
	char path[100];
	int score;

	stud(){
		clas[0] = '\0';
		path[0] = '\0';
		score = 0;
	}
	
	int update(stud tmp){
		cout << "Saving...\n";
		getch();
		stud stcmp;
		ifstream ifile("std.dat", ios::binary);
		ofstream ofile("temp.dat", ios::binary);
		if(!ifile) {
			cout << "File open error\n";
			return -1;
		}
		while(ifile.read((char*)&stcmp, sizeof(stud))) {
			if(strcmpi(stcmp.name, tmp.name) == 0)
				ofile.write((char*)&tmp, sizeof(stud));
			else 
				ofile.write((char*)&stcmp, sizeof(stud));
		}
		ifile.close();
		ofile.close();
		remove("std.dat");
		rename("temp.dat", "std.dat");
		return 0;
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
int dispstuds(char grade[4]);
void listQs(char *grade);
int getNumQuestions (char *grade);
int readNextQ (char *grade, int lastQDone, char *buf, int bufSize);
void removeLastQ(char *grade);

int main() {
	main_menu();
	cout << "Goodbye!\n\n\n";
	return 0;
}

int main_menu(){
	char com;
	do{								//Main menu window
		menu:
		system("cls");
		char per;
		cout << "\t /***********************************************************\\\n";
		cout << "\t|    __       ___  __     __   __   __    __    __     ___    |\n";
		cout << "\t|   /  \\ |  |  |  |  |   |    |  | |  \\  |        |   |   |   |\n";
		cout << "\t|   |--| |  |  |  |  |   |    |  | |  |  |--    --  @ |   |   |\n";
		cout << "\t|   |  | |__|  |  |__|   |__  |__| |_ /  |__   |__    |___|   |\n";
		cout << "\t \\___________________________________________________________/\n";

		cout << "\n\n\n\t\t\tPress l to login...\n";
		cout << "\t\t\tPress s to sign-up...\n";
		cout << "\t\t\tPress e to Quit...\n";
		cout << ">>";
		cin >> com;
		cout << com << endl;
		if(com == 'l')
			login();
		else if(com == 's')
			signup();
		else if(com == 'e')
			break;
		else{
			cout << "Invalid option\n";
			goto menu;
		}
		cin.ignore();
	} while(com != 'e');
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
		if(strcmp(spass, stud1.pass) == 0) {
			// Append to file
			ofile.seekp (0, ofile.end);
			ofile.write((char*)&stud1, sizeof(stud1));
		} else {
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
	system("cls");
	cout << "Successful!";
	getch();
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
	cout << "Welcome, " << stdtmp.name << endl;
	int count = 0, res = 0, qRemaining = 0;
	char com = 'y';
	questc squest;
	snprintf(stdtmp.path, 8, "submit");
	do{
		if (count > 0) {
			cout << "Press any key to continue...";
			getch();
			getch();
			system("cls");
		}
		// Find out how many questions are available
		int numQ = getNumQuestions (stdtmp.clas);
		// Check if any questions remaining beyond what the student has already done
		if (stdtmp.score < numQ) {
			qRemaining = 1;
			readNextQ (stdtmp.clas, stdtmp.score, (char *)&squest, sizeof(squest));
		} else {
			qRemaining = 0;
			printf ("All questions solved\n");
		}

		cout << "Score: " << stdtmp.score << endl;
		if (qRemaining) {
			cout << "Question: " << squest.quest << endl;
			cout << "Place the main.cpp file in " << stdtmp.path << " before submitting.\n";
		}
		cout << "\n\t======= Menu: =======\n";
		if (qRemaining) {
			cout << "Submit: (s)\n";
		}
		cout << "Exit: (e)\n";
		cout << "Enter Command: ";
		cin >> com;
		system("cls");
		switch (com) {
			case 's':
				if (qRemaining) {
					res = submit(stdtmp.path, squest);
					if(res == 0) {
						stdtmp.score++;
						stdtmp.update(stdtmp);
					}
				}
				break;
			case 'e':
				return 0;
		}
		count++;
	} while (com != 'e');
	stdtmp.update(stdtmp);
	return 0;
}

int tchr_win(tchr tchtmp) {						//Teacher Window
	system("cls");
	cout << "Welcome, " << tchtmp.name << endl;
	int count = 0;
	char com = 'y';
	do {
		if (count > 0) {
			cout << "Press any key to continue...";
			getch();
			system("cls");
		}
		cout << "\t======= Menu: =======\n";
		cout << "Display Student Details: (d)\n";
		cout << "Add question: (a)\n";
		cout << "List questions: (l)\n";
		cout << "Remove last question: (r)\n";
		cout << "Exit: (e)\n";
		cout << "Enter Command: ";
		cin >> com;
		system("cls");
		switch (com) {
			case 'a':
				adquest(tchtmp.clas);
			break;
			case 'l':
				listQs(tchtmp.clas);
				cin.ignore();
			break;
			case 'd':
				dispstuds(tchtmp.clas);
			break;
			case 'r':
				removeLastQ(tchtmp.clas);
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
	snprintf(stat, 500, "g++ -o %s %s/main.cpp %s", COMP_FILE, tmpath, CFLAGS);
	res = system(stat);
	if(res > 1) {
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
		res = system(stat);
		if (res > 0) {
			cout << "Error executing\n";
			return -1;
		}
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

int dispstuds(char grade[4]) {		//Display Student Details
	ifstream ifile("std.dat", ios::binary);
	stud tmp;
	if(!ifile) {
		cout << "File open error\n";
		return -1;
	}
	cout << "Students in my Class: " << grade << endl;
	while(ifile.read((char*)&tmp, sizeof(stud))) {
		if(strcmpi(tmp.clas, grade) == 0) {
			cout << "Name: " << tmp.name << endl;
			cout << "\tUsername: " << tmp.uname << endl;
			cout << "\tScore: " << tmp.score << endl;
		}
		cout << endl;
	}
	cin.ignore();
	ifile.close();
	return 0;
}

int getNumQuestions (char *grade) {
	char fpath[100];
	snprintf(fpath, sizeof(fpath), "Assignments/%s.dat", grade);
	ifstream ifile(fpath, ios::binary);
	if(!ifile){
		cout << "Missing assignment file!\n Check path: " << fpath << endl;
	}
	// Find out how many questions are available
	ifile.seekg (0, ifile.end);
	int numQ = ifile.tellg()/sizeof(questc);
	ifile.close();
	return numQ;
}

int readNextQ (char *grade, int lastQDone, char *buf, int bufSize) {
	char fpath[100];
	snprintf(fpath, sizeof(fpath), "Assignments/%s.dat", grade);
	ifstream ifile(fpath, ios::binary);
	if(!ifile){
		cout << "Missing assignment file!\n Check path: " << fpath << endl;
	}
	// Read the next question
	ifile.seekg(lastQDone*sizeof(questc));
	ifile.read(buf, bufSize);
	ifile.close();
	return 0;
}

void listQs(char *grade) {
	questc squest;
	char fpath[100];
	int qNo = 0;
	snprintf(fpath, sizeof(fpath), "Assignments/%s.dat", grade);
	cout << "Total " << getNumQuestions(grade) << " questions\n";
	ifstream ifile(fpath, ios::binary);
	if(!ifile){
		cout << "Missing assignment file!\n Check path: " << fpath << endl;
		return;
	}
	while (1) {
		ifile.read((char *)&squest, sizeof(questc));
		if (ifile.eof())
			break;
		cout << "==== Question # " << qNo + 1 <<" =====\n";
		cout << "\tQuestion:  " << squest.quest <<"\n";
		cout << "\tTest Case: " << squest.tc <<"\n";
		cout << "\tAnswer:    " << squest.ans <<"\n";
		cout << "\n";
		qNo++;
	}
	ifile.close();
}

void removeLastQ(char *grade) {
	char fpath[100], tpath[100];
	questc squest;
	int	numCopied = 0;
	snprintf(fpath, 100, "Assignments/%s.dat", grade);
	snprintf(tpath, 100, "Assignments/%s_tmp.dat", grade);
	ifstream ifile(fpath, ios::binary);
	ofstream ofile(tpath, ios::binary);
	if(!ifile) {
		cout << "File open error\n";
		return;
	}

	ifile.seekg (0, ifile.end);
	int numQ = ifile.tellg()/sizeof(questc);
	ifile.seekg (0, ifile.beg);

	while(numCopied < numQ - 1) {
		ifile.read((char*)&squest, sizeof(questc));
		ofile.write((char*)&squest, sizeof(questc));
		numCopied++;
	}
	ifile.close();
	ofile.close();
	remove(fpath);
	rename(tpath, fpath);
}
