#include <iostream>

double power(double num, int pwr)
{
    double result = 1;

    for (int i = 0; i < pwr; i++)
    {
        result *= num;
    }

    return result;
}

void print_chech(int value)
{
    if (value < 10)
        std::cout << "00" << value;
    else if (value < 100)
        std::cout << "0" << value;
    else
        std::cout << value;
}

void print_number_with_commas(int num)
{
    int high, low, printed_value;
    for (int i = 6; i > 0; i -= 3)
    {
        high = (int)num / power(10, i + 3);
        low = (int)num / power(10, i);

        printed_value = low - high * 1000;
        if (i != 6)
            print_chech(printed_value);
        else
            std::cout << printed_value;
        std::cout << ",";
    }
    printed_value = num - low * 1000;
    print_chech(printed_value);
}

int main()
{   
    float TARGET = 0.1;
    double x = 45.0 * 44.0 * 43.0 * 42.0 * 41.0 * 20.0 / 120.0;
    x = 1 / x;
    x = 1 - x; // probability of losing
    double temp = x;
    int count = 0;


    while (temp > TARGET) 
    {
        if (temp - TARGET > 0.1)
        {
            count += 10000;
            temp *= power(power(power(power(x, 10), 10), 10), 10);

        }
        else if (temp - TARGET > 0.01)
        {
            count += 1000;
            temp *= power(power(power(x, 10), 10), 10);
        }
        else if (temp - TARGET > 0.001)
        {
            count += 100;
            temp *= power(power(x, 10), 10);

        }
        else if (temp - TARGET > 0.0001)
        {
            count += 10;
            temp *= power(x, 10);
        }
        else
        {
            count++;
            temp *= x;
        }
    }
    
    
    std::cout << "You have " << (1 - TARGET) * 100 << "% chance of winning after ";
    print_number_with_commas(count);
    std::cout << " joker draws." << std::endl;
    std::cout << count << std::endl;
}

