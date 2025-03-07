#include <iostream>
#include <fstream>
using namespace std;

int getCountCols(const char* fileName) {
	ifstream file(fileName);
	if (!file.is_open())
	{
		return 0;
	}
	int count = 0;
	while (!file.eof())
	{
		int curr;
		file >> curr;
		count++;
		if (file.get() == '|')
		{
			file.close();
			return count;
		}
	}
	file.close();
	return count;
}

int getCountRows(const char* fileName) {
	ifstream file(fileName);
	if (!file.is_open())
	{
		return 0;
	}
	int count = 1;
	while (!file.eof())
	{
		int curr;
		file >> curr;
		if (file.get() == '|')
		{
			count++;
		}
	}
	file.close();
	return count;
}

int calculateElement(int i, int j, char* fileName1, char* fileName2) {
	ifstream file1(fileName1);
	ifstream file2(fileName2);
	if (!file1.is_open() || !file2.is_open())
	{
		return 0;
	}
	int count = 0;
	while (!file1.eof() && count != i)
	{
		int curr;
		file1 >> curr;
		if (file1.get() == '|')
		{
			count++;
		}
	}
	int sum = 0;
	while (!file1.eof())
	{
		int curr1;
		file1 >> curr1;

		count = 0;
		while (!file2.eof() && count != j)
		{
			int curr;
			file2 >> curr;
			if (file2.get() == ',')
			{
				count++;
			}
		}
		int curr2;
		file2 >> curr2;
		sum += curr1 * curr2;
		if (file2.get() != '|') {
			while (!file2.eof())
			{
				int curr;
				file2 >> curr;
				if (file2.get() == '|')
				{
					break;
				}
			}
		}

		if (file1.get() == '|')
		{
			file1.close();
			file2.close();
			return sum;
		}
	}
	file1.close();
	file2.close();
	return sum;
	
}

int main() {
	char fileName1[] = "fst.txt";
	char fileName2[] = "snd.txt";
	char resultName[] = "result.txt";
	if (getCountCols(fileName1) != getCountRows(fileName2))
	{
		return 0;
	}

	ofstream result(resultName);
	if (!result.is_open())
	{
		return 0;
	}

	for (size_t i = 0; i < getCountRows(fileName1); i++)
	{
		for (size_t j = 0; j < getCountCols(fileName2); j++)
		{
			result << calculateElement(i, j, fileName1, fileName2);
			if (j < getCountCols(fileName2)-1)
			{
				result << ",";
			}
		}
		if (i < getCountRows(fileName2) - 1)
		{
			result << "|";
		}
	}

	result.close();
}
