#pragma once
//#include "qlearn.h"
#define GENMAX  5000 /*学習の繰り返し回数*/
#define STATENO  100  /*状態の数*/
#define ACTIONNO 4  /*行動の数*/
#define ALPHA 0.1/*学習係数*/
#define GAMMA 0.9/*割引率*/
#define EPSILON 0.3 /*行動選択のランダム性を決定*/
#define SEED 32767 /*乱数のシード*/
#define REWARD 10 /*ゴール到達時の報酬*/

#define GOAL 55/*状態54がゴール状態*/
#define UP 0/*上方向の行動*/
#define DOWN 1/*下方向の行動*/
#define LEFT 2/*左方向の行動*/
#define RIGHT 3/*右方向の行動*/
#define LEVEL 1000 /*1試行における最大ステップ数*/
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

int rand03();/*0～3の値を返す乱数関数*/
double frand();/*0～1の実数を返す乱数関数*/
int rand100();
int rand600();
int nexts(int s, int a);