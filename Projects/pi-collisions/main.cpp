
#include "../../Engine/engine.h"

#include <iostream>
#include <cmath>
#include <algorithm>

#include <GL/freeglut.h>


const double height = 2;
const double width  = 2;

class Block {
public:
    double x;
    double y;
    double w;
    double v;
    double m;
    double xConstraint;
    
    int relative_pos;

    Block(double x, double w, double m, double v, double xc, bool isLeft = false)
        : x(x), w(w), m(m), v(v), xConstraint(xc) {
        y = 50;  // Setting y to 100 for demonstration
    if (isLeft) {
      relative_pos = -1;
    } else{
      relative_pos = 1;
    }
    }

    bool hitWall() {
        return (x <= 0);
    }

    void reverse() {
        v *= -1;
    }

    bool collide(const Block& other) {
        return !(x + w < other.x || x > other.x + other.w);
    }

    double bounce(const Block& other) {
        double sumM = m + other.m;
        double newV = (m - other.m) / sumM * v;
        newV += (2 * other.m / sumM) * other.v;
        return newV;
    }

    void update() {
        x += v;
    }

    void show() {
        // std::cout << "Rendering block at x = " << x << ", y = " << y << ", w = " << w << std::endl;
        
        // RenderEngine::rect(constrainedX, )

  char buffer[50]; // Allocate a buffer for the string representation

  // Format the double into the buffer as a string
  sprintf(buffer, "%lu kg", (long)m);

    RenderEngine::stroke(0);
          RenderEngine::rect(Vector3(x / 1000, y / 1000), Vector3(0.02, 0.1));
               RenderEngine::RenderString(x / 1000, y / 1000 + 0.1, GLUT_BITMAP_TIMES_ROMAN_10, buffer, 255, 0, 0); 


  // Format the double into the buffer as a string
  sprintf(buffer, "velocity: %.8f", v);
    if(relative_pos > 0)
  {
               RenderEngine::RenderString(x / 1000, y / 1000 - 0.1, GLUT_BITMAP_TIMES_ROMAN_10, buffer, 0, 0, 255); 
    } else
{
               RenderEngine::RenderString(x / 1000, y / 1000 - 0.075, GLUT_BITMAP_TIMES_ROMAN_10, buffer, 0, 0, 255); 
    }

  }
};
void update();

int count = 0;
double digits = 2;


double timeSteps = pow(10, digits - 1);

double m2 = pow(100, digits-1);


  Block block1(100, 20, 1, 0, 0, true);
  Block block2(300, 100, m2, -1 / timeSteps, 20);

int main(int argc, char** argv)
{

    if (argc > 1) {
        digits = std::atoi(argv[1]); // Convert argument to integer
    }

    
   timeSteps = pow(10, digits - 1);

   m2 = pow(100, digits-1);

  block2.m = m2;
  block2.v = -1 / timeSteps;

 
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
  RenderEngine::background(Color(255));
  RenderEngine::strokeWeight(2);
  RenderEngine::line(Vector3(0, 1), Vector3(0, -1));
  RenderEngine::line(Vector3(-1, 0), Vector3(1, 0));
  // RenderEngine::line(Vector3(100, 100), Vector3(200, 200));

  for (int i = 0; i < timeSteps; i++) 
  {
    if(block1.collide(block2))
    {
      double v1 = block1.bounce(block2);
      double v2 = block2.bounce(block1);

      block1.v = v1;
      block2.v = v2;

      count++;
    }
    if (block1.hitWall()) {
      block1.reverse();
      count++;
    }

    block1.update();
    block2.update();

  }




  block1.show();
  block2.show();

  // printf("%d \n", count);



  char buffer[50]; // Allocate a buffer for the string representation

  // Format the double into the buffer as a string
  sprintf(buffer, "# of Collisions: %d", count);

  RenderEngine::RenderString(0.25, 0.25, GLUT_BITMAP_TIMES_ROMAN_24, buffer, 0, 0, 0);
}

