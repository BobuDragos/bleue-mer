

#include <GL/freeglut_std.h>
#include <GL/freeglut.h>
unsigned char prevKey;
#include <stdio.h>

#include "engine.h"

namespace RenderEngine
{
  class opengl
  {
    public:
      static void (*loop)();
      static void setLoop(void (*func)())
      {
        printf("Loop function set.\n");
        loop = func;
      }

      static void (*start)();
      static void setStart(void (*func)())
      {
        printf("Loop function set.\n");
        start = func;
      }
      static void display(void)
      {
        if(loop)
          loop();

        // // Reset key states if needed
        // Input::resetKeyStates();

        glutSwapBuffers();
        glFlush();
        glutPostRedisplay();

      }

      static void reshape(int w, int h)
      {
        // printf("ReshapeFunction \n");
        
        glViewport(0,0,(GLsizei) w, (GLsizei) h);
      }

      static void keyboard(unsigned char key, int x, int y) {
        if (key == 27)
            exit(0);

        GameEngine::Input::updateKeyState(key, true);
      }

      static void keyUp(unsigned char key, int x, int y) {
        GameEngine::Input::updateKeyState(key, false);
      }

      static void mouse(int button, int state, int x, int y)
      {
        // printf("mouse %d \n", state);

        // if(state == 0)
        //   keyPressed(button + '0', x, y);

        // if (state == 1)
          // keyReleased(button + '0', x, y);
      }

      static void glutSetup(int *argc, char** argv) 
      {
      // glutInit(&argc, argv);
      glutInit(argc, argv);
      glutInitWindowSize(480, 480); // 480x640
      glutInitWindowPosition(0,0);
      glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
      glutCreateWindow("Canvas");

      glutReshapeFunc(reshape);
      glutDisplayFunc(display);
      glutKeyboardFunc(keyboard);
      glutKeyboardUpFunc(keyUp); // Register key release event
      glutMouseFunc(mouse);

      if(start)
        start();

      glutMainLoop();
      }
  };

void (*opengl::loop )() = nullptr;
void (*opengl::start)() = nullptr;



  void Enabled(bool state)
  {
    int argc = 1;
    char *argv[1] = {(char*)"App"};

    opengl::glutSetup(&argc, argv);
  }

  void setUpdate(void (*func)())
  {
    opengl::loop = func;
  }

  void setStart(void (*func)())
  {
    opengl::start = func;
  }





  void background(Color c)
  {
    glClearColor( c.r, c.g, c.b, c.a);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
  }

  /***** ***** ***** ***** ***** *****
                MODIFIERS
   ***** ***** ***** ***** ***** *****/

  void fill()
  {
    glPolygonMode(GL_FRONT, GL_FILL);
  }

  void noFill()
  {
    glPolygonMode(GL_BACK, GL_LINE);
  }

  void strokeWeight(double weight)
  {
    glPointSize(weight);
    glLineWidth(weight);
  }

  void stroke(Color c)
  {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(c.r,c.g,c.b,c.a);
  }

  /***** ***** ***** ***** ***** *****
               PRIMITIVES
   ***** ***** ***** ***** ***** *****/

  void point(Vector3 pos)
  {
    glBegin(GL_POINTS); 
      glVertex4f(pos.x, pos.y, pos.z, pos.w);
    glEnd();
  }

  void line(Vector3 start, Vector3 finish)
  {
    glBegin(GL_LINES);
      glVertex4f(start.x, start.y, start.z, start.w);
      glVertex4f(finish.x, finish.y, finish.z, finish.w);
    glEnd();
  }

  void rect(Vector3 center, Vector3 size)
  {
      Vector3 topLeft    (center.x - size.x / 2, center.y + size.y / 2, 0.0, 1.0);
      Vector3 topRight   (center.x + size.x / 2, center.y + size.y / 2, 0.0, 1.0);
      Vector3 bottomRight(center.x + size.x / 2, center.y - size.y / 2, 0.0, 1.0);
      Vector3 bottomLeft (center.x - size.x / 2, center.y - size.y / 2, 0.0, 1.0);

      glBegin(GL_POLYGON);
          glVertex4f(bottomLeft.x, bottomLeft.y, bottomLeft.z, bottomLeft.w);
          glVertex4f(bottomRight.x, bottomRight.y, bottomRight.z, bottomRight.w);
          glVertex4f(topRight.x, topRight.y, topRight.z, topRight.w);
          glVertex4f(topLeft.x, topLeft.y, topLeft.z, topLeft.w);
      glEnd();
  }


  // void rect(Vector3 bottomLeft, Vector3 topRight)
  // {
  //     Vector3 topLeft(bottomLeft.x, topRight.y, 0.0, 1.0);
  //     Vector3 bottomRight(topRight.x, bottomLeft.y, 0.0, 1.0);

  //     glBegin(GL_POLYGON);
  //         glVertex4f(bottomLeft.x, bottomLeft.y, bottomLeft.z, bottomLeft.w);
  //         glVertex4f(bottomRight.x, bottomRight.y, bottomRight.z, bottomRight.w);
  //         glVertex4f(topRight.x, topRight.y, topRight.z, topRight.w);
  //         glVertex4f(topLeft.x, topLeft.y, topLeft.z, topLeft.w);
  //     glEnd();
  // }

  // void circle(Vector3 center, double r, double segments = 1000){
  //   double π = 3.14159; 
  //   glBegin(GL_POLYGON);
  //   for (int i = 0; i< segments; i++)
  //   {
  //     double θ = 2.0f * π * i/segments;

  //     float x = r * cosf(θ);
  //     float y = r * sinf(θ);

  //     glVertex4f(x, y, center.x, center.w);
  //   }
  //   glEnd();
  // }
  // };
}

