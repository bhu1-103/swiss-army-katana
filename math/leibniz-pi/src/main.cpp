#include <raylib.h>
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

struct Screen
{int width;int height;};

struct Prev
{int x;int y;};

struct Sf //scaling factor
{int x;int y;};

int main()
{
  Screen screen = {2560,1440};
  Sf sf = {10,2};
  double pi025 = 0;
  InitWindow(screen.width,screen.height,"Leibniz pi");
  SetTargetFPS(60);
  int prec;
  double p1,p2,p3;
  float lt = 1;
  //Vector2 start, end;
	cout << "enter number of digits of precision required: ";
  cin >> prec;
/*
  BeginDrawing();
  ClearBackground(BLACK);

  for(int i=0;i<prec;i++)
  {
    p1 = pow(-1,i);
    p2 = 2*i + 1;
    p3 = p1 / p2;
    pi025 += p3;

    int x = i;
    //int y = screen.height / 2 - (int)(p3 * screen.height / 2);
    int y = screen.height / 2 - (int)(p3 * sf.y * screen.height / 2);
    Vector2 start = { float(prev.x * sf.x), float(prev.y) };
    Vector2 end   = { float(x * sf.x)     ,      float(y) };
    //DrawPixel(x,y,RED); //v1
    //DrawLine(prev.x*sf.x ,prev.y*sf.y ,x*sf.x ,y*sf.y ,RED);
    //DrawLine(prev.x * sf.x, prev.y, x * sf.x, y, RED);
    DrawLineEx(start,end,float(lt),RED);
    prev.x = x;
    prev.y = y;
    //if (i % 1000 == 0)
    //{
    //  EndDrawing();
    //  BeginDrawing();
    //} //flush code, but we'l keep that out for now
  }
  EndDrawing();
*/

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(BLACK);
    Prev prev = {0,screen.height/2};
    for(int i=1; i<prec; i++)
    {
      p1 = pow(-1,i);
      p2 = 2*i + 1;
      p3 = p1/p2;
      int x = i;
      int y = screen.height / 2 - (int)(p3 * sf.y * screen.height / 2);
      Vector2 start = { float(prev.x * sf.x), float(prev.y * sf.y)};
      Vector2 end = { float(x*sf.x), float(y * sf.y)};
      DrawLineEx(start,end,float(lt),RED);
      prev.x = x;
      prev.y = y;
    }
    EndDrawing();
  }
  cout << "value of pi is: " << fixed << setprecision(20) << pi025 * 4;

	return 0;
}
