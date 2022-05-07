#include "Mugunghwa.h"

Hurdle hurdle[BNum];



int score = 0; //점수
double beginTime;
double endTime;
double thisTime; //begin-end;

int answer[45]; //문제 저장
//좌표
void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}


//커서 숨기기
void CursorView()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

//커서 제어
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

//제목
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



//설명
void manual() {




}

//메뉴선택
int  menu() {

	int x = 45;
	int y = 22;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoxy(x-1, y);  printf("▶ 게 임 시 작");
	gotoxy(x, y += 2);  printf(" 게 임 종 료");
	gotoxy(30, y -= 2);
	while (1) {
		int n = keyControl();
		switch (n)
		{
		case UP: {
			if (y > 22) {
			
				gotoxy(x - 1, y); printf("  ");
				gotoxy(x - 1, y -= 2); printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 24) {
				gotoxy(x - 1, y); printf("  ");
				gotoxy(x - 1, y += 2); printf("▶");
			}

			break;
		}
		case SPACE: {
			return y - 22;
		}	break;
		}
	}

}


int m_x = 3; //화살표 처음 위치
//캐릭터 움직이기
int character_control(int x, int y) {
	int i = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
	gotoxy(x, y); printf("  ■  ");
	while (i<45) {
		int n = keyControl();
		Sleep(300);
		switch (n)
		{

		case RIGHT: {
			if (x < 50) {
				if (answer[i] == 0 || answer[i] == 1 || answer[i] == 2 || answer[i] == 3) { score += 10; }
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
				if (answer[i] == 5) { score += 10; }
				gotoxy(x, y); printf("    ");
				y--;
			}
			break;
		}

		case DOWN: {
			if (y < 23) {
				if (answer[i] == 4) { score += 10; }
				gotoxy(x, y); printf("    ");
				y++;
			}
			break;
		}
		
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
		gotoxy(x, y); printf("  ■  ");
		gotoxy(m_x++,27); printf("  ");
		i++;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		gotoxy(52, 27); printf("점수 :  %d", score);
		//Start 라인 지우기
		if (x > 0) {
			for (int i = 0; i < 25; i++) {
				gotoxy(3, i); printf(" ");
			}
		}


	}

}



unsigned _stdcall MusicTimer() {
	timeBeginPeriod(1);

	beginTime = timeGetTime();
	PlaySound(TEXT("sound.wav"), NULL, SND_FILENAME | SND_ASYNC); //음원
	while (1)
	{
		endTime = timeGetTime();

		thisTime = (endTime - beginTime) / 1000;
		if (thisTime == (double)6) {
			return 1;
		}
	}

	return ;
}

//영희 보여주기
void showYoungHee(int show) {
	int x = 52;
	int y = 7;

	if (show == 1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		gotoxy(x, y++);  printf("／￣￣￣￣＼");
		gotoxy(x, y++);  printf("/ㅡ　 　ㅡ ＼ ");
		gotoxy(x, y++);  printf("/(★) (★) ");
		gotoxy(x, y++);  printf("｜⌒ 人⌒   | ");
		gotoxy(x, y++);  printf("＼　　     ノ ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
		gotoxy(x, y++);  printf("  /⌒＼-イ ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTRED);
		gotoxy(x, y++);  printf(" (　r 　 ｜ ");
		gotoxy(x, y++);  printf(" ＼ノノ--｜ ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		gotoxy(x, y++);  printf("  |＿_/_/ ");
		gotoxy(x, y++);  printf("  `ㅡ^ㅡ`");
	}
	//영희 뒤돌기전
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		gotoxy(x, y++);  printf("／￣￣￣￣＼");
		gotoxy(x, y++);  printf("/　 ㅡ　 ㅡ＼ ");
		gotoxy(x, y++);  printf("/ (●) 　(●) ");
		gotoxy(x, y++);  printf("｜ ⌒  人⌒ | ");
		gotoxy(x, y++);  printf("＼　　     ノ ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
		gotoxy(x, y++);  printf("  /⌒＼-イ ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTRED);
		gotoxy(x, y++);  printf(" (　r 　 ｜ ");
		gotoxy(x, y++);  printf(" ＼ノノ--｜ ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		gotoxy(x, y++);  printf("  |＿_/_/ ");
		gotoxy(x, y++);  printf("  `ㅡ^ㅡ`");
	}
}

//술래 과정
void tagger() {
	_beginthreadex(NULL, 0, MusicTimer, 0, 0, NULL);

	int showMotion = 0; //아무생각 없이 선언한 변수.. 음원 끝나면 뒤돌게

	showYoungHee(showMotion);
	showMotion = MusicTimer();
	showYoungHee(showMotion);
	
	

	


}

//장해물 생성
void CreateHurdle() {
	
	for (int i = 0; i < BNum; i++) {
			hurdle[i].x = rand() % 42 + 4;
			hurdle[i].y = rand() % 22+1;
	}
}

//맵
void map() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	for (int i = 0; i < 60; i++) {
		gotoxy(i, 0); printf("■");
	}

	for (int i = 0; i < 60; i++) {
		gotoxy(i, 24); printf("■");
	}
	//start 라인
	for (int i = 0; i < 25; i++) {
		gotoxy(3, i); printf("|");
	}

	//finish 라인
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
	for (int i = 1; i < 24; i++) {
		gotoxy(50, i); printf("|");
	}
	tagger();

	CreateHurdle();
	for (int i = 0; i < BNum; i++) {
			gotoxy(hurdle[i].x, hurdle[i].y);
			printf("△");
		
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoxy(52, 27); printf("점수 :  %d", score);
}



//미션출력
void mission() {
	srand(time(NULL)); 
	char m[6][10]= {"→",  "→",  "→","→","↑","↓",};
	int color[6] = { 9,10,11,12,13,14 }; //컬러 랜덤
	
	gotoxy(3, 27);
	for (int i = 0; i < 45; i++) {
		int rn = (rand() % 6);
		answer[i] = rn;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[rn]);
		printf("%s",m[rn]); //화살표 출력
	}
}



//게임 시작
void game() {
	system("cls");
	CursorView(); //커서 숨기기
	
	mission(); //미션
	map(); //맵 그리기
	character_control(0, 11); //캐릭터그리기 유저시작 위치

	system("pause>null\n");
}
void main() {


	CursorView();
	system("mode con: cols=120 lines=30"); 
	system("title 무궁화꽃이 피었습니다");
	title();
	
	while (1) {
		switch (menu()) {
		case 0: game(); break; //게임시작
		case 2: exit(0);  break; // 게임종료
		}

	}

}

