#ifndef STATDATA_H
#define STATDATA_H

struct People { // �÷��̾ ���� ���� ����ü
	char name[30] = { 'h', 'u', 'm', 'a', 'n'};
	int level = 1;
	int exp = 0; // ����ġ
	int levelUp = 100; // �������� �ʿ��� ����ġ 
	int balance = 1000; // ��
	int maxHealth = 100; // HP �ִ�ü��
	int health = maxHealth; // HP ü��
	int attack = 50; // AT ���ݷ�
	int defense = 50; // DF ����
};
struct Enemy { // ��(����)�� ���� ���� ����ü
	char name[30] = { 'e', 'n', 'e', 'm', 'y' };
	int level = 1;
	int maxHealth = 30; // HP �ִ�ü��
	int health = maxHealth; // HP ü��
	int attack = 20; // AT ���ݷ�
	int defense = 20; // DF ����
	int monCode; // ���� �����ڵ�
	char explain[1000]; // ���� ����
};
struct Item { //�����ۿ� ���� ���� ����ü
	char name[30] = { 'i','t','e','m' };
	int upHealth; // ü�� ȸ��
	int upMaxHealth; // �ִ�ü�� ȸ�� �÷���.
	int upExp;
	int sellCost; // �ش� �������� ����
	int upAttack = 30; // AT ���ݷ�
	int upDefense = 30; // DF ����
	bool possession = false;  // ������ ���� ����
	int count = 0; // ��ǰ ����
	int itemCode; // ������ �����ڵ�
	char explain[1000]; // ������ ����
};

extern struct People player;

// ��ȯ ���� �ʿ��� �Լ� (���ڳ���)
int random(int set = 10); // 1~10 ������ ������ �Լ�
int lostMoney(); // �÷��̾ ���� �Ҵ� �Լ�. (�������� ������)
int getMoney(); // �÷��̾ ���� ��� �Լ�. (ȹ����� ������)

// �⺻ ���� �޴���.
void nameSet(); // �ʱ� �̸� ���� �޴�
void ifExp(); // ����ġ�� ��������� �Ѿ����� �Ǵ����ִ� �Լ�.
void expBar(); // ����ġ ����
void showMenu(); // �޴� ����Ʈ ���
void healthBar(int h, int mh); // ü�¹� ǥ��.
void gameLogo(); // ���� Ÿ��Ʋ �ΰ� ���
int startMenu(); // ��ŸƮ �޴� ���. �޴� ���� �� 0 ~ 3 ���� ��ȯ.
void potionBuy(); // �Һ� ����â
void weaponBuy(); // ���� ����â

// ���� �� �ʿ��� �޴�
void hunt(); // ���� �ý��� ����
bool bossHunt(); // ���� ���Ϳ� �ο��!, ���� ���Ϳ� �ο� ����. ������ ����� �� ����.
void playerBattle(); // ��Ʋ �� �÷��̾� ��
void monsterBattle(); // ��Ʋ �� ���� ��

// ������ ����
void shop(); // ���� ����Ʈ ���
void status(); // ���� ���� ���
void userSave(); // ���������� ���� �Լ�
void userLoad(); // ���� �ҷ����� �� ���� �����͸� �ҷ��´�.
void monsterDataLoad(); // ���� �����͸� �ҷ��´�.
void itemListLoad(); // ���� �� �Һ� ������ �����͸� �ҷ��´�.

// ��Ÿ...
void gotoxy(int x, int y); // Ŀ�� ��ġ �̵��Լ�
int keyControl(); // �Է��� Ű ���� ������ �ִ� �Լ�.
void colorText(int colorSet); // �۾����� �ٲ��ִ� �Լ�.
void itemTurn(int itemCode, int count);  // ���� �� ��������� ��� ��, 5�� ���� �����ް� ���ִ� ����.
void prologue(); // ���ѷα� �����ִ� �Լ�
void chapterLoad(int t); // é�� �� ���� ���� ���ؼ� �����ִ� �Լ�.
void Quiz(int level); // ��������!!!

#endif



