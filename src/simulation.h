#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <string>
#include <fstream>
#include "particle.h"
#include "obstacle.h"
using namespace std;

class Simulation
{
private:
    double width, height;    // tamaño de la caja
    double restitution;      // la e de los obstaculos
    double dt;
    double time;
    vector<Particle> particles;
    vector<Obstacle> obstacles;
    ofstream file;
    int collisionCount;

    void checkWalls(Particle &p);
    void checkObstacles(Particle &p);
    void checkParticles();
    void savePositions();

public:
    Simulation(double width, double height, double restitution, double dt);

    void addParticle(const Particle &p);
    void addObstacle(const Obstacle &o);
    bool run(int steps, string fileName);

    int getCollisionCount() const;
    int countAlive() const;
};

#endif // SIMULATION_H
