#include "Mugunghwa.h"


HANDLE musicThread;
HANDLE controlThread;

int score = 0; //점수
double beginTime;
double endTime;
double thisTime; //begin-end;
int showMN = 0;
double soundtime = 0; //술래 움직임 체크
double chktime = 0; // 플레이어 움직임 체크
int answer[160]; //문제 저장
int answer_len = 160;
int heart = 5; //목숨값
int input = 1;





//좌표
void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = x*2;
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
				case 27: 
					return ESC; break;
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

void showMenu() {
	int x = 45;
	int y = 22;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoxy(x - 1, y);  printf("▶ 게 임 시 작");
	gotoxy(x, y += 2);  printf(" 게 임 종 료");

	gotoxy(30, y -= 2);
}
//메뉴선택
int  menu() {

	int x = 45;
	int y = 22;
	int show = 0;

	//if (++showMN == 1) showMenu();

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

//완료 체크
void checkFinish(int x, int y) {
	if (x >= 50 && y >= 1 && y <= 23) {
		system("cls");
		gotoxy(30, 13); printf("완주");
	}
}

int m_x = 3; //화살표 처음 위치
//캐릭터 움직이기


unsigned _stdcall character_control() {
	int x = 4;
	int y = 6;

	int i = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
	gotoxy(x, y); printf("■");
	while (input) {
	
		int n = _getch();

		//게임종료
		if (n==27) {
		score = 0;
		heart = 5;
		PlaySound(NULL, 0, 0);
		system("cls");
		main();
		}
			n = keyControl();
			switch (n)
			{

		
			case RIGHT: {

				if (answer[i] == 0) { score += 10; }
				else heart--;
				break;


			}
			case LEFT: {

				if (answer[i] == 1) { score += 10; }
				else heart--;
				break;


			}
			case UP: {

				if (answer[i] == 3) { score += 10; }
				else heart--;


				break;
			}

			case DOWN: {

				if (answer[i] == 2) { score += 10; }
				else heart--;
				break;
			}


		}
		switch (i / 5)
		{
		case 0: gotoxy(x, y++); printf("  "); break;
		case 1:  gotoxy(x++, y); printf("  "); break;
		case 2:  gotoxy(x, y++); printf("  "); break;
		case 3: gotoxy(x++, y); printf("  "); break;
		case 4: gotoxy(x, y--);  printf("  "); break;
		case 5: gotoxy(x++, y); printf("  "); break;
		case 6:  gotoxy(x, y++); printf("  "); break;
		case 7:  gotoxy(x++, y); printf("  "); break;
		case 8:  gotoxy(x, y++); printf("  "); break;
		case 9:  gotoxy(x++, y);  printf("  "); break;
		case 10:  gotoxy(x, y--); printf("  "); break;
		case 11:  gotoxy(x, y--); printf("  "); break;
		case 12:  gotoxy(x, y--); printf("  "); break;
		case 13:  gotoxy(x--, y); printf("  "); break;
		case 14:  gotoxy(x--, y); printf("  "); break;
		case 15:  gotoxy(x, y--); printf("  "); break;
		case 16:  gotoxy(x++, y); printf("  "); break;
		case 17:  gotoxy(x++, y); printf("  "); break;
		case 18:  gotoxy(x++, y); printf("  "); break;
		case 19:  gotoxy(x, y++); printf("  "); break;
		case 20:  gotoxy(x, y++); printf("  "); break;
		case 21:  gotoxy(x, y++); printf("  "); break;
		case 22:  gotoxy(x++, y); printf("  "); break;
		case 23:  gotoxy(x, y++); printf("  "); break;
		case 24:  gotoxy(x++, y); printf("  "); break;
		case 25:  gotoxy(x, y--); printf("  "); break;
		case 26:  gotoxy(x, y--); printf("  "); break;
		case 27:  gotoxy(x++, y); printf("  "); break;
		}

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
		i++;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		gotoxy(20, 29); printf(" % d", score);
		gotoxy(46, 29); printf(" %d", heart);


	}

}

//영희 보여주기
void showYoungHee(int show) {
	int x = 52;
	int y = 7;

	if (show == 1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		gotoxy(x, y++);  printf("／￣￣￣￣＼");
		gotoxy(x, y++);  printf("/ㅡ　 　ㅡ ＼ ");
		gotoxy(x, y++);  printf("/(★) (★)     ");
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
void showGameOver() {

	system("cls");
	PlaySound(NULL, 0, 0);

	score = 0;
	heart = 5;

	gotoxy(30, 13); printf("GAME OVER");

	Sleep(2000);
	system("cls");
	main();

	
}


void check() {

	if (heart == 0) {
		input = 0;
		showGameOver();
		TerminateThread(musicThread, 0);
		TerminateThread(controlThread, 0);

	}

	if (_kbhit()) {

		if (thisTime > (double)soundtime && thisTime < (double)soundtime + 2) {
			input = 0;
			showGameOver();
			TerminateThread(musicThread, 0);
			TerminateThread(controlThread, 0);

		}
	}
}


 unsigned _stdcall  MusicTimer() {
	timeBeginPeriod(1);


	
	while (input) {
		
		int rn = (rand() % 5);

		switch (rn)
		{
		case 0:	PlaySound(TEXT("./music/sound1.wav"), NULL, SND_FILENAME | SND_ASYNC); soundtime = 4.5; break;
		case 1:	PlaySound(TEXT("./music/sound2.wav"), NULL, SND_FILENAME | SND_ASYNC); soundtime = 3.2; break;
		case 2:	PlaySound(TEXT("./music/sound3.wav"), NULL, SND_FILENAME | SND_ASYNC); soundtime = 2.3; break;
		case 3:	PlaySound(TEXT("./music/sound4.wav"), NULL, SND_FILENAME | SND_ASYNC); soundtime = 1.9; break;
		case 4:	PlaySound(TEXT("./music/sound5.wav"), NULL, SND_FILENAME | SND_ASYNC); soundtime = 1.5;   break;

		}
	
		beginTime = timeGetTime();

		while (input)
		{
			endTime = timeGetTime();

			thisTime = (endTime - beginTime) / 1000;

			if (thisTime == soundtime) {
				showYoungHee(1);
			}
			else if (thisTime == soundtime +2) {
				showYoungHee(0);
				beginTime = (double)0;
				break;
			}



		}
	}


}




//술래 과정
void tagger() {
	int showMotion = 0; //영희 모션 상태 1 - 뒤돌기, 0 - 앞 보기
	showYoungHee(showMotion);

	 controlThread = _beginthreadex(NULL, 0, character_control, 0, 0, NULL);
	musicThread = _beginthreadex(NULL, 0, MusicTimer, 0, 0, NULL);
	
	while (1) {
		check();
	}
	
}




void showHeart() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTRED);
	gotoxy(32, 27);  printf("  ,d88b.d88b,");
	gotoxy(32, 28);  printf("  88888888888");
	gotoxy(32, 29);  printf("  `Y8888888Y'");
	gotoxy(32, 30);  printf("    `Y888Y'    ");
	gotoxy(32, 31);  printf("      `Y' ");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoxy(40, 28);  printf("( ＼/ )");
	gotoxy(40, 29);  printf("  ) ( ");
	gotoxy(40, 30);  printf("(_/＼_)");
	gotoxy(46, 29); printf(" %d", 5);

}


//점수 나타내기
void showScore() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTBLUE);

	gotoxy(5, 27);  printf(" ___  ___ ___   _  __ ___   ");
	gotoxy(5, 28);  printf("/ __|/ __/ _ ＼ | '__/ _ ＼  0");
	gotoxy(5, 29);  printf("＼__＼ (_| (_)  | |  | __/");
	gotoxy(5, 30);  printf("|___/＼___＼___/|_|  ＼___|  0 ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoxy(20, 29); printf(" % d", 0);

}



