


#include "../../Engine/engine.h"
#include <GL/freeglut.h>

#include <math.h>
#include <iostream>

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

}








