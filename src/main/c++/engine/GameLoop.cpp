#include "GameLoop.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

GameLoop::GameLoop(Display* i_Disp, Mouse* i_Mouse, Keyboard* i_Key) :
m_Disp(i_Disp),
m_Mouse(i_Mouse),
m_Keyboard(i_Key)
{
	i_Mouse->scrollX = maxBufferDimensions().x / 2;
	i_Mouse->scrollY = maxBufferDimensions().y / 2;
	i_Mouse->maxScrollX = maxBufferDimensions().x;
	i_Mouse->maxScrollY = maxBufferDimensions().y;

	m_Queue = al_create_event_queue();
	if (m_Queue == nullptr){
		FatalErrorDialog("Creation of event queue failed.");
	}

	m_ScreenRefresher = al_create_timer(1.0 / TARGET_FPS);
	if (m_ScreenRefresher == nullptr){
		FatalErrorDialog("Creation of timer for screen refreshing failed.");
	}

	al_register_event_source(m_Queue, al_get_keyboard_event_source());
	al_register_event_source(m_Queue, al_get_mouse_event_source());
	al_register_event_source(m_Queue, al_get_display_event_source(i_Disp->m_Window));
	al_register_event_source(m_Queue, al_get_timer_event_source(m_ScreenRefresher));

	initializeCivsAndAIs();

	m_NumMoveProcs = 0;
	m_MoveProcs = new MoveProcess*[NB_CIV * MAX_POPULATION];
}

GameLoop::~GameLoop()
{
	al_destroy_timer(m_ScreenRefresher);
	al_destroy_event_queue(m_Queue);
}

void GameLoop::initializeCivsAndAIs()
{
	m_CivCtrlrs = new CivController*[NB_CIV];
	m_AIs = new AI*[NB_CIV];

	for (int i = 0; i < NB_CIV; ++i) {
		CivController* civ = new CivController();
		civ->placeFirstHuman();
		m_CivCtrlrs[i] = civ;
		m_AIs[i] = new AtomAI(civ);
	}
	m_Disp->setCivs(m_CivCtrlrs);
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                    START                                   //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

bool GameLoop::start()
{
	al_start_timer(m_ScreenRefresher);

	int currentFrame = 0;
	int frameForGameUpdate = TARGET_FPS * SECONDS_BETWEEN_AI_PROCESS;

	bool exitGame = false;
	bool refresh = true;
	int fps = 0, fps_accum = 0;
	double fps_time = 0;

	while (!exitGame) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(m_Queue, &ev);

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
			m_Mouse->handleMouseEvent(ev);
			break;

		case ALLEGRO_EVENT_TIMER:
			refresh = true;
			break;

		case ALLEGRO_EVENT_DISPLAY_RESIZE:
			al_acknowledge_resize(m_Disp->m_Window);
			refresh = true;
			break;
		}

		if (refresh && al_is_event_queue_empty(m_Queue)) {
			updateMovements();

			double time = al_get_time();

			m_Disp->draw();
			al_flip_display();

			fps_accum++;
			if (time - fps_time >= 1) {
				fps = fps_accum;
				fps_accum = 0;
				fps_time = time;
			}
			m_Disp->setFPS(fps);

			refresh = false;

			++currentFrame;
		}
	}
	return EXIT_SUCCESS;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                    UPDATE                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

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
		CivController* civ = m_CivCtrlrs[i];
		AI* ai = m_AIs[i];
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

bool GameLoop::processOrder(Human* io_Human, const Order& i_Order)
{
	PossibleOrders action = i_Order.getAction();

	switch (action) {
	case WALK:
		Direction direction = Direction(i_Order.getParams()[0]);
		assert(direction != MIDDLE);
		if (processMovingOrder(io_Human, action, direction)) {
			return EXIT_FAILURE;
		}
		break;
	}

	return EXIT_SUCCESS;
}

bool GameLoop::processMovingOrder(Human* i_Human,	
	                              PossibleOrders i_Action, 
                                  Direction i_Dir)
{
	float tilePerTurn = i_Human->getMoveSpeed();
	switch (i_Action) {
	case WALK: tilePerTurn; break;
	}

	Coord<float> after = i_Human->m_Pos.m_Coord.incrementedToDirection(i_Dir);
	Position dest = Position(after, i_Dir);

	if (verifyDestination(dest)) {
		m_MoveProcs[m_NumMoveProcs] = new MoveProcess(i_Human, dest);
		++m_NumMoveProcs;
	}

	return EXIT_SUCCESS;
}

bool GameLoop::verifyDestination(const Position& i_Dest) const
{
	Map* map = World::getInstance()->map;
	Coord<int> coord = Coord<int>(i_Dest.m_Coord.x, i_Dest.m_Coord.y);
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

bool GameLoop::isOccupied(Coord<int> i_Coord) const
{
	for (int i = 0; i < NB_CIV; ++i) {
		CivController* civ = m_CivCtrlrs[i];
		for (unsigned int j = 0; j < civ->getPopulation(); ++j) {
			Human* human = civ->getHuman(j);
			if (human->m_Pos == Position(UP, i_Coord)) {
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
	for (int i = 0; i < m_NumMoveProcs; ++i) {
		m_MoveProcs[i]->nextIteration();
	}
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                   END                       //
//- - - - - - - - - - - - - - - - - - - - - - -//

void GameLoop::endProcesses()
{
	for (int i = 0; i < m_NumMoveProcs; ++i) {
		delete m_MoveProcs[i];
	}
	m_NumMoveProcs = 0;
}