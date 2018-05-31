#include "stdafx.h"
#include "FileOperations.h"

void saveToFile(std::string input_data, std::string file_path)
{
	std::ofstream out;
	out.open(file_path, std::ios::app);
	out << input_data;
	out.close();
}

int* loadFromFile(std::string file_name)
{
	std::ifstream file(file_name);
	int size, *arr, val;
	if (file.is_open())
	{
		file >> size;
		if (file.fail())
		{
			std::cout << "File error - READ SIZE" << std::endl;
			system("PAUSE");
		}
		else
		{
			arr = new int[size + 1];
			arr[0] = size;
			for (int i = 1; i < size + 1; i++)
			{
				file >> val;
				if (file.fail())
				{
					std::cout << "File error - READ DATA" << std::endl;
					system("PAUSE");
					break;
				}
				else
				{
					arr[i] = val;
				}
			}
			file.close();
			return arr;
		}
		file.close();
		return nullptr;
	}
	else
	{
		std::cout << "File error - OPEN" << std::endl;
		system("PAUSE");
		return nullptr;
	}


}
