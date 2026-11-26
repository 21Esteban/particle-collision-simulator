#include "particle.h"
#include <cmath>

Particle::Particle(int id, double x, double y, double vx, double vy, double mass, double radius)
{
    this->id = id;
    this->x = x;
    this->y = y;
    this->vx = vx;
    this->vy = vy;
    this->mass = mass;
    this->radius = radius;
    alive = true;
}

// x = x0 + v*dt (no gravity, constant speed between collisions)
void Particle::move(double dt)
{
    x += vx * dt;
    y += vy * dt;
}

// perfectly inelastic: both become one body
void Particle::mergeWith(Particle &other)
{
    double totalMass = mass + other.mass;

    // momentum is conserved: m1*v1 + m2*v2 = (m1+m2)*v'
    vx = (mass * vx + other.mass * other.vx) / totalMass;
    vy = (mass * vy + other.mass * other.vy) / totalMass;

    // the new body goes to the center of mass
    x = (mass * x + other.mass * other.x) / totalMass;
    y = (mass * y + other.mass * other.y) / totalMass;

    // same total area -> r = sqrt(r1^2 + r2^2)
    radius = std::sqrt(radius * radius + other.radius * other.radius);

    mass = totalMass;
    other.alive = false;
}

int Particle::getId() const { return id; }
double Particle::getX() const { return x; }
double Particle::getY() const { return y; }
double Particle::getVx() const { return vx; }
double Particle::getVy() const { return vy; }
double Particle::getMass() const { return mass; }
double Particle::getRadius() const { return radius; }
bool Particle::isAlive() const { return alive; }

void Particle::setPosition(double newX, double newY)
{
    x = newX;
    y = newY;
}

void Particle::setVelocity(double newVx, double newVy)
{
    vx = newVx;
    vy = newVy;
}
