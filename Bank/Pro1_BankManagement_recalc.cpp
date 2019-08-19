#include "pch.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <fstream>
#include <chrono>
#include <ctime>

using namespace std;

inline void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

class Bank_sys
{
private:
public:
	/*admin - actions in class admin*/
	void admin();
	/*client*/
	void client();

	void _Quit();
	void log_type(string _type, unsigned int _id)
	{
		time_t result = time(NULL);
		char time_val[26];
		ctime_s(time_val, sizeof time_val, &result);
		ofstream ofs("trans_log.txt", ios::ios_base::app);
		if (ofs.is_open())
		{
			ofs << _id << "  " << _type << "   "<< string(time_val) << std::endl;
		}
		else
		{
			std::cout << "_Error!, Could not record the log..." << std::endl;
		}
		ofs.close();
	}
};
/* class admin */

class admin_cl
{
private:
	std::vector<unsigned int > acc_no;
public:
	admin_cl()
	{
		ifstream tempfile("temp.txt");
		if (tempfile.is_open())
		{
			unsigned int  temp_val = 9876543;
			tempfile >> temp_val;
			acc_no.push_back(temp_val);
		}
		else
		{
			std::cout << "__Error, agreeing with initial run..." << std::endl;
		}
	}
	/*admin implementations */
	void add_client();
	void del_client();
	void view_logs();
};
/*class client */

class client_cl
{
private:
public:
	void withdraw();
	void transfer();
	void deposit();
};
inline void edit(unsigned int &stat_cap, unsigned int &dorw_amount, int trans_type )
{
	if ( trans_type == 87)
	{
		stat_cap = stat_cap - dorw_amount;
	}
	if (trans_type == 68)
	{
		stat_cap = stat_cap + dorw_amount;
	}
	else
	{
		gotoxy(40, 17); std::cout << " Values not updated " << std::endl;
	}
}

/* structure to hold user's info */
typedef struct user
{
	string name;
	unsigned int id;
	unsigned int stat_cap;
} str_usr;

unsigned int get_id()
{
	unsigned int passed_id;
	gotoxy(40, 10); std::cout << " Enter your id : ";
	cin >> passed_id;
	return passed_id;
}

void transfer_depo(unsigned int);

int main()
{
	Bank_sys bank_main;
	char ch, cp;
	gotoxy(40, 10); std::cout << " Bank Management system " << std::endl;
	gotoxy(40, 12); std::cout << " Developed by Me  " << std::endl;
	gotoxy(40, 16); std::cout << " Please enter any key to continue  ...";
	ch = _getch();
	if (ch < 255)
	{
		system("CLS");
	}
LOG:
	gotoxy(40, 8); std::cout << " Log In" << std::endl;
	gotoxy(40, 18); std::cout << " Enter a for admin and c for user/client ... ";
	cp = _getch();
	if (cp == 'a' || cp == 'A')
	{
		bank_main.admin();
	}
	else if (cp == 'c' || cp == 'C')
	{
		bank_main.client();
	}
	else
	{
		gotoxy(43, 18); std::cout << "Wrong character !" << std::endl;
		goto LOG;
	}
}
/*admin implementations */
void Bank_sys::admin()
{
ADMIN_ACT:
	admin_cl admin_pr_1;
	Bank_sys quit_fn;
	system("CLS");
	gotoxy(43, 4); std::cout << " Actions " << std::endl;
	gotoxy(40, 6); std::cout << "1. Add a user " << std::endl;
	gotoxy(40, 8); std::cout << "2. Delete a user " << std::endl;
	gotoxy(40, 10); std::cout << "3. View all the transaction logs " << std::endl;
	gotoxy(40, 12); std::cout << "4. Quit " << std::endl;
	gotoxy(40, 13); std::cout << " Choose action ... ";
	int choice;
	std::cin >> choice;

	switch (choice)
	{
	case 1:
		admin_pr_1.add_client();
		break;
	case 2:
		admin_pr_1.del_client();
		break;
	case 3:
		admin_pr_1.view_logs();
		break;
	case 4:
		quit_fn._Quit();
		break;
	default:
		gotoxy(43, 14); std::cout << " Unacceptable choice !" << std::endl;
		goto ADMIN_ACT;
		break;
	}

}

