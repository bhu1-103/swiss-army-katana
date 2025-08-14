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
{float x;float y;};

int main()
{
  Screen screen = {2560,1440};
  Sf sf = {10,2};
  //double pi025 = 0.0f;
  float sfx = (sf.y - 1)/(sf.y);
  InitWindow(screen.width,screen.height,"Leibniz pi");
  SetTargetFPS(60);
  int prec;
  double p1,p2,p3;
  float lt = 5;
  //Vector2 start, end;
	cout << "enter number of digits of precision required: ";
  cin >> prec;

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(BLACK);
    double pi025 = 0.0f;
    Prev prev = {0,screen.height * (1/2)};
    for(int i=0; i<prec; i++)
    {
      p1 = pow(-1,i);
      p2 = 2*i + 1;
      p3 = p1/p2;
      cout << p3 << endl;
      pi025 += p3;
      int x = i;
      int y = screen.height * (1 - sfx) / (2) - (int)(p3 * (sf.y) * screen.height / 2);
      Vector2 start = { float(prev.x * sf.x), float(prev.y * sf.y)};
      Vector2 end = { float(x*sf.x), float(y * sf.y)};
      DrawLineEx(start,end,float(lt),RED);
      prev.x = x;
      prev.y = y;
    }
    cout << "value of pi is: " << fixed << setprecision(20) << pi025 * 4 << endl << endl;
    EndDrawing();
  }

	return 0;
}
