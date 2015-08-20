#include <iosfwd>
#include <FatalErrorDialog.h>
#include <RangeOfSight.h>

const std::string ERR_MSG("Invalid range of sight model file format: ");

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

RangeOfSight::RangeOfSight(std::ifstream& i_ROSFile) :
m_StraigthWin(i_ROSFile),
m_DiagonalWin(i_ROSFile)
{}

RangeOfSight::Window::Window(std::ifstream& io_File) :
Array2D<bool>(),
m_ULCorner(),
m_LRCorner()
{
    std::string line;

    // Skip comments and blank lines
    while (io_File.peek() != '.') {
        getline(io_File, line);
    }

    // Save position before reading
    unsigned int pos(io_File.tellg());

    // Read model size
    findWindowCorners(io_File);

    // Resize 2D boolean array
    clearAndResize(toCoord(m_LRCorner - m_ULCorner));

    // Return to beginning of model
    io_File.seekg(pos);

    // Read model
    readWindow(io_File);
}

void RangeOfSight::Window::findWindowCorners(std::ifstream& io_File)
{
    SCoord center(0, 0);
    SCoord dim(0, 0);
    std::string line;

    while (io_File.peek() != '#' && !io_File.eof()) {
        getline(io_File, line);

        if (line.empty()) {
            break;
        }

        if (line.length() % 2 == 0) {
            FatalErrorDialog(ERR_MSG + "pair number of characters in a line");
        }
        unsigned int len((line.length() + 1) * 0.5);
        if (dim.x == 0) {
            dim.x = len;
        }
        else if (dim.x != len) {
            FatalErrorDialog(ERR_MSG + "inconsitant line lengths");
        }
        int pos(line.find('^'));
        if (pos != -1) {
            center = SCoord((pos + 1) * 0.5, dim.y);
        }
        else {
            pos = line.find('7');
            if (pos != -1) {
                center = SCoord((pos + 1) * 0.5, dim.y);
            }
        }
        ++dim.y;
    }

    if (center == SCoord(0, 0)) {
        FatalErrorDialog(ERR_MSG + "no character position indicator");
    }

    m_ULCorner = center * -1;
    m_LRCorner = m_ULCorner + dim;
}

void RangeOfSight::Window::readWindow(std::ifstream& io_File)
{
    char c(0);

    for (unsigned int y(0); y < m_Dim.y; ++y) {
        for (unsigned int x(0); x < m_Dim.x; ++x) {
            io_File >> c;
            switch (c) {
            case '.':
                operator()(x,y) = false;
                break;
            case 'X': case '^': case '7':
                operator()(x, y) = true;
                break;
            case '\n': case '\r': case '\0':
                continue;
            default:
                FatalErrorDialog(ERR_MSG + "invalid character");
            }
        }
    }
    io_File.read(&c, 1);
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                IS VISIBLE                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

bool RangeOfSight::isVisible(SCoord i_Coord, Direction i_Direction) const
{
    // Rotate coordinate according to direction
    assertNonCenterDir(i_Direction);
    i_Coord = rotateCoord(i_Coord, i_Direction % 4);

    // Select appropriate window
    const Window& win(isDiagonal(i_Direction) ? m_DiagonalWin : m_StraigthWin);

    // De-center coordinate
    Coord decentered(toCoord(i_Coord - win.m_ULCorner));

    // Check if rotated coord is within window range
    if (!(decentered < win.dimensions())) {
        return false;
    }

    return win(decentered);
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   GETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

SCoord RangeOfSight::getWindowULCorner(Direction i_Direction) const
{
    // Select appropriate window
    assertNonCenterDir(i_Direction);
    const Window& win(isDiagonal(i_Direction) ? m_DiagonalWin : m_StraigthWin);

    switch (i_Direction % 4) {
    case UP   : return win.m_ULCorner;
    case RIGHT: return SCoord(-win.m_LRCorner.y + 1, win.m_ULCorner.x    );
    case DOWN : return SCoord(-win.m_LRCorner.x + 1,-win.m_LRCorner.y + 1);
    case LEFT : return SCoord( win.m_ULCorner.y    ,-win.m_LRCorner.x + 1);
    default   : return SCoord();
    }
}

SCoord RangeOfSight::getWindowLRCorner(Direction i_Direction) const
{
    // Select appropriate window
    assertNonCenterDir(i_Direction);
    const Window& win(isDiagonal(i_Direction) ? m_DiagonalWin : m_StraigthWin);

    switch (i_Direction % 4) {
    case UP   : return win.m_LRCorner;
    case RIGHT: return SCoord(-win.m_ULCorner.y + 1, win.m_LRCorner.x    );
    case DOWN : return SCoord(-win.m_ULCorner.x + 1,-win.m_ULCorner.y + 1);
    case LEFT : return SCoord( win.m_LRCorner.y    ,-win.m_ULCorner.x + 1);
    default   : return SCoord();
    }
}
