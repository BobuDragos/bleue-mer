#include "../../Engine/engine.h"
#include <GL/freeglut.h>
#include <math.h>

#include <iostream>

long double angle = M_PI / 4;

long double angleV = 0;
long double angleA = 0;

Vector3 bob;
long double len = 200;
Vector3 origin = Vector3(0,0);

double gravity = -1;

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


  long double force = gravity * sin(angle);
  angleA = (-1 * force) / len;
  angleV += angleA;
  angle += angleV;

  // std::cout <<"force: " << force;
  // std::cout << "angle: " << angle;

  bob.x = len * sin(angle) + origin.x;
  bob.y = len * cos(angle) + origin.y;

  std::cout<<bob.x / 200 << " " << bob.y / 200 << "\n";
  // std::cout<<bob.x << " " << bob.y << "\n";

  RenderEngine::stroke(255);
  RenderEngine::strokeWeight(8);
  // fill(127);
  RenderEngine::line(bob / 200, origin);
  RenderEngine::rect(bob / 200, Vector3(0.2, 0.2));
}








