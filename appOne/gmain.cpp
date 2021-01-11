#include"libOne.h"
class LISSAJOUS {
public:
    LISSAJOUS(float m1, float m2)
    :M1(m1)
    ,M2(m2)
    {
        //表示中心位置
        float length = Radius + Space;
        Cx = length + (length * 2) * m1;
        Cy = length + (length * 2) * m2;
        //色
        Hue = 10 * ((m2 - 1) * 6 + (m1 - 1));
    }
    static void update() {
        if (limmitDeg < 360) {
            limmitDeg += Inc;
        }
        else {
            Cnt++;
            if (Cnt > 60) {
                Cnt = 0;
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
            circle(Cx, l, Radius * 2);
            circle(l, Cy, Radius * 2);
            float x = cos(M1 * limmitDeg) * Radius;
            float y = sin(M2 * limmitDeg) * Radius;
            line(Cx + x, l - y, Cx + x, height);
            line(l + x, Cy - y, width, Cy - y);
            strokeWeight(10);
            point(Cx + x, l - y);
            point(l + x, Cy - y);
        }
    }
    float Cx, Cy;
    float M1, M2;
    float Hue;
    static float Radius;
    static float Space;
    static float limmitDeg;
    static float Inc;
    static int Cnt;
};
float LISSAJOUS::Radius = 50;
float LISSAJOUS::Space = 77 - LISSAJOUS::Radius;
float LISSAJOUS::limmitDeg = 0;
float LISSAJOUS::Inc = 2;
int LISSAJOUS::Cnt = 0;

#include<vector>
void gmain() {
    window(1080, 1080, full);
    angleMode(DEGREES);
    ShowCursor(FALSE);
    std::vector<LISSAJOUS> lissajous;
    for (int j = 1; j <= 6; j++) {
        for (int i = 1; i <= 6; i++) {
            lissajous.emplace_back(i, j);
        }
    }
    while (notQuit) {
        LISSAJOUS::update();
        clear(50);
        for (size_t i = 0; i < lissajous.size(); i++) {
            lissajous[i].draw();
        }
    }
    ShowCursor(TRUE);
}