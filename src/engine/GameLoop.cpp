#include <allegro5\allegro.h>
#include <AI.h>
#include <CivController.h>
#include <FullMapKnowledge.h>
#include <GameLoop.h>
#include <HumanInfo.h>
#include <HumanPerception.h>
#include <MoveProcess.h>
#include <Order.h>
#include <Parameters.h>
#include <Tile.h>

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

GameLoop::GameLoop() :
m_World(),
m_CivCtrls(initCivCtrls()),

m_DisplayInfo(m_World.map(), &m_CivCtrls[0]->getCiv().getHuman(0)),
m_Mouse(m_DisplayInfo),
m_Keyboard(m_DisplayInfo),
m_Disp(m_DisplayInfo),

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

    // Set default cursor
    al_set_system_mouse_cursor(&m_Disp.getWindow(),
        ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);

    // Register event sources
    al_register_event_source(m_Queue, al_get_keyboard_event_source());
    al_register_event_source(m_Queue, al_get_mouse_event_source());
    al_register_event_source(m_Queue, al_get_display_event_source(
        &m_Disp.getWindow()));
    al_register_event_source(m_Queue, al_get_timer_event_source(
        m_ScreenRefresher));
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

    int frameForGameUpdate = TARGET_FPS * SECONDS_BETWEEN_AI_PROCESS;
    int currentFrame = frameForGameUpdate;

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
            //--------------------------------- KEYBOARD ---------------------------------//
            // When a key is physicaly pressed
        case ALLEGRO_EVENT_KEY_DOWN:
            exitGame = !m_Keyboard.handlePressedKey(ev);
            break;

            // When a key is physicaly released
        case ALLEGRO_EVENT_KEY_UP:
            exitGame = !m_Keyboard.handleReleasedKey(ev);
            break;

            // When a character is typed or auto-repeated
        case ALLEGRO_EVENT_KEY_CHAR:
            exitGame = !m_Keyboard.handleTypedCharacter(ev);
            break;

            //---------------------------------- MOUSE -----------------------------------//
            // When there is a click
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            m_Mouse.handlePressedButton(ev);
            break;

            // When a button is released
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            m_Mouse.handleReleasedButton(ev);
            break;

            // When cursor is moved
        case ALLEGRO_EVENT_MOUSE_AXES:
            m_Mouse.handleMovedCursor(ev);
            break;

            //---------------------------------- DISPLAY ---------------------------------//
            // When main window is closed
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            exitGame = true;
            break;

            // When to update display
        case ALLEGRO_EVENT_TIMER:
            refresh = true;
            break;

            // When window is resized
        case ALLEGRO_EVENT_DISPLAY_RESIZE:
            m_Disp.resize();
            refresh = true;
            break;
        }

        if (refresh && al_is_event_queue_empty(m_Queue)) {
            // Move characters
            updateMovements();

            // Get current time
            double time(al_get_time());

            // Draw updated screen
            m_Disp.draw();

            // Display frame
            al_flip_display();

            // Update FPS
            ++fps_accum;
            if (time - fps_time >= 1) {
                fps = fps_accum;
                fps_accum = 0;
                fps_time = time;
            }
            m_Disp.setFPS(fps);

            // Don't refresh until asked
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
    for (unsigned int i = 0; i < NB_CIV; ++i) {
        for (unsigned int j = 0; j < m_CivCtrls[i]->getCiv().population(); ++j) {
            HumanInfo& human = m_CivCtrls[i]->getCiv().getHuman(j);
            if (!human.isReady()) {
                continue;
            }
            HumanPerception persep(human, m_World.map());
            processOrder(human, m_CivCtrls[i]->getAI()->giveOrder(persep));
        }
    }
}

void GameLoop::processOrder(HumanInfo& io_Human, const Order& i_Order)
{
    Action action(i_Order.getAction());

    switch (action) {
    case WALK:
        processMovingOrder(io_Human, action, Direction(i_Order.getParam(0)));
        break;
    }
}

void GameLoop::processMovingOrder(HumanInfo&     io_Human,
    Action i_Action,
    Direction      i_Dir)
{
    assertNonCenterDir(i_Dir);

    DCoord after(incrementedToDirection(io_Human.getPosition().coord(), i_Dir));
    Position dest(after, i_Dir);

    if (verifyDestination(dest)) {
        m_MoveProcs[m_NumMoveProcs] = new MoveProcess(io_Human,
            dest,
            m_World.map());
        ++m_NumMoveProcs;
    }
}

bool GameLoop::verifyDestination(const Position& i_Dest) const
{
    const Tile& destination(m_World.map().getTile(i_Dest.tileCoord()));

    if (!destination.isPassable()) {
        LOG(WARNING) << "ERROR IN AI: Cannot move on water";
        return false;
    }
    if (destination.hasHuman()) {
        LOG(WARNING) << "ERROR IN AI: Tile is already occupied";
        return false;
    }
    return true;
}

void GameLoop::updateMovements()
{
    for (unsigned int i = 0; i < m_NumMoveProcs; ++i) {
        m_MoveProcs[i]->nextIter();
    }
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                     END                                    //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void GameLoop::endProcesses()
{
    for (unsigned int i = 0; i < m_NumMoveProcs; ++i) {
        delete m_MoveProcs[i];
    }
    m_NumMoveProcs = 0;
}