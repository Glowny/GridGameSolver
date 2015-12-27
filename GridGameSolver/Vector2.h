#ifndef Vector2_h
#define Vector2_h
namespace Math
{

struct Vector2
{
	Vector2(){};
	Vector2(int x, int y){ this->x = x; this->y = y; }
	Vector2(const Vector2 &vector){ x = vector.x; y = vector.y; }
	int x;
	int y;
};

}
#endif;