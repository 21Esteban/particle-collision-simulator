#ifndef OBSTACLE_H
#define OBSTACLE_H

class Obstacle
{
private:
    int id;
    double x, y;    // esquina de arriba a la izq
    double size;    // es cuadrado

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
