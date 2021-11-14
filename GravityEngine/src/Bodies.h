#pragma once
#include <iostream>
#include <vector>


using std::string;
using std::vector;

const double bigG = 6.67408e-11; // [m^3/(kg*s^2)]
const double PI = 3.14159265358979323846;
const double EARTH_MASS = 5.9722e24;
const double SUN_MASS = 1.98847e30;
const double AU = 1.495978707e11; // 1 AU = 1.495978707e11 m
const double Dt = 500; // [s]

// Classes
class Body {
private:
    // Position, velocity and mass of the body
    vector<double> position, velocity;
    double mass;
    string name;

    // Gravitational forces
    vector<double> force; // 3 elements, 1 for each direction (x, y, z)

public:
    // Constructor
    Body(vector<double>& p0, vector<double>& v0, double& m, string& n);

    // Getters
    vector<double> getPosition();
    vector<double> getVelocity();
    double getMass();
    string getName();

    // Setters
    void setForce(vector<double> f);

    // Printing Methods
    void printPosition();
    void printVelocity();
    
    // Calculate the position and velocity in the next instance
    void nextInstance();
};

// Functions
vector<vector<vector<double>>> forceMatrixCreation(unsigned int numberOfMasses, int numberOfDimensions);
void forceMatrixPrint(vector<vector<double>>& f);
void forcesSolver(vector<Body>& masses);
void angleCal(double& dx, double& dy, double& dz, double& r, double& phi, double& theta);