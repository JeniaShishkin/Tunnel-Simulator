#ifndef __Compass_h__
#define __Compass_h__

namespace jb
{

class Compass {
public:
	static constexpr int MAX_DEGREES = 360;

	struct StepsOf90_t {};
	inline static constexpr StepsOf90_t STEPS_OF_90{};

	Compass() : m_headingDegrees(0) { }
	Compass(int initialHeadingSteps, StepsOf90_t dummy);

	int getHeading() const { return m_headingDegrees; }
	Compass rotateInStepsOf90(int steps) const;

private:
	struct InDegrees_t {};
	inline static constexpr InDegrees_t IN_DEGREES{};

	Compass(int initialHeading, InDegrees_t dummy);

	int m_headingDegrees;
};

bool operator==(const Compass &a, const Compass &b);
bool operator<(const Compass &a, const Compass &b);

void turnLeft(Compass *compass);
void turnRight(Compass *compass);



// const Compass NORTH(); 
// const Compass EAST();
// const Compass SOUTH(); 
// const Compass WEST();

extern Compass NORTH;
extern Compass EAST;
extern Compass SOUTH;
extern Compass WEST;


} // jb

#endif