void admin_cl::add_client()
{
USER:
	system("CLS");
	admin_cl _cltAdd;
	Bank_sys els;
	ofstream ofs("users.txt", ios::ios_base::app);
	if (ofs.is_open())
	{
		str_usr usr;
		gotoxy(40, 12); std::cout << " Client id : ";
		std::cin >> usr.id;
		cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		gotoxy(40, 14); std::cout << " Client name: ";
		getline(cin, usr.name);
		unsigned int last_acc = _cltAdd.acc_no.back();
		unsigned int new_acc = ++last_acc;
		els.log_type("Add_client", usr.id);
		fstream fs("temp.txt", ios::ios_base::in | ios_base::out);
		if (fs.is_open())
		{
			fs << new_acc;
		}
		_cltAdd.acc_no.push_back(new_acc);
		gotoxy(40, 16); std::cout << "User Account number : " << new_acc << std::endl;
		gotoxy(40, 18); std::cout << " user's stat_cap: ";
		std::cin >> usr.stat_cap;

		ofs << usr.id << "  " << usr.name << "  " << new_acc << "  " << usr.stat_cap << "\n";
		system("CLS");
		gotoxy(40, 12); std::cout << "Thank you , User's info has been saved" << std::endl;
		char response;
		gotoxy(40, 14); std::cout << " Wanna give another user (y/n)...";
		response = _getch();
		if (response == 'Y' || response == 'y')
		{
			goto USER;
		}
		else
		{
			els.admin();
		}
	}
	else
	{
		gotoxy(40, 10); std::cout << "_Error!, Accessing client initial data " << std::endl;
	}
	ofs.close();
}
void admin_cl::del_client()
{
	Bank_sys bank_delcl;
	DEL:
	system("CLS");
	ifstream fs("users.txt");
	ofstream ofs_1("users1.txt");
	unsigned int stat_cap, id, acc_no, got_id;
	string fname, lname;
	if (ofs_1.is_open())
	{
		if (fs.is_open())
		{
			got_id = get_id();
			bank_delcl.log_type("Del_client", got_id);
			while (fs >> id >> fname >> lname >> acc_no >> stat_cap)
			{
				if (id == got_id)
				{
					gotoxy(40, 14); std::cout << id << "  " << fname + " " + lname << "  " << acc_no << "  " << stat_cap << std::endl;
					gotoxy(40, 18); std::cout << " Client Deleted Successfully" << std::endl;
				}
				else
				{
					ofs_1 << id << "  " << fname + "  " + lname << "   " << acc_no << "   " << stat_cap << std::endl;
				}
			}
		}
		else
		{
			perror("_Error! , Accessing client db failed ");
		}
	}
	else
	{
		perror("_Error!, Temporary memory denied");
	}
	fs.close();
	ofs_1.close();
	unsigned int status = remove("users.txt");
	if (status == 0)
	{
		gotoxy(40, 20); std::cout << "Records updated successfully" << std::endl;
	}
	else
	{
		gotoxy(40, 20); std::cout << "_Error! , Updating Records failed ." << std::endl;
	}
	rename("users1.txt", "users.txt");
	gotoxy(40, 22); std::cout << "Delete another client(y,n)?  ";
	char ch = _getch();
	if (ch == 'y' || ch == 'Y')
	{
		goto DEL;
	}
	else
	{
		bank_delcl.admin();
	}
	
}
void admin_cl::view_logs()
{
	system("CLS");
	Bank_sys bank_vls;
	ifstream ifs("trans_log.txt");
	string line;
	if (ifs.is_open())
	{
		while (getline(ifs, line))
		{
			std::cout << line << std::endl;
		}
	}
	else
	{
		std::cout << " _Error ! , Could not fetch the trans_logs..." << std::endl;
	}
	ifs.close();
	std::cout << " Go Back to the admin menu (y/n)... ";
	char chw = _getch();
	if (chw == 'y' || chw == 'y')
	{
		bank_vls.admin();
	}
	else
	{
		bank_vls._Quit();
	}
}
/*user implementation*/
void Bank_sys::client()
{
CLIENT_ACT:
	client_cl client_pr_1;
	Bank_sys bankMain_cl;
	system("CLS");
	gotoxy(43, 4); std::cout << " Actions " << std::endl;
	gotoxy(40, 6); std::cout << "1. Deposit  " << std::endl;
	gotoxy(40, 8); std::cout << "2. Withdraw " << std::endl;
	gotoxy(40, 10); std::cout << "3. Transfer Amount " << std::endl;
	gotoxy(40, 12); std::cout << "4. Quit " << std::endl;
	gotoxy(40, 13); std::cout << " Choose action ... ";
	int resp = 0;
	cin >> resp;
	switch (resp)
	{
	case 1:
		client_pr_1.deposit();
		break;
	case 2:
		client_pr_1.withdraw();
		break;
	case 3:
		client_pr_1.transfer();
		break;
	case 4:
	    bankMain_cl._Quit();
		break;
	default:
		gotoxy(43, 14); std::cout << " Unacceptable choice !" << std::endl;
		goto CLIENT_ACT;
		break;
	}
}

