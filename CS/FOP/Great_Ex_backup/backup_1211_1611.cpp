#include <iostream>
#include <fstream>
#include <cstring>
#include <string.h>
#include <cmath>
#include <iomanip>
using namespace std;

#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a < b) ? a : b)
#define GAP 15

int *input;
int s_input;
int p_input = 0;
int *output;
int s_output;
int p_output = 0;
int *Space;
int s_Space;
bool *_Space;
int currentBox;
bool current_Box;
string *operation;
int s_operation;

int level;
int maxLevel = 0;
int N; //  输入的命令数量
string *userInput;
int *nums;

int *userOutput;
int s_userOutput = 0;
int p_userOutput = 0;

int instruction;
int op; ///////////////////////////////

int maxSize_in;
bool stepTag = false;
bool gameFinish = false;
bool have_error;

void blank(int n)
{
	for (int i = 0; i < n; i++)
		cout << ' ';
}
void line(int n)
{
	for (int i = 0; i < n; i++)
		cout << '-';
	cout << endl;
}
void _line(int n)
{
	for (int i = 0; i < n; i++)
		cout << '-';
}
void init()
{
	p_input = 0;
	p_output = 0;
	maxLevel = 0;
	s_userOutput = 0;
	p_userOutput = 0;
	maxSize_in = 2;
}
void release()
{
	delete[] input;
	delete[] output;
	delete[] Space;
	delete[] _Space;
	delete[] operation;
	delete[] userInput;
	delete[] userOutput;
}
void reset()
{
	ifstream level("level.txt");
	int levelNum = 0;
	while (!level.eof())
	{
		char tmp[1000] = {0};
		level.getline(tmp, 1000);
		levelNum++;
	}
	levelNum--;
	level.close();
	ofstream reLevel("level.txt");
	for (int i = 0; i < levelNum; i++)
		reLevel << "Level " << i + 1 << " unfinished" << endl;
}
void getLevelInfo()
{
	ifstream lv("level.txt");
	line(30);
	if (!lv)
	{
		ofstream newLv("level.txt");
		for (int i = 0; i < 3; i++)
		{
			newLv << "Level " << i + 1 << " unfinished" << endl;
			cout << "Level " << i + 1 << " unfinished" << endl;
		}
		maxLevel = 3;
		newLv.close();
	}
	else
	{
		maxLevel = 0;
		char tmp[1000] = {0};
		while (!lv.eof())
		{
			lv.getline(tmp, 1000);
			if (tmp[0] == 'L')
				cout << tmp << endl;
			maxLevel++;
		}
		line(30);
		maxLevel--;
		lv.close();
	}
}
void getCmd(bool &gameTag)
{
	string cmd;
	while (1)
	{
		cout << "Please enter you command.(continue/quit/reset)" << endl;
		cin >> cmd;
		line(30);
		if (cmd == "continue" || cmd == "quit")
			break;
		else if (cmd == "reset")
		{
			reset();
			cout << "reset complete." << endl;
			getLevelInfo();
		}
		else
			cout << "Command error." << endl;
	}
	if (cmd == "quit")
		gameTag = false;
	if (cmd == "continue")
		while (1)
		{
			string tmp;
			cout << "Please enter your simulation mode(step/continue)" << endl;
			cin >> tmp;
			line(30);
			if (tmp == "step" || tmp == "continue")
			{
				(tmp == "step") ? stepTag = true : stepTag = false;
				break;
			}
			else
				cout << "Simulation mode error." << endl;
		}
}
void print_level()
{
	line(30);
	cout << "Level " << level << endl;
	cout << "Input: ";
	for (int i = 0; i < s_input; i++)
		cout << input[i] << ' ';
	cout << endl;
	cout << "Output: ";
	for (int i = 0; i < s_output; i++)
		cout
			<< output[i] << ' ';
	cout << endl;
	cout << "Space: " << s_Space << endl;
	cout << "cmdEnable: ";
	for (int i = 0; i < s_operation; i++)
		cout << operation[i] << ' ';
	cout << endl;
	line(30);
}
bool loadLevel()
{
	char levelName[] = "level_info_ .txt";
	levelName[11] = '0' + level;
	ifstream curLevel(levelName);
	if (!curLevel)
	{
		cout << "Level " << level << " does not exist." << endl;
		return false;
	}
	else
	{
		char tmp[1000] = {0};
		curLevel >> tmp;
		memset(tmp, 0, sizeof(tmp));
		curLevel >> tmp;
		s_input = atoi(tmp);
		if (s_input)
		{
			input = new int[s_input];
			for (int i = 0; i < s_input; i++)
				curLevel >> input[i];
		}
		else
			input = NULL;
		curLevel >> tmp;
		memset(tmp, 0, sizeof(tmp));
		curLevel >> tmp;
		s_output = atoi(tmp);
		if (s_output)
		{
			output = new int[s_output];
			for (int i = 0; i < s_output; i++)
				curLevel >> output[i];
		}
		else
			output = NULL;
		curLevel >> tmp;
		memset(tmp, 0, sizeof(tmp));
		curLevel >> tmp;
		s_Space = atoi(tmp);
		if (s_Space)
		{
			Space = new int[s_Space];
			_Space = new bool[s_Space]();
		}
		else
		{
			Space = NULL;
			_Space = NULL;
		}
		curLevel >> tmp;
		memset(tmp, 0, sizeof(tmp));
		curLevel >> tmp;
		s_operation = atoi(tmp);
		if (s_operation)
		{
			operation = new string[s_operation];
			for (int i = 0; i < s_operation; i++)
				curLevel >> operation[i];
		}
		else
			operation = NULL;
		curLevel.close();
		for (int i = p_input; i < s_input; i++)
			for (int j = 0;; j++)
			{
				maxSize_in = (j > maxSize_in) ? j : maxSize_in;
				maxSize_in = (j == maxSize_in && input[i] < 0) ? maxSize_in + 1 : maxSize_in;
				if (!(int)(input[i] / pow(10, j)))
					break;
			}
	}
	return true;
}
bool getUserInput()
{
	string temp; //临时保存用户每一行输入的文字指令
	int tempNum; // 临时保存用户每一行（如有）输入的操作数
	string mode;
	while (1)
	{
		cout << "Please enter level." << endl;
		cin >> level;
		if (level > maxLevel)
			cout << "Selected level error, please reselect level." << endl;
		else
			break;
	}
	cout << "Please enter your input mode.(keyboard/file)" << endl;
	while (1)
	{
		cin >> mode;
		line(30);
		if (mode != "keyboard" && mode != "file")
			cout << "Mode error." << endl;
		else
			break;
	}
	if (mode == "keyboard")
	{
		if (!loadLevel())
			return false;
		print_level();
		cout << "Please enter command num." << endl;
		cin >> N;
		line(30);
		cout << "Please enter your command." << endl;
		userInput = new string[N + 1];
		nums = new int[N + 1];
		for (int i = 1; i < N + 1; i++)
		{
			cin >> temp;
			userInput[i] = temp;
			if (temp == "add" || temp == "sub" || temp == "copyto" || temp == "copyfrom" ||
				temp == "jump" || temp == "jumpifzero") //如果是包含操作数的输入，则获取操作数
			{
				cin >> tempNum;
				nums[i] = tempNum;
			}
			else
				nums[i] = 0;
		}
		line(30);
	}
	if (mode == "file")
	{
		string path;
		cout << "Please enter the file path." << endl;
		while (1)
		{
			cin >> path;
			line(30);
			ifstream in(path);
			if (!in)
				cout << "Could not open the file in the path " << path << endl;
			else
			{
				cout << "Open file in the path " << path << " successfully." << endl;
				in.close();
				break;
			}
		}
		ifstream in(path);
		in >> N;
		if (!loadLevel())
			return false;
		print_level();
		userInput = new string[N + 1];
		nums = new int[N + 1];
		for (int i = 1; i < N + 1; i++)
		{
			in >> temp;
			userInput[i] = temp;
			if (temp == "add" || temp == "sub" || temp == "copyto" || temp == "copyfrom" ||
				temp == "jump" || temp == "jumpifzero") //如果是包含操作数的输入，则获取操作数
			{
				in >> tempNum;
				nums[i] = tempNum;
			}
			else
				nums[i] = 0;
		}
		in.close();
	}
	return true;
}
void print_field(int curIns)
{
	int maxSize_space = 2, maxSize_out = 2, maxSize_cur = 2, count = 0;
	for (int i = 0; i < s_Space; i++)
		if (_Space[i])
			for (int j = 0;; j++)
			{
				maxSize_space = (j > maxSize_space) ? j : maxSize_space;
				maxSize_space = (j == maxSize_space && userOutput[i] < 0) ? maxSize_space + 1 : maxSize_space;
				if (!(int)(Space[i] / pow(10, j)))
					break;
			}
	for (int i = 0; i < s_userOutput; i++)
		for (int j = 0;; j++)
		{
			maxSize_out = (j > maxSize_out) ? j : maxSize_out;
			maxSize_out = (j == maxSize_out && userOutput[i] < 0) ? maxSize_out + 1 : maxSize_out;
			if (!(int)(userOutput[i] / pow(10, j)))
				break;
		}
	if (current_Box)
		for (int i = 0;; i++)
		{
			maxSize_cur = (i > maxSize_out) ? i : maxSize_out;
			maxSize_cur = (i == maxSize_out && currentBox < 0) ? maxSize_out + 1 : maxSize_out;
			if (!(int)(currentBox / pow(10, i)))
				break;
		}
	blank(maxSize_in + 4);
	blank(GAP);
	for (int i = 0; i < s_Space; i++)
	{
		cout << '*';
		_line(maxSize_space + 2);
		cout << '*';
	}
	blank(5);
	cout << '*';
	_line(maxSize_cur + 2);
	cout << '*';
	cout << endl;
	blank(maxSize_in + 4);
	blank(GAP);
	for (int i = 0; i < s_Space; i++)
		if (_Space[i])
			cout << "| " << setw(maxSize_space) << Space[i] << " |";
		else
		{
			cout << "| ";
			blank(maxSize_space);
			cout << " |";
		}
	blank(5);
	if (current_Box)
		cout << "| " << setw(maxSize_cur) << currentBox << " |";
	else
		cout << "|    |";
	cout << endl;
	blank(maxSize_in + 4);
	blank(GAP);
	for (int i = 0; i < s_Space; i++)
	{
		cout << '*';
		_line(maxSize_space + 2);
		cout << '*';
	}
	blank(5);
	cout << '*';
	_line(maxSize_cur + 2);
	cout << '*';
	cout << endl;
	cout << endl;
	///////////////////
	for (int in = p_input, out = 0, k = 0; k < MAX(s_input - p_input, s_userOutput); in++, out++, k++)
	{
		if (in < s_input)
		{
			cout << '*';
			// for (int j = 0; j < maxSize_in + 2; j++)
			// 	cout << "-";
			_line(maxSize_in + 2);
			cout << '*';
		}
		else
			blank(maxSize_in + 4);
		blank(maxSize_in + 4 + GAP + (s_Space - 1) * (maxSize_space + 4) + GAP);
		if (out < s_userOutput)
		{
			cout << '*';
			for (int j = 0; j < maxSize_out + 2; j++)
				cout << "-";
			cout << '*';
		}
		else
			blank(maxSize_out + 4);
		if (!count)
		{
			cout << "  | ===== CODE =====";
			count++;
		}
		else if (count <= N)
		{
			cout << "  | " << ((count == curIns) ? "> " : "  ") << userInput[count];
			if (userInput[count] == "add" || userInput[count] == "sub" || userInput[count] == "copyto" || userInput[count] == "copyfrom" ||
				userInput[count] == "jump" || userInput[count] == "jumpifzero")
				cout << ' ' << nums[count];
			count++;
		}
		cout << endl;
		if (in < s_input)
			cout << "| " << setw(maxSize_in) << input[in] << " |";
		else
			blank(maxSize_in + 4);
		blank(maxSize_in + 4 + GAP + (s_Space - 1) * (maxSize_space + 4) + GAP);
		if (out < s_userOutput)
			cout << "| " << setw(maxSize_out) << userOutput[out] << " |";
		else
			blank(maxSize_out + 4);
		if (count <= N)
		{
			cout << "  | " << ((count == curIns) ? "> " : "  ") << userInput[count];
			if (userInput[count] == "add" || userInput[count] == "sub" || userInput[count] == "copyto" || userInput[count] == "copyfrom" ||
				userInput[count] == "jump" || userInput[count] == "jumpifzero")
				cout << ' ' << nums[count];
			count++;
		}
		cout << endl;
		if (in < s_input)
		{
			cout << '*';
			for (int j = 0; j < maxSize_in + 2; j++)
				cout << "-";
			cout << '*';
		}
		else
			blank(maxSize_in + 4);
		blank(maxSize_in + 4 + GAP + (s_Space - 1) * (maxSize_space + 4) + GAP);
		if (out < s_userOutput)
		{
			cout << '*';
			for (int j = 0; j < maxSize_out + 2; j++)
				cout << "-";
			cout << '*';
		}
		else
			blank(maxSize_out + 4);
		if (count <= N)
		{
			cout << "  | " << ((count == curIns) ? "> " : "  ") << userInput[count];
			if (userInput[count] == "add" || userInput[count] == "sub" || userInput[count] == "copyto" || userInput[count] == "copyfrom" ||
				userInput[count] == "jump" || userInput[count] == "jumpifzero")
				cout << ' ' << nums[count];
			count++;
		}
		cout << endl;
	}
	for (; count <= N; count++)
	{
		blank(maxSize_in + 4 + GAP + s_Space * (maxSize_space + 4) + GAP + maxSize_out + 4);
		cout << "  | " << ((count == curIns) ? "> " : "  ") << userInput[count];
		if (userInput[count] == "add" || userInput[count] == "sub" || userInput[count] == "copyto" || userInput[count] == "copyfrom" ||
			userInput[count] == "jump" || userInput[count] == "jumpifzero")
			cout << ' ' << nums[count];
		cout << endl;
	}
	line(50);
}
void onestepOperate()
{
	if (userInput[instruction] == "inbox") //// more than 1
	{
		if (p_input < s_input)
		{
			currentBox = input[p_input++];
			current_Box = true;
		}
		else
		{
			gameFinish = true; //、、、、、。。。。。。。。。。。。。。。。。。
			return;
		}
	}
	else if (userInput[instruction] == "outbox")
	{
		if (!current_Box)
		{
			cout << "Error on instruction " << instruction << endl;
			have_error = true;
			return;
		}
		userOutput[p_userOutput++] = currentBox;
		s_userOutput++;
		current_Box = false;
	}
	else if (userInput[instruction] == "add")
	{
		if (!current_Box)
		{
			cout << "Error on instruction " << instruction << endl;
			have_error = true;
			return;
		}
		if (nums[instruction] >= s_Space)
		{
			cout << "Error on instruction " << instruction << endl;
			have_error = true;
			return;
		}
		if (!_Space[nums[instruction]])
		{
			cout << "Error on instruction " << instruction << endl;
			have_error = true;
			return;
		}
		currentBox += Space[nums[instruction]];
	}
	else if (userInput[instruction] == "sub")
	{
		if (!current_Box)
		{
			cout << "Error on instruction " << instruction << endl;
			have_error = true;
			return;
		}
		if (nums[instruction] >= s_Space)
		{
			cout << "Error on instruction " << instruction << endl;
			have_error = true;
			return;
		}
		if (!_Space[nums[instruction]])
		{
			cout << "Error on instruction " << instruction << endl;
			have_error = true;
			return;
		}
		currentBox -= Space[nums[instruction]];
	}
	else if (userInput[instruction] == "copyto")
	{
		if (!current_Box)
		{
			cout << "Error on instruction " << instruction << endl;
			have_error = true;
			return;
		}
		if (nums[instruction] >= s_Space)
		{
			cout << "Error on instruction " << instruction << endl;
			have_error = true;
			return;
		}
		Space[nums[instruction]] = currentBox;
		_Space[nums[instruction]] = true;
	}
	else if (userInput[instruction] == "copyfrom")
	{
		if (nums[instruction] >= s_Space)
		{
			cout << "Error on instruction " << instruction << endl;
			have_error = true;
			return;
		}
		if (!_Space[nums[instruction]])
		{
			cout << "Error on instruction " << instruction << endl;
			have_error = true;
			return;
		}
		currentBox = Space[nums[instruction]];
		current_Box = true;
	}
	else if (userInput[instruction] == "jump")
	{
		if (nums[instruction] > N)
		{
			cout << "Error on instruction " << instruction << endl;
			have_error = true;
			return;
		}
		instruction = nums[instruction] - 1; //  simulation()中还要加1

		return;
	}
	else if (userInput[instruction] == "jumpifzero")
	{
		if (nums[instruction] > N)
		{
			cout << "Error on instruction " << instruction << endl;
			have_error = true;
			return;
		}
		if (!current_Box)
		{
			cout << "Error on instruction " << instruction << endl;
			have_error = true;
			return;
		}
		if (currentBox == 0)
		{
			instruction = nums[instruction] - 1;
		}
	}
	else
	{
		cout << "Error on instruction " << instruction << endl;
		have_error = true;
		return;
	}
}
void simulation()
{
	if (stepTag)
		getchar();
	print_field(0);
	if (stepTag)
		getchar();
	instruction = 1; //从第一行开始执行
	gameFinish = false;
	userOutput = new int[N];
	s_userOutput = 0;
	while (instruction <= N && !gameFinish) //指令尚未执行完  且  输入队列非空   ////////////////////////如何考虑input为空
	{
		int p_operation = 0;																  // 要执行的这一条指令 存放在operation中秩为 p_operation 处
		while (p_operation < s_operation && userInput[instruction] != operation[p_operation]) //注意第一个条件必须写在前面，以防止向量访问越界
		{
			p_operation++;
		}
		if (p_operation >= s_operation) //  在operation中找不到这条指令
		{
			cout << "Error on instruction " << instruction << endl;
			return;
		}
		else
		{
			int curIns = instruction;
			onestepOperate();
			print_field(curIns);
			if (stepTag)
				getchar();
			if (have_error)
				return;
			instruction++;
		}
	}

	p_userOutput = 0;

	while (p_output < s_output) //! output.empty()
	{
		if (p_userOutput >= s_userOutput) //情况不会相反,即userOutput.size()<=output.size()
		{
			cout << "Fail" << endl;
			return;
		}
		if (output[p_output] != userOutput[p_userOutput])
		{
			cout << "Fail" << endl;
			return;
		}
		p_output++;
		p_userOutput++;
	}
	cout << "Success" << endl;
	bool *levelFin = new bool[maxLevel]();
	ifstream lv("level.txt");
	for (int i = 0; i < maxLevel; i++)
	{
		char tmp[1000] = {0};
		lv >> tmp >> tmp >> tmp;
		if (!strcmp(tmp, "finished"))
			levelFin[i] = true;
	}
	lv.close();
	levelFin[level - 1] = true;
	ofstream newLv("level.txt");
	for (int i = 0; i < maxLevel; i++)
		newLv << "Level " << i + 1 << (levelFin[i] ? " finished" : " unfinished") << endl;
	delete[] levelFin;
	return;
}

int main()
{
	bool gameTag = true;
	while (1)
	{
		init();
		getLevelInfo();
		getCmd(gameTag);
		if (!gameTag)
			break;
		if (getUserInput())
			simulation();
		release();
	}
	cout << "Game end" << endl;
	return 0;
}