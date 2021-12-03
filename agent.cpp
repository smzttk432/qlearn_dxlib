#include "agent.h"
#include "DxLib.h"
//#include "qlearn.h"
#include <stdio.h>


void agent::print_graph() {
	// �`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);
	// ��ʂɕ`����Ă�����̂����S������

	//int x = this->x, y = this->y;
	unsigned int Color;
	int GraphHandle = LoadGraph(this->filename, FALSE);
	Color = GetColor(255, 255, 255);
	// �G��\��
	ClearDrawScreen();
	DrawGraph(this->x, this->y, GraphHandle, FALSE);
	DrawFormatString(0, 0, Color, "%d,%d", this->x, this->y);
	DrawFormatString(0, 600, Color, "%d���s��%d�X�e�b�v��", this->round, this->step);
	DrawFormatString(0, 620, Color, "���: % d �S�[���� : % d", this->state, this->goalcount);
	DrawFormatString((GOAL % 10) * 60, (GOAL - (GOAL % 10)) * 6, Color, "GOAL");
	ScreenFlip();
	WaitTimer(10);
	//	check_cursor(&this->x, &this->y);
	DeleteGraph(GraphHandle);

// ����ʂ̓��e��\��ʂɔ��f������


// �Q�O���̂P�b�҂�

}

void check_cursor(int* p1, int* p2) {
	if (CheckHitKey(KEY_INPUT_LEFT) == 1) *p1 -= 6;
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1) *p1 += 6;
	if (CheckHitKey(KEY_INPUT_UP) == 1) *p2 -= 6;
	if (CheckHitKey(KEY_INPUT_DOWN) == 1) *p2 += 6;
}
void agent::set_status(int x, int y, const char* filename) {
	this->x = x;
	this->y = y;
	this->filename = filename;
}

int agent::set_a_by_q(int s)
{
	double maxq = 0;/*Q�l�̍ő�l���*/
	int maxaction = 0;/*Q�l�ő�ɑΉ�����s��*/
	int i;

	for (i = 0; i < ACTIONNO; ++i)
		if ((this->qvalue[s][i]) > maxq) {
			maxq = this->qvalue[s][i];/*�ő�l�̍X�V*/
			maxaction = i;/*�Ή�����s��*/
		}

	return maxaction;
}


void agent::move_agent(int a) {
	int i;
	for (i = 0; i < 6; i++) {
		if (a == 3) this->x += 10;
		if (a == 2) this->x -= 10;
		if (a == 1) this->y += 10;
		if (a == 0) this->y -= 10;
		print_graph();
	}
}
/*�p�l�̏�����*/
void agent::initqvalue() {
	int i,j;
	for (i = 0; i < STATENO; ++i) {
		for (j = 0; j < ACTIONNO; ++j) {
			this->qvalue[i][j] = frand();
			if (i <= 9) this->qvalue[i][UP] = 0;/*�ŏ�i�ł�UP�����ɐi�܂Ȃ�*/
			if (i >= 90) this->qvalue[i][DOWN] = 0;/*�ŉ��i�ł�DOWN�����ɐi�܂Ȃ�*/
			if (i % 10 == 0) this->qvalue[i][LEFT] = 0;/*���[�ł�LEFT�����ɐi�܂Ȃ�*/
			if (i % 10 == 9) this->qvalue[i][RIGHT] = 0;/*�E�[�ł�RIGHT�����ɐi�܂Ȃ�*/
		}
	}
}

//�S�[���̃J�E���g
void agent::goalcounter(int count){
	this->goalcount = count;
}

//���s�񐔃J�E���g
void agent::roundcount(int round) {
	this->round = round;
}

//�G�[�W�F���g�̈ʒu
void agent::setposition(int x, int y) {
	this->x = x;
	this->y = y;
}

//�s���̌���
int agent::selecta(int s) {
	int a;/*�I�����ꂽ�s��*/

/*��-greedy�@�ɂ��s���I��*/
	if (frand() < EPSILON) {
		/*�����_���ɍs��*/
		do {
			a = rand03();
		}
		while (qvalue[s][a] == 0);/*�ړ��ł��Ȃ������Ȃ��蒼��*/
	}
	else {
		a = set_a_by_q(s);
	}
	return a;
}

void agent::updateq(int s, int snext, int a)
{
	double qv;/*�X�V�����Q�l*/

	/*Q�l�̍X�V*/
	if (snext == GOAL) {/*��V���t�^�����ꍇ*/
		qv = qvalue[s][a] + ALPHA * (REWARD - qvalue[s][a]);
	}
	else {/*��V�Ȃ�*/
		qv = qvalue[s][a]
			+ ALPHA * (GAMMA * qvalue[snext][set_a_by_q(snext)] - qvalue[s][a]);
	}
	this->qvalue[s][a] = qv;
	//return qv;
}

void agent::stepcount(int step) {
	this->step = step;
}
void agent::set_state(int state) {
	this->state = state;
}


/****************************/
/*     frand()�֐�          */
/*0�`1�̎�����Ԃ������֐�  */
/****************************/
double frand()
{
	/*�����̌v�Z*/
	return (double)rand() / RAND_MAX;
}

/****************************/
/*     rand03()�֐�         */
/*�@ 0�`3�̒l��Ԃ������֐� */
/****************************/
int rand03()
{
	int rnd;

	/*�����̍ő�l������*/
	while ((rnd = rand()) == RAND_MAX);
	/*�����̌v�Z*/
	return (int)((double)rnd / RAND_MAX * 4);
}

int rand100()
{
	int rnd;

	/*�����̍ő�l������*/
	while ((rnd = rand()) == RAND_MAX);
	/*�����̌v�Z*/
	return (int)((double)rnd / RAND_MAX * 100);
}
int rand600()
{
	int rnd;

	/*�����̍ő�l������*/
	while ((rnd = rand()) == RAND_MAX);
	/*�����̌v�Z*/
	return (int)((double)rnd / RAND_MAX * 600);
}

/****************************/
/*    nexts()�֐�           */
/*�s���ɂ���Ď��̏�ԂɑJ��*/
/****************************/
int nexts(int s, int a)
{
    int next_s_value[] = { -10,10,-1,1 };
    /*�s��a�ɑΉ����Ď��̏�ԂɑJ�ڂ��邽�߂̉��Z�l*/

    return s + next_s_value[a];
}