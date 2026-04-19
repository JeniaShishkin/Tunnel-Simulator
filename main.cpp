#include <iostream>
#include <string>
#include <string_view>
#include <map>
#include <cassert>
#include <sstream>

#include "Drone.h"
#include "Navigation/WorldGrid.h"
#include "Tiles/Tile.h"

/* COMMAND INCLUDES */
#include "Cmd/Command.h"
#include "Cmd/Forward.h"
#include "Cmd/TurnLeft.h"
#include "Cmd/TurnRight.h"
#include "Cmd/Execute.h"
#include "Cmd/PointOfView.h"
#include "Cmd/Map.h"
#include "Cmd/SetSensor.h"

/* SENSOR INCLUDES */
#include "Cmd/Context.h"
#include "Sensors/Sensor.h"
#include "Sensors/WideSensor.h"
#include "Sensors/CircularSensor.h"
#include "Sensors/DistanceSensor.h"

/* NETWORKING */
#include "Networking/NaiveNetworkHandler.h"

using namespace jb;

using CommandsMap = std::map<std::string_view, Command *>;

Command &parseCommand(const CommandsMap &commands, const std::string &s);


struct CmdUnknown : public Command
{
	virtual std::string execute() const override { std::stringstream buffer; buffer << "ERROR: Unknown command\n"; return buffer.str(); }
} CMD_UNKNOWN;

static NaiveNetworkHandler nh{9000};
static size_t socketId;
static std::string input;

int main()
{
 
	WorldGrid theWorld;
	//Drone d;
	Position p{0,1};
	Compass c{NORTH};
    Context ctx{theWorld, p, c};
	CmdForward forward{&theWorld, &p, &c};
	CmdTurnLeft left{&c};
	CmdTurnRight right{&c};
	CmdPointOfView pov{ctx};
	CmdMap map{theWorld};
	CircularSensor c_sensor{};
	WideSensor w_sensor{};
	DistanceSensor d_sensor{};
    SetSensor s_a{ctx, c_sensor};
    SetSensor s_b{ctx, w_sensor};
    SetSensor s_c{ctx, d_sensor};

	bool doLoop = true;
	CmdExecute exitLoop{[&doLoop]() { doLoop=false;} };

	const CommandsMap commands {
		{ "fwd", &forward },
		{ "+90", &right },
		{ "-90", &left },
		{ "exit", &exitLoop },
		{ "pov" , &pov},
		{ "map", &map},
		{ "s_a", &s_a},
		{ "s_b", &s_b},
		{ "s_c", &s_c}
	};

	std::string input;
	while (doLoop && !theWorld.getTile(p.getX(), p.getY()).shouldExit())
	{
        nh.GetInput(&socketId, &input);
		if (input.empty())
		{
            nh.PutOutput(socketId,"> ");
            continue;
		}
        
		Command &cmd = parseCommand(commands, input);
		std::string buffer = cmd.execute();
        nh.PutOutput(socketId, buffer);
        nh.PutOutput(socketId,"> ");
	}
}

Command &parseCommand(const CommandsMap &commands, const std::string &s)
{
	CommandsMap::const_iterator cmdItr = commands.find(s);
	if (cmdItr == commands.end())
	{
		return CMD_UNKNOWN;
	}
	return *(cmdItr->second);
}









// const const_iterator begin(const Position& start);
// const const_iterator end(const Position& end);
// 
// Position from(2,1);
// Position afterTo(6,5);
// WorldGrid::const_iterator itr = w.begin(from);
// WorldGrid::const_iterator end = w.end(afterTo);
// 
// for ( ; itr != end ; ++itr)
// {
//     const Tile &tile = *itr;
// }
// 
// 
//    0123456789ABCDEFG
//  0 ### #####E#######
//  1 # # #####   ###  
//  2 #    ##      #  #
//  3 ##             ##
//  4 #################

void checkBeginZeroIdxGridCell(const WorldGrid &w)
{
   WorldGrid::const_iterator t1 = w.begin(Position{0,0},Position{0,0});
   assert(*t1 == &w.getTile(0,0));
}

void checkBeginForMiddleCell(const WorldGrid &w)
{
	WorldGrid::const_iterator t1 = w.begin(Position{3,1},Position{0,0});
	assert(*t1 == &w.getTile(3,1));
	WorldGrid::const_iterator t2 = w.begin(Position{9,0}, Position{0,0});
	assert(*t2 == &w.getTile(9,0));
	WorldGrid::const_iterator t3 = w.begin(Position{5,2}, Position{0,0});
	assert(*t3 == &w.getTile(5,2));
}
void checkEndOperator(const WorldGrid &w)
{
	WorldGrid::const_iterator t1 = w.end(Position{3,1}, Position{0,0});
	assert(*t1);
}
void checkOutOfBounds(const WorldGrid &w)
{
	WorldGrid::const_iterator t1 = w.end(Position{-1,1}, Position{0,0});
   assert(*t1 != &w.getTile(3,1));
}

