#include "Body.h"
#include <iostream>

using std::string;
using std::cout;
using std::endl;

// Class Constructor
Body::Body(vector<double>& p0, vector<double>& v0, double& m, string& n) {
    if (p0.size() != 3 || v0.size() != 3)
        cout << "Position and Velocity must have 3 elements!" << endl;

    position = p0;
    velocity = v0;
    mass = m;
    name = n;
}

// Getter Methods
vector<double> Body::getPosition() { return position; }
vector<double> Body::getVelocity() { return velocity; }
double Body::getMass() { return mass; }
string Body::getName() { return name; }

// Setter methods
void Body::setForce(vector<double> f) {
    force = f;
}

// Printing Methods
void Body::printPosition() {
    cout << "x = " << position[0];
    cout << ", y = " << position[1];
    cout << ", z = " << position[2] << endl;
}

void Body::printVelocity() {
    cout << "u = " << velocity[0];
    cout << ", v = " << velocity[1];
    cout << ", w = " << velocity[2] << endl;
}

// Next position and velocity method
void Body::nextInstance() {
    for (unsigned int i = 0; i < 3; i++) {
        // Position
        position[i] = position[i] + velocity[i] * Dt;

        // Velocity
        double acceleration = force[i] / mass;
        velocity[i] = velocity[i] + acceleration * Dt;
    }
}

// Pre-allocation Function for Forces Matrices
vector<vector<vector<double>>> forceMatrixCreation(unsigned int numberOfMasses, int numberOfDimensions = 3) {
    vector<double> zeros(numberOfMasses, 0);
    vector<vector<double>> fi(numberOfMasses, zeros);
    vector<vector<vector<double>>> f(numberOfDimensions, fi);
    return f;
}

// Print Force Matrix Function
void forceMatrixPrint(vector<vector<double>>& f) {
    for (unsigned int i = 0; i < f.size(); i++) {
        for (unsigned int j = 0; j < f[i].size(); j++) {
            cout << f[i][j] << ", ";
        }
        cout << endl;
    }
}

// Angle Calculation
void angleCal(double& dx,double& dy, double& dz,double& r, double& phi, double& theta) {
    phi = std::acos(std::abs(dz) / r);
    theta = std::acos(std::abs(dx) / (r * std::sin(phi)));

    // theta cases
    if (dx > 0 && dy < 0)
        theta = -theta;
    else if (dx < 0 && dy > 0)
        theta = PI - theta;
    else if (dx < 0 && dy < 0)
        theta += PI;

    // phi cases
    if (dz < 0)
        phi = PI - phi;

}

// Gravity Solver
void forcesSolver(vector<Body>& masses) {
    double dx, dy, dz, r, phi, theta, f_G, mi, mj;
    vector<double> posi, posj;

    // Pre-allocation
    vector<vector<vector<double>>> f = forceMatrixCreation(masses.size());

    for (unsigned int i = 0; i < (masses.size() - 1); i++) {
        for (unsigned int j = i + 1; j < masses.size(); j++) {
            // Get position and mass of the 2 bodies
            posi = masses[i].getPosition();
            posj = masses[j].getPosition();
            mi = masses[i].getMass();
            mj = masses[j].getMass();

            // Calculate distances
            dx = posj[0] - posi[0];
            dy = posj[1] - posi[1];
            dz = posj[2] - posi[2];
            r = std::sqrt(dx * dx + dy * dy + dz * dz);

            // Calculate angles
            angleCal(dx, dy, dz, r, phi, theta);

            // Calculate Forces
            f_G = bigG * (mi * mj) / (r * r) * (EARTH_MASS / (AU * AU * AU));
            f[0][i][j] = f_G * std::cos(theta) * std::sin(phi); // x-dimension
            f[1][i][j] = f_G * std::sin(theta) * std::sin(phi); // y-dimension
            f[2][i][j] = f_G * std::cos(phi);                   // z-dimension

            f[0][j][i] = -f[0][i][j];
            f[1][j][i] = -f[1][i][j];
            f[2][j][i] = -f[2][i][j];
        }
    }

    // Set forces in bodies
    for (unsigned int i = 0; i < masses.size(); i++) {
        // Sum Calculation
        vector<double> sums(3, 0);
        for (unsigned int j = 0; j < masses.size(); j++) {
            for (int n = 0; n < 3; n++) {
                sums[n] += f[n][i][j];
            }
        }
        masses[i].setForce(sums);
    }

}

