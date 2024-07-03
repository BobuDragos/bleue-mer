#include <cmath>
#include <vector>
#include <GL/freeglut.h>
#include "../../Engine/engine.h"
#include <iostream> // for std::cout, std::endl
#include <cstdlib> // for std::atoi

double Time = 0;
std::vector<double> wave;

const int slider_min = 1;
const int slider_max = 50;
int slider_value = 5;
int direction = 1; // 1 for increment, -1 for decrement

int main(int argc, char** argv) {
    // Parse command-line argument for slider_value
    if (argc > 1) {
        slider_value = std::atoi(argv[1]);
        if (slider_value < slider_min || slider_value > slider_max) {
            std::cerr << "Slider value must be between " << slider_min << " and " << slider_max << std::endl;
            return 1;
        }
    } else {
        std::cerr << "Usage: " << argv[0] << " <slider_value>" << std::endl;
        return 1;
    }

    RenderEngine::setStart([]() {
        RenderEngine::background(Color(0));
        RenderEngine::strokeWeight(2);
        RenderEngine::stroke(Color(255));
    });
    RenderEngine::setUpdate([]() {
        RenderEngine::background(Color(0));

        Vector3 offset(0, 0); // Offset vector for translation

        double x = 0;
        double y = 0;
        double prevx, prevy;

        // Draw circles and lines for the Fourier series
        for (int i = 0; i < slider_value; ++i) {
            prevx = x;
            prevy = y;

            int n = i * 2 + 1;
            double radius = 0.75 * (4.0 / (n * M_PI));
            x += radius * cos(n * Time);
            y += radius * sin(n * Time);

            RenderEngine::stroke(Color(255, 255, 255, 0.4)); // White with 40% opacity
            RenderEngine::noFill();
            RenderEngine::circle(offset + Vector3(prevx, prevy), radius);

            RenderEngine::stroke(Color(255, 255, 255, 1.0)); // White with full opacity
            RenderEngine::line(offset + Vector3(prevx, prevy), offset + Vector3(x, y));
        }
        wave.insert(wave.begin(), y);

        // Draw the wave
        Vector3 waveOffset(0.5, 0); // Offset vector for wave drawing
        RenderEngine::line(offset + Vector3(x - waveOffset.x, y), offset + Vector3(0, wave[0]) + waveOffset);

        // Draw points to represent the wave
        for (size_t i = 0; i < wave.size(); ++i) {
            RenderEngine::point(offset + Vector3((double)i / wave.size(), wave[i]));

            // Draw lines between consecutive points
            if (i > 0) {
                RenderEngine::line(offset + Vector3((double)(i - 1) / wave.size(), wave[i - 1]),
                                   offset + Vector3((double)i / wave.size(), wave[i]));
            }
        }

        // Increment or decrement slider_value
        slider_value += direction;
        if (slider_value <= slider_min || slider_value >= slider_max) {
            direction *= -1; // Reverse direction at boundaries
        }

        Time += 0.05;

        if (wave.size() > 250) {
            wave.pop_back();
        }
    });
    RenderEngine::Enabled(true);
    return 0;
}

