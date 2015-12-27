#ifndef Rotations_h
#define Rotations_h
#include "Vector2.h"

namespace Rotate
{

static Math::Vector2 limits;

enum RotateAxis
{
	X,  
	Y,
	XY,
};

static void SetLimits(Math::Vector2 Limits)
{
	limits = Limits;
}

// Rotate on axis and return rotated position.

static Math::Vector2 RotateOnAxis(Math::Vector2 position, RotateAxis axis)
{
	switch (axis)
	{
	
	case X:
		position.x = limits.x - position.x;
		return position;
	
	case Y:
		position.y = limits.y - position.y;
		return position;
	
	case XY:
		position.x = limits.x - position.x;
		position.y = limits.y - position.y;
		return position;

	default:
		return position;
	}
}


static Math::Vector2 SwapAxis(Math::Vector2 vector)
{
	int x = vector.x;
	vector.x = vector.y;
	vector.y = vector.x;
	return vector;
}

// Code for halving the time to check all nodes. (Needs testing)
// (Check only half, and mirror the other half)

//Vector2 SwapXY(Vector2 vector)
//{
//	int x = vector.x;
//	vector.x = vector.y;
//	vector.y = vector.x;
//	return vector;
//}
//
//
//Vector2 Rotate(Vector2 vector, int axis)
//{
//	vector = SwapXY(vector);
//
//	if (axis == X)
//	{
//		vector.x = -vector.x;
//	}
//	else
//	{
//		vector.y = -vector.y;
//	}
//		
//	return vector;
//}
//Vector2 Mirror(Vector2 vector)
//{
//	vector.x = -vector.x;
//	vector.y = -vector.y;
//
//	return vector;
//}
}
#endif;