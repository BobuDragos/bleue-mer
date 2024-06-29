#include <stdio.h>
#pragma once

#include <string>
#include <map>
/**
 * \file engine.h
 *
 * This file contains the definitions for a simple rendering engine, 
 * vector mathematics, color representation, and game object components.
 */


namespace MathEngine
{
  class Vector3
  {
  public:
    double x, y, z, w;
    static Vector3 zero;
    static Vector3  one;
    // static Vector3 random;


      /**
       * \brief Default constructor initializing vector to (0,0,0,1).
       */
    Vector3();

      /**
       * \brief Parameterized constructor for initializing vector components.
       *
       * \param _x X component.
       * \param _y Y component (default is 0.0).
       * \param _z Z component (default is 0.0).
       * \param _w W component (default is 1.0).
       */
    Vector3(double _x, double _y = 0.0f, double _z = 0.0f, double _w = 1.0f);

    Vector3& operator=(const Vector3& other);
    Vector3& operator+=(const Vector3& other);
    Vector3& operator*=(double scalar);
    Vector3 operator*(double scalar) const;
    Vector3 operator-(const Vector3& other) const; 
    Vector3 operator+(const Vector3& other) const; 
    double dot(const Vector3& other) const;
    Vector3 operator/(double scalar) const;

    double distance(const Vector3& other) const ;
  };

  // Vector3 Vector3::zero = Vector3(0, 0, 0, 1);
  // Vector3 Vector3::one  = Vector3(1, 1, 1, 1);

  class Color
  {
  public:
    float r, g, b, a;
    /* 4bit color support */
    static Color black;
    static Color white;
    static Color red;
    static Color green;
    static Color blue;
    static Color yellow;
    static Color cyan;
    static Color magenta;
    static Color gray;
    static Color darkGray;
    static Color lightGray;
    static Color darkRed;
    static Color darkGreen;
    static Color darkBlue;
    static Color brown;
    static Color orange;


     /**
     * \brief Default constructor initializing color to white (1.0, 1.0, 1.0, 1.0).
     */
    Color(); 

      /**
       * \brief Constructor for grayscale color.
       *
       * \param _value Grayscale value.
       */
    Color(double _value);
      /**
       * \brief Constructor for RGB color.
       *
       * \param _r Red component.
       * \param _g Green component.
       * \param _b Blue component.
       */
    Color(double _r, double _g, double _b);

      /**
       * \brief Main constructor for RGBA color.
       *
       * \param _r Red component.
       * \param _g Green component.
       * \param _b Blue component.
       * \param _a Alpha component.
       */
    Color(double _r, double _g, double _b, double _a);
  };
  class Random
  {
    // public:
      // static Vector3 Vector3();
      // static Color     Color();
  };
}

using MathEngine::Vector3;
using MathEngine::Color;

namespace RenderEngine
{
  /**
   * \brief Enable or disable the rendering engine.
   *
   * \param state Boolean flag to enable or disable the engine.
   */
  void Enabled(bool state);

  /**
   * \brief Set the start function callback.
   *
   * \param func Pointer to the start function.
   */
  void setStart (void (*func)());

  /**
   * \brief Set the update function callback.
   *
   * \param func Pointer to the update function.
   */
  void setUpdate(void (*func)());


  class opengl;


  void background(Color c);
  void fill();
  void noFill();
  void strokeWeight(double weight);
  void stroke(Color c);
  void point(Vector3 pos);
  void line(Vector3 start, Vector3 finish);
  void rect(Vector3 bottomLeft, Vector3 topRight);
  void circle(Vector3 center, double r, double segments = 1000);

  

  // class primitives;
}

namespace GameEngine
{
  namespace Component
  {
    class Transform
    {
      public:
        Vector3 position; ///< Position of the component.
        Vector3 rotation; ///< Rotation of the component.
        Vector3 scale;    ///< Scale of the component.
    };
    class Rigidbody
    {
      public:
        Vector3 velocity;
    };
    class Renderer
    {
      public:
        Color color;
    };
    class Collider
    {

    };
  }

  class GameObject
  {
  public:
    Component::Transform transform;
    Component::Rigidbody rigidbody;
    Component::Renderer  renderer ;
    Component::Collider  collider ;

    GameObject();

    void show();
    bool collides(GameObject& other);
  };

  enum KeyCode 
  {
      // Alphabets
      KEY_A = 'a',
      KEY_B = 'b',
      KEY_C = 'c',
      KEY_D = 'd',
      KEY_E = 'e',
      KEY_F = 'f',
      KEY_G = 'g',
      KEY_H = 'h',
      KEY_I = 'i',
      KEY_J = 'j',
      KEY_K = 'k',
      KEY_L = 'l',
      KEY_M = 'm',
      KEY_N = 'n',
      KEY_O = 'o',
      KEY_P = 'p',
      KEY_Q = 'q',
      KEY_R = 'r',
      KEY_S = 's',
      KEY_T = 't',
      KEY_U = 'u',
      KEY_V = 'v',
      KEY_W = 'w',
      KEY_X = 'x',
      KEY_Y = 'y',
      KEY_Z = 'z',

      // Numbers
      KEY_0 = '0',
      KEY_1 = '1',
      KEY_2 = '2',
      KEY_3 = '3',
      KEY_4 = '4',
      KEY_5 = '5',
      KEY_6 = '6',
      KEY_7 = '7',
      KEY_8 = '8',
      KEY_9 = '9',

      // Function keys
      KEY_F1  = 0x70,
      KEY_F2  = 0x71,
      KEY_F3  = 0x72,
      KEY_F4  = 0x73,
      KEY_F5  = 0x74,
      KEY_F6  = 0x75,
      KEY_F7  = 0x76,
      KEY_F8  = 0x77,
      KEY_F9  = 0x78,
      KEY_F10 = 0x79,
      KEY_F11 = 0x7A,
      KEY_F12 = 0x7B,

      // Special keys
      KEY_SPACE     = ' ',
      KEY_ENTER     = '\n',
      KEY_ESCAPE    = 0x1B,
      KEY_TAB       = '\t',
      KEY_BACKSPACE = 0x08,
      KEY_SHIFT     = 0x10,
      KEY_CTRL      = 0x11,
      KEY_ALT       = 0x12,
      KEY_DELETE    = 0x7F,
      // Add more special keys as needed
  };

  class Input
  {
  public:
    static std::map<unsigned char, bool> KeyTable;
    static std::map<unsigned char, bool> KeyDownTable;

    static bool getKeyDown(GameEngine::KeyCode key);
    static bool getKey(GameEngine::KeyCode key);
    

    static float getAxisRaw(std::string axisName); 

    static void updateKeyState(unsigned char key, bool state = true);
    static void resetKeyStates();
  };
}

using GameEngine::GameObject;
using GameEngine::KeyCode;

