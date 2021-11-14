#include <iostream>
#include <math.h>
#include <bitset>



long double pi(int nInt);

int main()
{
	double PI = pi(10000000);

	std::cout.precision(17);
	std::cout << "Pi: " << PI << std::endl;

	int x = 0b10101;
	std::bitset<sizeof(x) * 8> a(x);
	std::cout << sizeof(x) << '\n';
	std::cout << a << '\n';


	system("pause>0");
}


long double pi(int nInt) {
	long double ans = 3.0;

	long double n = 0;

	for (int i = 1; i <= nInt; i++) {
		n = 2.0 * i;
		ans += pow(-1, i - 1) * 4 / (n * (n + 1) * (n + 2));
	}

	return ans;
}
