#pragma once
/// <summary>
/// Base class for each component 
/// </summary>

enum TravelDirection {
	stop, up, down, right, left, up_right, up_left, down_right, down_left
};

struct Position {
	int x, y;
	int xPX, yPX;
	double tmpX, tmpY;
};

struct Hitbox {
	int xPX1, yPX1;
	int xPX2, yPX2;
};

class Component
{
public:
   virtual ~Component() = default;
   virtual void init() = 0;
   virtual void update() = 0;
   virtual void draw() = 0;

   virtual Position getPosition() const = 0 ;
   virtual bool lineOfSight(const Position& position) const = 0;

   virtual void decHealth(unsigned char health = 1) = 0;
   virtual void incHealth(unsigned char health = 1) = 0;
};