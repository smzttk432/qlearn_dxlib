#pragma once
//#include "qlearn.h"
#define GENMAX  5000 /*�w�K�̌J��Ԃ���*/
#define STATENO  100  /*��Ԃ̐�*/
#define ACTIONNO 4  /*�s���̐�*/
#define ALPHA 0.1/*�w�K�W��*/
#define GAMMA 0.9/*������*/
#define EPSILON 0.3 /*�s���I���̃����_����������*/
#define SEED 32767 /*�����̃V�[�h*/
#define REWARD 10 /*�S�[�����B���̕�V*/

#define GOAL 55/*���54���S�[�����*/
#define UP 0/*������̍s��*/
#define DOWN 1/*�������̍s��*/
#define LEFT 2/*�������̍s��*/
#define RIGHT 3/*�E�����̍s��*/
#define LEVEL 1000 /*1���s�ɂ�����ő�X�e�b�v��*/
class agent
{
	int x, y;
	int state, round, step;
	int goalcount;
	int genmax;
	const char* filename;
	double qvalue[STATENO][ACTIONNO];
public:
	void print_graph();
	void set_status(int x, int y, const char* filename);
	void move_agent(int a);
	void initqvalue();
	void goalcounter(int count);
	void roundcount(int round);
	void setposition(int x, int y);
	int selecta(int s);
	void updateq(int s, int snext, int a);
	void stepcount(int step);
	void set_state(int state);
	int set_a_by_q(int s);
};

int rand03();/*0�`3�̒l��Ԃ������֐�*/
double frand();/*0�`1�̎�����Ԃ������֐�*/
int rand100();
int rand600();
int nexts(int s, int a);