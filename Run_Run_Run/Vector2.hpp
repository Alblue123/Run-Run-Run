#pragma once

class Vector2:
{
 public:
     float x, y;
     Vector2()
     ~Vecotr2();

     Vector2(loat x, float y);
     void sub(Vector2 v);
     void sub(float x, float y);
     void add(Vector2 v);
     void add(float x, float y);
     void mul(float f);
     Vector2 mul_N(float f);
};
