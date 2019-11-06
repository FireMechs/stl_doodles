#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <chrono>
#include <vector>
#include <fstream>
#include <Windows.h>
#include <thread>
#include <algorithm>

using namespace std;

/* constructor*/
class student_io
{
private:
	unsigned int memb_id;
	/*finally hoping for this*/
	std::ofstream ofs;
	std::ifstream ifs;
	std::fstream  _fs;
public:
	student_io();
	~student_io();
	void feed_db(std::vector<std::string> *stud_info);
	std::string  search_db(std::string );
	void delete_line(std::string);
	std::vector<std::string>  disp_db();
	bool transfer_data();
};

