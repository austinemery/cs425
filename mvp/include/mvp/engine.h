#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <sys/time.h>
#include <assert.h>
#include <mobileye_560_660_msgs/Lane.h>
#include <mobileye_560_660_msgs/LkaLane.h>
#include <mobileye_560_660_msgs/ObstacleData.h>
#include <queue>
#include <string>

#include "window.h"
#include "graphics.h"
#include "ros/ros.h"
#include "std_msgs/String.h"

class Engine
{
  public:
    Engine(string name, int width, int height);
    Engine(string name);
    ~Engine();
    bool Initialize(int, char **argv);
    void Run();
    void Keyboard();
    unsigned int getDT();
    long long GetCurrentTimeMillis();
    void PopulateBuffer(string);

  private:
    //Buffer
    queue<string> buffer;

    // Window related variables
    Window *m_window;    
    string m_WINDOW_NAME;
    int m_WINDOW_WIDTH;
    int m_WINDOW_HEIGHT;
    bool m_FULLSCREEN;
    SDL_Event m_event;

    Graphics *m_graphics;
    unsigned int m_DT;
    long long m_currentTimeMillis;
    bool m_running;
};

#endif // ENGINE_H
