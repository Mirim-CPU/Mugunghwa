#include "Mugunghwa.h"

//��ǥ
void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}


//Ŀ�� �����
void CursorView()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

//Ŀ�� ����
int keyControl() {
	char c;
	while (1) {
		if (_kbhit()) {
			c = _getch();
			if (c == -32) {
				c = _getch();
				switch (c) {
				case 72:
					return UP; break;
				case 80:
					return DOWN;  break;
				case 75:
					return LEFT; break;
				case 77:
					return RIGHT; break;
				}
			}
			else if (c == ' ')
				return SPACE;
		}
	}
}

//����
void title() {
	int x = 1;
	int y = 1;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
	gotoxy(x, y++);  printf(" _______ ______   _______ _______ __    _   ___     ___ _______ __   __ _______ ");
	gotoxy(x, y++);  printf("|       |    _ | |       |       |  |  | | |   |   |   |       |  | |  |       |");
	gotoxy(x, y++);  printf("|    ___|   | || |    ___|    ___|   |_| | |   |   |   |    ___|  |_|  |_     _|");
	gotoxy(x, y++);  printf("|   | __|   |_||_|   |___|   |___|       | |   |   |   |   | __|       | |   | ");
	gotoxy(x, y++);  printf("|   ||  |    __  |    ___|    ___|  _    | |   |___|   |   ||  |       | |   | ");
	gotoxy(x, y++);  printf("|   |_| |   |  | |   |___|   |___| | |   | |       |   |   |_| |   _   | |   | ");
	gotoxy(x, y++);  printf("|_______|___|__|_|_______|_______|_|__|__|_|_______|___|_______|__| |__| |___|");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
	gotoxy(x, y++);  printf("|    _ | |       |      |  |   |   |   |       |  | |  |       |   ");
	gotoxy(x, y++);  printf("|   | || |    ___|  _    | |   |   |   |    ___|  |_|  |_     _|   ");
	gotoxy(x, y++);  printf("|   |_||_|   |___| | |   | |   |   |   |   | __|       | |   |   ");
	gotoxy(x, y++);  printf("|    __  |    ___| |_|   | |   |___|   |   ||  |       | |   |   ");
	gotoxy(x, y++);  printf("|   |  | |   |___|       | |       |   |   |_| |   _   | |   |     ");
	gotoxy(x, y++);  printf("|___|  |_|_______|______|  |_______|___|_______|__| |__| |___| ");


}

//�޴�����
int  menu() {

	int x = 35;
	int y = 10;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoxy(34, y);  printf("�� �� �� �� ��");
	gotoxy(x, y += 2);  printf(" �� �� �� ��");
	gotoxy(30, y -= 2);
	while (1) {
		int n = keyControl();
		switch (n)
		{
		case UP: {
			if (y > 10) {
				gotoxy(x - 1, y); printf("  ");
				gotoxy(x - 1, y -= 2); printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 12) {
				gotoxy(x - 1, y); printf("  ");
				gotoxy(x - 1, y += 2); printf("��");
			}

			break;
		}
		case SPACE: {
			return y - 10;
		}	break;
		}
	}

}


//ĳ���� �����̱�
int character_control(int x, int y) {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
	gotoxy(x, y); printf("  ��  ");
	while (1) {
		int n = keyControl();
		Sleep(300);
		switch (n)
		{
		case RIGHT: {
			if (x < 50) {
				x++;
				break;
			}

		}
		case LEFT: {
			if (x > 2) {
				x--;
				break;
			}

		}
		case UP: {
			if (y > 1) {
				gotoxy(x, y); printf("    ");
				y--;
			}
			break;
		}

		case DOWN: {
			if (y < 24) {
				gotoxy(x, y); printf("    ");
				y++;
			}
			break;
		}
		}

		gotoxy(x, y); printf("  ��  ");

		//Start ���� �����
		if (x > 0) {
			for (int i = 0; i < 25; i++) {
				gotoxy(3, i); printf(" ");
			}
		}


	}

}



//��
void map() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	for (int i = 0; i < 50; i++) {
		gotoxy(i, 0); printf("��");
	}

	for (int i = 0; i < 50; i++) {
		gotoxy(i, 24); printf("��");
	}
	//start ����
	for (int i = 0; i < 25; i++) {
		gotoxy(3, i); printf("|");
	}

	//finish ����
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
	for (int i = 1; i < 24; i++) {
		gotoxy(45, i); printf("|");
	}


}

void game() {
	system("cls");

	map();
	character_control(0, 3); //�������� ��ġ

	system("pause>null\n");
}
void main() {
	CursorView();
	system("title ����ȭ���� �Ǿ����ϴ�");
	system("mode con: cols=100 lines=25");
	title();

	while (1) {
		switch (menu()) {
		case 0: game(); break; //���ӽ���
		case 2: exit(0);  break; // ��������
		}

	}

}

