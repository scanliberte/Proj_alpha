#include "func.h"

char* pID;

void select_1() {
	int sel = 0, sel1 = 0;

	system("cls");

	while (1) {	//** while2
		system("cls");
		gotoxy(gX,gY);
		printf("----------메인화면입니다----------");
		gotoxy(gX, gY+2);
		printf("1. 로그인");
		gotoxy(gX, gY+3);
		printf("2. 회원가입");
		gotoxy(gX, gY+4);
		printf("이용하실 번호를 입력하세요 : ");
		scanf_s("%d", &sel1);

		switch (sel1) {	//** switch2
		case 1:
			system("cls");
			gotoxy(gX, gY);
			printf("-----------로그인-----------\n");
			pID = login();	//** DB 로그인 함수

			if (!strcmp(pID, "1")) {
				system("cls");
				gotoxy(gX, gY+2);
				printf("없는 아이디입니다. 로그인 화면으로 이동합니다.\n");
				system("pause");
			}
			else if (!strcmp(pID, "2")) {
				system("cls");
				gotoxy(gX, gY+2);
				printf("비밀번호를 틀리셨습니다. 로그인 화면으로 이동합니다.\n");
				system("pause");
			}
			else if (strcmp(pID, "root")) {
				select_2();
			}
			else {
				gotoxy(gX, gY);
				printf("관리자 모드\n");
				//관리자 모드
				root();
			}

			break;

		case 2:
			system("cls");
			gotoxy(gX, gY);
			printf("-----------회원가입-----------\n");
			membership();	//** DB 회원가입 함수
			break;
		default:
			if (sel1 == -1) {
				exit(1);
			}
			else {
				gotoxy(gX, gY+2);
				printf("잘못입력하셨습니다\n");
				break;
			}
		}	//** switch2_end
	}	//** while_end2
}

void select_2() {
	int sel = 0;
	int sw = 1;

	while (sw) {
		system("cls");
		gotoxy(gX, gY);
		printf("----------로그인 성공------------\n");
		gotoxy(gX, gY+2);
		printf("1.주문\n");
		gotoxy(gX, gY+3);
		printf("2.캐쉬충전\n");
		gotoxy(gX, gY+4);
		printf("3.캐쉬 및 마일리지 확인\n");
		gotoxy(gX, gY+5);
		printf("4.회원탈퇴\n");
		gotoxy(gX, gY+6);
		printf("번호를 입력하세요(-1 = 로그인화면) : ");
		scanf_s("%d", &sel);

		switch (sel) {
		case 1:
			system("cls");
			gotoxy(gX, gY);
			printf("-----------주문-----------\n");
			//** 메뉴판 db
			//** 주문 db
			order();
			//spend_point();
			break;
		case 2:
			system("cls");
			gotoxy(gX, gY);
			printf("-----------캐쉬충전-----------\n");
			charge_cashDB();
			break;
		case 3:
			system("cls");
			gotoxy(gX, gY);
			printf("-----------캐쉬 및 마일리지 확인-----------\n");
			check_cash_point();
			break;
		case 4:
			system("cls");
			gotoxy(gX, gY);
			printf("-----------회원탈퇴-----------\n");
			member_leaveDB();
			gotoxy(gX, gY+2);
			printf("회원탈퇴 되었습니다.\n");
			gotoxy(gX, gY+3);
			printf("로그인 화면으로 이동합니다.\n");
			system("pause");
			sel = -1;
			break;
		default:
			if (sel == -1) {
				sw = 0;
				break;
			}
			gotoxy(gX, gY+2);
			printf("잘못입력하셨습니다\n");
			break;
		}
		if (sel == -1) {
			sw = 0;
			break;
		}
	}
}

void order() {
	int sel = 0;
	int amount = 0;
	char address[100] = { 0, };
	int i=0;

	while (1) {
		gotoxy(gX, gY);
		printf("----------category----------\n");
		gotoxy(gX, gY+2);
		printf("1. 육류\n");
		gotoxy(gX, gY+3);
		printf("2. 과일\n");
		gotoxy(gX, gY+4);
		printf("3. 채소\n");
		gotoxy(gX, gY+5);
		printf("4. 생선\n");
		gotoxy(gX, gY + 6);
		printf("번호를 입력하세요 (-1 = 뒤로) : ");
		scanf_s("%d", &sel);

		if (sel > 0 && sel < 5) {
			i = menuDB(sel);
			break;
		} 
		else if (sel == -1) {
			system("cls");
			gotoxy(gX, gY+2);
			printf("주문을 끝냅니다.\n");
			break;
		} 
		else {
			gotoxy(gX, gY+2);
			printf("잘못입력하셨습니다.\n");
			system("pause");
		}

		//++ 주문추가 db
	}	//** end_while
	gotoxy(gX, gY + 2 + i + 1);
	printf("몇번 품목을 구입하시겠습니까 : ");
	scanf_s("%d", &selectedId);

	gotoxy(gX, gY + 2 + i + 2);
	printf("수량을 입력하세요 : ");
	scanf_s("%d", &amount);

	gotoxy(gX, gY + 2 + i + 3);
	printf("배송지를 입력하세요 : ");
	getchar();
	gets_s(address, sizeof(address));
	
	orderDB(amount, address);
}

void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

int root() {
	int sel = 0;
	int sw = 1;

	while (sw) {
		system("cls");
		gotoxy(gX, gY);
		printf("----------관리자 모드------------\n");
		gotoxy(gX, gY + 2);
		printf("1. 회원목록 출력\n");
		gotoxy(gX, gY + 3);
		printf("2. 주문 현황\n");
		gotoxy(gX, gY + 4);
		printf("3. 정산\n");
		gotoxy(gX, gY + 5);
		printf("번호를 입력하세요(-1 = 로그인화면) : ");
		scanf_s("%d", &sel);

		switch (sel) {
		case 1:
			system("cls");
			gotoxy(gX, gY);
			printf("-----------회원목록-----------\n");
			memberlist();
			//
			break;
		case 2:
			system("cls");
			gotoxy(gX, gY);
			printf("-----------주문 현황-----------\n");
			orderlist();
			//
			break;
		case 3:
			system("cls");
			gotoxy(gX, gY);
			printf("-----------정산-----------\n");
			income();
			//
			break;
		default:
			if (sel == -1) {
				sw = 0;
				break;
			}
			gotoxy(gX, gY + 2);
			printf("잘못입력하셨습니다\n");
			break;
		}
		if (sel == -1) {
			sw = 0;
			break;
		}
	}
}