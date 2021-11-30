#include <stdio.h>
#include <iostream>
#include <String>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h> // _getch() ����� ����...

#include "StatData.h" // ����ü, �Լ� ���� ����� �������
#define WEAPON "weapon.txt" // �ҽ����� �� ���ⵥ����
#define USERDATA "userdata.txt" // ���������� ���� (���Ӽ��̺� ����)
#define POTION "potion.txt" // �ҽ����� �� ���ǵ�����
#define MONSTER "monster_data.txt" // �ҽ����� �� ���͵�����

#define WEAPONSIZE 5 // ���ӿ� �ִ� ���� ���� (��� �����ؾ� ��)
#define POTIONSIZE 4 // ���ӿ� �ִ� ���� ���� (��� �����ؾ� ��)
#define MONSTERSIZE 11 // ���� ��ü �� (��� �����ؾ� ��)

People player; // ����ü �÷��̾� ���� ����.
Enemy monsterSelect[MONSTERSIZE]; // ���� ���� ����. (���� �迭�� ����� �� ����) 
Item weapon[WEAPONSIZE]; // ���� �� ���� ����ü ����
Item potion[POTIONSIZE]; // ���� �� ���� ����ü ����

// ����Ű�� ������ ��... ������ ��.
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80 
#define SPACE 32
#define ENTER 13

// ���� �ý��� ���ù�ȣ (������� 1 ~ 4)
enum { AT = 1, CHAT, ITEM, RUN };

// ���� ������ �������� ����
static Enemy* monster = monsterSelect;


int random(int set) { // �Ű������� �ƹ��͵� �Է����� ������ �⺻���� 10�̴�.
	srand(time(NULL));
	int random = (rand() % set) + 1; // 1 ~ 10 ���� ����, ������ Ȯ���� ���Ѵ�.
	return random;
}
int lostMoney() {
	// ���� 1 ~ 10�� 10�� ���ϰ� �÷��̾� ������ ���� 
	// ���� ������ ���� ���� �� ���� Ŀ����.
	int lostCost = random() * 10 * player.level;
	player.balance -= lostCost; // ��������� �÷��̾� �ڱݿ��� ����.
	return lostCost;
}
int getMoney() {
	// ���� 1 ~ 10�� 10�� ���ϰ� �÷��̾� ������ ���� 
	// ���� ������ ���� ���� �� ���� Ŀ����.
	int getCost = random() * 10 * player.level;
	player.balance += getCost; // ȹ������ �÷��̾� �ڱݿ��� ���Ѵ�.
	return getCost;
}
int getExp() {
	// ���� 1 ~ 10�� 10�� ���ϰ� �÷��̾� ������ ���� 
	// ���� ������ ���� ���� �� ���� Ŀ����.
	int getExp = random() * 10 * player.level;
	player.exp += getExp; // ��������� �÷��̾� �ڱݿ��� ����.
	return getExp;
}
int playerFight() {
	// �÷��̾��� ���ݷ¿��� ���� ���� * 0.2�� �� ������ ���� �ش�.
	int damage = player.attack - (monster->defense * 0.2);
	if (damage < 0) damage = 0; // �������� 0���� ������ 0���� �������. (������ ���溸�� �е����̿��� �׷�)
	monster->health -= damage; // ���� ü�¿��� ������ ����.
	return damage;
}
int monsterFight() {
	// �÷��̾��� ���ݷ¿��� ���� ���� * 0.2�� �� ������ ���� �ش�.
	int damage = monster->attack - (player.defense * 0.2);
	if (damage < 0) damage = 0; // �������� 0���� ������ 0���� �������.
	player.health -= damage; // ���� ü�¿��� ������ ����.
	return damage;
}
int keyControl() { // �Է��� Ű ���� ������ �ִ� �Լ�.
	char temp = _getch();
	if (temp == -32) { // 224�� �ԷµǸ�?
		temp = _getch(); // �ٽ� �� �� �д´�.
		return temp;
	}
}
int startMenu() { // ��ŸƮ �޴� ���. �޴� ���� �� 0 ~ 3 ���� ��ȯ.
	int x = 25, y = 12;
	gotoxy(x, y); // -2 �� �� �����̴�.
	printf("ó �� �� ��"); // 0��
	gotoxy(x, y + 1);
	printf("�� �� �� ��"); // 1��
	gotoxy(x, y + 2);
	printf("�� �� �� ��"); // 2��
	gotoxy(x, y + 3);
	printf("�� �� �� ��"); // 3��
	while (1) {
		int n = keyControl(); // Ű���� �������� �޾ƿ���
		switch (n) {
		case UP: // ���� ������ ���
			if (y > 12) {
				gotoxy(x - 3, y); // -2 �� �� �����̴�.
				printf("  "); // ȭ��ǥ �����
				gotoxy(x - 3, --y); // �Ʒ��� �̵�
				printf("��"); // �ٽ� �׸���
			}
			break;
		case DOWN: // �Ʒ�Ű ������ ���
			if (y < 15) {
				gotoxy(x - 3, y);
				printf("  ");
				gotoxy(x - 3, ++y);
				printf("��");
			}
			break;
		case SPACE:
			return y - 12;
		case ENTER:
			return y - 12;
		}
	}
}
void gotoxy(int x, int y) { // Ŀ�� ��ġ �̵��Լ�
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // �ܼ� �ڵ� ��������
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}
void colorText(int colorSet) {
	/*
		���� 0
	    ��ο� �Ķ� 1
		��ο� �ʷ� 2
		��ο� �ϴ� 3
		��ο� ���� 4
		��ο� ���� 5
		��ο� ��� 6
		ȸ�� 7
		��ο� ȸ�� 8
		�Ķ� 9
		�ʷ� 10
		�ϴ� 11
		���� 12
		���� 13
		��� 14
		�Ͼ� 15												
	*/	 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorSet);
}
void gameLogo() { // �� �� �״�� �ΰ��Դϴ�. (�ƽ�Ű ��Ʈ��� ī����)
	colorText(1);
	printf("\n ######   ######   ##  ##   ######     #####    #####     #####\n");
	printf("   ##     ##       ##  ##     ##       ##  ##   ##  ##   ##    \n");
	colorText(3);
	printf("   ##     #####     ####      ##       ##  ##   ##  ##   ##    \n");	
	printf("   ##     ##        ####      ##       #####    #####    ## ###\n");
	colorText(11);
	printf("   ##     ##       ##  ##     ##       ## ##    ##       ##  ##\n");
	printf("   ##     ######   ##  ##     ##       ##  ##   ##        #####\n\n");
	printf("=================================================================");
	colorText(15);
}

