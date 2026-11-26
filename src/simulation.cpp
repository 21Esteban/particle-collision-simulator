#include "simulation.h"
#include <cmath>
#include <algorithm>

Simulation::Simulation(double width, double height, double restitution, double dt)
{
    this->width = width;
    this->height = height;
    this->restitution = restitution;
    this->dt = dt;
    time = 0;
    collisionCount = 0;
}

void Simulation::addParticle(const Particle &p)
{
    particles.push_back(p);
}

void Simulation::addObstacle(const Obstacle &o)
{
    obstacles.push_back(o);
}

// walls are perfectly elastic: just flip the speed that goes into the wall
void Simulation::checkWalls(Particle &p)
{
    double r = p.getRadius();
    string side = "";

    if (p.getX() - r < 0 && p.getVx() < 0) {
        p.setPosition(r, p.getY());
        p.setVelocity(-p.getVx(), p.getVy());
        side = "left";
    }
    else if (p.getX() + r > width && p.getVx() > 0) {
        p.setPosition(width - r, p.getY());
        p.setVelocity(-p.getVx(), p.getVy());
        side = "right";
    }

    if (p.getY() - r < 0 && p.getVy() < 0) {
        p.setPosition(p.getX(), r);
        p.setVelocity(p.getVx(), -p.getVy());
        side = "top";
    }
    else if (p.getY() + r > height && p.getVy() > 0) {
        p.setPosition(p.getX(), height - r);
        p.setVelocity(p.getVx(), -p.getVy());
        side = "bottom";
    }

    if (side != "") {
        file << "C " << time << " wall " << p.getId() << " " << side << " "
             << p.getX() << " " << p.getY() << endl;
        collisionCount++;
    }
}

void Simulation::checkObstacles(Particle &p)
{
    for (Obstacle &o : obstacles) {
        double cx = p.getX();
        double cy = p.getY();
        double r = p.getRadius();

        // the point of the square that is closest to the center of the particle
        double closestX = clamp(cx, o.getX(), o.getRight());
        double closestY = clamp(cy, o.getY(), o.getBottom());
        double dx = cx - closestX;
        double dy = cy - closestY;

        if (dx * dx + dy * dy >= r * r) continue;   // not touching
        if (dx == 0 && dy == 0) continue;           // center inside, shouldn't happen with a small dt

        // which side did it hit? nx, ny is the normal of that side
        string side;
        double nx = 0, ny = 0;
        if (dy == 0) {
            if (dx < 0) side = "left"; else side = "right";
            nx = (dx < 0) ? -1 : 1;
        }
        else if (dx == 0) {
            if (dy < 0) side = "top"; else side = "bottom";
            ny = (dy < 0) ? -1 : 1;
        }
        else {
            // hit a corner, the normal points from the corner to the center
            side = "corner";
            double distance = sqrt(dx * dx + dy * dy);
            nx = dx / distance;
            ny = dy / distance;
        }

        // part of the speed that goes against the side
        double vPerp = p.getVx() * nx + p.getVy() * ny;
        if (vPerp >= 0) continue;   // it's already going away

        // v_perp' = -e * v_perp and v_parallel stays the same
        // that is the same as v' = v - (1 + e) * v_perp * n
        double newVx = p.getVx() - (1 + restitution) * vPerp * nx;
        double newVy = p.getVy() - (1 + restitution) * vPerp * ny;
        p.setVelocity(newVx, newVy);

        // take it out of the square so it doesn't get stuck
        p.setPosition(closestX + nx * r, closestY + ny * r);

        file << "C " << time << " obstacle " << p.getId() << " " << o.getId() << " "
             << side << " " << p.getX() << " " << p.getY() << endl;
        collisionCount++;
    }
}

// two particles touching -> they become one (perfectly inelastic)
void Simulation::checkParticles()
{
    for (size_t i = 0; i < particles.size(); i++) {
        for (size_t j = i + 1; j < particles.size(); j++) {
            Particle &a = particles[i];
            Particle &b = particles[j];
            if (!a.isAlive() || !b.isAlive()) continue;

            double dx = a.getX() - b.getX();
            double dy = a.getY() - b.getY();
            double minDistance = a.getRadius() + b.getRadius();

            if (dx * dx + dy * dy < minDistance * minDistance) {
                a.mergeWith(b);
                file << "C " << time << " merge " << a.getId() << " " << b.getId() << " "
                     << a.getX() << " " << a.getY() << " mass " << a.getMass() << endl;
                collisionCount++;
            }
        }
    }
}

void Simulation::savePositions()
{
    for (Particle &p : particles) {
        if (!p.isAlive()) continue;
        file << "P " << time << " " << p.getId() << " " << p.getX() << " " << p.getY()
             << " " << p.getRadius() << endl;
    }
}

bool Simulation::run(int steps, string fileName)
{
    file.open(fileName);
    if (!file.is_open()) return false;

    // header with the box and the obstacles so we can draw them later
    file << "# box width height" << endl;
    file << "B " << width << " " << height << endl;
    file << "# obstacle id x y size" << endl;
    for (Obstacle &o : obstacles) {
        file << "O " << o.getId() << " " << o.getX() << " " << o.getY() << " " << o.getSize() << endl;
    }
    file << "# position: P time id x y radius" << endl;
    file << "# collision: C time type ..." << endl;

    savePositions();
    for (int step = 1; step <= steps; step++) {
        time = step * dt;

        for (Particle &p : particles) {
            if (!p.isAlive()) continue;
            p.move(dt);
            checkWalls(p);
            checkObstacles(p);
        }
        checkParticles();
        savePositions();
    }

    file.close();
    return true;
}

int Simulation::getCollisionCount() const
{
    return collisionCount;
}

int Simulation::countAlive() const
{
    int count = 0;
    for (const Particle &p : particles) {
        if (p.isAlive()) count++;
    }
    return count;
}
