#include "Mugunghwa.h"

Hurdle hurdle[BNum];
HANDLE musicThread;


int score = 0; //����
double beginTime;
double endTime;
double thisTime; //begin-end;
int showMN = 0;

int answer[45]; //���� ����
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

void showMenu() {
	int x = 45;
	int y = 22;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoxy(x - 1, y);  printf("�� �� �� �� ��");
	gotoxy(x, y += 2);  printf(" �� �� �� ��");

	gotoxy(30, y -= 2);
}
//�޴�����
int  menu() {

	int x = 45;
	int y = 22;
	int show = 0;

	if (++showMN == 1) showMenu();

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

//�Ϸ� üũ
void checkFinish(int x, int y) {
	if (x >= 50 && y >= 1 && y <= 23) {
		system("cls");
		gotoxy(30, 13); printf("����");
	}
}

int m_x = 3; //ȭ��ǥ ó�� ��ġ
//ĳ���� �����̱�


unsigned _stdcall character_control() {
	int x = 0;
	int y = 11;

	int i = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
	gotoxy(x, y); printf("  ��  ");
	while (i<45) {
		int n = keyControl();
		Sleep(300);
		switch (n)
		{
			checkFinish(x, y);
		case RIGHT: {
			if (x < 50) {
				if (answer[i] == 0 || answer[i] == 1 ) { score += 10; }
				x++;

				break;
			}

		}
		case LEFT: {
			if (x > 2) {	
				if( answer[i] == 2 || answer[i] == 3)
				x--;
				break;
			}

		}
		case UP: {
			if (y > 1) {
				if (answer[i] == 4) { score += 10; }
				gotoxy(x, y); printf("    ");
				y--;
			}
			break;
		}

		case DOWN: {
			if (y < 23) {
				if (answer[i] == 5) { score += 10; }
				gotoxy(x, y); printf("    ");
				y++;
			}
			break;
		}
		
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
		gotoxy(x, y); printf("  ��  ");
		gotoxy(m_x++,27); printf("  ");
		i++;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		gotoxy(52, 27); printf("���� :  %d", score);
		//Start ���� �����
		if (x > 0) {
			for (int i = 0; i < 25; i++) {
				gotoxy(3, i); printf(" ");
			}
		}


	}

}

//���� �����ֱ�
void showYoungHee(int show) {
	int x = 52;
	int y = 7;

	if (show == 1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		gotoxy(x, y++);  printf("������������");
		gotoxy(x, y++);  printf("/�ѡ� ���� �� ");
		gotoxy(x, y++);  printf("/(��) (��) ");
		gotoxy(x, y++);  printf("���� �ѡ�   | ");
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
	//���� �ڵ�����
	else {
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

}
void showGameOver() {
	system("cls");
	gotoxy(30, 13); printf("GAME OVER");
	
}
void check() {
	
	//if (_kbhit()) {
	//	gotoxy(12, 12); printf("hit");
	//}
	if (_kbhit()) {
		if (thisTime > (double)6 && thisTime < (double)8) {
			printf("check");
			showGameOver();
			TerminateThread(musicThread, 0);
			
		}
	}
}
unsigned _stdcall MusicTimer() {
	timeBeginPeriod(1);

	while (1) {
		PlaySound(TEXT("sound.wav"), NULL, SND_FILENAME | SND_ASYNC); //����
		beginTime = timeGetTime();

		while (1)
		{
			endTime = timeGetTime();

			thisTime = (endTime - beginTime) / 1000;

			if (thisTime == (double)6) {
				showYoungHee(1);
			}
			else if (thisTime == (double)8) {
				showYoungHee(0);
				beginTime = (double)0;
				break;
			}



		}
	}

	return ;
}


//���� ����
void tagger() {
	int showMotion = 0; //���� ��� ���� 1 - �ڵ���, 0 - �� ����
	showYoungHee(showMotion);

	HANDLE controlThread = _beginthreadex(NULL, 0, character_control, 0, 0, NULL);
	musicThread = _beginthreadex(NULL, 0, MusicTimer, 0, 0, NULL);
	//HANDLE checkThread = _beginthreadex(NULL, 0, check, 0, 0, NULL);

	while (1) {
		check();
	}
	
}

//���ع� ����
void CreateHurdle() {
	
	for (int i = 0; i < BNum; i++) {
			hurdle[i].x = rand() % 42 + 4;
			hurdle[i].y = rand() % 22+1;
	}
}

//���� ��Ÿ����
void showScore(int score) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoxy(52, 27); printf("���� :  %d", score);
}

//��
void map() {
	int show = 0; // 1 = show, 0 - hide
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

	 //showScore(score);
}



//�̼����
void mission() {
	srand(time(NULL)); 
	char m[6][10]= {"��",  "��",  "��","��","��","��",};
	int color[6] = { 9,10,11,12,13,14 }; //�÷� ����
	
	gotoxy(3, 27);
	for (int i = 0; i < 45; i++) {
		int rn = (rand() % 6);
		answer[i] = rn;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[rn]);
		printf("%s",m[rn]); //ȭ��ǥ ���
	}
}



//���� ����
void game() {
	system("cls");
	CursorView(); //Ŀ�� �����
	
	mission(); //�̼�
	map(); //�� �׸���
	

	system("pause>null\n");
}
void main() {


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

