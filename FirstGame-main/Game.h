#pragma once
#include "Window.h"
#include "Renderer.h"
#include "Vector2.h"
#include "Car.h"
#include <vector>

struct Track {

	Track() : pos(0, 0), width(0), height(0) {}
	Track(const int w, const int h) : pos(0, 0), width(w), height(h) {}
	Track(Vector2 position, const int w, const int h) : pos(position), width(w), height(h) {}

	void operator=(Track myTrack)
	{
		this->pos = myTrack.pos;
		this->width = myTrack.width;
		this->height = myTrack.height;
	}

	Vector2 pos;
	int width = 65;
	int height = 20;
	bool hit = false;
};


class Game
{
public:
	static Game& instance()
	{
		static Game inst;
		return inst;
	}

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

private:
	Game(): isRunning(true){}

public:

	int TRACK_W = 40;
	int TRACK_H = 40;
	int TRACK_GAP = 1;
	const int TRACK_COLS = 20;
	const int TRACK_ROWS = 15;


	std::vector<int> trackGrid {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
								1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
								1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
								1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1,
								1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
								1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1,
								1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1,
								1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1,
								1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,
								1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,
								1, 0, 2, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1,
					   			1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
								1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1,
								1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1,
								1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

	float tileRow, tileCol;

	Vector2 BEGIN_POS;

	Car myCar;
	std::vector<Track> tracks;


	bool initialize();
	void loop();
	void close();
	void processInput();
	int trackTileToIndex(int col, int row);
	bool checkForTrackAtPixelCoord(int pixelX, int pixelY);

private:
	void update(float dt);
	void render();

	bool isRunning;
	Window window;
	Renderer renderer;


};