void nameSet() {
	printf("ȯ���մϴ�. ����! \n");
	printf("����� �̸��� �����Դϱ�? >> ");
	//scanf_s�� ���ڿ��� �Է¹��� �� �ڿ� �迭 ����� �Է������ ��.
	scanf_s("%s", player.name, sizeof(player.name)); //sizeof(player.name) = 30
	printf("�ݰ����ϴ�. %s��. \n", player.name);
	Sleep(500); // 0.5�� ����
	char write[7] = { 'E','N','J','O','Y','!'};
	for (int i = 0; i < strlen(write); i++) {
		printf("%c\t", write[i]);
		Sleep(300);
	}
	system("cls");
}
void expBar() {
	// �ۼ�Ʈ�� ���Ѵ� ~ 1~10 ! �ٸ� �󸶳� ä���� �����ִ� ����.
	int bar = (float)player.exp / (float)player.levelUp * 10;
	printf("EXP ");
	colorText(10);
	for (int i = 0; i < bar; i++)
		printf("��");
	for (int i = 0; i < 10 - bar; i++)
		printf("��");
	colorText(15);
	printf(" (%d/%d)", player.exp, player.levelUp);
}
void healthBar(int h, int mh) { // h ü�� / mh �ִ�ü��
	// �ۼ�Ʈ�� ���Ѵ� ~ 1~10 ! �ٸ� �󸶳� ä���� �����ִ� ����.
	int bar = (float)h / (float)mh * 10;
	printf("HP ");
	colorText(4);
	for (int i = 0; i < bar; i++)
		printf("��");
	for (int i = 0; i < 10 - bar; i++)
		printf("��");
	colorText(15);
	printf(" (%d/%d)", h, mh);
}
void ifExp() {
	int eventMaxLevel = 30;// �̺�Ʈ�� �߻��ϴ� ������ 30���� �����̴�. 5���� ������ �̺�Ʈ�� �߻�. (1...5...10...)
	if (player.exp > player.levelUp) {
		// �÷��̾� ����ġ�� ����ġ�� �Ѿ��ٸ�?
			// ����ġ ���� ����ġ ���� ������ �Ѱ��ֱ� ���� ~
		int tempExp = player.exp - player.levelUp;
		printf("\t���� ��!!! \n");
		player.level += 1; // �÷��̾� ������.
		printf("%s ������ %d�� �ö����ϴ�.\n", player.name, player.level);
		player.exp = 0; // ����ġ 0���� �ʱ�ȭ
		player.exp += tempExp; // ���������μ� ���� �ִ� ����ġ ��.
		player.levelUp += player.level * 100; // ����ġ ����ġ ������ ����� �÷���.
		player.maxHealth *= (player.level * 0.5); // �ִ�ü�� ������ ����� �÷���.
		player.health = player.maxHealth; // ü�� ȸ��.
		player.attack *= (player.level * 0.5); // ���ݷ� ������ ����� �÷���.
		player.defense *= (player.level * 0.5); // ���� ������ ����� �÷���.

		// �̺�Ʈ �߻� ĭ. �������� �� �� �̺�Ʈ�� �߻� ��ų�� �Ǵ��Ѵ�.
		// �̺�Ʈ�� �߻��ϴ� ������ 30���� �����̴�. 5���� ������ �̺�Ʈ�� �߻�. (1...5...10...)
		if ((player.level % 5) == 0) {
			if (player.level <= eventMaxLevel) { // �÷��̾� ������ 30���� ������...
				int temp = 0;
				temp += player.level / 5; // ������ 5�� ���� temp�� ������. é�� �������� �����ִ°���.
				if (temp == 0) return; // �ݸ� temp�� �ƹ��͵� ���ٸ� �׳� ����.
				else { // �ƴ϶��?
					chapterLoad(temp);
				}
			}
		}
		Quiz(player.level); // Ư�� ������ �޼����� ��, ���� �̺�Ʈ!
	}
}
void showMenu() {
	ifExp(); // ������ ���� �Ǵ�.
	printf("\n--------------------------------\n");
	printf("\t    GAME MENU\n");
	printf("--------------------------------\n");
	printf("�̸� : %s | ���� : %d | �� : %d \n", player.name, player.level, player.balance);
	expBar(); printf("\n"); // ����ġ ����
	printf("\n(1) ��  ��\t       * BATTLE\n");
	printf("(2) ��  ��\t       * SHOP\n");
	printf("(3) ��  ��\t       * STATUS\n");
	printf("(4) ��  ��\t       * EXIT\n");
}
void hunt()
{
	int choice; // ����ȭ�� ��ȣ �����Լ�
	int potionCount = 0; // ������ ��ȣ �ο�
	int potionArr[POTIONSIZE + 1] = { 0 }; // ������ �����ϱ� ����... �׷� �迭
	int temp = 0, itemTemp = 0, tempTurn = 1; // ��� ���ڸ� ������ ����
	monster = monsterSelect; // ������ ���� �ʱ�ȭ

	monsterDataLoad(); // ���� �����͸� �ҷ��´�.
	// �÷��̾� ������ ���������� ���Ͱ� �پ��ϰ� ���´�.
	if (player.level >= 1 && player.level < 10) { // ���� 10���� ���� �ڵ� �� 1 ~ 3���� �����Ѵ�.
		temp = random(3) - 1;
		monster += temp;
	}
	else if (player.level >= 10 && player.level < 20) { // ���� 10 ~ 20����
		// ���� �ڵ� �� 1 ~ 6���� �����Ѵ�.
		temp = random(6) - 1;
		monster += temp;
	}
	else if (player.level >= 20) { // ���� 20���ʹ�! ���� �ڵ� �� 1 ~ 10�� �� ����!
		temp = random(10) - 1;
		monster += temp;
	}
	// ������ ���Ͱ� ��������, �÷��̾� ������ ���� �ɷ�ġ�� �����Ѵ�.
	monster->level = player.level;
	monster->maxHealth *= monster->level; // �ִ�ü�� ������ ����� �÷���.
	monster->health = monster->maxHealth; // ü�� ȸ��.
	monster->attack *= (monster->level * 0.8); // ���ݷ� ������ ����� �÷���.
	monster->defense *= (monster->level * 0.8); // ���� ������ ����� �÷���.

	printf("�߻��� %s(��)�� ��Ÿ����! \n", monster->name);
	Sleep(500); // 0.5�� ����

	while (1) {

		if (tempTurn == 4) { // �Һ� ������ 3���� �Ǵ� �����̸� ȿ�� ����.
			itemTurn(itemTemp, 1);
			itemTemp = 0;
		}
		printf("\n--------------------------------\n");
		printf("\t    BATTLE\n");
		printf("--------------------------------\n");
		printf("Player ~ %s ", player.name);
		printf("\n"); healthBar(player.health, player.maxHealth); printf("\n\n");
		printf("Enemy  ~ %s ", monster->name);
		printf("\n"); healthBar(monster->health, monster->maxHealth); printf("\n\n");
		printf("--------------------------------\n");
		printf("   1) �����Ѵ� \t 2) ��    ��\n");
		printf("   3) �� �� �� \t 4) ��������\n");
		printf("--------------------------------\n");
		Sleep(500); // 0.5�� ����
		printf("%s(��)�� ������ �ұ�? >> ", player.name);
		scanf_s("%d", &choice);
		fseek(stdin, 0, SEEK_END);
		system("cls");

		switch (choice) {
		case AT:
			playerBattle(); 
			if (monster->health < 0) { // ���� HP �����ϸ� �̱��.
				printf("%s(��)�� ��������! \n", monster->name);
				Sleep(300); // 0.3�� ����
				printf("%s(��)�� ����ġ %d�� %d���� �����! \n", player.name, getExp(), getMoney());
				monster->health = 0; // ü�� �ʱ�ȭ
				monster->health += monster->maxHealth; // ü�� �ʱ�ȭ
				Sleep(2000);
				system("pause");
				system("cls");
				if (itemTemp != 0) {
					itemTurn(itemTemp, 1); // ���� ����
					itemTemp = 0;
				}
				return; // ���θ޴��� �̵�
			}
			monsterBattle();
			if (player.health < 0) { // �÷��̾ ����...
				printf("%s(��)�� �������� �й��ߴ�... \n", player.name);
				Sleep(300); // 0.3�� ����
				printf("%s(��)�� ġ���� %d���� �Ҿ���... \n", player.name, lostMoney());
				player.health = 0; // ü�� �ʱ�ȭ
				player.health += player.maxHealth; // ü�� �ʱ�ȭ
				Sleep(2000);
				system("pause");
				system("cls");
				if (itemTemp != 0) {
					itemTurn(itemTemp, 1); // ���� ����
					itemTemp = 0;
				}
				return; // ���θ޴��� �̵�
			}
			if (itemTemp != 0) {
				printf("%s��(��) ��� �� ��, %d�� °�Դϴ�. \n", potion[itemTemp - 1].name, tempTurn);
				tempTurn++; // ������ ����� �����ߴٸ�, �� ���� ���� ����.
			}
			Sleep(1000); // 1�� ����
			system("cls");
			break;
		case CHAT:
			printf("\n--------------------------------\n");
			printf("\t    PLAYER STATUS\n");
			printf("--------------------------------\n");
			printf("��  �� : %s\n", player.name);
			printf("��  �� : %d\n", player.level);
			printf("ü  �� : %d / %d\n", player.health, player.maxHealth);
			printf("���ݷ� : %d\n", player.attack);
			printf("���� : %d\n", player.defense);
			printf("\n--------------------------------\n");
			printf("\t    MONSTER STATUS\n");
			printf("--------------------------------\n");
			printf("��  �� : %s\n", monster->name);
			printf("��  �� : %d\n", monster->level);
			printf("ü  �� : %d / %d\n", monster->health, monster->maxHealth);
			printf("���ݷ� : %d\n", monster->attack);
			printf("���� : %d\n", monster->defense);
			printf("\n�������� - %s\n\n", monster->explain);
			system("pause");
			system("cls");
			break;
		case ITEM:
			for (int i = 0; i < POTIONSIZE; i++) {// ������ �ִ� �Һ�����۰� ���� ���.
				if (potion[i].possession == 1) {
					potionCount++;
					potionArr[potionCount] = potion[i].itemCode; // ���ǹ迭�� ����ī��Ʈ��� �������ڵ带 �ִ´�.
					// �������ڵ�) 1. HP���� 2. ����ȸ���� 3. ���������� 4. ��������� ... ���� ����
					printf("%d) %s %dEA \n", potionCount, potion[i].name, potion[i].count);
					printf("- %s\n", potion[i].explain);
				}
			}
			printf("\n");
			// ������ �������� �ϳ��� ���ٸ�?
			if (potionCount == 0) { printf("���� ����� �� �ִ� �������� �����ϴ�!\n"); break; } // ����ȭ������~ 
			while (1) {
				printf("%d ~ %d �� ����� ������ ���� | 0 ������ \n", 1, potionCount);
				printf("� �������� ���ðڽ��ϱ�? >> ");
				scanf_s("%d", &choice);
				if (choice >= 1 && choice <= potionCount) {
					for (int i = 0; i < POTIONSIZE; i++) {
						if (potionArr[choice] == potion[i].itemCode) { // ���ǹ迭�� �ִ� ���ڰ� �������ڵ�� ��ġ�� ��
							printf("%s�� ����Ͻðڽ��ϱ�? \n", potion[i].name);
							printf("1. �� | 2. �ƴϿ� >> ");
							scanf_s("%d", &choice);
							if (choice == 1) {
								printf("\n%s��(��) %s��(��) ����ߴ�!", player.name, potion[i].name);
								if (player.maxHealth <= player.health + potion[i].upHealth) { // ȸ�������� ��� �� �÷��̾��� �ִ�ü���� �Ѵ´ٸ�...
									temp = player.health + potion[i].upHealth - player.maxHealth; // ���� �� �󸶳� �ʰ��ϴ°�? ���
									player.health += (potion[i].upHealth - temp); // �ִ�ü���� ���� �ʵ��� ����.
									potion[i].count -= 1; // ���� ���� 1 ����
									if (potion[i].itemCode == 3 || potion[i].itemCode == 4) { // �����������̳� ��������� ��� ��
										if (itemTemp == 0) {
											itemTemp = potion[i].itemCode; // 3�� ���� ���� �������� ����� ����ϴ� ����. ���� ȿ���� �ٰ����� ������.
											itemTurn(itemTemp, 0);
										}
										else { printf("\n�̹� �ٸ� ȿ���� �ֽ��ϴ�! \n"); potion[i].count += 1; }
									}
									if (potion[i].count == 0) { potion[i].possession = 0; } // ������ 0����� �������� ����.
								}
								else { // ���� �ʴ´ٸ�.
									potion[i].count -= 1; // ���� ���� 1 ����
									player.health += potion[i].upHealth;
									if (potion[i].itemCode == 3 || potion[i].itemCode == 4) { // �����������̳� ��������� ��� ��
										if (itemTemp == 0) {
											itemTemp = potion[i].itemCode; // 3�� ���� ���� �������� ����� ����ϴ� ����. ���� ȿ���� �ٰ����� ������.
											itemTurn(itemTemp, 0);
										}
										else { printf("\n�ٸ� ȿ���� �� ����� �� ������ּ���! \n"); potion[i].count += 1; }
									}
									if (potion[i].count == 0) { potion[i].possession = 0; } // ������ 0����� �������� ����.
								}
								break;
							}
							else break;
						}
					}
				}
				break;
			}
			potionCount = 0; // ���� ī��Ʈ �ʱ�ȭ
			break;
		case RUN:
			// ��������� 50% Ȯ���� ������ �� ����.
			printf("�������� ����Ĩ�ϴ�... \n");
			Sleep(1500); // 1.5�� ����
			if (random() >= 5 && random() <= 10) { // ������ 6~10�� ���´ٸ�?
				printf("�������� �����ƽ��ϴ�! \n");
				Sleep(300); // 0.3�� ����
				printf("����ġ�� ���� %d���� �Ҿ����ϴ�...\n\n", lostMoney());
				Sleep(2000); // 1�� ����
				system("pause");
				system("cls");
				if (itemTemp != 0) {
					itemTurn(itemTemp, 1); // ���� ����
					itemTemp = 0;
				}
				return; // while ���ѷ��� Ż�� �� ���α׷� ����
			}
			else { // 1~5���?
				printf("������ ���� ���߽��ϴ�! \n");
				Sleep(1000); // 1�� ����
				printf("���? ���Ͱ� �ݰ��մϴ�! \n");
				monsterBattle();
				Sleep(2000);
				system("pause");
				system("cls");
				if (player.health < 0) {
					printf("%s(��)�� �������� �й��ߴ�... \n", player.name);
					Sleep(300); // 0.3�� ����
					printf("%s(��)�� ġ���� %d���� �Ҿ���... \n", player.name, lostMoney());
					Sleep(2000); // 0.5�� ����
					player.health = 0; // ü�� �ʱ�ȭ
					player.health += player.maxHealth; // ü�� �ʱ�ȭ
					system("pause");
					system("cls");
					if (itemTemp != 0) {
						itemTurn(itemTemp, 1); // ���� ����
						itemTemp = 0;
					}
					return; // ���� ȭ������ �̵�
				}
				break;
			}
		default:
			printf("�߸��� �Է��Դϴ�. \n"); break;
		}
	}
}
void itemTurn(int itemCode, int count) {  // ���� �� ��������� ��� ��, 3�� ���� �����ް� ���ִ� ����.
	for (int i = 0; i < POTIONSIZE; i++) {
		// ī��Ʈ�� 0ȸ�Ͻ� ���� 1ȸ �ߵ�.
		if (potion[i].itemCode == itemCode && count == 0) {
			player.attack += potion[i].upAttack;
			player.defense += potion[i].upDefense;
			printf("\n������ 3�� �� %s�� ȿ���� �ް� �˴ϴ�. \n", potion[i].name);
		}
	}
	for (int i = 0; i < POTIONSIZE; i++) {
		// ī��Ʈ�� 3ȸ�Ͻ� ���� ��.
		if (potion[i].itemCode == itemCode && count == 1) {
			player.attack -= potion[i].upAttack;
			player.defense -= potion[i].upDefense;
			printf("\n%s�� ȿ���� ��������ϴ�. \n", potion[i].name);
		}
	}
}
void playerBattle() {
	printf("%s(��)�� �����ߴ�! \n", player.name);
	Sleep(1000); // 1�� ����
	printf("%s���� %d��ŭ �������� �־���. \n", monster->name, playerFight());
}
void monsterBattle() {
	printf("%s(��)�� �����ߴ�! \n", monster->name);
	Sleep(1000); // 1�� ����
	printf("%s���� %d��ŭ �������� �־���. \n", player.name, monsterFight());
}
void monsterDataLoad() {
	FILE* f = 0; // ���� ������ �Լ�.

	fopen_s(&f, MONSTER, "r"); // ���� ������ �о���� ����

	if (f == 0) printf("���� �б� ����");
	for (int i = 0; i < MONSTERSIZE; i++) {
		fscanf_s(f, "%s %[^\n]s", monsterSelect[i].name, sizeof(monsterSelect[i].name), monsterSelect[i].explain, sizeof(monsterSelect[i].explain)); // ������ ���⼳�� �о��.
		fscanf_s(f, "%d %d %d %d", &monsterSelect[i].maxHealth, &monsterSelect[i].attack, &monsterSelect[i].defense, &monsterSelect[i].monCode);
	}
	fclose(f); // ���� �ݱ�.
}
void status()
{
	printf("\n--------------------------------\n");
	printf("\t    STATUS\n");
	printf("--------------------------------\n");
	printf("��  �� : %s\n", player.name);
	printf("��  �� : %d\n", player.level);
	printf("  ��   : %d\n", player.balance);
	printf("ü  �� : %d / %d\n", player.health, player.maxHealth);
	printf("���ݷ� : %d\n", player.attack);
	printf("���� : %d\n", player.defense);

	printf("\n�� �����ϰ� �ִ� ���� \n");
	for (int i = 0; i < WEAPONSIZE; i++) {
		if (weapon[i].possession == true) {
			printf("%s\n", weapon[i].name);
		}
	}
	printf("\n�� �����ϰ� �ִ� ������\n");
	for (int i = 0; i < POTIONSIZE; i++) {
		if (potion[i].possession == true) {
			printf("%s %dEA\n", potion[i].name, potion[i].count);
		}
	}
}

