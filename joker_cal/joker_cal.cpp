#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>


double factorial(int x)
{
    if (x == 1)
        return 1;
    else if (x == 0)
        return 1;

    double res = x;
    for (int i = x - 1; i > 2; --i)
        res *= i;
    
    return res;
}


double expected_value();


double power(double num, int pwr)
{
    double result = 1;

    for (int i = 0; i < pwr; i++)
    {
        result *= num;
    }

    return result;
}


std::string corrected_to_string(int value)
{
    if (value < 10)    
        return "00" + std::to_string(value);
    else if (value < 100)
        return "0" + std::to_string(value);
    
    return std::to_string(value);
}


std::string num_to_string(int num)
{   
    std::string res;
    // find where the first comma goes
    int n = 3;
    while ((num / power(10, n)) > 1)
    {
        n += 3;
    }
    n -= 3;

    
    int high, low, printed_value;
    for (int i = n; i > 0; i -= 3)
    {
        high = (int)num / power(10, i + 3);
        low = (int)num / power(10, i);

        printed_value = low - high * 1000;
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


double get_winning_probability()
{
    // calculation of possible combinations
    double res = 45.0 * 44.0 * 43.0 * 42.0 * 41.0 * 20.0 / 120.0;
    return 1 / res;
}


int winning_atleast_once(double target, bool on_display = false)
{
    double lose = 1 - get_winning_probability(); // probability of losing
    double temp = lose;
    int count = 0;


    while (temp > target)
    {
        if (temp - target > 0.01)
        {
            count += 1000;
            temp *= power(power(power(lose, 10), 10), 10);
        }
        else if (temp - target > 0.001)
        {
            count += 100;
            temp *= power(power(lose, 10), 10);

        }
        else if (temp - target > 0.0001)
        {
            count += 10;
            temp *= power(lose, 10);
        }
        else
        {
            count++;
            temp *= lose;
        }
    }
    return count;
}



int main(int argc, char* argv[])
{   
    double target_prob;
    bool on_display = false;

    switch (argc)
    {
    case 1:
        std::cout << "Type target probability in decimal format: ";
        std::cin >> target_prob;
        break;
    case 2:
        target_prob = std::atof(argv[1]);
        break;
    case 3:
        target_prob = std::atof(argv[1]);
        if (std::strcmp(argv[2], "-o") == 0)
            on_display = true;
        else
            printf("Unknown argument `%s` ignored. Try `-o` to display results on screen\n", argv[2]);
        break;
    default:
        std::cout << "Unknown amount of arguments\n";
        exit(1);
    }
    
    if (target_prob >= 1)
    {
        std::cout << "Target probability should be less than 1.\n";
        exit(1);
    }
    else if (target_prob < 0)
    {
        std::cout << "Target probability should be greater than 0.\n";
        exit(1);
    }

    int draws = winning_atleast_once(1 - target_prob, on_display);
    std::string draws_str = num_to_string(draws);
    std::string years_str = num_to_string((int)draws / 104);
    
    std::cout << "You have " << target_prob * 100 << "% chance of winning after ";
    std::cout << draws_str << " draws or " << years_str << " years.\n";

    return 0;
}

