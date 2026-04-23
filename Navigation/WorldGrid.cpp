#include "WorldGrid.h"
#include "Position.h"
#include "../Tiles/EmptyTile.h"
#include "../Tiles/WallTile.h"
#include "../Tiles/ExitTile.h"
#include "../Tiles/DroneTile.h"
#include "../Tiles/MineTile.h"
#include "../Tiles/BatteryTile.h"

namespace jb
{
static constexpr int ASCII_RANGE = 127;
static Tile* SYMBOL_TABLE[ASCII_RANGE + 1] = { nullptr };
static EmptyTile EMPTY{};
static WallTile WALL{};
static ExitTile EXIT{};
static DroneTile DRONE{};
static MineTile MINE{};
static BatteryTile BATTERY{};


static std::unordered_set<Tile*> DESTRUCTIVE_TILES { &DRONE, &MINE };
static std::unordered_set<Tile*> BOOSTING_TILES { &BATTERY };

void initAsciiTable()
{

    SYMBOL_TABLE['%'] = &BATTERY;
    SYMBOL_TABLE['D'] = &DRONE;
    SYMBOL_TABLE['@'] = &MINE;
    SYMBOL_TABLE['#'] = &WALL;
    SYMBOL_TABLE['.'] = &EMPTY;
    SYMBOL_TABLE['E'] = &EXIT;
}


WorldGrid GLOBAL_MAP;



WorldGrid::WorldGrid()
{
    m_grid.resize(NUM_ROWS, std::vector<Tile*>(NUM_COLS, &EMPTY));

    /* ===== internal obstacles ===== */
    m_grid[1][3] = &WALL;
    m_grid[2][3] = &WALL;
    m_grid[3][6] = &WALL;
    m_grid[4][6] = &WALL;
    m_grid[6][2] = &WALL;
    m_grid[7][2] = &WALL;

    /* ===== mines ===== */
    m_grid[2][5] = &MINE;
    m_grid[5][5] = &MINE;
    m_grid[7][7] = &MINE;
    m_grid[3][8] = &MINE;

    /* ===== batteries ===== */
    m_grid[1][1] = &BATTERY;
    m_grid[4][2] = &BATTERY;
    m_grid[6][6] = &BATTERY;
    m_grid[8][3] = &BATTERY;

    /* ===== exit ===== */
    m_grid[9][8] = &EXIT;
}


Tile &WorldGrid::getTile(int x, int y) const
{
	if (x < 0 || y < 0)
	{
		return WALL;
	}
	if (x >= NUM_ROWS || y >= NUM_COLS)
	{
		return WALL;
	}

	Tile *tile = m_grid[x][y];
	return tile ? *tile : EMPTY;
}

void WorldGrid::loadFromFile(std::ifstream& file)
{
    initAsciiTable();
    std::string line;
    int x = 0;
    while (std::getline(file, line) && x < NUM_ROWS)
    {
        int y = 0;
        for (char c : line)
        {
            if (y >= NUM_COLS) break;
			m_grid[x][y] = SYMBOL_TABLE[c];
            ++y;
        }
        ++x;
    };
}

void WorldGrid::updatePosition(const Position& cur, const Position& next) 
{
    if(DESTRUCTIVE_TILES.contains(&getTile(next.getX() ,next.getY())))
    {
        throw std::runtime_error("Collision with drone/landed on mine, aircraft destroyed");
    }
    if(&getTile(next.getX() ,next.getY()) != &EXIT)
    {
        std::swap(m_grid[cur.getX()][cur.getY()], m_grid[next.getX()][next.getY()]); 
    }
}


void WorldGrid::setDroneLocation(const Position& pos)
{   
    m_grid[pos.getX()][pos.getY()] = &DRONE;
}


void WorldGrid::placeMine(const Position& pos)
{
    m_grid[pos.getX()][pos.getY()] = &MINE;
}


WorldGrid::const_iterator::const_iterator(const WorldGrid* world, const Position start, const Position end)
    : m_world(world), m_current(start), m_start(start), m_end(end) { }

const WorldGrid::const_iterator& WorldGrid::const_iterator::operator++()
{ 	
    int curX = getCurrentX();
    int curY = getCurrentY();

    if (curY < m_end.getY()) { m_current = Position{curX, curY + 1}; }

    else { m_current = Position{curX + 1, m_start.getY()}; }
    
    return *this;
}

bool WorldGrid::const_iterator::operator!=(const const_iterator& other) const
{
    return getCurrentX() != other.getCurrentX() || getCurrentY() != other.getCurrentY();
}

const WorldGrid::const_iterator WorldGrid::begin(const Position& start, const Position& end) const
{
    return const_iterator{this, start, end};
}

const WorldGrid::const_iterator WorldGrid::end(const Position& start, const Position& end) const
{
    return const_iterator{this, Position{end.getX() + 1, start.getY()}, end};
}

} // jb