void potionBuy() { // �Һ� ����â

	FILE* f = 0;
	int choice; // ���� ����
	int count = 0, m = player.balance; // �÷��̾ �󸶸�ŭ ������ �� �� �ִ��� ���ִ� ����.
	printf("\n--------------------------------\n");
	printf("\t    POTION\n");
	printf("--------------------------------\n");

	printf("%2s %13s %6s %9s %9s %4s \n", "��", "ǰ��", "ȸ����", "��������", "�������", "����");
	for (int i = 0; i < POTIONSIZE; i++) {
		// ����, ����, ���, ü��, ���� ���
		printf("%2d %12s %6d %9d %9d %4d \n %s\n\n", i + 1, potion[i].name, potion[i].upHealth, potion[i].upAttack, potion[i].upDefense, potion[i].sellCost, potion[i].explain);
	}

	printf("1 ~ %d ���� �� ��ǰ ���� | 0 ����\n", POTIONSIZE);
	printf("� ��ǰ�� ���ðڽ��ϱ�? >> ");
	scanf_s("%d", &choice);
	for (int i = 1; i <= POTIONSIZE; i++) {
		if (choice == i) { // ������ �迭�� ��� ã�´�.
			printf("\n%s�� �����Ͻðڽ��ϱ�? \n", potion[i - 1].name);
			printf("1. ��\t 2. �ƴϿ� >> ");
			scanf_s("%d", &choice);
			fseek(stdin, 0, SEEK_END);
			if (choice == 1) {
				while (1) { // �÷��̾ �� ������ �ִ� �󸶱��� �� �� �ִ��� �������ֱ� ���� �ݺ���.
					m -= potion[i - 1].sellCost;
					if (m < 0) break;
					count++;
				}
				printf("\n�� ���� �����Ͻðڽ��ϱ�? \n");
				printf("������ �Է����ּ���. (%d������ ���Ű���) >> ", count);
				scanf_s("%d", &choice);
				fseek(stdin, 0, SEEK_END);
				if (choice <= 0) { printf("�� ������!\n"); return; }
				if (player.balance >= potion[i - 1].sellCost * choice) {
					Sleep(1000);
					printf("������ �Ϸ�Ǿ����ϴ�!\n");
					player.balance -= potion[i - 1].sellCost * choice; // ������ ���� ���� �ܾ׿��� ����
					potion[i - 1].possession = true;
					potion[i - 1].count += choice; // ������ ���� ����.
					Sleep(1000);
					system("cls");
					return;
				}
				else if (player.balance <= potion[i - 1].sellCost) {
					// ���� ���ڸ���.
					Sleep(1000);
					printf("�ܾ��� �����մϴ�.\n");
					Sleep(1000);
				}
			}
			else {
				printf("�� ������!\n");
				Sleep(1000);
				system("cls");
				return;
			}
		}
	}
	printf("�� ������!\n");
	system("cls");
	return;
}
void weaponBuy() { // ���� ����â

	FILE* f = 0;
	int choice; // ���� ����

	printf("\n--------------------------------\n");
	printf("\t    WEAPON\n");
	printf("--------------------------------\n");

	printf("%2s %13s %6s %6s %6s %4s \n", "��", "����", "���ݷ�", "����", "ü��", "����");
	for (int i = 0; i < WEAPONSIZE; i++) {
		// ����, ����, ���, ü��, ���� ���
		printf("%2d %12s %6d %6d %6d %4d \n %s\n\n", i + 1, weapon[i].name, weapon[i].upAttack, weapon[i].upDefense, weapon[i].upMaxHealth, weapon[i].sellCost, weapon[i].explain);
	}

	printf("1 ~ %d ���� �� ���� ���� | 0 ����\n", WEAPONSIZE);
	printf("� ���⸦ ���ðڽ��ϱ�? >> ");
	scanf_s("%d", &choice);
	for (int i = 1; i <= WEAPONSIZE; i++) {
		if (choice == i) { // ������ �迭�� ��� ã�´�.
			printf("\n%s�� �����Ͻðڽ��ϱ�? \n", weapon[i - 1].name);
			printf("1. ��\t 2. �ƴϿ� >> ");
			scanf_s("%d", &choice);
			if (choice == 1) {
				if (player.balance >= weapon[i - 1].sellCost && weapon[i - 1].possession == false) {
					Sleep(1000);
					printf("������ �Ϸ�Ǿ����ϴ�!\n");
					player.balance -= weapon[i - 1].sellCost; // ������ ���� ���� �ܾ׿��� ����
					player.attack += weapon[i - 1].upAttack;
					player.defense += weapon[i - 1].upDefense;
					player.maxHealth += weapon[i - 1].upMaxHealth;
					weapon[i - 1].possession = true; // ������ �� ������ ǥ��.
					Sleep(1000);
					system("cls");
					return;
				}
				else if (player.balance <= weapon[i - 1].sellCost) {
					// ���� ���ڸ���.
					Sleep(1000);
					printf("�ܾ��� �����մϴ�...\n");
					Sleep(1000);
				}
				else if (weapon[i - 1].possession == true) {
					// �̹� �����ϰ� �ִ� �����̸�?
					Sleep(1000);
					printf("�̹� �����ϰ� �ִ� �����Դϴ�.\n");
					Sleep(1000);
				}
			}
			else if (choice == 2) {
				printf("�� ������!\n");
				Sleep(1000);
				system("cls");
				return;
			}
			else {
				printf("�߸��� �Է��Դϴ�.\n");
			}
		}
	}
	if (choice == 0) {
		printf("�� ������!\n");
		Sleep(1000);
		system("cls");
		return;
	}
}
void userSave() { // ���� ���� �� ���� �����͸� �����Ѵ�.
	FILE* f = 0; // ���������� ������ �Լ�.
	fopen_s(&f, USERDATA, "wt"); // ������ �������.
	if (f == NULL) { // ���� �����Ϳ� ������ ���� ��...
		printf("���忡 �����Ͽ����ϴ�.\n");
		return;
	}
	fprintf(f, "%s\n", player.name);
	fprintf(f, "%d\n", player.level);
	fprintf(f, "%d\n", player.balance);
	fprintf(f, "%d\n", player.exp);
	fprintf(f, "%d\n", player.levelUp);
	fprintf(f, "%d\n", player.health);
	fprintf(f, "%d\n", player.maxHealth);
	fprintf(f, "%d\n", player.attack);
	fprintf(f, "%d\n", player.defense); // ���� ������ ���� ����.
	for (int i = 0; i < WEAPONSIZE; i++) // ���� �������� ����
		fprintf(f, "%d\n", weapon[i].possession);
	for (int i = 0; i < POTIONSIZE; i++) // ���� �������� ����
		fprintf(f, "%d %d\n", potion[i].possession, potion[i].count);
	fclose(f); // ���� �ݱ�.
	printf("���̺� ���忡 �����Ͽ����ϴ�.\n");
	return;
}

