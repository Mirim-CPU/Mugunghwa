#include "Mugunghwa.h"

Hurdle hurdle[BNum];


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
	int y = 6;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTRED);
	gotoxy(x, y++);  printf(" __   __ __   __ _______ __   __ __    _ _______ __   __ _     _ _______ ");
	gotoxy(x, y++);  printf("|  |_|  |  | |  |       |  | |  |  |  | |       |  | |  | | _ | |   _   |");
	gotoxy(x, y++);  printf("|       |  | |  |    ___|  | |  |   |_| |    ___|  |_|  | || || |  |_|  |");
	gotoxy(x, y++);  printf("|       |  |_|  |   | __|  |_|  |       |   | __|       |       |       |");
	gotoxy(x, y++);  printf("|       |       |   ||  |       |  _    |   ||  |       |       |       |");
	gotoxy(x, y++);  printf("| ||_|| |       |   |_| |       | | |   |   |_| |   _   |   _   |   _   |");
	gotoxy(x, y++);  printf("|_|   |_|_______|_______|_______|_|  |__|_______|__| |__|__| |__|__| |__|");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTBLUE);
	gotoxy(x, y++);  printf("|  | |  |   _   |       |     ");
	gotoxy(x, y++);  printf("|  |_|  |  |_|  |  _____|   ");
	gotoxy(x, y++);  printf("|       |       | |_____  ");
	gotoxy(x, y++);  printf("|       |       |_____  |    ");
	gotoxy(x, y++);  printf("|   _   |   _   |_____| |   ");
	gotoxy(x, y++);  printf("|__|_|__|__| |__|_______|");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTGREEN);
	printf("_______ __   __ _______ ______          ");
	gotoxy(x, y++);  printf("|  _    |   |   |       |       |  |_|  |       |      |         ");
	gotoxy(x, y++);  printf("| |_|   |   |   |   _   |   _   |       |    ___|  _    |   ");
	gotoxy(x, y++);  printf("|       |   |   |  | |  |  | |  |       |   |___| | |   |   ");
	gotoxy(x, y++);  printf("|  _   ||   |___|  |_|  |  |_|  |       |    ___| |_|   |    ");
	gotoxy(x, y++);  printf("| |_|   |       |       |       | ||_|| |   |___|       |     ");
	gotoxy(x, y++);  printf("|_______|_______|_______|_______|_|   |_|_______|______|    ");


}



//����
void manual() {




}

//�޴�����
int  menu() {

	int x = 45;
	int y = 22;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoxy(x-1, y);  printf("�� �� �� �� ��");
	gotoxy(x, y += 2);  printf(" �� �� �� ��");
	gotoxy(30, y -= 2);
	while (1) {
		int n = keyControl();
		switch (n)
		{
		case UP: {
			if (y > 22) {
				gotoxy(x - 1, y); printf("  ");
				gotoxy(x - 1, y -= 2); printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 24) {
				gotoxy(x - 1, y); printf("  ");
				gotoxy(x - 1, y += 2); printf("��");
			}

			break;
		}
		case SPACE: {
			return y - 22;
		}	break;
		}
	}

}

int i;
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
			if (y < 23) {
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



//���� �ڵ��ƺ�����
void tagger() {

	PlaySound(TEXT("sound.wav"), NULL, SND_FILENAME | SND_ASYNC); //�����׽�Ʈ
	int x = 52;
	int y = 7;

	//����
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoxy(x, y++);  printf("������������");
	gotoxy(x, y++);  printf("/�� �ѡ� �ѡ� ");
	gotoxy(x, y++);  printf("/ (��) ��(��) ");
	gotoxy(x, y++);  printf("�� ��  �ѡ� | ");
	gotoxy(x, y++);  printf("������     �� ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
	gotoxy(x, y++);  printf("  /�ҡ�-�� ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTRED);
	gotoxy(x, y++);  printf(" (��r �� �� ");
	gotoxy(x, y++);  printf(" ���Ϋ�--�� ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoxy(x, y++);  printf("  |��_/_/ ");
	gotoxy(x, y++);  printf("  `��^��`");


}

//���ع� ����
void CreateHurdle() {
	
	for (int i = 0; i < BNum; i++) {
			hurdle[i].x = rand() % 42 + 4;
			hurdle[i].y = rand() % 22+1;
	}
}

//��
void map() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	for (int i = 0; i < 60; i++) {
		gotoxy(i, 0); printf("��");
	}

	for (int i = 0; i < 60; i++) {
		gotoxy(i, 24); printf("��");
	}
	//start ����
	for (int i = 0; i < 25; i++) {
		gotoxy(3, i); printf("|");
	}

	//finish ����
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
	for (int i = 1; i < 24; i++) {
		gotoxy(50, i); printf("|");
	}
	tagger();

	CreateHurdle();
	for (int i = 0; i < BNum; i++) {
			gotoxy(hurdle[i].x, hurdle[i].y);
			printf("��");
		
	}

}


//���ع� ����
int TouchHurdle() {
}
//���� ����
void game() {
	system("cls");

	map();
	character_control(0, 3); //�������� ��ġ

	system("pause>null\n");
}
void main() {
	srand(time(NULL));

	CursorView();
	system("mode con: cols=120 lines=30"); 
	system("title ����ȭ���� �Ǿ����ϴ�");
	title();
	
	while (1) {
		switch (menu()) {
		case 0: game(); break; //���ӽ���
		case 2: exit(0);  break; // ��������
		}

	}

}

