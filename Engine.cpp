#include "Engine.h"

void Engine::input()
{

}
void Engine::update(float dtAsSeconds)
{

    
}
void Engine::draw()
{
}



// The Engine constructor
Engine::Engine()
{
    int pixelWidth = VideoMode::getDesktopMode().width;
    int pixelHeight = VideoMode::getDesktopMode().height;

    //Construct the RenderWindow
    VideoMode vm(pixelWidth, pixelHeight);
    RenderWindow m_Window;
    m_Window.create(vm, "Particles", Style::Default);
}

/ Run will call all the private functions
void Engine::run()
{
    Clock clock;
    Time dt = clock.getElapsedTime();
    cout << "Starting Particle unit tests..." << endl;
    Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
    p.unitTests();
    cout << "Unit tests complete.  Starting engine..." << endl;
  // Game Loop
    while (m_Window.isOpen())
	  {
      //Restart the clock (this will return the time elapsed since the last frame)
      Time restart =  clock.restart();
      //Convert the clock time to seconds
      float seconds = dt.asSeconds();
      // Call input, update draw
      input();
      update(seconds);
      draw();
    } 
}

