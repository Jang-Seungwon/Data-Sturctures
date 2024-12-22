#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define MAX_SIZE 20000

typedef struct {
	int num;
	char name[7];
	int score;
} student;

student STU[MAX_SIZE];
int current_size = 10000;

void swap(student* pa, student* pb) {
	student temp = *pa;
	*pa = *pb;
	*pb = temp;
}

void Insert_Record(student* STU) {
	printf("\n>> Enter num name score\n");
	int in_num, in_score;
	char in_name[7];
	scanf("%d %s %d", &in_num, in_name, &in_score);

	if (current_size >= MAX_SIZE) {
		printf("Error: Database is full!\n");
		return;
	}

	for (int i = current_size; i > in_num - 1; i--) {
		STU[i] = STU[i - 1];
		STU[i].num++; // Update numbers
	}
	STU[in_num - 1].num = in_num;
	strcpy(STU[in_num - 1].name, in_name);
	STU[in_num - 1].score = in_score;

	current_size++;

	FILE* fp = fopen("test.txt", "wt");
	if (fp == NULL) { printf("error"); exit(-1); }
	for (int i = 0; i < current_size; i++) {
		fprintf(fp, "%d %s %d\n", STU[i].num, STU[i].name, STU[i].score);
	}
	fclose(fp);
	printf("Success\n");
}

void Delete_Record(student* STU) {
	printf("\nEnter name: ");
	char del_name[7];
	scanf("%s", del_name);

	int index = -1;
	for (int i = 0; i < current_size; i++) {
		if (strcmp(STU[i].name, del_name) == 0) {
			index = i;
			break;
		}
	}

	if (index == -1) {
		printf("Record not found!\n");
		return;
	}

	for (int i = index; i < current_size - 1; i++) {
		STU[i] = STU[i + 1];
		STU[i].num--; // Update numbers
	}
	current_size--;

	FILE* fp = fopen("test.txt", "wt");
	if (fp == NULL) { printf("error"); exit(-1); }
	for (int i = 0; i < current_size; i++) {
		fprintf(fp, "%d %s %d\n", STU[i].num, STU[i].name, STU[i].score);
	}
	fclose(fp);
	printf("Success\n");
}

void List_Record(student* STU) {
	printf("\n>> Enter Name: ");
	char List_Name[7];
	scanf("%s", List_Name);
	for (int i = 0; i < current_size; i++) {
		if (strcmp(STU[i].name, List_Name) == 0) {
			printf("%d %s %d\n", STU[i].num, STU[i].name, STU[i].score);
		}
	}
}

void Sort_UpName(student* STU) {
	for (int i = 0; i < current_size - 1; i++) {
		for (int j = i + 1; j < current_size; j++) {
			if (strcmp(STU[i].name, STU[j].name) > 0) {
				swap(&STU[i], &STU[j]);
			}
		}
	}

	FILE* fp = fopen("test.txt", "wt");
	for (int i = 0; i < current_size; i++) {
		fprintf(fp, "%d %s %d\n", STU[i].num, STU[i].name, STU[i].score);
	}
	fclose(fp);
	printf("Sorted by Name Ascending\n");
}

void Sort_DownName(student* STU) {
	for (int i = 0; i < current_size - 1; i++) {
		for (int j = i + 1; j < current_size; j++) {
			if (strcmp(STU[i].name, STU[j].name) < 0) {
				swap(&STU[i], &STU[j]);
			}
		}
	}

	FILE* fp = fopen("test.txt", "wt");
	for (int i = 0; i < current_size; i++) {
		fprintf(fp, "%d %s %d\n", STU[i].num, STU[i].name, STU[i].score);
	}
	fclose(fp);
	printf("Sorted by Name Descending\n");
}

void Sort_UpScore(student* STU) {
	for (int i = 0; i < current_size - 1; i++) {
		for (int j = i + 1; j < current_size; j++) {
			if (STU[i].score < STU[j].score) {
				swap(&STU[i], &STU[j]);
			}
		}
	}

	FILE* fp = fopen("test.txt", "wt");
	for (int i = 0; i < current_size; i++) {
		fprintf(fp, "%d %s %d\n", STU[i].num, STU[i].name, STU[i].score);
	}
	fclose(fp);
	printf("Sorted by Score Ascending\n");
}

void Sort_DownScore(student* STU) {
	for (int i = 0; i < current_size - 1; i++) {
		for (int j = i + 1; j < current_size; j++) {
			if (STU[i].score > STU[j].score) {
				swap(&STU[i], &STU[j]);
			}
		}
	}

	FILE* fp = fopen("test.txt", "wt");
	for (int i = 0; i < current_size; i++) {
		fprintf(fp, "%d %s %d\n", STU[i].num, STU[i].name, STU[i].score);
	}
	fclose(fp);
	printf("Sorted by Score Descending\n");
}

void Write_DB(student* STU) {
	FILE* fp = fopen("test_new.txt", "wt");
	for (int i = 0; i < current_size; i++) {
		fprintf(fp, "%d %s %d\n", STU[i].num, STU[i].name, STU[i].score);
	}
	fclose(fp);
	printf("Database written successfully!\n");
}

int main() {
	srand(time(NULL));
	FILE* fp = fopen("test.txt", "wt");
	if (fp == NULL) { printf("error"); exit(-1); }
	for (int i = 0; i < current_size; i++) {
		STU[i].num = i + 1;
		for (int j = 0; j < 6; j++) {
			STU[i].name[j] = 'a' + rand() % 26;
		}
		STU[i].name[6] = '\0';
		STU[i].score = rand() % 101;
		fprintf(fp, "%d %s %d\n", STU[i].num, STU[i].name, STU[i].score);
	}
	fclose(fp);

	while (1) {
		char command[20];
		printf("Command? (insert, delete, list, sortupname, sortdownname, sortupscore, sortdownscore, write, exit): ");
		scanf("%s", command);
		if (strcmp(command, "insert") == 0) Insert_Record(STU);
		else if (strcmp(command, "delete") == 0) Delete_Record(STU);
		else if (strcmp(command, "list") == 0) List_Record(STU);
		else if (strcmp(command, "sortupname") == 0) Sort_UpName(STU);
		else if (strcmp(command, "sortdownname") == 0) Sort_DownName(STU);
		else if (strcmp(command, "sortupscore") == 0) Sort_UpScore(STU);
		else if (strcmp(command, "sortdownscore") == 0) Sort_DownScore(STU);
		else if (strcmp(command, "write") == 0) Write_DB(STU);
		else break;
	}
	return 0;
}
