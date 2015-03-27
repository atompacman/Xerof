#include "GameLoop.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

GameLoop::GameLoop():
m_Mouse(),
m_Keyboard(),
m_Disp(&m_Mouse),

m_Queue(al_create_event_queue()),
m_ScreenRefresher(al_create_timer(1.0 / TARGET_FPS)),

m_CivCtrlrs(NULL),
m_AIs(NULL),

m_NumMoveProcs(0),
m_MoveProcs(new MoveProcess*[NB_CIV * MAX_POPULATION])
{
	if (m_Queue == NULL){
		FatalErrorDialog("Creation of event queue failed.");
	}
    if (m_ScreenRefresher == NULL){
		FatalErrorDialog("Creation of timer for screen refreshing failed.");
	}

	al_register_event_source(
        m_Queue, al_get_keyboard_event_source());
	al_register_event_source(
        m_Queue, al_get_mouse_event_source());
	al_register_event_source(
        m_Queue, al_get_display_event_source(m_Disp.getWindow()));
	al_register_event_source(
        m_Queue, al_get_timer_event_source(m_ScreenRefresher));

	initializeCivsAndAIs();
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
	m_Disp.setCivs(m_CivCtrlrs);
}

GameLoop::~GameLoop()
{
    al_destroy_timer(m_ScreenRefresher);
    al_destroy_event_queue(m_Queue);
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                    START                                   //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void GameLoop::run()
{
   GameLoop().startGame();
}

void GameLoop::startGame()
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
            updateGame();
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
			m_Mouse.handleMouseEvent(ev);
			break;

		case ALLEGRO_EVENT_TIMER:
			refresh = true;
			break;

		case ALLEGRO_EVENT_DISPLAY_RESIZE:
            m_Disp.resize();
			refresh = true;
			break;
		}

		if (refresh && al_is_event_queue_empty(m_Queue)) {
			updateMovements();

			double time = al_get_time();

			m_Disp.draw();
			al_flip_display();

			fps_accum++;
			if (time - fps_time >= 1) {
				fps = fps_accum;
				fps_accum = 0;
				fps_time = time;
			}
			m_Disp.setFPS(fps);

			refresh = false;

			++currentFrame;
		}
	}
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                    UPDATE                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void GameLoop::updateGame()
{
	if (processAI() == EXIT_FAILURE) {
        FatalErrorDialog("Error processing AIs");
	}
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

bool GameLoop::processMovingOrder(Human*         i_Human,	
	                              PossibleOrders i_Action, 
                                  Direction      i_Dir)
{
	float tilePerTurn = i_Human->getMoveSpeed();
	switch (i_Action) {
	case WALK: tilePerTurn; break;
	}

    DCoord after = incrementedToDirection(i_Human->m_Pos.m_Coord, i_Dir);
	Position dest = Position(after, i_Dir);

	if (verifyDestination(dest)) {
		m_MoveProcs[m_NumMoveProcs] = new MoveProcess(i_Human, dest);
		++m_NumMoveProcs;
	}

	return EXIT_SUCCESS;
}

bool GameLoop::verifyDestination(const Position& i_Dest) const
{
	Map* map = World::getInstance()->m_Map;
	Coord coord = Coord(i_Dest.m_Coord.x, i_Dest.m_Coord.y);
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

bool GameLoop::isOccupied(Coord i_Coord) const
{
	for (int i = 0; i < NB_CIV; ++i) {
		CivController* civ = m_CivCtrlrs[i];
		for (unsigned int j = 0; j < civ->getPopulation(); ++j) {
			Human* human = civ->getHuman(j);
            if (human->m_Pos == Position(i_Coord, UP)) {
				return true;
			}
		}
	}
	return false;
}

void GameLoop::updateMovements()
{
	for (UINT i = 0; i < m_NumMoveProcs; ++i) {
		m_MoveProcs[i]->nextIteration();
	}
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                     END                                    //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void GameLoop::endProcesses()
{
	for (UINT i = 0; i < m_NumMoveProcs; ++i) {
		delete m_MoveProcs[i];
	}
	m_NumMoveProcs = 0;
}