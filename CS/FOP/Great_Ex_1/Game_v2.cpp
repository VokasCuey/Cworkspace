#include <iostream>
#include <fstream>
#include <cstring>
#include <string.h>
using namespace std;

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

bool gameFinish;
bool have_error;
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
}
void getCmd(bool gameTag)
{
	string cmd;
	while (1)
	{
		cout << "Please enter you command.(continue/quit/reset)" << endl;
		cin >> cmd;
		if (cmd == "continue" || cmd == "quit")
			break;
		else if (cmd == "reset")
		{
			cout << "reset complete." << endl;
		}
		else
			cout << "Command error." << endl;
	}
}
void getLevelInfo()
{
	ifstream lv("level.txt");
	cout << "-----------------------------" << endl;
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
			cout << tmp << endl;
			maxLevel++;
		}
		maxLevel--;
		lv.close();
	}
}
void getUserInput()
{
	string temp; //临时保存用户每一行输入的文字指令
	int tempNum; // 临时保存用户每一行（如有）输入的操作数
	string mode;
	cout << "Please enter your input mode.(keyboard/file)" << endl;
	while (1)
	{
		cin >> mode;
		if (mode != "keyboard" && mode != "file")
			cout << "Mode error, please enter mode again." << endl;
		else
			break;
	}
	if (mode == "keyboard")
	{
		while (1)
		{
			cin >> level;
			if (level > maxLevel)
				cout << "Selected level error, please reselect level." << endl;
			else
				break;
		}
		cin >> N;
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
	}
	if (mode == "file")
	{
		string path;
		cout << "Please enter the file path." << endl;
		while (1)
		{
			cin >> path;
			ifstream in(path);
			if (!in)
				cout << "Could not open the file in the path " << path << endl
					 << "Please enter the file path again." << endl;
			else
			{
				cout << "Open file in the path " << path << " successfully." << endl;
				in.close();
				break;
			}
		}
		ifstream in(path);
		in >> level >> N;
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
	return;
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
			_Space = new bool[s_Space];
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
	}
	return true;
	// switch (level)
	// {
	// case 1:
	// 	s_input = 2;
	// 	s_output = 2;
	// 	input = new int[s_input];
	// 	output = new int[s_output];
	// 	input[0] = 1;
	// 	input[1] = 2;
	// 	output[0] = 1;
	// 	output[1] = 2;
	// 	s_Space = 0;
	// 	Space = NULL;
	// 	_Space = NULL;
	// 	s_operation = 2;
	// 	operation = new string[s_operation];
	// 	operation[0] = "inbox";
	// 	operation[1] = "outbox";
	// 	break;
	// case 2:
	// 	s_input = 8;
	// 	s_output = 8;
	// 	input = new int[s_input];
	// 	output = new int[s_output];
	// 	s_Space = 3;
	// 	Space = new int[s_Space];
	// 	_Space = new bool[s_Space];
	// 	_Space[0] = _Space[1] = _Space[2] = false;
	// 	input[0] = 3;
	// 	input[1] = 9;
	// 	input[2] = 5;
	// 	input[3] = 1;
	// 	input[4] = -2;
	// 	input[5] = -2;
	// 	input[6] = 9;
	// 	input[7] = -9;
	// 	output[0] = -6;
	// 	output[1] = 6;
	// 	output[2] = 4;
	// 	output[3] = -4;
	// 	output[4] = 0;
	// 	output[5] = 0;
	// 	output[6] = 18;
	// 	output[7] = -18;
	// 	s_operation = 8;
	// 	operation = new string[s_operation];
	// 	operation[0] = "inbox";
	// 	operation[1] = "outbox";
	// 	operation[2] = "copyfrom";
	// 	operation[3] = "copyto";
	// 	operation[4] = "add";
	// 	operation[5] = "sub";
	// 	operation[6] = "jump";
	// 	operation[7] = "jumpifzero";
	// 	break;
	// case 3:
	// 	s_input = 8;
	// 	s_output = 2;
	// 	input = new int[s_input];
	// 	output = new int[s_output];
	// 	s_Space = 3;
	// 	Space = new int[s_Space];
	// 	_Space = new bool[s_Space];
	// 	_Space[0] = _Space[1] = _Space[2] = false;
	// 	input[0] = 6;
	// 	input[1] = 2;
	// 	input[2] = 7;
	// 	input[3] = 7;
	// 	input[4] = -9;
	// 	input[5] = 3;
	// 	input[6] = -3;
	// 	input[7] = -3;
	// 	output[0] = 7;
	// 	output[1] = -3;
	// 	s_operation = 8;
	// 	operation = new string[s_operation];
	// 	operation[0] = "inbox";
	// 	operation[1] = "outbox";
	// 	operation[2] = "copyfrom";
	// 	operation[3] = "copyto";
	// 	operation[4] = "add";
	// 	operation[5] = "sub";
	// 	operation[6] = "jump";
	// 	operation[7] = "jumpifzero";
	// 	break;
	// default:
	// 	break;
	// }
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
			onestepOperate();
			if (have_error)
				return;
			instruction++;
		}
	}

	p_userOutput = 0;

	while (p_output < s_output) //!output.empty()
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
	while (1)
	{
		bool gameTag = true;
		getLevelInfo();
		getUserInput();
		if (loadLevel())
			simulation();
		release();
	}
	return 0;
}