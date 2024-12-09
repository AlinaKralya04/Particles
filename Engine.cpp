#include "Engine.h"

// The Engine constructor
Engine::Engine()
{
	int pixelWidth = VideoMode::getDesktopMode().width;
	int pixelHeight = VideoMode::getDesktopMode().height;

	//Construct the RenderWindow
	VideoMode vm(pixelWidth, pixelHeight);
	//possible edit 
	m_Window.create(vm, "Particles", Style::Default);
}

// Run will call all the private functions
void Engine::run()
{
	Clock clock;

	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;
	
	// Game Loop
	while (m_Window.isOpen())
	{
		Time dt = clock.restart();
		float seconds = dt.asSeconds();

		while (Keyboard::isKeyPressed(Keyboard::Space))
		{
			input();
			draw();
			Time dt = clock.restart();
		}

		// Call input, update draw
		input();
		update(seconds);
		draw();
	}
}

void Engine::input()
{
	Event event;
	while (m_Window.pollEvent(event))
	{
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			m_Window.close();
		}

		if (event.type == Event::Closed)
		{
			m_Window.close();
		}

		Vector2i current_pos(event.mouseButton.x, event.mouseButton.y);
		if (event.type == Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == Mouse::Left)
			{
				/*added sound
				SoundBuffer buffer("new-year-fireworks-sound4-180205.wav");
				Sound sound(buffer);
				sound.play();
				*/
				//new
				SoundBuffer buffer;
    				buffer.loadFromFile("new-year-fireworks-sound4-180205.wav");
				Sound sound;
				sound.setBuffer(buffer);
				sound.play();
				
				for (int i = 0; i < 5; i++)
				{
					int numPoints = rand() % 26 + 25;
					m_particles.push_back(Particle(m_Window, numPoints, current_pos));
				}
			}
		}
	}
}

void Engine::update(float dtAsSeconds)
{
	for (int i = 0; i < m_particles.size();)
	{
		if (m_particles[i].getTTL() > 0.0)
		{
			//check call update on each Particle in the vector whose ttl (time to live) has not expired
			m_particles[i].update(dtAsSeconds);
			i++;
		}
		else
		{
			m_particles.erase(m_particles.begin() + i);
		}
	}
}

void Engine::draw()
{
	m_Window.clear();

	//Loop through each Particle in m_Particles
	for (int i = 0; i < m_particles.size(); i++)
	{
		m_Window.draw(m_particles.at(i));
	}
	m_Window.display();
	
}
