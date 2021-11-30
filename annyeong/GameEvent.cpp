#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "StatData.h" // ����ü, �Լ� ���� ����� �������

bool eventExection[5] = { false }; // �̺�Ʈ �б��� �������� �ʱ�ȭ
char text[1000]; // �ؽ�Ʈ �����ִ� ����

void prologue() { // ���ѷα� �����ִ� �Լ�.
	system("cls");
	FILE* f = 0; // ���� ������ �Լ�.
	fopen_s(&f, "story\\prologue.txt", "r"); // ������ ����.
	if (f == NULL) // ���� �����Ϳ� ������ ���� ��...
		printf("�̺�Ʈ ������ �������� �ʽ��ϴ�!.\n\n");
	printf("\t���ѷα� ~~ ����\n");
	while (1) {
		fgets(text, sizeof(text), f);
		// Ư�� ���ڿ��� ã�Ƽ�. �÷��̾��� �̸��� ����Ѵ�.
		// �÷��̾� �̸��� ����ü ���������� ����Ǿ��ִ�. (������� ����)
		if (strstr(text, "��")) printf("%s", player.name);
		if (feof(f)) break; // ������ ������ ���� ����.
		for (int i = 0; i < strlen(text); i++) {
			printf("%c", text[i]);
			Sleep(50);
		}
		printf("\n");
	}
	system("pause");
	system("cls");
	fclose(f);
	printf("ó�� �÷��� �Ͻ� ���� ȯ���մϴ�!\n");
}

void chapterLoad(int t) { // é�� �� ���� ���� ���ؼ� �����ִ� �Լ�.
	system("cls");
	FILE* f = 0; // ���� ������ �Լ�.
	if(t == 1) // ���� 5
		fopen_s(&f, "story\\chap1.txt", "r"); // ������ ����.
	if (t == 2) // ���� 10
		fopen_s(&f, "story\\chap2.txt", "r"); // ������ ����.
	if (t == 3) // ���� 15
		fopen_s(&f, "story\\chap3.txt", "r"); // ������ ����.
	if (t == 4) // ���� 20
		fopen_s(&f, "story\\chap4.txt", "r"); // ������ ����.
	if (t == 5) // ���� 25
		fopen_s(&f, "story\\chap5.txt", "r"); // ������ ����.
	if (t == 6) { // ���� 30 (���� ���� ����)
		fopen_s(&f, "story\\chap6.txt", "r"); // ������ ����.
		if (f == NULL) // ���� �����Ϳ� ������ ���� ��...
			printf("�̺�Ʈ ������ �������� �ʽ��ϴ�!.\n\n");
		printf("\t-- CHAPTER %d --\n", t);
		while (1) {
			fgets(text, sizeof(text), f);
			if (feof(f)) break; // ������ ������ ���� ����.
			// Ư�� ���ڿ��� ã�Ƽ�. �÷��̾��� �̸��� ����Ѵ�.
			// �÷��̾� �̸��� ����ü ���������� ����Ǿ��ִ�. (������� ����)
			if (strstr(text, "��")) printf("%s", player.name);
			for (int i = 0; i < strlen(text); i++) {
				printf("%c", text[i]);
				Sleep(50);
			}
			printf("\n");
		}
		system("pause");
		system("cls");
		bool vic = bossHunt(); // ���� ���Ϳ� ��¯�߱�
		if (vic) { // ���������� �̰�ٸ�?
			fopen_s(&f, "story\\happy_end.txt", "r"); // ������ ����.
		}
		else { // ������.
			fopen_s(&f, "story\\bad_end.txt", "r"); // ������ ����.
		}
	}
	if (f == NULL) // ���� �����Ϳ� ������ ���� ��...
		printf("�̺�Ʈ ������ �������� �ʽ��ϴ�!.\n\n");
	printf("\t-- CHAPTER %d --\n", t);
	while (1) {
		fgets(text, sizeof(text), f);
		if (feof(f)) break; // ������ ������ ���� ����.
		// Ư�� ���ڿ��� ã�Ƽ�. �÷��̾��� �̸��� ����Ѵ�.
		// �÷��̾� �̸��� ����ü ���������� ����Ǿ��ִ�. (������� ����)
		if (strstr(text, "��")) printf("%s", player.name);
		for (int i = 0; i < strlen(text); i++) {
			printf("%c", text[i]);		
			Sleep(50);
		}
		printf("\n");
	}
	system("pause");
	system("cls");
	fclose(f);
	printf("CHAPTER %d���� �Ϸ��Ͽ����ϴ�.\n", t);
}

