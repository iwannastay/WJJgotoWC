#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <cstring>
#include <io.h>
#include <windows.h> 
using namespace std;


#define MAX_FILE 10000
#define PATH 260

char File[MAX_FILE];


int Function[3][7] = {
	0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,
	0,0,0,0,0,0,0
};//-c -w -l -o -s -a -e 

string Source_File, Temp_File;
char Result_File[PATH] = "result.txt";
char Stop_File[PATH] = { 0 };

set<string> Stop_List;
map<char, int> link;



bool WriteFunction(fstream& _stream, int n, char** argv)
{
	if (2 == n && !strcmp("-x", argv[1]))
	{
		WinExec("WordCountUI.exe", SW_NORMAL);
		return false;
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
			Temp_File = Source_File = argv[i];
			/*_stream.open(Source_File);
			if (!_stream)
			{
				cout << "Fail to open the source file." << endl;
				return false;
			}*/
		}
	}
	return true;
}

bool LoadFile(fstream& _File, char* _file)
{
	_File.open(_file);
	if (!_File)
	{
		cout << "Fail to open the source file." << endl;
		return false;
	}
	_File.read(File, MAX_FILE);
	int num = _File.gcount();
	if (num == MAX_FILE)
	{
		cout << "The file size is out if range." << endl;
		return false;
	}
	Function[1][0] = num;
	return true;
}

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
		else if (i > 0 && (_File[i] == ' ' || _File[i] == ',' || _File[i - 1] == '\t'))
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

	for (int i = 0; i < 7; i++)
	{
		if (Function[0][i] == 1)
		{
			bool suc = GetSample(i, add);
			if (!suc) continue;
			str = Temp_File + ", " + add;
			_stream.write(str.c_str(), str.length());
			if (i == 5)
				_stream << Function[1][i - 2] << " " << Function[1][i - 1] << " " << Function[1][i] << endl;
			else
				_stream << Function[1][i] << endl;
		}

	}
	return true;
}

bool GetStopWords()
{
	char A[200] = { '\0' }, B[20] = { '\0' };
	int begin, end;
	fstream Stop_Stream(Stop_File);
	if (!Stop_Stream) return false;

	Stop_Stream.read(A, 200);
	int num = Stop_Stream.gcount();
	if (num == 200)
	{
		cout << "The file size is out if range." << endl;
		return false;
	}

	for (int i = 0; i < num; )
	{
		while (A[i++] == ' ');
		if (i >= num)break;
		begin = i - 1;
		while (A[i++] != ' '&&A[i - 1] != '\0');
		end = i - begin - 1;

		strncpy_s(B, A + begin, end);
		B[end] = '\0';
		Stop_List.insert(B);
	}

	return true;
}

void JudgeWords()
{
	char B[200] = { '\0' };

	int begin, end, num = Function[1][0] + Function[1][2] - 1;
	set<string>::iterator iter;

	for (int i = 0; i < num; )
	{
		while (File[i] == ' ' || File[i] == ',' || File[i] == '\n' || File[i] == '\t') i++;
		if (i >= num)break;
		begin = i;
		while ((File[i] != ' ' && File[i] != ',' && File[i] != '\n' && File[i] != '\t') && File[i] != '\0') i++;
		end = i - begin;

		strncpy_s(B, File + begin, end);
		B[end] = '\0';

		if (B[0] == 'G')
			int cc = 123;
		iter = Stop_List.find(B);
		if (iter != Stop_List.end())
			Function[1][1]--;
	}


}

void LineAnalysis(fstream& _stream)
{
	char A[200] = { '\0' };
	int flag = 0;
	int num = 0;
	//_stream.seekg(0, ios::beg);
	_stream.close();
	_stream.open(Temp_File);
	while (!_stream.eof())
	{
		_stream.getline(A, 200);
		num = _stream.gcount() - 1;
		if (0 >= num)
			Function[1][4] ++;
		else
		{
			for (int i = 0; i < num; i++)
			{
				if (A[i] != ' '&&A[i] != '/')
					if (++flag > 1) {
						Function[1][3]++; flag = 0; break;
					}
				if (A[i] == '/'&&A[i + 1] == '/')
				{
					Function[1][5]++; break;
				}
			}
		}
	}

}

