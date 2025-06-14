#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include<string.h>
#define Max 1000
#define NumMaps 5  // Number of maps you have

// 2일차 카운트 ,출력 이미지 변경,미로 탈출 지점
// 3일차 last함수,movable_check 함수, SelectMap함수
// 4일차 BFS알고리즘 함수,방향키로도 상하좌우 가능하게 만듬,crrunt count 함수
// 5일차 점수 추가,맵 크기 키울수 있게함,맵 개수 늘림,다시하기 기능 ak드는 중
// 6일차 다시하기 기능 완성 (5월 10일)
// 7일차 구상도,스코어 바 뼈대 만듬 (6월 7일)
// 8일차 스코어보드, 각종 버그 제거 (6월 8일)

int x, y;
int arr[Max][Max] = { 0, };
int lastnum = 0;
int crrunt_move_count;
int Mapindex;
int maxpoint[NumMaps] = {0,};
int cnt = 0;
//맵 입력 출력 함수
void SelectMap(int Mapindex) {

	int mapsScale[NumMaps][2] = {
		{11, 9},
		{11, 9},
		{11, 9},
		{11, 9},
		{13, 11}
	};
	int maps[NumMaps][Max][Max] = {
		{
			{100, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0},
			{1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1},
			{1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1},
			{0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1},
			{1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1},
			{1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1},
			{1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1},
			{0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1},
			{1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 3}
		},
		{
			{100, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0},
			{1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1},
			{1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1},
			{0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1},
			{1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1},
			{1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1},
			{1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
			{0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1},
			{1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 3}
		},
		{
			{100, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1},
			{1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0},
			{0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0},
			{1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0},
			{0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
			{1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0},
			{1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1},
			{0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0},
			{1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 3}
		},
		{
			{0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1},
			{1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0},
			{0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0},
			{1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0},
			{0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1},
			{1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0},
			{1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 100},
			{0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3}
		},
		{
			{0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0},
			{1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0},
			{0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1},
			{1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0},
			{0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0},
			{1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0},
			{1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 100, 1, 1},
			{1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1},
			{1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1},
			{0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0},
			{0, 3, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
		},
	};

	x = mapsScale[Mapindex][0], y = mapsScale[Mapindex][1];

	for (int i = 0; i < Max; i++) {
		for (int j = 0; j < Max; j++) {
			arr[i][j] = maps[Mapindex][i][j];
		}
	}
		
}

int place_value(int n) {
	int c = 1;
	while (1) {
		if (n < 10) {
			return c;
		}
		else {
			n = n / 10;
			c++;
		}
	}
}


// 구상도
//■■■■■■■■■■■■■       ║  
//■▲              ■  ■■       ║  ┌───────────────┐
//■  ■■■  ■    ■    ■       ║  │              : 78점          │
//■      ■■■■  ■■  ■       ║  └───────────────┘
//■■■        ■  ■    ■       ║  ┌───────────────┐
//■        ■■■  ■■  ■       ║  │ 최고점수:???                 │ 
//■  ■  ■              ■       ║  └───────────────┘
//■            ■■■■■■       ║  ┌───────────────┐
//■■  ■  ■  ■        ■       ║  │ Count : 0                    │
//■        ■        ■○■       ║  │ Current Count : 20           │
//■■■■■■■■■■■■■       ║  └───────────────┘


char* scoreboard(int c) {
	static char str[100];
	if (c > y+1) {
		return 0;
	}
	else if (c == 0 || c > 10) {
		printf("       ||");
		//strcpy(str, "       ||");
	}
	else if (c == 1 || c == 4 || c == 7) {
		printf("       ||     ┌────────────────────────────┐");
		/*strcpy(str, "       ||     ┌────────────────────────────┐");*/
	}
	else if (c == 3 || c == 6 || c == 10) {
		printf("       ||     └────────────────────────────┘");
		/*strcpy(str, "       ||     └────────────────────────────┘");*/
	}
	else if (c == 2) {
		printf("       ||     │         Scoreboard         │");
		/*strcpy(str, "       ||     │ Scoreboard : %d점          │");*/
	}
	else if (c == 5) {
		if (maxpoint[Mapindex] == -1) {
			printf("       ||     │  최고점수: ?점           │");
		}
		else {
			printf("       ||     │  최고점수: %d점",   maxpoint[Mapindex]);
			for (int i = 0; i < 14 - place_value(maxpoint[Mapindex]); i++) {
				printf(" ");
			}
			printf("│");
		}
		/*strcpy(str, "       ||     │ 최고점수:???               │");*/
	}
	else if (c == 8) {
		printf("       ||     │  Count : %d",cnt);
		for (int i = 0; i < 18 - place_value(cnt); i++) {
			printf(" ");
		}
		printf("│");
		/*strcpy(str, "       ||     │ Count : 0                  │")*/;
	}
	else if (c == 9) {
		printf("       ||     │  Current Count : %d        │", crrunt_move_count);
		/*strcpy(str, "       ||     │ Current Count : 20         │");*/
	}


	return 0;
}

void PrintMap(int cnt) {
	int num = 0,p;
	for (int i = 0; i < x+2; i++) {
		printf("■");
	}
	scoreboard(0);

	printf("\n");
	for (int i = 0; i < y; i++) {
		printf("■");
		for (int j = 0; j < x; j++) {
			if (arr[i][j] == 0) {
				printf("■");
			}
			else if (arr[i][j] == 1) {
				printf("  ");
			}
			else if (arr[i][j] == 100) {
				printf("▲");
			}
			else if(arr[i][j] == 3){
				printf("○");
			}
			else if (arr[i][j] == 4) {
				printf("◎");
				
				num = last();
			}
		}
		printf("■");
		scoreboard(i + 1);

		printf("\n");
	}
	for (int i = 0; i < x + 2; i++) {
		printf("■");
	}


	
	scoreboard(y+1);
	printf("\n");
	//이쪽부터
	//for (int i = 0; i < x+1 ; i++) {
	//	printf("  ");
	//}
	//printf("||");
	//scoreboard(y + 2);

	//printf("\ncount: %d", cnt);
	//for (int i = 0; i < 2*x - 5 - (place_value(cnt)); i++) {
	//	printf(" ");
	//}
	//printf("||");
	//scoreboard(y + 2);
	//printf("\n");

	//for (int i = 0; i < x + 1; i++) {
	//	printf("  ");
	//}
	//printf("||");
	//scoreboard(y + 4);

	//printf("\ncrrunt count: %d", crrunt_move_count);
	//for (int i = 0; i < 2 * x - 12 - (place_value(crrunt_move_count)); i++) {
	//	printf(" ");
	//}
	//printf("||");
	//scoreboard(y + 3);
	//여기까지는 나중에 고칠 거임 버그는 아닌데 나중엔 필요 없음 일단 주석 처리함
	if (num == 1) {
		p = point(cnt);
		if (maxpoint[Mapindex] < p) {
			maxpoint[Mapindex] = p;
		}
		printf("\n끝");
		printf("\n\n  다시하고 싶으면 R키를 누르시요.");
	}
}







int last() {
	lastnum = 1;
	return 1;
}

int movable_check(int x_p,int y_p,int num) {
	//num 은  1~4까지만 1상 2하 3좌 4우
	if (num == 1) {
		if (y_p > 0 && arr[y_p - 1][x_p] != 0) {
			return 1;
		}
	}
	else if (num == 2) {
		if (y_p < y - 1 && arr[y_p + 1][x_p] != 0) {
			return 1;
		}
	}
	else if (num == 3) {
		if (x_p < x - 1 && arr[y_p][x_p + 1] != 0) {
			return 1;
		}
	}
	else if (num == 4) {
		if (x_p > 0 && arr[y_p][x_p - 1] != 0) {
			return 1;
		}
	}
	return 0;
}

int checkBFS() {
	int cpy_arr[Max][Max] = { 0, };
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
		    /*printf("%d", arr[i][j]);*/
			cpy_arr[i][j] = arr[i][j];
		}
	/*	printf("\n");*/
	}
	
	int move_num = 100;
	int di[4] = { 0, 1, 0, -1 };
	int dj[4] = { 1, 0, -1, 0 };
	while (1) {
		for (int i = 0; i < y; i++) {
			for (int j = 0; j < x; j++) {
				if (cpy_arr[i][j] == move_num) {
					for (int d = 0; d < 4; d++) {
						if (i + di[d] >= 0 && i + di[d] < y && j + dj[d] >= 0 && j + dj[d] <= x) {
							if (cpy_arr[i + di[d]][j + dj[d]] == 3) {
								return move_num - 100 + 1;
							}
							else if (cpy_arr[i + di[d]][j + dj[d]] == 1) {
								cpy_arr[i + di[d]][j + dj[d]] = move_num + 1;
							}
						}
					}
				}
			}
		}
		move_num++;

		//for (int i = 0; i < y; i++) {
		//	for (int j = 0; j < x; j++) {
		//		printf("%d\t", cpy_arr[i][j]);
		//	}
		//	printf("\n");
		//}
		//printf("\n"); printf("\n"); printf("\n");
	}
	return 0;
}


int point(int cnt) {
	int p;
	if (100 - 5*(cnt - crrunt_move_count) >= 30) {
		p = 100 - 5 * (cnt - crrunt_move_count);
	}
	else {
		p = 30 - 6 * (cnt - 14 - crrunt_move_count);
	}
	if (p < 0) {
		p = 0;
	}
	return p;
	
}





void main() {

	while (1) {
		printf("맵 번호를 입력해주세요 (1~5)\n");
		scanf("%d", &Mapindex);
		Mapindex--;
		if (Mapindex >= 0 && Mapindex < NumMaps) {
			system("cls");
			SelectMap(Mapindex);
		}
		else {
			continue;
		}



		crrunt_move_count = checkBFS();

		int x_p = 0, y_p = 0;

		for (int i = 0; i < y; i++) {
			for (int j = 0; j < x; j++) {
				if (arr[i][j] == 100) {
					x_p = j, y_p = i;
					break;
				}
			}
		}

		char a = 'a', n, m;
		int breakcnt = 0;

		while (a != 'p') {
			while (1) {
			system("cls");
			PrintMap(cnt);
			
				n = getch();
				a = n;

			
				if (lastnum != 1) {
					break;
				}
				if (a == 'r' || a == 'R') {
					cnt = 0;
					breakcnt = 1;
					lastnum = 0;
					break;
				}
				else {
					continue;
				}
			}
			if (breakcnt == 1) {
				break;
			}




			if (a == 'a' || a == 'A' || a == 75) {
				if (movable_check(x_p, y_p, 4) == 1) {
					if (arr[y_p][x_p - 1] == 3) {
						arr[y_p][x_p] = 1;
						arr[y_p][x_p - 1] = 4;
						cnt++;
					}
					else {
						arr[y_p][x_p] = arr[y_p][x_p - 1];
						arr[y_p][x_p - 1] = 100;
						x_p -= 1;
						cnt++;
					}
				}
				continue;
			}

			else if (a == 's' || a == 'S' || a == 80) {
				if (movable_check(x_p, y_p, 2) == 1) {
					if (arr[y_p + 1][x_p] == 3) {
						arr[y_p][x_p] = 1;
						arr[y_p + 1][x_p] = 4;
						cnt++;
					}
					else {
						arr[y_p][x_p] = arr[y_p + 1][x_p];
						arr[y_p + 1][x_p] = 100;
						y_p += 1;
						cnt++;
					}
				}
				continue;
			}

			else if (a == 'd' || a == 'D' || a == 77) {
				if (movable_check(x_p, y_p, 3) == 1) {
					if (arr[y_p][x_p + 1] == 3) {
						arr[y_p][x_p] = 1;
						arr[y_p][x_p + 1] = 4;
						cnt++;
					}
					else {
						arr[y_p][x_p] = arr[y_p][x_p + 1];
						arr[y_p][x_p + 1] = 100;
						x_p += 1;
						cnt++;
					}
				}
				continue;
			}

			else if (a == 'w' || a == 'W' || a == 72) {
				if (movable_check(x_p, y_p, 1) == 1) {
					if (arr[y_p - 1][x_p] == 3) {
						arr[y_p][x_p] = 1;
						arr[y_p - 1][x_p] = 4;
						cnt++;
					}
					else {
						arr[y_p][x_p] = arr[y_p - 1][x_p];
						arr[y_p - 1][x_p] = 100;
						y_p -= 1;
						cnt++;
					}
				}
				continue;
			}

		}
		system("cls");

	}
}


