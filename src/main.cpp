#include <iostream>
#include "simulation.h"
using namespace std;

int main()
{
    // caja de 800x600, e = 0.7 y dt = 0.01
    Simulation sim(800, 600, 0.7, 0.01);

    // los 4 obstaculos
    sim.addObstacle(Obstacle(1, 150, 120, 80));
    sim.addObstacle(Obstacle(2, 570, 120, 80));
    sim.addObstacle(Obstacle(3, 150, 400, 80));
    sim.addObstacle(Obstacle(4, 570, 400, 80));

    // id, x, y, vx, vy, masa, radio
    sim.addParticle(Particle(1, 60, 60, 120, 80, 2, 10));
    sim.addParticle(Particle(2, 400, 300, -90, 140, 3, 12));
    sim.addParticle(Particle(3, 700, 60, -110, 100, 1.5, 9));
    sim.addParticle(Particle(4, 60, 540, 150, -60, 2.5, 11));
    sim.addParticle(Particle(5, 740, 540, -80, -130, 1, 8));
    sim.addParticle(Particle(6, 400, 80, 60, 170, 2, 10));

    int steps = 3000;   // 30 segundos
    string fileName = "simulation.txt";

    if (!sim.run(steps, fileName)) {
        cout << "Could not create " << fileName << endl;
        return 1;
    }

    cout << "Simulation done (" << steps << " steps)" << endl;
    cout << "Collisions: " << sim.getCollisionCount() << endl;
    cout << "Particles left: " << sim.countAlive() << endl;
    cout << "Results saved in " << fileName << endl;
    cout << "To plot it: python plot.py" << endl;
    return 0;
}
