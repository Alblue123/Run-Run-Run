#pragma once

class Vector2
{
 public:
     float x, y;
     Vector2();
     ~Vecotr2();

     Vector2(loat x, float y);
     void sub(Vector2 v);
     void sub(float x, float y);
     void add(Vector2 v);
     void add(float x, float y);
     void mul(float f);
     Vector2 mul_N(float f);
     Vector2 Lerp(Vector2 start, Vector2 end, float t);
     float Lerp(float start, float end, float t);

};
