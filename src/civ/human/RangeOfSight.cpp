#include "RangeOfSight.h"
#include <iosfwd>
#include "..\..\utils\FatalErrorDialog.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

RangeOfSight::RangeOfSight(std::ifstream& i_ROSFile) :
m_StraigthModel(i_ROSFile),
m_DiagonalModel(i_ROSFile)
{}

RangeOfSight::ROSModel::ROSModel(std::ifstream& io_File)
{
    std::string line;

    // Skip comments
    while (io_File.peek() == '#') {
        getline(io_File, line);
    }

    // Save position before reading
    unsigned int pos(io_File.tellg());

    // Read model size
    readModelSize(io_File);

    // Return to beginning of model
    io_File.seekg(pos);

    // Create the sight matrix
    m_Tiles = new bool*[m_LRCorner.y - m_ULCorner.y];
    for (int y(0); y < m_LRCorner.y - m_ULCorner.y; ++y) {
        m_Tiles[y] = new bool[m_LRCorner.x - m_ULCorner.x];
    }
    m_Dim = toCoord(m_LRCorner - m_ULCorner);

    // Read model
    readModel(io_File);
}

void RangeOfSight::ROSModel::readModelSize(std::ifstream& io_File)
{
    unsigned int width(0);
    unsigned int height(0);
    std::string line;
    Coord center(0, 0);
    char c(0);

    while (io_File.peek() != '#' && !io_File.eof()) {
        getline(io_File, line);
        if (line.length() % 2 == 0) {
            FatalErrorDialog("Invalid range of sight model file format");
        }
        unsigned int len((line.length() + 1) * 0.5);
        if (width == 0) {
            width = len;
        }
        else if (width != len) {
            FatalErrorDialog("Invalid range of sight model file format");
        }
        int pos(line.find('^'));
        if (pos != -1) {
            center = Coord((pos + 1) * 0.5, height);
        }
        else {
            pos = line.find('7');
            if (pos != -1) {
                center = Coord((pos + 1) * 0.5, height);
            }
        }

        ++height;
    }
    if (center == Coord(0, 0)) {
        FatalErrorDialog("Invalid range of sight model file format");
    }

    m_ULCorner = SCoord(-(int)center.x, -(int)center.y);
    m_LRCorner = SCoord(width - (int)center.x, height - (int)center.y);
}

void RangeOfSight::ROSModel::readModel(std::ifstream& io_File)
{
    char c(0);

    for (int y(0); y < m_LRCorner.y - m_ULCorner.y; ++y) {
        for (int x(0); x < m_LRCorner.x - m_ULCorner.x; ++x) {
            io_File >> c;
            switch (c) {
            case '.':
                m_Tiles[y][x] = false;
                break;
            case 'X': case '^': case '7':
                m_Tiles[y][x] = true;
            case '\n': case '\r':
                continue;
            default:
                FatalErrorDialog("Invalid range of sight model file format");
            }
        }
    }
    io_File.read(&c, 1);
}

RangeOfSight::ROSModel::~ROSModel()
{
    for (int y(0); y < m_LRCorner.y - m_ULCorner.y; ++y) {
        delete[] m_Tiles[y];
    }
    delete[] m_Tiles;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   GETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

const RangeOfSight::ROSModel& RangeOfSight::getStraigthModel() const
{
    return m_StraigthModel;
}

const RangeOfSight::ROSModel& RangeOfSight::getDiagonalModel() const
{
    return m_DiagonalModel;
}