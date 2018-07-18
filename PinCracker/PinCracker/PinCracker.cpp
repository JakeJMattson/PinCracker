#include <string>
#include <iostream>
#include <Windows.h>

using std::string;
using std::cout;
using std::endl;

INPUT input;

void initKeyboard()
{
	//Set up a generic keyboard event.
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = 0;
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;
}

void typeKey(char key)
{
	//Calculate virtual keycode
	input.ki.wVk = key + 48;

	//Press key
	input.ki.dwFlags = 0;
	SendInput(1, &input, sizeof(INPUT));

	//Release key
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
}

string constructPin(unsigned int number)
{
	//Determine number of digits
	int length = number > 0 ? (int) log10(number) + 1 : 1;

	string pin = "";

	//Pad remaining pin length with '0'
	for (int i = 0; i < 4 - length; i++)
		pin += "0";

	pin += "" + std::to_string(number);

	return pin;
}

void sendPin(string pin)
{
	//Display progress
	cout << "Attempting: " << pin << endl;
	
	//Type each key from the pin
	for (char currentChar : pin)
	{
		int num = currentChar - '0';
		typeKey(num);

		//Wait after each press to minimize game crashes
		Sleep(100);
	}
}

int main()
{
	initKeyboard();

	//Allow user to prepare in-game
	Sleep(5000);

	for (int i = 0; i < 10000; i++)
	{
		typeKey(21); //Press 'E'

		//Wait for storage container to open
		Sleep(250);

		sendPin(constructPin(i));
		
		//Wait for storage container to close
		Sleep(250);
	}
}