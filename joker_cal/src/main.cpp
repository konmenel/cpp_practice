#pragma once
#include "joker.h"


int main(int argc, const char* argv[])
{
#ifdef _DEBUG
    int args_len = 2;
    const char* args[] = {"", "0.5", "2000000", "500000" , "-o"};
    set_config(args_len, args);
#else
    set_config(argc, argv);
#endif // DEBUG

    int draws = winning_atleast_once(1 - config::target_prob);
    double money = draws * 0.5 / 1e6; // in millions
    string draws_str = num_to_string(draws);
    string years_str = num_to_string((int)draws / 6 / 104);

    cout.precision(3);
    cout << "\nYou have " << config::target_prob * 100 << "% chance of winning after ";
    cout << draws_str << " draws and a total of " << money << " million euros.\n";
    cout << "If you spend 3 euros per week on tickets (6 tickets/week) you ";
    cout << "will need " << years_str << " years.\n";

    if (config::jackpot != 0)
    {
        double expected_val = expected_value() - 0.5;
        string jackpot_str = num_to_string((int)config::jackpot);
        string number_of_tickets_str = num_to_string((int)config::number_of_tickets);

        cout << "\nFor a Jackpot of " << jackpot_str << " euros and " << number_of_tickets_str;
        cout << " number of tickets, the expected value is " << expected_val << " euro!\n";
    }
    return 0;
}