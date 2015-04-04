#include "GameLoop.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

GameLoop::GameLoop():
m_World(),
m_CivCtrls(initCivCtrls()),

m_Mouse(m_World.map().dim(), TILE_SIZE[0]),
m_Keyboard(),
m_Disp(m_World, m_Mouse, m_CivCtrls),

m_Queue(al_create_event_queue()),
m_ScreenRefresher(al_create_timer(1.0 / TARGET_FPS)),

m_NumMoveProcs(0),
m_MoveProcs(new MoveProcess*[NB_CIV * CIV_MAX_POP])
{
    // Check if Allegro instances are correct
	if (m_Queue == NULL){
		FatalErrorDialog("Creation of event queue failed.");
	}
    if (m_ScreenRefresher == NULL){
		FatalErrorDialog("Creation of timer for screen refreshing failed.");
	}

    // Register event sources
	al_register_event_source(
        m_Queue, al_get_keyboard_event_source());
	al_register_event_source(
        m_Queue, al_get_mouse_event_source());
	al_register_event_source(
        m_Queue, al_get_display_event_source(&m_Disp.getWindow()));
	al_register_event_source(
        m_Queue, al_get_timer_event_source(m_ScreenRefresher));
}

CivController** GameLoop::initCivCtrls()
{
    m_CivCtrls = new CivController*[NB_CIV];
    for (int i = 0; i < NB_CIV; ++i) {
        (m_CivCtrls[i] = new CivController(m_World))->placeFirstHuman();
    }
    return m_CivCtrls;
}

GameLoop::~GameLoop()
{
    for (int i = 0; i < NB_CIV; ++i) {
        delete m_CivCtrls[i];
    }
    delete[] m_CivCtrls;
    al_destroy_timer(m_ScreenRefresher);
    al_destroy_event_queue(m_Queue);
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                    START                                   //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

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
    processAI();
}

void GameLoop::processAI()
{
	for (UINT i = 0; i < NB_CIV; ++i) {
        for (UINT j = 0; j < m_CivCtrls[i]->getCiv().population(); ++j) {
            Human& human = m_CivCtrls[i]->getHuman(j);
            if (!human.isReady()) {
				continue;
			}
            processOrder(human, m_CivCtrls[i]->getAI()->giveOrder(human));
		}
	}
}

void GameLoop::processOrder(Human& io_Human, const Order& i_Order)
{
	PossibleOrders action(i_Order.getAction());

	switch (action) {
	case WALK:
        processMovingOrder(io_Human, action, Direction(i_Order.getParam(0)));
		break;
	}
}

void GameLoop::processMovingOrder(Human&         io_Human,
	                              PossibleOrders i_Action, 
                                  Direction      i_Dir)
{
    assertNonCenterDir(i_Dir);

    DCoord after(incrementedToDirection(io_Human.getPos().m_Coord, i_Dir));
	Position dest(after, i_Dir);

    if (verifyDestination(dest)) {
        m_MoveProcs[m_NumMoveProcs] = new MoveProcess(&io_Human, dest);
        ++m_NumMoveProcs;
    }
}

bool GameLoop::verifyDestination(const Position& i_Dest) const
{
    if (!m_World.map().getTile(i_Dest.tileCoord()).isPassable()) {
		LOG(WARNING) << "ERROR IN AI: Cannot move on water";
		return false;
	}
    if (isOccupied(i_Dest.tileCoord())) {
		LOG(WARNING) << "ERROR IN AI: Tile is already occupied";
		return false;
	}
	return true;
}

bool GameLoop::isOccupied(Coord i_Coord) const
{
	for (UINT i = 0; i < NB_CIV; ++i) {
		const Civilization civ = m_CivCtrls[i]->getCiv();
        for (UINT j = 0; j < civ.population(); ++j) {
			Human human = civ.getHuman(j);
            if (human.getPos() == Position(i_Coord, UP)) {
				return true;
			}
		}
	}
	return false;
}

void GameLoop::updateMovements()
{
	for (UINT i = 0; i < m_NumMoveProcs; ++i) {
		m_MoveProcs[i]->nextIter();
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