void client_cl::deposit()
{
	DEPO:
	system("CLS");
	   ifstream fs("users.txt");
	   Bank_sys bank_cl;
		ofstream ofs_1("users1.txt");
	unsigned int stat_cap, id, acc_no, got_id,depo_amount;
	string fname, lname;
	if (ofs_1.is_open())
	{
		if (fs.is_open())
		{
			got_id = get_id();
			bank_cl.log_type("deposit", got_id);
			while (fs >> id >> fname >> lname >> acc_no >> stat_cap)
			{
				if (id == got_id)
				{
					gotoxy(40, 14); std::cout << id << "  " << fname + " " + lname << "  " << acc_no << "  " << stat_cap << std::endl;
					gotoxy(40, 16); std::cout << "Enter amount to deposit : ";
					cin >> depo_amount;
					edit(stat_cap, depo_amount,68);
					ofs_1 << id << "  " << fname + "  " + lname << "  " << acc_no << "  " << stat_cap << std::endl;
					gotoxy(40, 18); std::cout << " Deposit successful" << std::endl;
				}
				else
				{
					ofs_1 << id << "  " << fname + "  " + lname << "   " << acc_no << "   " << stat_cap << std::endl;
				}
			}
		}
		else
		{
			perror("_Error! , Accessing client db failed ");
		}
	}
	else
	{
		perror("_Error!, Temporary memory denied");
	}
	fs.close();
	ofs_1.close();
	unsigned int status = remove("users.txt");
	if (status == 0)
	{
		gotoxy(40, 20); std::cout << "Records updated successfully" << std::endl;
	}
	else
	{
		gotoxy(40, 20); std::cout << "_Error! , Updating Records failed ." << std::endl;
	}
	rename("users1.txt", "users.txt");
	gotoxy(40, 22); std::cout << "Another deposit?(y/n)...";
	char chr = _getch();
	if (chr == 'y' || chr == 'Y')
	{
		goto DEPO;
	}
	else
	{
		bank_cl.client();
	}
}

void client_cl::withdraw()
{
	WITHD:
	system("CLS");
	Bank_sys bank_cl_w;
	ifstream fs("users.txt");
	ofstream ofs_1("users1.txt");
	unsigned int stat_cap, id, acc_no, got_id,withd_amount;
	string fname, lname;
	if (ofs_1.is_open())
	{
		if (fs.is_open())
		{
			got_id = get_id();
			bank_cl_w.log_type("Withdrawal", got_id);
			while (fs >> id >> fname >> lname >> acc_no >> stat_cap)
			{
				if (id == got_id)
				{
					gotoxy(40, 14); std::cout << id << "  " << fname + " " + lname << "  " << acc_no << "  " << stat_cap << std::endl;
					gotoxy(40, 16); std::cout << " Enter amount to withdraw: ";
					cin >> withd_amount;
					if (withd_amount <= stat_cap)
					{
						edit(stat_cap , withd_amount , 87);
					}
					else
					{
						gotoxy(40, 18); std::cout << "Insufficient funds" << std::endl;
					}
					ofs_1 << id << "  " << fname + "  " + lname << "  " << acc_no << "  " << stat_cap << std::endl;
				}
				else
				{
					ofs_1 << id << "  " << fname + "  " + lname << "   " << acc_no << "   " << stat_cap << std::endl;
				}
			}
		}
		else
		{
			perror("_Error! , Accessing client db failed ");
		}
	}
	else
	{
		perror("_Error!, Temporary memory denied");
	}
	fs.close();
	ofs_1.close();
	unsigned int status = remove("users.txt");
	if (status == 0)
	{
		gotoxy(40, 18); std::cout << " Records updated successfully" << std::endl;
	}
	else
	{
		gotoxy(40, 18); std::cout << " _Error!, Updating records failed " << std::endl;
	}
	rename("users1.txt", "users.txt");
	gotoxy(40, 20); std::cout << "Another Withdrawal?(y/n)...";
	char chr = _getch();
	if (chr == 'y' || chr == 'Y')
	{
		goto WITHD;
	}
	else
	{
		bank_cl_w.client();
	}
}