//맵
void map() {

	int show = 0; // 1 = show, 0 - hide
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




}



//미션출력
void mission() {
	srand(time(NULL)); 
	char m[4][10]= {"→","←","↓","↑"};
	int color[6] = { 9,10,11,12,13,14 }; //컬러 랜덤
	int x = 4, y = 6;

	for (int i = 0; i < 160; i++) {
		int rn = (rand() % 4);
		answer[i] = rn;

		switch (i / 5)
		{
		case 0: gotoxy(x, y++); printf("%s", m[rn]); break;
		case 1:  gotoxy(x++, y); printf("%s", m[rn]);   break;
		case 2:  gotoxy(x, y++); printf("%s", m[rn]);   break;
		case 3: gotoxy(x++, y); printf("%s", m[rn]);  break;
		case 4: gotoxy(x, y--);  printf("%s", m[rn]);  break;
		case 5: gotoxy(x++, y); printf("%s", m[rn]); break;
		case 6:  gotoxy(x, y++); printf("%s", m[rn]);  break;
		case 7:  gotoxy(x++, y);  printf("%s", m[rn]);  break;
		case 8:  gotoxy(x, y++); printf("%s", m[rn]);  break;
		case 9:  gotoxy(x++, y);  printf("%s", m[rn]);  break;
		case 10:  gotoxy(x, y--); printf("%s", m[rn]);  break;
		case 11:  gotoxy(x, y--); printf("%s", m[rn]);  break;
		case 12:  gotoxy(x, y--); printf("%s", m[rn]);  break;
		case 13:  gotoxy(x--, y); printf("%s", m[rn]);  break;
		case 14:  gotoxy(x--, y); printf("%s", m[rn]);  break;
		case 15:  gotoxy(x, y--); printf("%s", m[rn]);  break;
		case 16:  gotoxy(x++, y); printf("%s", m[rn]);  break;
		case 17:  gotoxy(x++, y); printf("%s", m[rn]);  break;
		case 18:  gotoxy(x++, y); printf("%s", m[rn]);  break;
		case 19:  gotoxy(x, y++); printf("%s", m[rn]);  break;
		case 20:  gotoxy(x, y++); printf("%s", m[rn]);  break;
		case 21:  gotoxy(x, y++); printf("%s", m[rn]);  break;
		case 22:  gotoxy(x++, y); printf("%s", m[rn]);  break;
		case 23:  gotoxy(x, y++); printf("%s", m[rn]);  break;
		case 24:  gotoxy(x++, y); printf("%s", m[rn]);  break;
		case 25:  gotoxy(x, y--); printf("%s", m[rn]);  break;
		case 26:  gotoxy(x, y--); printf("%s", m[rn]);  break;
		case 27:  gotoxy(x++, y); printf("%s", m[rn]);  break;
		}

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[rn]);
		//화살표 출력
	}
}








//게임 시작
void game() {
	system("cls");
	CursorView(); //커서 숨기기
	showScore();//점수판
	showHeart();//목숨판
	mission(); //미션

	map(); //맵 그리기



	system("pause>null\n");
}
void main() {


	CursorView();
	system("mode con: cols=120 lines=30"); 
	system("title 무궁화꽃이 피었습니다");

	title();
	showMenu();

	while (1) {
		switch (menu()) {
		case 0: 	input = 1;  game(); break; //게임시작
		case 2: exit(0);  break; // 게임종료
		//case esc: main() break;
		}

	}
	system("pause>null\n");
}

