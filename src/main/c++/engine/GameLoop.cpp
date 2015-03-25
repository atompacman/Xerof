#include "GameLoop.h"

//= = = = = = = = = = = = = = = = = = = = = = =//
//           CONSTRUCTOR/DESCTRUCTOR           //
//- - - - - - - - - - - - - - - - - - - - - - -//

GameLoop::GameLoop(Display* display, Mouse* mouse, Keyboard* keyboard) :
	display(display),
	mouse(mouse),
	keyboard(keyboard)
{
	mouse->scrollX = maxBufferDimensions().x / 2;
	mouse->scrollY = maxBufferDimensions().y / 2;
	mouse->maxScrollX = maxBufferDimensions().x;
	mouse->maxScrollY = maxBufferDimensions().y;

	queue = al_create_event_queue();
	if (queue == nullptr){
		FatalErrorDialog("Creation of event queue failed.");
	}

	screenRefresher = al_create_timer(1.0 / TARGET_FPS);
	if (screenRefresher == nullptr){
		FatalErrorDialog("Creation of timer for screen refreshing failed.");
	}

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_display_event_source(display->m_Window));
	al_register_event_source(queue, al_get_timer_event_source(screenRefresher));

	initializeCivsAndAIs();

	nbMoveProcess = 0;
	moveProcesses = new MoveProcess*[NB_CIV * MAX_POPULATION];
}

GameLoop::~GameLoop()
{
	al_destroy_timer(screenRefresher);
	al_destroy_event_queue(queue);
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//               INITIALIZE CIVS               //
//- - - - - - - - - - - - - - - - - - - - - - -//

void GameLoop::initializeCivsAndAIs()
{
	civilizations = new CivController*[NB_CIV];
	ais = new AI*[NB_CIV];

	for (int i = 0; i < NB_CIV; ++i) {
		CivController* civ = new CivController();
		civ->placeFirstHuman();
		civilizations[i] = civ;
		ais[i] = new AtomAI(civ);
	}
	display->setCivs(civilizations);
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                    START                    //
//- - - - - - - - - - - - - - - - - - - - - - -//

bool GameLoop::start()
{
	al_start_timer(screenRefresher);

	int currentFrame = 0;
	int frameForGameUpdate = TARGET_FPS * SECONDS_BETWEEN_AI_PROCESS;

	bool exitGame = false;
	bool refresh = true;
	int fps = 0, fps_accum = 0;
	double fps_time = 0;

	while (!exitGame) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(queue, &ev);

		if (currentFrame == frameForGameUpdate) {
			endProcesses();
			if (updateGame() == EXIT_FAILURE) {
				return EXIT_FAILURE;
			}
			currentFrame = 0;
		}

		switch (ev.type) {
		case ALLEGRO_EVENT_DISPLAY_CLOSE: 
			exitGame = true; 
			break;

		case ALLEGRO_EVENT_KEY_DOWN: 
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				exitGame = true;
			}
			break;

		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN :
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP :
		case ALLEGRO_EVENT_MOUSE_AXES :
			mouse->handleMouseEvent(ev);
			break;

		case ALLEGRO_EVENT_TIMER:
			refresh = true;
			break;

		case ALLEGRO_EVENT_DISPLAY_RESIZE:
			al_acknowledge_resize(display->m_Window);
			refresh = true;
			break;
		}

		if (refresh && al_is_event_queue_empty(queue)) {
			updateMovements();

			double time = al_get_time();

			display->draw();
			al_flip_display();

			fps_accum++;
			if (time - fps_time >= 1) {
				fps = fps_accum;
				fps_accum = 0;
				fps_time = time;
			}
			display->setFPS(fps);

			refresh = false;

			++currentFrame;
		}
	}
	return EXIT_SUCCESS;
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                   UPDATE                    //
//- - - - - - - - - - - - - - - - - - - - - - -//

bool GameLoop::updateGame()
{
	if (processAI() == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

bool GameLoop::processAI()
{
	for (int i = 0; i < NB_CIV; ++i) {
		CivController* civ = civilizations[i];
		AI* ai = ais[i];
		int civPop = civ->getPopulation();

		for (int j = 0; j < civPop; ++j) {
			Human* human = civ->getHuman(j);
			if (!human->isReady()) {
				continue;
			}
			Order order = ai->giveOrder(*human);
			if (processOrder(human, order) == EXIT_FAILURE) {
				return EXIT_FAILURE;
			}
		}
	}
	return EXIT_SUCCESS;
}

bool GameLoop::processOrder(Human* human, const Order& order)
{
	PossibleOrders action = order.getAction();

	switch (action) {
	case WALK:
		Direction direction = Direction(order.getParams()[0]);
		assert(direction != MIDDLE);
		if (processMovingOrder(human, action, direction)) {
			return EXIT_FAILURE;
		}
		break;
	}

	return EXIT_SUCCESS;
}

bool GameLoop::processMovingOrder(Human* human,	
	PossibleOrders action, Direction direction)
{
	float tilePerTurn = human->getMoveSpeed();
	switch (action) {
	case WALK: tilePerTurn; break;
	}

	Coord<float> after = human->m_Pos.m_Coord.incrementedToDirection(direction);
	Position dest = Position(after, direction);

	if (verifyDestination(dest)) {
		moveProcesses[nbMoveProcess] = new MoveProcess(human, dest);
		++nbMoveProcess;
	}

	return EXIT_SUCCESS;
}

bool GameLoop::verifyDestination(const Position& destination) const
{
	Map* map = World::getInstance()->map;
	Coord<int> coord = Coord<int>(destination.m_Coord.x, destination.m_Coord.y);
	Tile* destTile = map->getTile(coord);
	if (!destTile->isPassable()) {
		LOG(WARNING) << "ERROR IN AI: Cannot move on water";
		return false;
	}
	if (isOccupied(coord)) {
		LOG(WARNING) << "ERROR IN AI: Tile is already occupied";
		return false;
	}
	return true;
}

bool GameLoop::isOccupied(Coord<int> coord) const
{
	for (int i = 0; i < NB_CIV; ++i) {
		CivController* civ = civilizations[i];
		for (unsigned int j = 0; j < civ->getPopulation(); ++j) {
			Human* human = civ->getHuman(j);
			if (human->m_Pos == Position(UP, coord)) {
				return true;
			}
		}
	}
	return false;
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//              UPDATE  MOVEMENTS              //
//- - - - - - - - - - - - - - - - - - - - - - -//

void GameLoop::updateMovements()
{
	for (int i = 0; i < nbMoveProcess; ++i) {
		moveProcesses[i]->nextIteration();
	}
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                   END                       //
//- - - - - - - - - - - - - - - - - - - - - - -//

void GameLoop::endProcesses()
{
	for (int i = 0; i < nbMoveProcess; ++i) {
		delete moveProcesses[i];
	}
	nbMoveProcess = 0;
}