#pragma once
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <map>
#include <vector>


using std::string;
using std::map;
using std::cout;
using std::cin;
using std::vector;



struct config
{
    static double WIN; // probability to win
    static map<vector<int>, double> PRIZES;
    static double target_prob, jackpot, number_of_tickets; // command line arguments in order
    static bool on_display; // command line option ("-o")
};


void set_config(int& argc, const char* argv[]);

void example_format();

double factorial(int x);

double nchoosek(int n, int k);

double get_comb_prize(vector<int> prize_group);

double pow_factorial(double x, int n);

double prob_of_n_winners(int n, double prob);

double expected_value(double tol = 1e-16);

string num_to_string(int num);

int winning_atleast_once(double target);