void Quiz(int level) {
	int choice;
	if (level == 5) {
		while (1) {
			printf("���� �� ��¿� ���Ǵ� ��ɾ��?\n 1. printf\t2. scanf\n 3. int\t\t4. double \n\n");
			printf("������ �Է����ּ���!>> ");
			scanf_s("%d", &choice);
			if (choice == 1) { // ���� �Է��ϸ�.
				printf("�����Դϴ�!\n");
				break;
			} // �� ���� �Էµ���.
			else printf("�����Դϴ�. �ٽ� �ѹ� �����غ�����.\n\n");
		}
	}
	if (level == 10)
	{
		while (1) {
			printf("���� �� �ݺ����� ���Ǵ� ��ɾ��?\n 1. if\t2. for\n 3. double\t\t4. int \n\n");
			printf("������ �Է����ּ���!>> ");
			scanf_s("%d", &choice);
			if (choice == 2) { // ���� �Է��ϸ�.
				printf("�����Դϴ�!\n");
				break;
			} // �� ���� �Էµ���.
			else printf("�����Դϴ�. �ٽ� �ѹ� �����غ�����.\n\n");
		}
	}
	if (level == 15)
	{
		while (1) {
			printf("���� �� ���α׷��־��׽ǽ� ������ ������?\n 1. ������\t2. ������\n 3. ������\t\t4. ������ \n\n");
			printf("������ �Է����ּ���!>> ");
			scanf_s("%d", &choice);
			if (choice == 2) { // ���� �Է��ϸ�.
				printf("�����Դϴ�!\n");
				break;
			} // �� ���� �Էµ���.
			else printf("�����Դϴ�. �ٽ� �ѹ� �����غ�����.\n\n");
		}
	}
	if (level == 20)
	{
		while (1) {
			printf("���� �� ��������, ��������, �繰���ͳ� �� ICT����� ������ ���ǰ��� �ش�ȭ�ϴ� �����?\n 1. ��Ƽ����\t2. �ó�����\n 3. ��Ÿ����\t\t4. �и����� \n\n");
			printf("������ �Է����ּ���!>> ");
			scanf_s("%d", &choice);
			if (choice == 3) { // ���� �Է��ϸ�.
				printf("�����Դϴ�!\n");
				break;
			} // �� ���� �Էµ���.
			else printf("�����Դϴ�. �ٽ� �ѹ� �����غ�����.\n\n");
		}
	}
	if (level == 25)
	{
		while (1) {
			printf("���� �� ��ǻ�Ͱ� ������ �� �ִ� ����Ʈ���� ���� ��Ģ��? \n 1. ���ڵ�\t2. XML\n 3. �׷ν���ŷ\t\t4. ��ŷ \n\n");
			printf("������ �Է����ּ���!>> ");
			scanf_s("%d", &choice);
			if (choice == 1) { // ���� �Է��ϸ�.
				printf("�����Դϴ�!\n");
				break;
			} // �� ���� �Էµ���.
			else printf("�����Դϴ�. �ٽ� �ѹ� �����غ�����.\n\n");
		}
	}
	if (level == 30)
	{
		while (1) {
			printf("���� �� ����� ����̽��� ������ ��ȣȭ�Ͽ� ��ȣ�� �����ϱ� ���ؼ� �������� ������ �䱸�ϴ� ���˴�?\n 1. ���̽�\t2. �Ĺ�\n 3. �����丵\t\t4. �������� \n\n");
			printf("������ �Է����ּ���!>> ");
			scanf_s("%d", &choice);
			if (choice == 4) { // ���� �Է��ϸ�.
				printf("�����Դϴ�!\n");
				break;
			} // �� ���� �Էµ���.
			else printf("�����Դϴ�. �ٽ� �ѹ� �����غ�����.\n\n");
		}
	}
	system("pause");
	system("cls");
}