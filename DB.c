void login() {
	FILE* fp;
	char ID[20];
	char PW[20];
	char cID[20];
	char cPW[20];
	int sw = 0;

	printf("ID를 입력하세요 : ");
	scanf("%s", ID);

	if ((fp = fopen("membership.txt", "r")) == NULL) {
		printf("파일 오류");
		exit(1);
	}

	while (!feof(fp)) {	//** while1
		fscanf(fp, "%s", cID);

		if (strcmp(ID, cID) == 0) {	//** ID값 비교
			sw = 1;
			break;
		}
	}	//** while1_end

	if (sw == 0) {
		printf("일치하는 ID가 없습니다.");
	}
	else {
		printf("PW를 입력하세요 : ");
		scanf("%s", PW);

		fseek(fp, 1L, SEEK_CUR);
		//fread(cPW, sizeof(char), 1, fp);
		printf("%s", cPW);
	}
}

void membership() {
	typedef struct human {
		//char name[20];
		char ID[20];
		char PW[20];
		//int age;
	}human;

	FILE* fp;
	human man;
	char cID[20];
	int sw = 0;

	while (1) {		//** while1
		printf("ID를 입력하세요 : ");
		scanf("%s", man.ID);

		if ((fp = fopen("membership.txt", "r")) == NULL) {
			printf("파일 오류");
			exit(1);
		}

		while (!feof(fp)) {	//** while2
			fscanf(fp, "%s", cID);

			if (strcmp(man.ID, cID) == 0) {	//** ID값 비교
				printf("중복되는 아이디가 있습니다.\n");
				sw = 1;
				break;
			}
		}	//** while2_end

		if (sw == 0) {
			break;
		}
	}	//** while1_end
	fclose(fp);

	printf("PW를 입력하세요 : ");
	scanf("%s", man.PW);

	if ((fp = fopen("membership.txt", "a")) == NULL) {
		printf("파일 오류");
		exit(1);
	}

	fprintf(fp, "%s %s\n", man.ID, man.PW);
	
	fclose(fp);
	printf("회원가입이 되었습니다.\n");
}