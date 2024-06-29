#include "engine.h"
#include <math.h>
// namespace GameEngine
// {
//     namespace Component
//     {
//         bool Collider::collides(Collider other) 
//         {
//             return false;
//         }
//     }
// }

// #include <stdio.h>

namespace GameEngine
{
    GameObject::GameObject() 
    {
        // Initialize the components with default values
        transform.position = Vector3(0, 0, 0);
        transform.rotation = Vector3(0, 0, 0);
        transform.scale = Vector3(1, 1, 1);
        rigidbody.velocity = Vector3(0, 0, 0);
        renderer.color = Color(1, 1, 1, 1); // Default to white color
    }

    void GameObject::show()
    {
        // RenderEngine::fill();
        RenderEngine::stroke(renderer.color);
        // RenderEngine::strokeWeight(10);
        RenderEngine::rect(transform.position, transform.scale);
        // printf("%f \n", transform.position.x);
    }

    bool GameObject::collides(GameObject& other) 
    {
        // Calculate half-widths and half-heights of both squares
        double halfWidthA = transform.scale.x / 2.0;
        double halfHeightA = transform.scale.y / 2.0;
        double halfWidthB = other.transform.scale.x / 2.0;
        double halfHeightB = other.transform.scale.y / 2.0;

        // Calculate the absolute difference between the x and y coordinates of the centers
        double deltaX = abs(transform.position.x - other.transform.position.x);
        double deltaY = abs(transform.position.y - other.transform.position.y);

        // Calculate the sum of half-widths and half-heights of both squares
        double sumHalfWidths = halfWidthA + halfWidthB;
        double sumHalfHeights = halfHeightA + halfHeightB;

        // Check if the absolute difference is less than or equal to the sum of half-widths and half-heights
        bool collisionX = deltaX <= sumHalfWidths;
        bool collisionY = deltaY <= sumHalfHeights;

        // If both axes have collisions, squares intersect
        return collisionX && collisionY;
    }
}


namespace GameEngine
{

std::map<unsigned char, bool> Input::KeyTable;
std::map<unsigned char, bool> Input::KeyDownTable;
  bool Input::getKeyDown(GameEngine::KeyCode key) 
  {
    if (Input::KeyDownTable[key]) {
        Input::KeyDownTable[key] = false; // Reset after the first check
        return true;
    }
    return false;
  }

  bool Input::getKey(GameEngine::KeyCode key) 
  {
      return Input::KeyTable[key];
  }

  float Input::getAxisRaw(std::string axisName) {
      if (axisName == "Horizontal") {
          if (Input::getKey(GameEngine::KEY_A)) return -1.0f;
          if (Input::getKey(GameEngine::KEY_D)) return 1.0f;
      } else if (axisName == "Vertical") {
          if (Input::getKey(GameEngine::KEY_W)) return 1.0f;
          if (Input::getKey(GameEngine::KEY_S)) return -1.0f;
      }
      return 0.0f;
  }

  void Input::updateKeyState(unsigned char key, bool state) 
  {
    bool oldState = Input::KeyTable[key];
    Input::KeyTable[key] = state;
    if (state && !oldState) {
      Input::KeyDownTable[key] = true; // Register key down event
    }
  }

  void Input::resetKeyStates() 
  {
    for (auto& kv : Input::KeyTable) {
        kv.second = false;
    }
  }
}