void client_cl::transfer()
{
	TRAN:
	system("CLS");
	Bank_sys bank_cl_2;
	ifstream fs("users.txt");
	ofstream ofs_1("users1.txt");
	unsigned int stat_cap, id, acc_no, drawer_id ,trans_amount;
	string fname, lname;
	if (ofs_1.is_open())
	{
		if (fs.is_open())
		{
			drawer_id = get_id();
			bank_cl_2.log_type("Transfer", drawer_id);
			while (fs >> id >> fname >> lname >> acc_no >> stat_cap)
			{
				if (id == drawer_id)
				{
					gotoxy(40, 12); std::cout << id << "  " << fname + " " + lname << "  " << acc_no << "  " << stat_cap << std::endl;
					gotoxy(40, 14); std::cout << "Enter the amount to transfer: ";
					cin >> trans_amount;
					if (trans_amount <= stat_cap)
					{
						edit(stat_cap , trans_amount, 87);
					}
					else
					{
						gotoxy(40, 15); std::cout << " Insufficient funds" << std::endl;
					}
					ofs_1 << id << "  " << fname + "  " + lname << "  " << acc_no << "  " << stat_cap << std::endl;
					transfer_depo(trans_amount);
				}
				else
				{
					ofs_1 << id << "  " << fname + "  " + lname << "   " << acc_no << "   " << stat_cap << std::endl;
				}
			}
		}
		else
		{
			perror("_Error! , Accessing client db failed ");
		}
	}
	else
	{
		perror("_Error!, Temporary memory denied");
	}
	fs.close();
	ofs_1.close();
	unsigned int status = remove("users.txt");
	if (status == 0)
	{
		gotoxy(40, 22); std::cout << " Records updated successfully" << std::endl;
	}
	else
	{
		gotoxy(40, 22); std::cout << "_Error! Failed to Update records  " << std::endl;
	}
	rename("users1.txt", "users.txt");
	gotoxy(40, 23); std::cout << "Another Transfer?(y/n)...";
	char chr = _getch();
	if (chr == 'y' || chr == 'Y')
	{
		goto TRAN;
	}
	else
	{
		bank_cl_2.client();
	}
}
/*_Quit function */
void Bank_sys::_Quit()
{
	return;
}/*transfer DEPO */
void transfer_depo(unsigned int trans_amount)
{
	ifstream fs("users.txt");
	ofstream ofs_1("users1.txt");
	unsigned int stat_cap, id, acc_no, receiver_id;
	string fname, lname;
	if (ofs_1.is_open())
	{
		if (fs.is_open())
		{
			gotoxy(40, 16); std::cout << " Enter receiver id or Acc_no: ";
			cin >> receiver_id;
			while (fs >> id >> fname >> lname >> acc_no >> stat_cap)
			{
				if (id == receiver_id || acc_no == receiver_id)
				{
					gotoxy(40, 18); std::cout <<"Receiver DET: "<< id << "  " << fname + " " + lname << "  " << acc_no << std::endl;
					edit(stat_cap, trans_amount, 68);
					ofs_1 << id << "  " << fname + "  " + lname << "  " << acc_no << "  " << stat_cap << std::endl;
					gotoxy(40, 20); std::cout << "Amount Transferred successfully " << std::endl;
				}
				else
				{
					ofs_1 << id << "  " << fname + "  " + lname << "   " << acc_no << "   " << stat_cap << std::endl;
				}
			}
		}
		else
		{
			std::cout << " File could not open for transfer amount " << std::endl;
		}
	}
	else
	{
		std::cout << " File could not reopen for the transfer " << std::endl;
	}
}
