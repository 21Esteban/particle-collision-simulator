#include "obstacle.h"

Obstacle::Obstacle(int id, double x, double y, double size)
{
    this->id = id;
    this->x = x;
    this->y = y;
    this->size = size;
}

int Obstacle::getId() const { return id; }
double Obstacle::getX() const { return x; }
double Obstacle::getY() const { return y; }
double Obstacle::getSize() const { return size; }
double Obstacle::getRight() const { return x + size; }
double Obstacle::getBottom() const { return y + size; }
