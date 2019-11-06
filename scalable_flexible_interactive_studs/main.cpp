#include "student_io.h"


inline void gotoxy(const int x, const int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


int main()
{
	int choice;
	std::string search_key;
	bool flag_main = true;
	gotoxy(35, 10); std::cout << "Simple student details Capture" << std::endl;
	gotoxy(35, 11); std::cout << "Build by  FireMechs{Tech Cider}" << std::endl;
	gotoxy(35, 13); std::cout << "Press any key to continue...";
	student_io *io = new student_io();
	_getch();

BA:
	system("CLS");
	std::vector<std::string> display_data = io->disp_db();
	for (size_t i = 0; i < display_data.size(); ++i)
	{
		gotoxy(33, (6 + i)); std::cout << display_data.at(i) << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(800));
	system("CLS");
	gotoxy(37, 8); std::cout << " 1. Search  existing database " << std::endl;
	gotoxy(37, 10); std::cout << " 2. Add a  new record " << std::endl;
	gotoxy(37, 12); std::cout << " 3 . Delete existing entry" << std::endl;
	gotoxy(37, 14); std::cout << " 4 . Quit" << std::endl;
	gotoxy(37, 16); std::cout << "			....";
	cin >> choice;
	system("CLS");

	std::vector<std::string> loop_strings = { "one :","two: ","three: " ,"four: ","five:  " ,"six:  " ,"seven: ","eight: " ,"nine: " };
	std::vector<std::string> input_strings;
	std::string returned_string;
	char ch = 'y';
	size_t i = 0;
	switch (choice)
	{
	case 2:
		gotoxy(20, 10); std::cout << "Pass one_word parameters/column Heads:  " << std::endl;

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		/*looping input animation*/
		while (i <= loop_strings.size() && ch == 'y')
		{
			std::string temp_str;
			gotoxy(20, (12+i)); std::cout << loop_strings[i];
			cin >> temp_str;
			input_strings.push_back(temp_str);
			gotoxy(40,(12+i)); std::cout <<"Another parameter(y/n): ";
			cin >> ch;
			i++;
		}

		do {
			system("CLS");

			/* Real input loop*/
			std::vector<std::string> fin_data;
			std::cin.ignore(256, '\n');
			for (size_t i = 0; i < input_strings.size(); ++i)
			{
				std::string temp_name;
				gotoxy(20,(6 + i)); cout << "Student  " + input_strings[i] << ": ";
				getline(cin, temp_name);
				fin_data.push_back(temp_name);
			}
			io->feed_db(&fin_data);
			flag_main = io->transfer_data();
			if (flag_main == true)
			{
				puts("Another student(y/n)?:  ");
				ch = getchar();
			}
			else
			{
				exit(-1);
			}
		} while (ch == 'y' || ch == 'Y');
		goto BA;
		break;
	case 1:
		gotoxy(35, 10); std::cout << "Enter any search key : ";
		cin >> search_key;
	    returned_string = io->search_db(search_key);
		gotoxy(35, 12); std::cout << returned_string << std::endl;
		_getch();
		goto BA;
		break;
	case 3:
		gotoxy(35, 10); std::cout << "Enter any search key : ";
		cin >> search_key;
		returned_string = io->search_db(search_key);
		gotoxy(35, 12); std::cout << returned_string << std::endl;
		io->delete_line(returned_string);

		gotoxy(38, 13); std::cout << "Updating" << std::endl;
		for (int i = 0; i < 4; i++)
		{
			gotoxy((36 + i), 15); std::cout << ".";
			std::this_thread::sleep_for(std::chrono::milliseconds(300));
		}
		flag_main = io->transfer_data();
		if (flag_main == true)
		{
			goto BA;
		}
		else
		{
			exit(-1);
		}
		break;
	case 4:
		io->~student_io();
		exit(-1);
		break;
	default:
		std::cout << "Option not available" << std::endl;
		std::cout << "try again ..." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		goto BA;
		break;
	}

	return 0;
}