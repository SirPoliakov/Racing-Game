#include "Game.h"
#include "Actor.h"
#include "Assets.h"
#include "Timer.h"




bool Game::initialize()
{
	bool isWindowInit = window.initialize();
	bool isRendererInit = myRenderer.initialize(window);

	return isWindowInit && isRendererInit; // Return bool && bool && bool ...to detect error
}

void Game::load()
{
	// SHADERS ==============================
	Assets::loadShader("Rsc\\Shaders\\Sprite.vert", "Rsc\\Shaders\\Sprite.frag", "", "", "", "Sprite");

	// TEXTURES =============================
	Assets::loadTexture(myRenderer, "Rsc\\Textures\\Tree.bmp", "Tree");
	Assets::loadTexture(myRenderer, "Rsc\\Textures\\concrete.bmp", "Concrete");
	Assets::loadTexture(myRenderer, "Rsc\\Textures\\Car.bmp", "Car");

	// ACTORS QUEUE LOADING =================

	Vector3 vec3 = Vector3::zero;
	vec3.x = -WINDOW_WIDTH / 2 + 50;
	vec3.y = WINDOW_HEIGHT / 2 - 50;
	Actor* tmpActor;
	int k = 0; int kmax = TRACK_COLS * TRACK_ROWS;

	for (int i = 0; i < TRACK_ROWS; i++)
	{
		for (int j = 0; j < TRACK_COLS; j++)
		{
			tmpActor = new Actor(Vector2(TRACK_W, TRACK_H), vec3);
			if (trackGrid[k] == 1) new SpriteComponent(actors.back(), Assets::getTexture("Tree"), 1);
			else if (trackGrid[k] == 0 || trackGrid[k] == 2)
			{
				new SpriteComponent(actors.back(), Assets::getTexture("Concrete"), 1);
				if (trackGrid[k] == 2) { BEGIN_POS.x = vec3.x; BEGIN_POS.y = vec3.y; }
			}

			std::cout << "Tile position :  (" << tmpActor->getPosition().x << "; " << tmpActor->getPosition().y << ") ;" << std::endl;

			vec3.x += TRACK_W;

			if (k < kmax - 1) k++;
		}

		tmpActor = new Actor(Vector2(TRACK_W, TRACK_H), vec3);
		if (trackGrid[k] == 1) new SpriteComponent(actors.back(), Assets::getTexture("Tree"), 1);
		if (trackGrid[k] == 0 || trackGrid[k] == 2) new SpriteComponent(actors.back(), Assets::getTexture("Concrete"), 1);
		vec3.x = -WINDOW_WIDTH / 2 + 50;
		vec3.y -= TRACK_H;

	}

	myCar = new Car(CAR_DIMENSIONS, 0);
	vec3 = Vector3::zero; vec3.x = BEGIN_POS.x; vec3.y = BEGIN_POS.y;
	myCar->setPosition(vec3); myCar->setRotation(M_PI / 2);

	new SpriteComponent(actors.back(), Assets::getTexture("Car"), 1);
}

void Game::processInput()
{
	// SDL Event
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		}
	}
	// Keyboard state
	const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);


	// Escape: quit game
	if (keyboardState[SDL_SCANCODE_ESCAPE])
	{
		isRunning = false;
	}

	// Car launch
	if (keyboardState[SDL_SCANCODE_W])
	{
		myCar->processInput(Z);

	}
	else if (myCar->getVelo() > 0)
	{
		myCar->slowDown(0.5);
	}

	if (keyboardState[SDL_SCANCODE_A])
	{
		myCar->processInput(Q);
	}
	if (keyboardState[SDL_SCANCODE_D])
	{
		myCar->processInput(D);
	}

	if (keyboardState[SDL_SCANCODE_S])
	{
		myCar->processInput(S);
	}

	// Car reset
	if (keyboardState[SDL_SCANCODE_SPACE])
	{
		Vector3 vec3 = Vector3::zero; vec3.x = BEGIN_POS.x; vec3.y = BEGIN_POS.y;
		myCar->setPosition(vec3);
		myCar->setVelocity(0);
		myCar->setRotation(1.0);
	}

	// Escape: quit game
	if (keyboardState[SDL_SCANCODE_ESCAPE])
	{
		isRunning = false;
	}
}

void Game::update(float dt)
{
	//v =============================================================╗
	//v Common actor management                                      ║

	// Update actors 
	isUpdatingActors = true;
	for (auto actor : actors)
	{
		actor->update(dt);
	}
	isUpdatingActors = false;

	// Move pending actors to actors
	for (auto pendingActor : pendingActors)
	{
		pendingActor->computeWorldTransform();
		actors.emplace_back(pendingActor);
	}
	pendingActors.clear();

	// Delete dead actors
	std::vector<Actor*> deadActors;
	for (auto actor : actors)
	{
		if (actor->getState() == Actor::ActorState::Dead)
		{
			deadActors.emplace_back(actor);
		}
	}
	for (auto deadActor : deadActors)
	{
		delete deadActor;
	}

	//^ Common actor management                                      ║
	//^ =============================================================╝

}

void Game::render()
{
	myRenderer.beginDraw();
	myRenderer.draw();
	myRenderer.endDraw();
}


void Game::loop()
{
	Timer timer;
	float dt = 0;
	while (isRunning)
	{
		float dt = timer.computeDeltaTime() / 1000.0f;
		processInput();
		update(dt);
		render();
		timer.delayTime();
	}
}

void Game::unload()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!actors.empty())
	{
		delete actors.back();
	}

	// Resources
	Assets::clear();
}

void Game::close()
{
	myRenderer.close();
	window.close();
	SDL_Quit();
}

void Game::addActor(Actor* actor)
{
	if (isUpdatingActors)
	{
		pendingActors.emplace_back(actor);
	}
	else
	{
		actors.emplace_back(actor);
	}
}

void Game::removeActor(Actor* actor)
{
	// Erase actor from the two vectors
	auto iter = std::find(begin(pendingActors), end(pendingActors), actor);
	if (iter != end(pendingActors))
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, end(pendingActors) - 1);
		pendingActors.pop_back();
	}
	iter = std::find(begin(actors), end(actors), actor);
	if (iter != end(actors))
	{
		std::iter_swap(iter, end(actors) - 1);
		actors.pop_back();
	}
}