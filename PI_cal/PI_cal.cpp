#include <iostream>
#include <math.h>
#include <bitset>
using namespace std;

long double pi(int nInt);

int main()
{
	/*double PI = pi(10000000);

	cout.precision(17);
	cout << "Pi: " << fixed << PI << endl;*/

	int x = 0b10101;
	std::bitset<sizeof(x) * 8> a(x);
	std::cout << sizeof(x) << '\n';
	std::cout << a << '\n';


	system("pause>0");
}


long double pi(int nInt) {
	long double ans = 3.0;

	for (int i = 1; i <= nInt; i++) {
		long double n = 2 * i;
		ans += pow(-1, i - 1) * 4 / (n * (n + 1) * (n + 2));
	}

	return ans;
}
