#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iterator>
#include <algorithm>
#include <functional>
#include <vector>
#include <cstdio>

int main(int argc, char ** argv)
{
	std::map<char, char> charmap;
	charmap.insert(std::make_pair('á', 'a'));
	charmap.insert(std::make_pair('Á', 'A'));
	charmap.insert(std::make_pair('č', 'c'));
	charmap.insert(std::make_pair('Č', 'C'));
	charmap.insert(std::make_pair('ď', 'd'));
	charmap.insert(std::make_pair('Ď', 'D'));
	charmap.insert(std::make_pair('ě', 'e'));
	charmap.insert(std::make_pair('Ě', 'E'));
	charmap.insert(std::make_pair('é', 'e'));
	charmap.insert(std::make_pair('É', 'E'));
	charmap.insert(std::make_pair('í', 'i'));
	charmap.insert(std::make_pair('Í', 'I'));
	charmap.insert(std::make_pair('ó', 'o'));
	charmap.insert(std::make_pair('Ó', 'O'));
	charmap.insert(std::make_pair('ř', 'r'));
	charmap.insert(std::make_pair('Ř', 'R'));
	charmap.insert(std::make_pair('š', 's'));
	charmap.insert(std::make_pair('Š', 'S'));
	charmap.insert(std::make_pair('ť', 't'));
	charmap.insert(std::make_pair('Ť', 'T'));
	charmap.insert(std::make_pair('ú', 'u'));
	charmap.insert(std::make_pair('Ú', 'U'));
	charmap.insert(std::make_pair('ů', 'u'));
	charmap.insert(std::make_pair('Ů', 'U'));
	charmap.insert(std::make_pair('ý', 'y'));
	charmap.insert(std::make_pair('Ý', 'Y'));
	charmap.insert(std::make_pair('ž', 'z'));
	charmap.insert(std::make_pair('Ž', 'Z'));

	std::string tempname, tmp;
	std::map<char, char>::iterator itr;
	std::size_t found;

	std::fstream fs;
	std::vector<char> data;
	size_t fsize;
	try
	{
		for (unsigned int i = 1; i < argc; i++)
		{// argv is char filenames, then - make them string
			tempname = argv[i];
			fs.open(tempname.c_str(), std::ios::binary | std::ios::in);
			fs.seekg(0, fs.end);
			fsize = fs.tellg();
			fs.seekg(0, fs.beg);
			data.resize(fsize);
			fs.read(&data[0], fsize);
			fs.close();
			std::remove(tempname.c_str());
			for (itr = charmap.begin(); itr != charmap.end(); itr++)
			{
				found = tempname.find_first_of(itr->first);
				while (found != std::string::npos)
				{
					tmp = itr->first;
					tempname.erase(found, tmp.length());
					tmp = itr->second;
					tempname.insert(found, tmp);
					found = tempname.find_first_of(itr->first, found + 1);
				}
			}
			
			fs.open(tempname.c_str(), std::ios::binary | std::ios::out);
			fs.write((char*)&data[0], data.size());
			fs.close();
		}
	}
	catch (std::string *e)
	{
		std::cout << *e << std::endl;
	}
	catch (...)
	{
		std::cout << "unk error" << std::endl;
	}
	return 0;
}
