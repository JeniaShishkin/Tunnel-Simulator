#ifndef __WorldGrid_h__
#define __WorldGrid_h__

#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <cstddef>
#include <fstream>
#include <utility>
#include <unordered_set>

#include "Position.h"

namespace jb
{

class Tile;

class WorldGrid
{
private:

public:
	static constexpr size_t NUM_ROWS = 10;
	static constexpr size_t NUM_COLS = 10;
	using Grid = std::vector<std::vector<Tile*>>;
	
	WorldGrid();

	class const_iterator
	{
	public:
		explicit const_iterator(const WorldGrid* world, const Position start, const Position end);
		const const_iterator& operator++();
		bool operator!=(const const_iterator& other) const;
		const Tile* operator*() const { return &m_world->getTile(getCurrentX(), getCurrentY()); }
		int getCurrentX() const { return m_current.getX(); }
		int getCurrentY() const { return m_current.getY(); }
		~const_iterator() = default;
		
	private:
		const WorldGrid* m_world;
		Position m_current;
		const Position m_start;
		const Position m_end;
	};


	const const_iterator begin(const Position& start, const Position& end) const;
	const const_iterator end(const Position& start, const Position& end) const;

	void loadFromFile(std::ifstream& file);
	void setDroneLocation(const Position& pos);
	void updatePosition(const Position& cur, const Position& next);
	Tile &getTile(int x, int y) const;
	void placeMine(const Position& pos);
	int getRowSize() const { return m_grid.size(); }
	int getColSize() const { return m_grid.empty() ? 0 : m_grid[0].size(); }

private:
	Grid m_grid;
};

extern WorldGrid GLOBAL_MAP;

} // jb

#endif
