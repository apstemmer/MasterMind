// mastermind.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>

using namespace std;



class Seq {
private:
	char code[5] = "rgby";
public:
	Seq();
	void check(char cArr[5]);
	void output(char oArr[5]);
	static void setColor(char color);
};




Seq::Seq() {
	time_t seconds;
	time(&seconds);
	std::string lib = "rgbywc";
	for (int i = 0; i < 4; i++) {
		srand((unsigned int)(seconds + i));
		code[i] = lib.at(rand() % 6);
		//std::cout << code[i];
	}
}
void Seq::check(char inArr[5]) {
	int posncolor = 0, color = 0, it = 0;
	char chk[] = "rgybwc";
	std::vector<char> hBeen(3);
	for (int i = 0; i < 4; i++)//checks how many times the position and the color are correct
	{
		if (strpbrk(chk, &inArr[i]) == nullptr) {
			std::cout << "invalid input. please use the characters r, g, b, y, c or w" << std::endl;
			return;
		}

		if (inArr[i] == code[i])
			posncolor++;

		for (int j = 0; j < 4; j++)
		{
			if ((inArr[i] == code[j] && hBeen[0] != inArr[i] && hBeen[1] != inArr[i] && hBeen[2] != inArr[i]) && inArr[i] != code[i])
			{
				color++;
				hBeen[it] = inArr[i];//fills the hBeen with the already checked value.
				it++;
			}
		}
	}
	output(inArr);
	if (posncolor == 4) {
		std::cout << "Congrats. You have won!";
	}
	else {
		std::cout << "correct placement and color :" << posncolor << std::endl;
		std::cout << "correct color, wrong placement :" << color << std::endl;
	}
}

void Seq::output(char oArr[5]) {
	const char blk = (char)219;
	char disp[] = { blk, blk, blk, blk, '\0' };
	for (int i = 0; i < 4; i++)
	{
		this->setColor(oArr[i]);
		std::cout << disp[i] << ' ';
	}
	this->setColor('w');
	std::cout << std::endl;
}

void Seq::setColor(char color) {
	switch (color)
	{
	case 'r':
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
		break;
	case 'g':
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
		break;
	case 'b':
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
		break;
	case 'y':
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED);
		break;
	case 'c':
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN);
		break;
	case 'w':
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
		break;
	default:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
		break;
	}
}



int main()
{
	cout << "-----------MASTERMIND-----------" << endl;
	cout << "The computer has generated a code for you to crack!\n"
		<< "You can enter either r, g, b, y, c or w to guess red, green, blue, yellow, cyan or white respectively\n"
		<< "An example entry is: rgyc this would guess red, green, yellow and cyan. In that order." << endl;
	char mCode[] = "rgbw";
	Seq tCode;
	while (cin >> mCode){
		tCode.check(mCode);
	}
	return 0;
}

