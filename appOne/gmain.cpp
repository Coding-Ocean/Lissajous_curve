#include"libOne.h"
class LISSAJOUS {
public:
    LISSAJOUS(float m1, float m2)
    :M1(m1)
    ,M2(m2)
    {
        //�����ł́AM1=���ʒu�AM2=�c�ʒu�Ƃ��Ďg�p���邪�A
        //draw()�ł́A�O�p�֐��ɓn��deg�̌W���Ƃ��Ďg�p����

        //�\�����S�ʒu
        float length = Radius + Space;
        Cx = length + (length * 2) * m1;
        Cy = length + (length * 2) * m2;
        //�F
        Hue = 10 * ((m2 - 1) * 6 + (m1 - 1));
    }
    static void animControl() {
        if (limmitDeg < 360) {
            limmitDeg += Inc;
        }
        else {
            WaitCnt++;
            if (WaitCnt > 60) {
                WaitCnt = 0;
                limmitDeg = 0;
            }
        }
    }
    void draw() {
        //���T�[�W���Ȑ�
        strokeWeight(4);
        colorMode(HSV);
        stroke(Hue, 100, 255);
        float deg = 0;
        float sx = cos(M1 * deg) * Radius;
        float sy = sin(M2 * deg) * Radius;
        while (deg <= limmitDeg) {
            float ex = cos(M1 * (deg + Inc)) * Radius;
            float ey = sin(M2 * (deg + Inc)) * Radius;
            line(Cx + sx, Cy - sy, Cx + ex, Cy - ey);
            sx = ex;
            sy = ey;
            deg += Inc;
        }
        //���Ə�̉~�A��
        if (M1 == M2) {
            float l = Radius + Space;
            stroke(200);
            strokeWeight(1);
            fill(0, 0, 0, 0);
            circle(Cx, l, Radius * 2);//����̉~
            circle(l, Cy, Radius * 2);//�����̉~
            float x = cos(M1 * limmitDeg) * Radius;
            float y = sin(M2 * limmitDeg) * Radius;
            line(Cx + x, l - y, Cx + x, height);//cosTheta�̏c��
            line(l + x, Cy - y, width, Cy - y);//sinTheta�̉���
            strokeWeight(10);
            point(Cx + x, l - y);
            point(l + x, Cy - y);
        }
    }
private:
    float M1, M2;//�u�c���C���f�b�N�X�v���udeg�̌W���v
    float Cx, Cy;
    float Hue;
    //�S���T�[�W���Ȑ����L�f�[�^
    static float Radius;
    static float Space;
    static float limmitDeg;//�P�t���[���ł��̊p�x�܂ł̋Ȑ���`��
    static float Inc;
    static int WaitCnt;
};
float LISSAJOUS::Radius = 50;
float LISSAJOUS::Space = 77 - LISSAJOUS::Radius;//2����1�̊Ԋu
float LISSAJOUS::limmitDeg = 0;
float LISSAJOUS::Inc = 2;
int LISSAJOUS::WaitCnt = 0;

#include<vector>
void gmain() {
    window(1080, 1080, full);
    angleMode(DEGREES);
    ShowCursor(FALSE);
    std::vector<LISSAJOUS> lissajous;
    //�ʒu�����߂Ȃ���C���X�^���X����
    for (int j = 1; j <= 6; j++) {
        for (int i = 1; i <= 6; i++) {
            lissajous.emplace_back(i, j);
        }
    }
    while (notQuit) {
        LISSAJOUS::animControl();
        //�`��
        clear(50);
        for (size_t i = 0; i < lissajous.size(); i++) {
            lissajous[i].draw();
        }
    }
    ShowCursor(TRUE);
}