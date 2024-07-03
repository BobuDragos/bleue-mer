
#include "../../Engine/engine.h"
#include <GL/freeglut.h>
#include <math.h>
#include <iostream>
#include <vector>


// Maximum number of iterations for each point on the complex plane
int maxiterations = 100;


long double mapValue(long double value, long double fromMin, long double fromMax, long double toMin, long double toMax) {
    return (value - fromMin) / (fromMax - fromMin) * (toMax - toMin) + toMin;
}


// Precomputed colors for each possible iteration count
std::vector<Color> colors;
// Function to precompute colors
void setupColors() {
    for (int n = 0; n < maxiterations; n++) {
        long double hu = sqrt(static_cast<long double>(n) / maxiterations);
        int red = static_cast<int>(mapValue(hu, 0.0, 1.0, 0, 255));
        int green = static_cast<int>(mapValue(255, 0, 255, 0, 255));  // Keeping green constant
        int blue = static_cast<int>(mapValue(150, 0, 255, 0, 255));   // Keeping blue constant
        colors.push_back(Color(red, green, blue));
    }
}

long double angle = 0;




void update();


int main(int argc, char** argv)
{
     setupColors();
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
  long double ca = cos(angle * 3.213); //sin(angle);
  long double cb = sin(angle);

  angle += 0.02;

  RenderEngine::background(Color::white);
     int width = 800;  // Assuming a window width of 800 pixels
    int height = 800; // Assuming a window height of 800 pixels
  long double w = 5;
  long double h = (w * height) / width;

  long double xmin = -w / 2;
  long double ymin = -h / 2;


  long double xmax = xmin + w;
  long double ymax = ymin + h;

  long double dx = (xmax - xmin) / width;
  long double dy = (ymax - ymin) / height;

  long double y = ymin;

   for (int j = 0; j < height; j++) {
        long double x = xmin;
        for (int i = 0; i < width; i++) {
            long double a = x;
            long double b = y;
            int n = 0;
            while (n < maxiterations) {
                long double aa = a * a;
                long double bb = b * b;
                if (aa + bb > 4.0) {
                    break;
                }
                long double twoab = 2.0 * a * b;
                a = aa - bb + ca;
                b = twoab + cb;
                n++;
            }

            Color color;
            if (n == maxiterations) {
                color = Color(0, 0, 0); // Black
            } else {
                color = colors[n];
            }
          colors[n].g = 0;
        // std::cout<<color.r << " " << color.g << " " << color.b << '\n';

            RenderEngine::stroke(color);
            // RenderEngine::strokeWeight(10);

            RenderEngine::point(Vector3(mapValue(i, 0, 800, -1, 1)
, mapValue(j, 0, 800, -1, 1)));
            // RenderEngine::point(Vector3((long double)i / 800, (long double)j / 800, 0));
            x += dx;
        }
        y += dy;
    }
}






