#pragma once
#include "joker.h"


using std::string;
using std::map;
using std::cout;
using std::cin;
using std::vector;


double config::WIN = 45.0 * 44.0 * 43.0 * 42.0 * 41.0 / 120.0;
bool config::on_display = false;
double config::jackpot = 0.0;
double config::number_of_tickets = 0.0;
double config::target_prob = 0.0;
map<vector<int>, double> config::PRIZES = { {{1, 1}, 1.5 },
                                            {{2, 1}, 2.0},
                                            {{3, 0},   2.0},
                                            {{3, 1}, 50.0},
                                            {{4, 0},   50.0},
                                            {{4, 1}, 2500.0} };


void set_config(int& argc, const char* argv[])
{
    std::string user_input;
    switch (argc)
    {
    case 1:
        cout << "Please provide the following arguments:\n";
        cout << "Probability in decimal format: ";
        cin >> config::target_prob;
        cout << "Jackpot value in euros (can be skipped): ";
        cin.ignore();
        std::getline(std::cin, user_input);
        if (!user_input.empty())
        {
            config::jackpot = std::stof(user_input);
            cout << "Estimated number of tickets being sold: ";
            cin >> config::number_of_tickets;
        }
        break;
    case 2:
        config::target_prob = std::atof(argv[1]);
        break;
    case 3:
        cout << "Not enough arguments. Try one or three arguments.\n";
        example_format();
        exit(1);
    case 4:
        config::target_prob = std::atof(argv[1]);
        config::jackpot = std::atof(argv[2]);
        config::number_of_tickets = std::atof(argv[3]);
        break;
    case 5:
        config::target_prob = std::atof(argv[1]);
        config::jackpot = std::atof(argv[2]);
        config::number_of_tickets = std::atof(argv[3]);
        if (std::strcmp(argv[4], "-o") == 0)
            printf("`%s` not implemented yet.\n", argv[4]); //config::on_display = true;
        else
            printf("Unknown argument `%s` ignored. Try `-o` to display results of calculetion.\n", argv[4]);
        break;
    default:
        cout << "Unknown amount of arguments\n";
        exit(1);
    }

    if (config::target_prob >= 1)
    {
        cout << "Target probability should be less than 1.\n";
        exit(1);
    }
    else if (config::target_prob < 0)
    {
        std::cout << "Target probability should be greater than 0.\n";
        exit(1);
    }

    config::PRIZES.emplace(std::initializer_list<int>{ 5, 0 }, 0.05 * config::jackpot);
    config::PRIZES.emplace(std::initializer_list<int>{ 5, 1 }, config::jackpot);
}


void example_format()
{
    cout << "The file should be run with the following arguments: \n";
    cout << "\t>>./joker_cal.exe <target-probability> <jackpot> <total-number-of-tickets> <options>\n";
}


double factorial(int x)
{
    if (x <= 1)
        return 1;

    double res = x;
    for (int i = x - 1; i > 1; --i)
        res *= i;
    return res;
}


double nchoosek(int n, int k)
{
    double res = 1;
    
    double i = n, j = k;

    while (true)
    {
        if (isinf(res))
            return 0;

        if (i > n-k && j > 1)
        {
            res *= i / j;
            i--; j--;
        }
        else if (i > n-k)
        {
            res *= i;
            i--;
        }
        else if (j > 1)
        {
            res /= j;
            j--;
        }
        else
        {
            break;
        }
    }
    return res;
}


double get_comb_prize(vector<int> prize_group)
{
    double res = 1;
    int start = 45; 
    int end = 45 - prize_group[0];
    for (int i = 45; i > end; i--)
        res *= i;

    res /= factorial(prize_group[0]);

    if (prize_group[1])
        res *= 20;

    return res;
}


double pow_factorial(double x, int n)
{
    if (n == 0)
        return 1;
    else if (n == 1)
        return x;

    double res = 1;
    for (double i = n; i > 0; i--)
        res *= x / i;
    return res;
}


double prob_of_n_winners(int n, double prob)
{
    double expected_winners = config::number_of_tickets * prob;
    return pow_factorial(expected_winners, n) * exp(-expected_winners);
}


double expected_value(double tol)
{
    // TODO: fix nan in res and term.

    double prob_for_1, prob, term, exp_winners, n_choose_k;
    double res = 0;
    int winners;

    for (auto prize = config::PRIZES.rbegin(); prize != config::PRIZES.rend(); ++prize)
    {
        prob_for_1 = 1 / get_comb_prize(prize->first);
        exp_winners = prob_for_1 * config::number_of_tickets;


        winners = 1;
        while (winners <= config::number_of_tickets)
        {
            n_choose_k = nchoosek(config::number_of_tickets, winners);
            if (n_choose_k != 0.0)
                prob = prob_of_n_winners(winners, prob_for_1) / n_choose_k;
            else
                prob = 0.0;
            term = prob * prize->second / winners;

            if (res != 0 && winners > exp_winners && term < tol)
                break;

            res += term;
            winners++;

#ifdef _DEBUG
            cout.precision(4);
            if (winners % 10 == 0)
                cout << exp_winners << " " << winners << " " << res << std::endl;
#endif // _DEBUG
        }
    }
    return res;
}

string corrected_to_string(int value)
{
    if (value < 10)    
        return "00" + std::to_string(value);
    else if (value < 100)
        return "0" + std::to_string(value);
    
    return std::to_string(value);
}


string num_to_string(int num)
{   
    string res;
    // find where the first comma goes
    int n = 0;
    while ((num / pow(10, n+3)) >= 1)
    {
        n += 3;
    }
    
    int high, low, printed_value;
    low = 0;
    for (int i = n; i > 0; i -= 3)
    {
        high = (int)num / pow(10, i + 3);
        low = (int)num / pow(10, i);

        printed_value = low - high * 1000;
        if (i == n && printed_value == 0)
            printed_value = 1;

        if (i != n)
            res += corrected_to_string(printed_value);
        else
            res += std::to_string(printed_value);
        res += ",";
    }
    printed_value = num - low * 1000;
    res += corrected_to_string(printed_value);
    return res;
}


int winning_atleast_once(double target)
{
    // TODO: add on-display option

    vector<int> jackpot_comb = { 5, 1 };
    double lose = 1 - (1 / (get_comb_prize(jackpot_comb))); // probability of losing
    double temp = lose;
    int count = 0;


    while (temp > target)
    {
        if (temp - target > 0.01)
        {
            count += 1000;
            temp *= pow(pow(pow(lose, 10), 10), 10);
        }
        else if (temp - target > 0.001)
        {
            count += 100;
            temp *= pow(pow(lose, 10), 10);

        }
        else if (temp - target > 0.0001)
        {
            count += 10;
            temp *= pow(lose, 10);
        }
        else
        {
            count++;
            temp *= lose;
        }
    }
    return count;
}