void userLoad() { // ���� �ҷ����� �� ���� �����͸� �ҷ��´�.

	FILE* f = 0; // ���� ������ �Լ�.
	fopen_s(&f, USERDATA, "r"); // ������ �������.
	if (f == NULL) { // ���� �����Ϳ� ������ ���� ��...
		printf("�ҷ����⿡ �����Ͽ����ϴ�.\n");
		printf("������ ������ ���ų� �ջ�Ǿ����ϴ�!\n");
		Sleep(1000);
		exit(1);
	}
	fscanf_s(f, "%s", player.name, sizeof(player.name));
	fscanf_s(f, "%d", &player.level);
	fscanf_s(f, "%d", &player.balance);
	fscanf_s(f, "%d", &player.exp);
	fscanf_s(f, "%d", &player.levelUp);
	fscanf_s(f, "%d", &player.health);
	fscanf_s(f, "%d", &player.maxHealth);
	fscanf_s(f, "%d", &player.attack);
	fscanf_s(f, "%d", &player.defense); // ���� ������ ���� �ҷ���.
	for (int i = 0; i < WEAPONSIZE; i++) // ���� �������� �ε�
		fscanf_s(f, "%d", &weapon[i].possession);
	for (int i = 0; i < POTIONSIZE; i++) // ���� �������� �ε�
		fscanf_s(f, "%d %d", &potion[i].possession, &potion[i].count);

	fclose(f); // ���� �ݱ�.

	itemListLoad(); // �����۸���Ʈ �о����

	printf("���̺� �ε忡 �����Ͽ����ϴ�.\n");
	printf("�ȳ��ϼ���! %s��.\n", player.name);
	return;
}
void itemListLoad() {
	FILE* f = 0; // ���� ������ �Լ�.

	fopen_s(&f, WEAPON, "r"); // ���� ������ �о���� ����

	if (f == 0) printf("���� �б� ����");
	for (int i = 0; i < WEAPONSIZE; i++) {
		fscanf_s(f, "%s %[^\n]s", weapon[i].name, sizeof(weapon[i].name), weapon[i].explain, sizeof(weapon[i].explain)); // ������ ���⼳�� �о��.
		fscanf_s(f, "%d %d %d %d", &weapon[i].upAttack, &weapon[i].upDefense, &weapon[i].upMaxHealth, &weapon[i].sellCost);
	}
	fclose(f); // ���� �ݱ�.

	fopen_s(&f, POTION, "r"); // ���� ������ �о���� ����

	if (f == 0) printf("���� �б� ����");


	for (int i = 0; i < POTIONSIZE; i++) {
		fscanf_s(f, "%s %[^\n]s", potion[i].name, sizeof(potion[i].name), potion[i].explain, sizeof(potion[i].explain)); // �̸��� ��ǰ���� �о��.
		fscanf_s(f, "%d %d %d %d %d", &potion[i].upHealth, &potion[i].upAttack, &potion[i].upDefense, &potion[i].sellCost, &potion[i].itemCode);
	}
	fclose(f);
}
bool bossHunt() // ���� ���Ϳ� �ο��!, ���� ���Ϳ� �ο� ����. ������ ����� �� ����.
{
	int choice; // ����ȭ�� ��ȣ �����Լ�
	int temp = 0, itemTemp = 0, tempTurn = 1; // ��� ���ڸ� ������ ����
	monsterDataLoad(); // ���� �����͸� �ҷ��´�.
	monster = monsterSelect; // ������ ���� �ʱ�ȭ
	monster += 10; // ���� ���Ͱ� 10��° ��Ͽ� �ִ�.
	// ������ ���Ͱ� ��������, �÷��̾� ������ ���� �ɷ�ġ�� �����Ѵ�.
	monster->level = player.level;
	monster->maxHealth *= (monster->level * 0.8); // �ִ�ü�� ������ ����� �÷���.
	monster->health = monster->maxHealth; // ü�� ȸ��.
	monster->attack *= (monster->level * 0.7); // ���ݷ� ������ ����� �÷���.
	monster->defense *= (monster->level * 0.7); // ���� ������ ����� �÷���.
	printf("\t    DANGER!!!\n");
	Sleep(500); // 0.5�� ����
	printf("%s(��)�� �����ؿ´�. \n", monster->name);
	Sleep(500); // 0.5�� ����
	printf("�� �� ���� ������ �������� ����� �� ����!\n");
	printf("�׸��� ������ �� �� ����! �������̴�!\n");
	while (1) {
		printf("\n--------------------------------\n");
		printf("    BOSS !!!! BATTLE\n");
		printf("--------------------------------\n");
		printf("Player ~ %s ", player.name);
		printf("\n"); healthBar(player.health, player.maxHealth); printf("\n\n");
		printf("Enemy  ~ %s ", monster->name);
		printf("\n"); healthBar(monster->health, monster->maxHealth); printf("\n\n");
		printf("--------------------------------\n");
		printf("   1) �����Ѵ� \t 2) ��    ��\n");
		printf("   3) �� �� �� \t 4) ��������\n");
		printf("--------------------------------\n");
		Sleep(500); // 0.5�� ����
		printf("%s(��)�� ������ �ұ�? >> ", player.name);
		scanf_s("%d", &choice);
		fseek(stdin, 0, SEEK_END);
		system("cls");

		switch (choice) {
		case AT:
			playerBattle();
			if (monster->health < 0) { // ���� HP �����ϸ� �̱��.
				printf("%s(��)�� %s�� ����Ʈ�ȴ�! \n", player.name, monster->name);
				printf("���� ��ȭ�� ã�ƿԴ�... \n", player.name, monster->name);
				monster->health = 0; // ü�� �ʱ�ȭ
				monster->health += monster->maxHealth; // ü�� �ʱ�ȭ
				Sleep(2000);
				system("pause");
				system("cls");
				return true; // ���θ޴��� �̵�
			}
			monsterBattle();
			if (player.health < 0) { // �÷��̾ ����...
				printf("%s(��)�� �������� �й��ߴ�... \n", player.name);
				Sleep(300); // 0.3�� ����
				printf("%s(��)�� %s���� ���������� ���Ҵ�...\n", player.name, monster->name);
				player.health = 0; // ü�� �ʱ�ȭ
				player.health += player.maxHealth; // ü�� �ʱ�ȭ
				Sleep(2000);
				system("pause");
				system("cls");
				return false;
			}
			Sleep(1000); // 1�� ����
			system("cls");
			break;
		case CHAT:
			printf("\n--------------------------------\n");
			printf("\t    PLAYER STATUS\n");
			printf("--------------------------------\n");
			printf("��  �� : %s\n", player.name);
			printf("��  �� : %d\n", player.level);
			printf("ü  �� : %d / %d\n", player.health, player.maxHealth);
			printf("���ݷ� : %d\n", player.attack);
			printf("���� : %d\n", player.defense);
			printf("\n--------------------------------\n");
			printf("\t    MONSTER STATUS\n");
			printf("--------------------------------\n");
			printf("��  �� : %s\n", monster->name);
			printf("��  �� : %d\n", monster->level);
			printf("ü  �� : %d / %d\n", monster->health, monster->maxHealth);
			printf("���ݷ� : %d\n", monster->attack);
			printf("���� : %d\n", monster->defense);
			printf("\n�������� - %s\n\n", monster->explain);
			system("pause");
			system("cls");
			break;
		case ITEM:
			printf("������������ �������� ��� �� �� �����ϴ�!\n");
			break;
		case RUN:
			printf("������������ �������⸦ �� �� �����ϴ�!\n"); break;
		default:
			printf("�߸��� �Է��Դϴ�. \n"); break;
		}
	}
}