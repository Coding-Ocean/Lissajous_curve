#include"libOne.h"
class LISSAJOUS {
public:
    LISSAJOUS(float m1, float m2)
    :M1(m1)
    ,M2(m2)
    {
        //ここでは、M1=横位置、M2=縦位置として使用するが、
        //draw()では、三角関数に渡すdegの係数として使用する

        //表示中心位置
        float length = Radius + Space;
        Cx = length + (length * 2) * m1;
        Cy = length + (length * 2) * m2;
        //色
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
        //リサージュ曲線
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
        //左と上の円、線
        if (M1 == M2) {
            float l = Radius + Space;
            stroke(200);
            strokeWeight(1);
            fill(0, 0, 0, 0);
            circle(Cx, l, Radius * 2);//上方の円
            circle(l, Cy, Radius * 2);//左側の円
            float x = cos(M1 * limmitDeg) * Radius;
            float y = sin(M2 * limmitDeg) * Radius;
            line(Cx + x, l - y, Cx + x, height);//cosThetaの縦線
            line(l + x, Cy - y, width, Cy - y);//sinThetaの横線
            strokeWeight(10);
            point(Cx + x, l - y);
            point(l + x, Cy - y);
        }
    }
private:
    float M1, M2;//「縦横インデックス」かつ「degの係数」
    float Cx, Cy;
    float Hue;
    //全リサージュ曲線共有データ
    static float Radius;
    static float Space;
    static float limmitDeg;//１フレームでこの角度までの曲線を描く
    static float Inc;
    static int WaitCnt;
};
float LISSAJOUS::Radius = 50;
float LISSAJOUS::Space = 77 - LISSAJOUS::Radius;//2分の1の間隔
float LISSAJOUS::limmitDeg = 0;
float LISSAJOUS::Inc = 2;
int LISSAJOUS::WaitCnt = 0;

#include<vector>
void gmain() {
    window(1080, 1080, full);
    angleMode(DEGREES);
    ShowCursor(FALSE);
    std::vector<LISSAJOUS> lissajous;
    //位置を決めながらインスタンス生成
    for (int j = 1; j <= 6; j++) {
        for (int i = 1; i <= 6; i++) {
            lissajous.emplace_back(i, j);
        }
    }
    while (notQuit) {
        LISSAJOUS::animControl();
        //描画
        clear(50);
        for (size_t i = 0; i < lissajous.size(); i++) {
            lissajous[i].draw();
        }
    }
    ShowCursor(TRUE);
}