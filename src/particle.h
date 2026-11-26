#ifndef PARTICLE_H
#define PARTICLE_H

class Particle
{
private:
    int id;
    double x, y;      // center
    double vx, vy;
    double mass;
    double radius;
    bool alive;       // false when it got merged into another one

public:
    Particle(int id, double x, double y, double vx, double vy, double mass, double radius);

    void move(double dt);
    void mergeWith(Particle &other);

    int getId() const;
    double getX() const;
    double getY() const;
    double getVx() const;
    double getVy() const;
    double getMass() const;
    double getRadius() const;
    bool isAlive() const;

    void setPosition(double newX, double newY);
    void setVelocity(double newVx, double newVy);
};

#endif // PARTICLE_H
