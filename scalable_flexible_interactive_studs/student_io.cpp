#include "student_io.h"



student_io::student_io()
{
	memb_id = 0;
}

void student_io::feed_db(std::vector<std::string> *stud_info)
{
	ofs.open("data_temp.txt");
	if (ofs.is_open())
	{
		for (size_t i = 0; i < stud_info->size(); ++i)
		{
			ofs << stud_info->at(i) << "  ";
		}
		ofs << '\n';
	}
	else
	{
		std::cout << "$Error! File could not open" << std::endl;
	}
	ofs.close();
}
string  student_io::search_db(std::string search_key)
{
	std::string line, return_string;
	try
	{
		ifs.open("student_data.txt");
		int pos = 0;
		if (ifs.is_open())
		{
			while (getline(ifs, line))
			{
				pos = line.find(search_key, ++pos);
				if (pos != std::string::npos)
				{
					return_string = line;
				}
				else
				{
					continue;
				}
			}
		}
		else
		{
			return_string = "#Error!_ search key provided matches none";
		}
		ifs.close();
	}
	catch (std::exception &e)
	{
		return_string = e.what();
	}
	return return_string;
}
void student_io::delete_line(std::string del)
{
	std::string line;
	_fs.open("student_data.txt");
	if (ofs.is_open())
	{
		while (getline(_fs, line))
		{
			line.replace(line.find(del), del.length(), "");
			_fs << line << '\n';
		}
	}
	else
	{
		std::cout << "#Error!_ File could not open for action" << std::endl;
	}
	_fs.close();
}

std::vector<std::string> student_io::disp_db()
{
	ifs.open("student_data.txt");
	std::string line;
	std::vector<std::string> total_data;
	if (ifs.is_open())
	{
		while (getline(ifs, line))
		{
			total_data.push_back(line);
		}
	}
	else
	{
		total_data.push_back("#Error_ File could not open for reading ");
	}
	ifs.close();
	return total_data;
}
bool student_io::transfer_data()
{
	std::string line;
	bool flag = true;
	try
	{
		_fs.open("data_temp.txt");
		ofs.open("student_data.txt",std::ios::app);
		if (_fs.is_open() && ofs.is_open())
		{
			while (getline(_fs, line))
			{
				ofs << line << '\n';
			}
			_fs.close();
			unsigned int i = remove("data_temp.txt");
			if (i == 0)
			{
				flag = true;
			}
			else
			{
				flag = false;
			}
		}
		else
		{
			std::cout << "$Error_ file could not open" << std::endl;
		}
	}
	catch(std::exception &e)
	{
		std::cout << "Error_ " << e.what() << std::endl;
	}
	ofs.close();
	return flag;
}
student_io::~student_io()
{
	_fs.close();
	ofs.close();
	ifs.close();
}
