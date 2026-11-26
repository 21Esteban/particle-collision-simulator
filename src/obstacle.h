#ifndef OBSTACLE_H
#define OBSTACLE_H

class Obstacle
{
private:
    int id;
    double x, y;    // top left corner
    double size;    // it's a square

public:
    Obstacle(int id, double x, double y, double size);

    int getId() const;
    double getX() const;
    double getY() const;
    double getSize() const;
    double getRight() const;
    double getBottom() const;
};

#endif // OBSTACLE_H
