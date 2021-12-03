#include "agent.h"
#include "DxLib.h"
//#include "qlearn.h"
#include <stdio.h>


void agent::print_graph() {
	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);
	// 画面に描かれているものを一回全部消す

	//int x = this->x, y = this->y;
	unsigned int Color;
	int GraphHandle = LoadGraph(this->filename, FALSE);
	Color = GetColor(255, 255, 255);
	// 絵を表示
	ClearDrawScreen();
	DrawGraph(this->x, this->y, GraphHandle, FALSE);
	DrawFormatString(0, 0, Color, "%d,%d", this->x, this->y);
	DrawFormatString(0, 600, Color, "%d試行目%dステップ目", this->round, this->step);
	DrawFormatString(0, 620, Color, "状態: % d ゴール回数 : % d", this->state, this->goalcount);
	DrawFormatString((GOAL % 10) * 60, (GOAL - (GOAL % 10)) * 6, Color, "GOAL");
	ScreenFlip();
	WaitTimer(10);
	//	check_cursor(&this->x, &this->y);
	DeleteGraph(GraphHandle);

// 裏画面の内容を表画面に反映させる


// ２０分の１秒待つ

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
	double maxq = 0;/*Q値の最大値候補*/
	int maxaction = 0;/*Q値最大に対応する行動*/
	int i;

	for (i = 0; i < ACTIONNO; ++i)
		if ((this->qvalue[s][i]) > maxq) {
			maxq = this->qvalue[s][i];/*最大値の更新*/
			maxaction = i;/*対応する行動*/
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
/*Ｑ値の初期化*/
void agent::initqvalue() {
	int i,j;
	for (i = 0; i < STATENO; ++i) {
		for (j = 0; j < ACTIONNO; ++j) {
			this->qvalue[i][j] = frand();
			if (i <= 9) this->qvalue[i][UP] = 0;/*最上段ではUP方向に進まない*/
			if (i >= 90) this->qvalue[i][DOWN] = 0;/*最下段ではDOWN方向に進まない*/
			if (i % 10 == 0) this->qvalue[i][LEFT] = 0;/*左端ではLEFT方向に進まない*/
			if (i % 10 == 9) this->qvalue[i][RIGHT] = 0;/*右端ではRIGHT方向に進まない*/
		}
	}
}

//ゴールのカウント
void agent::goalcounter(int count){
	this->goalcount = count;
}

//試行回数カウント
void agent::roundcount(int round) {
	this->round = round;
}

//エージェントの位置
void agent::setposition(int x, int y) {
	this->x = x;
	this->y = y;
}

//行動の決定
int agent::selecta(int s) {
	int a;/*選択された行動*/

/*ε-greedy法による行動選択*/
	if (frand() < EPSILON) {
		/*ランダムに行動*/
		do {
			a = rand03();
		}
		while (qvalue[s][a] == 0);/*移動できない方向ならやり直し*/
	}
	else {
		a = set_a_by_q(s);
	}
	return a;
}

void agent::updateq(int s, int snext, int a)
{
	double qv;/*更新されるQ値*/

	/*Q値の更新*/
	if (snext == GOAL) {/*報酬が付与される場合*/
		qv = qvalue[s][a] + ALPHA * (REWARD - qvalue[s][a]);
	}
	else {/*報酬なし*/
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
/*     frand()関数          */
/*0～1の実数を返す乱数関数  */
/****************************/
double frand()
{
	/*乱数の計算*/
	return (double)rand() / RAND_MAX;
}

/****************************/
/*     rand03()関数         */
/*　 0～3の値を返す乱数関数 */
/****************************/
int rand03()
{
	int rnd;

	/*乱数の最大値を除く*/
	while ((rnd = rand()) == RAND_MAX);
	/*乱数の計算*/
	return (int)((double)rnd / RAND_MAX * 4);
}

int rand100()
{
	int rnd;

	/*乱数の最大値を除く*/
	while ((rnd = rand()) == RAND_MAX);
	/*乱数の計算*/
	return (int)((double)rnd / RAND_MAX * 100);
}
int rand600()
{
	int rnd;

	/*乱数の最大値を除く*/
	while ((rnd = rand()) == RAND_MAX);
	/*乱数の計算*/
	return (int)((double)rnd / RAND_MAX * 600);
}

/****************************/
/*    nexts()関数           */
/*行動によって次の状態に遷移*/
/****************************/
int nexts(int s, int a)
{
    int next_s_value[] = { -10,10,-1,1 };
    /*行動aに対応して次の状態に遷移するための加算値*/

    return s + next_s_value[a];
}