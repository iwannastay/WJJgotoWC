#include <iostream>
#include <fstream>
#include <map>
using namespace std;


#define MAX_FILE 10000
#define PATH 256

char _Char;
char File[MAX_FILE];

int num_char = 0;
int num_word = 0;
int num_line = 0;

int Function[3][7] = {
	0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,
	0,0,0,0,0,0,0
};//-c -w -l -o -s -a -e 
string Source_File;
char Result_File[PATH] = "result.txt";
char Stop_File[PATH] = { 0 };

map<char, int> link;



bool WriteFunction(fstream& _stream, int n, char** argv)
{
	if (1 == n && !strcmp("-x", argv[0]))
	{
		//高级功能
	}
	map<char, int>::iterator iter;
	for (int i = 1; i < n; i++)
	{
		if ('-' == argv[i][0])
		{
			iter = link.find(argv[i][1]);
			if (iter != link.end())
			{
				int k = iter->second;
				Function[0][k] = 1;
				if (k == 3)
				{
					i++;
					memset(Result_File, 0, PATH);
					string str = argv[i];
					memcpy_s(Result_File, PATH, argv[i], str.length());
				}
				else if (k == 6)
				{
					i++;
					string str = argv[i];
					memcpy_s(Stop_File, PATH, argv[i], str.length());
				}
			}
			else
			{
				cout << "Unavailable parameter occurred." << endl;
				return false;
			}
		}
		else
		{
			Source_File = argv[i];
			_stream.open(Source_File);
			if (!_stream)
			{
				cout << "Fail to open the source file." << endl;
				return false;
			}
		}
	}
	return true;
}

bool LoadFile(fstream& _File, char* _file)
{
	_File.read(_file, MAX_FILE);
	int num = _File.gcount();
	if (num == MAX_FILE)
	{
		cout << "The file size is out if range." << endl;
		return false;
	}
	Function[1][0] = num;
	return true;
}

bool CountChar(fstream& _File, int *num)
{
	int count = _File.gcount();

	return true;
}

bool CountWord(fstream& _File, int *num)
{
	return true;
}
bool CountLine(fstream& _File, int *num)
{
	return true;
}

//typedef char* pChar;
void ScanFile(char* _File)
{
	int n = Function[1][0];
	int CountA = 0;//line
	int CountB = 0;//word
	for (int i = 0; i < n; i++)
	{
		if (_File[i] == '\n')
		{
			CountA++;
			if (i > 0 && (_File[i - 1] != ' ' && _File[i - 1] != ',' && _File[i - 1] != '\n'&& _File[i - 1] != '\t'))
				CountB++;
		}
		else if (i > 0 && (_File[i] == ' ' || _File[i] == ','|| _File[i - 1] != '\t'))
			if (_File[i - 1] != ' ' && _File[i - 1] != ',' && _File[i - 1] != '\n'&& _File[i - 1] != '\t')
				CountB++;

	}
	Function[1][1] = CountB;
	Function[1][2] = CountA;
}

void Calculate()
{
	int i = Function[1][0];
	Function[1][0] -= Function[1][2];
	if (Function[1][0] > 0 && (File[i - 1] != ' ' && File[i - 1] != ',' && File[i - 1] != '\n'))
		Function[1][1] ++;
	Function[1][2] ++;

}

bool GetSample(int n, string& _str)
{
	switch (n)
	{
	case 0:
		_str = "字符数：";
		break;
	case 1:
		_str = "单词数：";
		break;
	case 2:
		_str = "行数：";
		break;
	case 5:
		_str = "代码行/空行/注释行：";
		break;
	default:
		return false;
		break;
	}
	return true;
}

bool OutputResult(fstream& _stream)
{
	string str, add;
	_stream.open(Result_File);
	if (!_stream)
	{
		cout << "Fail to open the output file:"<< Result_File << endl;
		return false;
	}
	for (int i = 0; i < 7; i++)
	{
		if (Function[0][i] == 1)
		{
			bool suc = GetSample(i, add);
			if (!suc) continue;
			str = Source_File + ", " + add;
			_stream.write(str.c_str(), str.length());
			if (i == 5)
				_stream << Function[1][i - 2] << Function[1][i - 1] << Function[1][i] << endl;
			else
				_stream << Function[1][i] << endl;
		}

	}
	return true;
}




int main(int argc, char *argv[])
{
	link.insert(make_pair('c', 0));
	link.insert(make_pair('w', 1));
	link.insert(make_pair('l', 2));
	link.insert(make_pair('o', 3));
	link.insert(make_pair('s', 4));
	link.insert(make_pair('a', 5));
	link.insert(make_pair('e', 6));


	fstream Input_File, Output_File;


	int argcT = 7;
	char* argvT[7] =
	{
		"WJJgotoWC.exe",
		"-c",
		"-l",
		"-w",
		"-o",
		"Xresult.txt",
		"aaa.txt"
	};

	//int suc = WriteFunction(Input_File, argcT, argvT);
	int suc = WriteFunction(Input_File, argc, argv);
	if (!suc) return 0;

	suc = LoadFile(Input_File, File);
	if (!suc) return 0;

	ScanFile(File);

	Calculate();

	suc = OutputResult(Output_File);
	if (!suc) return 0;




	Input_File.close();
	Output_File.close();
	return 0;
}
