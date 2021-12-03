#include "DxLib.h"
#include "agent.h"
//#include "qlearn.h"
#include "DobotDll.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
    SetGraphMode(660, 660, 32);
    ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ɐݒ�
    SetAlwaysRunFlag(TRUE);
    DxLib_Init();   // DX���C�u��������������
    const char* file = "100.png";
    //print_graph(file);
    int i, j;
    int s, snext;/*���݂̏�ԂƁA���̏��*/
    int t;/*����*/
    int a;/*�s��*/
    int count = 0;
    int snextx,snexty;
    int pointx, pointy;
    FILE* fp;
   // int point;
    //unsigned int Color;
    //Color = GetColor(255, 255, 255);
    srand(SEED);/*�����̏�����*/
    if ((fopen_s(&fp, "step.dat", "wb")) != 0) {
        fprintf(stderr, "Data file open error.\n");
        return 1;
    }
    
    // printqvalue(qvalue);
    agent chara1;
    chara1.set_status(0, 0, file);
    chara1.initqvalue();
    for (i = 1; i <= GENMAX; ++i) {
        chara1.goalcounter(count);
        chara1.roundcount(i);
        s = rand100();/*�������*/
        chara1.setposition((s % 10) * 60, (s - (s % 10)) * 6);
        chara1.print_graph();
        for (t = 0; t < LEVEL; t++) {/*�ő�X�e�b�v���܂ŌJ��Ԃ�*/
            chara1.stepcount(t);
            chara1.set_state(s);
            /*�s���I��*/
            a = chara1.selecta(s);
            snext = nexts(s, a);
            chara1.move_agent(a);
            chara1.updateq(s, snext, a);
            s = snext;
            chara1.print_graph();
            /*�S�[���ɓ��B�����珉����Ԃɖ߂�*/
            if (s == GOAL) {
                count++;
                fprintf(fp, "%d, %d\n",i, t);
                break;
            }

        }
        /*Q�l�̏o��*/
       // printqvalue(qvalue);

    }
   /* fclose(fp);
    if ((fopen_s(&fp,"q.dat", "wb")) != 0) {
        fprintf(stderr, "Data file open error.\n");
        return 1;
    }
    for (i = 0; i < STATENO; i++) {
        for (j = 0; j < ACTIONNO; j++) {
            fprintf(fp, "%lf", qvalue[i][j]);
            if (j == ACTIONNO - 1) {
                fprintf(fp, "\n");
            }
            else {
                fprintf(fp, ",");
            }
        }
    }
    fclose(fp);*/

    //rand03();
    WaitKey();      // �L�[���͑҂�
    DxLib::DxLib_End();    // DX���C�u�����I������
    return 0;
}