void checkOperatorNotEqual(const WorldGrid &w)
{
	WorldGrid::const_iterator t1 = w.begin(Position{3,2}, Position{0,0});
	WorldGrid::const_iterator t2 = w.begin(Position{3,3}, Position{0,0});
	assert(*t1 != *t2);
}

void checkOperatorIncrement(const WorldGrid &w)
{
	// Check in the middle of the row. assume window of 4x4.
	WorldGrid::const_iterator t1 = w.begin(Position{2,1}, Position{0,0});
	WorldGrid::const_iterator t2 = w.begin(Position{2,1}, Position{0,0});
	++t1;
	assert(!(t1 != t2));

	// check increment at the end of the row.
	WorldGrid::const_iterator t3 = w.begin(Position{1,3}, Position{0,0});
	WorldGrid::const_iterator t4 = w.begin(Position{2,0}, Position{0,0});
	++t3;
	assert(!(t3 != t4));

	// check increment to the end of the window.
	WorldGrid::const_iterator t5 = w.begin(Position{3,3}, Position{0,0});
	WorldGrid::const_iterator t6 = w.begin(Position{3,3}, Position{0,0});
	++t1;
	assert(!(t5 != t6));

}

using namespace jb;

void test_basic_iteration()
{
    WorldGrid grid;

    Position start(0, 0);
    Position end(4, 5);

    int count = 0;

    for (auto it = grid.begin(start, end); it != grid.end(start, end); ++it)
	{
        assert(*it != nullptr);
        ++count;
    }

    assert(count > 0);
}

void test_single_cell()
{
    WorldGrid grid;

    Position p(2, 3);

    auto it = grid.begin(p, p);
    auto itEnd = grid.end(p, p);

    assert(!(it != itEnd));
    assert(*it != nullptr);
}

void test_horizontal_edge()
{
    WorldGrid grid;

    Position start(0, 0);
    Position end(4, 0);

    auto it = grid.begin(start, end);

    for (int i = 0; i < 5; ++i)
    {
        assert(*it != nullptr);
        ++it;
    }
}

void test_vertical_edge()
{
    WorldGrid grid;

    Position start(0, 0);
    Position end(0, 5);

    auto it = grid.begin(start, end);

    for (int i = 0; i < 6; ++i)
    {
        assert(*it != nullptr);
        ++it;
    }
}

void test_full_grid_count()
{
    WorldGrid grid;

    Position start(0, 0);
    Position end(6, 5);

    int count = 0;

    for (auto it = grid.begin(start, end); it != grid.end(start, end); ++it)
	{
        ++count;
    }
    assert(count == 30); // 5 * 6 grid
}

void test_reverse_range()
{
    WorldGrid grid;

    Position start(4, 5);
    Position end(0, 0);

    auto it = grid.begin(start, end);

    // This is expected to likely fail or behave incorrectly
    assert(*it != nullptr);
}

void test_out_of_bounds()
{
    WorldGrid grid;

    Position start(4, 5);
    Position end(10, 10);

    auto it = grid.begin(start, end);

    // Likely UB test (should not crash ideally)
    assert(*it != nullptr);
}

void test_iterator_comparison()
{
    WorldGrid grid;

    Position start(0, 0);
    Position end(4, 5);

    auto it1 = grid.begin(start, end);
    auto it2 = grid.begin(start, end);

    // This may fail depending on your operator!= logic
    assert(!(it1 != it2));
}

void test_end_behavior()
{
    WorldGrid grid;

    Position start(0, 0);
    Position end(4, 5);

    auto it = grid.begin(start, end);
    auto itEnd = grid.end(start, end);

    while (it != itEnd)
    {
        ++it;
    }

    // Should terminate cleanly
    assert(true);
}

//int main()
//{
//    test_basic_iteration();
//    test_single_cell();
//    test_horizontal_edge();
//    test_vertical_edge();
//    test_full_grid_count();
//    test_reverse_range();
//    test_out_of_bounds();
//    test_iterator_comparison();
//    test_end_behavior();
//
//    std::cout << "All tests executed (some may expose iterator issues intentionally)." << std::endl;
//}
