#include <iostream>
#include <Windows.h>
#include <conio.h>

bool game_over;
const int32_t width = 40, height = 20;
int32_t X, Y, food_X, food_Y, counter, tail_X[50], tail_Y[50], length_tail;
enum menu { MOTIONLESS = 0, KEY_LEFT, KEY_UP, KEY_RIGHT, KEY_DOWN };
menu choice;

void Сonfigure() {
	game_over = false;
	X = width / 2;
	Y = height / 2;
	food_X = rand() % width;
	food_Y = rand() % height;
}

void set_color(int text, int bg) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

void Window() {
	system("cls");
	for (int indent = 0; indent < height; indent++)  std::cout << " ";//для отступов.не обязательно.
	for (int i = 0; i <= width + 1; i++) {
		if (i == width + 1)  std::cout << char(191);
		else if (i == 0)  std::cout << char(218);
		else  std::cout << char(196);
	}

	std::cout << std::endl;

	for (int i = 0; i < height; i++) {
		for (int indent = 0; indent < height; indent++)  std::cout << " ";//для отступов.не обязательно.
		for (int j = 0; j <= width; j++) {
			if ((j == 0) || (j == width))  std::cout << char(179);
			if ((i == Y) && (j == X)) {
				set_color(2, 0);
				std::cout << '\2';//head
			}
			else if ((i == food_Y) && (j == food_X)) {
				set_color(4, 0);
				std::cout << '\3';//food
			}
			else {
				bool print = false;
				for (int l = 0; l < length_tail; l++) {
					if ((tail_X[l] == j) && (tail_Y[l] == i)) {
						std::cout << "+";
						print = true;
					}
				}
				if (!print)  std::cout << " ";
			}
			set_color(7, 0);
		}
		std::cout << std::endl;
	}

	for (int indent = 0; indent < height; indent++)  std::cout << " ";//для отступов.не обязательно.
	for (int i = 0; i <= width + 1; i++) {
		if (i == width + 1)  std::cout << char(217);
		else if (i == 0)  std::cout << char(192);
		else  std::cout << char(196);
	}

	std::cout << std::endl;
	std::cout << "Lenght Achieved: " << counter;
}

void Input() {
	if (_kbhit()) {
		switch (_getch())
		{
		case 75: choice = KEY_LEFT; break;

		case 72: choice = KEY_UP; break;

		case 77: choice = KEY_RIGHT; break;

		case 80: choice = KEY_DOWN; break;

		case 27: game_over = true; break;
		}
	}
}

void Logic() {
	int32_t earlier_X = tail_X[0],earlier_Y = tail_Y[0];
	int32_t earlier_2X, earlier_2Y;
	tail_X[0] = X;
	tail_Y[0] = Y;
	for (int i = 1; i < length_tail; i++) {
		earlier_2X = tail_X[i];
		earlier_2Y = tail_Y[i];
		tail_X[i] = earlier_X;
		tail_Y[i] = earlier_Y;
		earlier_X = earlier_2X;
		earlier_Y = earlier_2Y;
	}
	switch (choice) {
	case KEY_LEFT: X--; break;

	case KEY_UP: Y--; break;

	case KEY_RIGHT: X++; break;

	case KEY_DOWN: Y++; break;
	}

	//if (X >= width || X < 0 || Y >= height || Y < 0)  game_over = true;//Если хотим,чтобы змея не выходила из поля.

	if (X >= width) X = 0; else if (X < 0) X = width - 1;
	if (Y >= height) Y = 0; else if (Y < 0) Y = height - 1;

	for (int i = 0; i < length_tail; i++)
		if ((tail_X[i] == X) && (tail_Y[i] == Y))
			game_over = true;

	if ((X == food_X) && (Y == food_Y)) {
		counter++;
		length_tail++;
		food_X = rand() % width;
		food_Y = rand() % height;
	}
}

int main() {
	Сonfigure();
	while (!game_over) {
		Window();
		Input();
		Logic();
		Sleep(50);
	}
	return 0;
}
