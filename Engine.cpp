#include "Engine.h"

void Engine::input()
{
	while (m_Window.isOpen())
	{
		Event event;
		while (m_Window.pollEvent(event))
		{
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}
			// handle input segment
			Vector2i current_pos(event.mouseButton.x, event.mouseButton.y);
			if (event.type == Event::Closed)
			{
				// Quit the game when the window is closed
				m_Window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					for (int i =0; i <5; i++)
					{
						int numPoints =  25 + rand() % (50 - 25 + 1);
						Particle(numPoints);
						
					}
				}
			}
}
void Engine::update(float dtAsSeconds)
{

}
void Engine::draw()
{
	w_Window.clear();
	//Loop through each Particle in m_Particles
	for (i=0; i < m_Particles; i++)
	{
		// whaaaat???
		w_Window.draw(m_Particles[i]);
		w_Window.display();
	}
}



// The Engine constructor
Engine::Engine()
{
    int pixelWidth = VideoMode::getDesktopMode().width;
    int pixelHeight = VideoMode::getDesktopMode().height;

    //Construct the RenderWindow
    VideoMode vm(pixelWidth, pixelHeight);
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