bool SingleFile(char* _File, fstream& in_stream, fstream& out_stream)
{
	int suc = LoadFile(in_stream, _File);
	if (!suc) return 0;

	ScanFile(File);

	Calculate();

	if (Function[0][5])
	{
		LineAnalysis(in_stream);
	}

	if (Function[0][6])
	{
		GetStopWords();
		JudgeWords();
	}

	suc = OutputResult(out_stream);
	if (!suc) return 0;

	memset(*Function + 7, 0, 14 * sizeof(int));
	memset(File, 0, MAX_FILE * sizeof(char));

	in_stream.close();
}

void MultiFiles(const char * _dir, const char * file, fstream& in_stream, fstream& out_stream)
{
	char dir[100], dirNew[100];
	intptr_t handle;
	_finddata_t findData;

	strcpy_s(dir, _dir);
	strcat_s(dir, "\\");
	strcat_s(dir, "*.*");


	handle = _findfirst(dir, &findData);    // 查找目录中的第一个文件
	if (handle == -1)
	{
		cout << "Failed to find first file!\n";
		return;
	}

	do
	{
		if (strcmp(findData.name, ".") == 0
			|| strcmp(findData.name, "..") == 0);
		else if (findData.attrib & _A_SUBDIR)    // 是否是子目录并且不为"."或".."
		{
			strcpy_s(dirNew, _dir);
			strcat_s(dirNew, "\\");
			strcat_s(dirNew, findData.name);

			MultiFiles(dirNew, file, in_stream, out_stream);
		}
		else {
			strcpy_s(dirNew, _dir);
			strcat_s(dirNew, "\\");
			strcat_s(dirNew, findData.name);
			Temp_File = dirNew;
			if (file[0] == '*')
			{
				if (string(findData.name).find(string(file + 1)) != -1)
					SingleFile(dirNew, in_stream, out_stream);
			}
			else if (0 == strcmp(findData.name, file))
				SingleFile(dirNew, in_stream, out_stream);
		}
	} while (_findnext(handle, &findData) == 0);    // 查找目录中的下一个文件

	_findclose(handle);    // 关闭搜索句柄
}


int main(int argc, char *argv[])
{

	{
		link.insert(make_pair('c', 0));
		link.insert(make_pair('w', 1));
		link.insert(make_pair('l', 2));
		link.insert(make_pair('o', 3));
		link.insert(make_pair('s', 4));
		link.insert(make_pair('a', 5));
		link.insert(make_pair('e', 6));
	}

	fstream Input_File, Output_File;

	//int argcT = 2;
	//char* argvT[2] =
	//{
	//	"WJJgotoWC.exe",
	//	"-x"
	//};

	//int argcT = 11;
	//char* argvT[11] =
	//{
	//	"WJJgotoWC.exe",
	//	"-c",
	//	"-l",
	//	"-w",
	//	"-o",
	//	"Xresult.txt",
	//	"-e",
	//	"stopList.txt",
	//	"-a",
	//	"-s",
	//	"*.txt"
	//};
	//int suc = WriteFunction(Input_File, argcT, argvT);

	int suc = WriteFunction(Input_File, argc, argv);
	if (!suc) return 0;

	Output_File.open(Result_File, ios::out);
	if (!Output_File)
	{
		cout << "Fail to open the output file:" << Result_File << endl;
		return 0;
	}

	if (Function[0][4] == 1)
	{
		char dir[100] = { '\0' }, file_name[20] = { '\0' };
		int length = Source_File.length();
		int pos = Source_File.rfind("\\");
		if (pos != -1)
			strncpy_s(dir, Source_File.c_str(), pos);
		else dir[0] = '.';
		memcpy_s(file_name, 20, Source_File.c_str() + pos + 1, length - pos - 1);
		MultiFiles(dir, file_name, Input_File, Output_File);
	}
	else
	{
		char file_name[100] = { 0 };
		memcpy_s(file_name, sizeof(file_name), Source_File.c_str(), Source_File.length());
		SingleFile(file_name, Input_File, Output_File);
	}

	/*suc = LoadFile(Input_File, File);
	if (!suc) return 0;

	ScanFile(File);

	Calculate();

	if (Function[0][5])
	{
		LineAnalysis(Input_File);
	}

	if (Function[0][6])
	{
		GetStopWords();
		JudgeWords();
	}

	suc = OutputResult(Output_File);
	if (!suc) return 0;

	memset(Function + 7, 0, 14);

	Input_File.close();*/


	Output_File.close();
	return 0;
}
