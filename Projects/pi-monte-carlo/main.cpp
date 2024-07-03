

#include <cstdio> // For sprintf
#include <cstring>

float r = 1;

long double total = 0;
long double in_circle = 0;

long double record_PI = 0;

// Function to convert double to const char*
const char* doubleToString(double value) {
    static char buffer[50]; // Create a static buffer to hold the string
    sprintf(buffer, "%.6f", value); // Format the double value into the buffer
    return buffer; // Return the buffer as const char*
}

// Function to convert long double to const char*
const char* longDoubleToString(long double value) {
    static char buffer[100]; // Create a static buffer to hold the string
    sprintf(buffer, "%.30Lf", value); // Format the long double value into the buffer
    return buffer; // Return the buffer as const char*
}


const char* intToString(int value) {
    static char buffer[20]; // Create a static buffer to hold the string
    sprintf(buffer, "%d", value); // Format the integer value into the buffer
    return buffer; // Return the buffer as const char*
}
const char* concat(const char* str1, const char* str2) {
    char* result = new char[strlen(str1) + strlen(str2) + 1]; // +1 for null terminator
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}



#include "../../Engine/engine.h"
#include <GL/freeglut.h>
#include <random> // Include the <random> header for random number generation


int points_per_frame = 250;
void update();

int main(int argc, char** argv)
{
     if (argc > 1) {
        points_per_frame = std::atoi(argv[1]); // Convert argument to integer
    }
  RenderEngine::setStart([]() 
    {
        RenderEngine::background(Color(255));
        RenderEngine::strokeWeight(10);
        RenderEngine::stroke(0);

        // RenderEngine::circle(Vector3::zero, r);
    });
    RenderEngine::setUpdate(update);
    RenderEngine::Enabled(true);

}
std::random_device rd;  // Obtain a random number from hardware
std::mt19937 gen(rd()); // Seed the generator
std::uniform_real_distribution<float> dist(-r, r); // Define the range [0, 99]



bool firstFrame = true;

void update()
{
  if(firstFrame)
  {
    RenderEngine::background(Color::black);
    firstFrame = false;
  }
        RenderEngine::strokeWeight(10);
        RenderEngine::stroke(Color(255, 255, 255, 0.001));
        RenderEngine::rect(Vector3::zero, Vector3::one * 2);
        RenderEngine::stroke(Color(0,0,0,0.01));
        RenderEngine::noFill();
        RenderEngine::circle(Vector3::zero, r);



  // printf("%.30Lf\n", record_PI);
  
  for (int i = 0 ; i< points_per_frame; i++) 
  {
    float x =  dist(gen);
    float y =  dist(gen);

    // printf("%f ", x);
    // printf("%f \n", y);

    total++;

    int d = x*x + y*y;

    double opacity = 1;


    if(points_per_frame > 1000)
      opacity = 0.1;
    else if(points_per_frame > 10000)
      opacity = 0.01;
    else if(points_per_frame > 100000)
      opacity = 0.0001;
    else if(points_per_frame > 100000)
      opacity = 0.00001;

   if (d < r * r) 
    {
      in_circle++;
                // RenderEngine::stroke(Color(255, 0,0,1));
                // RenderEngine::stroke(Color(255, 0,0,0.01));
                RenderEngine::stroke(Color(255, 0,0,opacity));
    } else {
                // RenderEngine::stroke(Color(0, 0,255,1));
                // RenderEngine::stroke(Color(0, 0,255,0.01));
                RenderEngine::stroke(Color(0, 0,255,opacity));
    }
    RenderEngine::strokeWeight(10);
    RenderEngine::point(Vector3(x, y));

    // points[points_idx++] = Vector3(x, y);

    long double pi = 4 * (in_circle / total);
    long double recordDiff = std::abs(M_PI - record_PI);
    long double diff = std::abs(M_PI - pi);
    if (diff < recordDiff) 
    {
      recordDiff = diff;
      record_PI = pi;
      // printf("%f", record_PI);
    }
  }

  points_per_frame *= 1.02;



        RenderEngine::stroke(Color(0,0,0, 1));
        RenderEngine::rect(Vector3(0, 0.9), Vector3(0.3, 0.1));
      RenderEngine::RenderString(-0.1, 0.9, GLUT_BITMAP_TIMES_ROMAN_24, concat(intToString(points_per_frame), " points per frame"), 255,255, 255);


      RenderEngine::rect(Vector3(-0.9, 0.9), Vector3(1.2, 0.1));
      RenderEngine::RenderString(-0.9, 0.9, GLUT_BITMAP_TIMES_ROMAN_24,    concat("Estimated pi:", longDoubleToString(record_PI)), 0, 0, 0);

        RenderEngine::stroke(Color(255,255,255, 1));
      RenderEngine::rect(Vector3(0.9, 0.9), Vector3(1.2, 0.1));
      RenderEngine::RenderString( 0.3, 0.9, GLUT_BITMAP_TIMES_ROMAN_24,concat("The value of pi:" , longDoubleToString(M_PI)), 0,0, 0);
}








