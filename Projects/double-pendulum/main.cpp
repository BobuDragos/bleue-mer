#include "../../Engine/engine.h"
#include <GL/freeglut.h>
#include <math.h>

long double r1 = 125;
long double r2 = 125;
long double m1 = 10;
long double m2 = 10;
long double a1 = M_PI / 2;
long double a2 = M_PI / 2;
long double a1_v = 0;
long double a2_v = 0;
long double g = -1;

long double px2 = -1;
long double py2 = -1;
long double cx = 1.0f / 2, cy = 1.0f / 4;

void update();

int main(int argc, char** argv)
{
  RenderEngine::setStart([]() 
    {
        RenderEngine::background(Color(255));
        RenderEngine::strokeWeight(10);
        RenderEngine::stroke(0);
    });
    RenderEngine::setUpdate(update);
    RenderEngine::Enabled(true);
}

void update()
{
  RenderEngine::background(Color::black);
  long double num1 = -g * (2 * m1 + m2) * sin(a1);
  long double num2 = -m2 * g * sin(a1 - 2 * a2);
  long double num3 = -2 * sin(a1 - a2) * m2;
  long double num4 = a2_v * a2_v * r2 + a1_v * a1_v * r1 * cos(a1 - a2);
  long double den = r1 * (2 * m1 + m2 - m2 * cos(2 * a1 - 2 * a2));
  long double a1_a = (num1 + num2 + num3 * num4) / den;

  num1 = 2 * sin(a1 - a2);
  num2 = (a1_v * a1_v * r1 * (m1 + m2));
  num3 = g * (m1 + m2) * cos(a1);
  num4 = a2_v * a2_v * r2 * m2 * cos(a1 - a2);
  den = r2 * (2 * m1 + m2 - m2 * cos(2 * a1 - 2 * a2));
  long double a2_a = (num1 * (num2 + num3 + num4)) / den;

  RenderEngine::stroke(Color::white);
  RenderEngine::strokeWeight(10);

  long double x1 = r1 * sin(a1);
  long double y1 = r1 * cos(a1);
  long double x2 = x1 + r2 * sin(a2);
  long double y2 = y1 + r2 * cos(a2);

 RenderEngine::strokeWeight(2);
 RenderEngine::line(Vector3(0, 0), Vector3(x1 / 400, y1 / 400));
 // RenderEngine::fill(0);
 RenderEngine::rect(Vector3(x1/400, y1/400), Vector3(m1*2 / 400, m1*2 / 400));

 RenderEngine::line(Vector3(x1 / 400, y1 / 400), Vector3(x2 / 400, y2 / 400));
 // RenderEngine::fill(0);
 RenderEngine::rect(Vector3(x2/400, y2/400), Vector3(m2*2 / 400, m2*2 / 400));

  a1_v += a1_a;
  a2_v += a2_a;
  a1 += a1_v;
  a2 += a2_v;
}








