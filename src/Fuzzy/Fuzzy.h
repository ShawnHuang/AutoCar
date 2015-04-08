#ifndef FUZZY_H
#define FUZZY_H

class Rule;

class Fuzzy
{
  public:
    Fuzzy ();
    Fuzzy (float left, float center, float right);
    void init(float left, float center, float right);
    float getSteer();
    float getSpeed();
    Rule *r1,*r2,*r3,*r4,*r5,*r6,*r7,*r8,*r9,*r10,*r11;

  private:
    float offset,dist;
    float steer,speed;


};
#endif
