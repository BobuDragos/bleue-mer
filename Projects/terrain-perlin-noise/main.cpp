#include "../../Engine/engine.h"
#include <cmath>

const int cols = 70;
const int rows = 50;
const int scl = 20;
const float w = 2.0f / cols; // Adjusted to fit within -1 to 1 range
const float h = 2.0f / rows; // Adjusted to fit within -1 to 1 range

float flying = 0;

float terrain[cols][rows];

void setup() {
    // Setup function (if required in your engine)
}

void draw() {
    flying -= 0.1f;
    float yoff = flying;
    
    for (int y = 0; y < rows; y++) {
        float xoff = 0;
        for (int x = 0; x < cols; x++) {
            // Simulating Perlin noise with a basic sine wave pattern
            terrain[x][y] = sin(xoff) * 0.2f; // Adjusted to fit within -1 to 1 range
            xoff += 0.2f;
        }
        yoff += 0.2f;
    }
    
    RenderEngine::background(Color(255));

    // Define translation vector
    Vector3 translation(-1.0f, -1.0f, 0.0f); // Adjust translation as needed

    RenderEngine::strokeWeight(10);
    RenderEngine::stroke(Color(0));
    // RenderEngine::noFill();

    // Draw lines
    for (int y = 0; y < rows - 1; y++) {
        for (int x = 0; x < cols; x++) {
            float x1 = x * scl * w; // Map x coordinate to -1 to 1 range
            float y1 = terrain[x][y];
            float x2 = x * scl * w; // Map x coordinate to -1 to 1 range
            float y2 = terrain[x][y + 1];
            
            // Apply translation
            Vector3 p1(x1 / 20, y1 / 2, 0);
            Vector3 p2(x2 / 20, y2 / 2, 0);
            p1 += translation;
            p2 += translation;
      
      printf("%f %f ", p1.x, p1.y);
      printf("%f %f \n", p2.x, p2.y);

            RenderEngine::line(p1, p2);
        }
    }
}

int main() {
    RenderEngine::setStart([]() {
        // Initialization
    });

    RenderEngine::setUpdate(draw);
    RenderEngine::Enabled(true);
}

