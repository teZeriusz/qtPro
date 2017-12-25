#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <memory>


using namespace std;

/*
Problem Statement
In an old school arcade video game, you have reached the following bonus level. There are a number of
platforms containing coins, and you must jump from platform to platform collecting the coins. You may
only jump to lower platforms, so your entire journey will be downward. You can select any platform as
your starting platform.
Your jumping behavior is defined as follows. On each jump, your horizontal speed is constant and does
not exceed v. Your fall down follows the standard laws of physics: your free fall acceleration is g and
initially your speed is 0.

For simplicity, we will represent each platform as a single point. Each element of platforms represents a
single platform and is formatted "X Y C" (quotes for clarity), where X and Y are the x and y coordinates
of the platform and C is the number of coins on the platform. Greater values of y represent higher
locations. Return the greatest number of coins you can collect.

Definition (here java but you can use PHP, C++ or C# language)

Class: PlatformJumper
Method: maxCoins
Parameters: string[], int, int
Returns: int
Method signature: int maxCoins(string[] platforms, int v, int g)
(be sure your method is public)
*/

/*
Notes
● A dropped object without starting velocity will fall down (g*t2)/2 units in time t.
● Note, that you always can drop to the platform right below you.

Constraints
● platforms will contain between 1 and 50 elements, inclusive.
● Each element of platforms will be formatted as "X Y C", where X, Y and C are integers with no
extra leading zeroes.
● In each element of platforms, X and Y will be between 0 and 5000, inclusive.
● In each element of platforms, C will be between 0 and 10000, inclusive.
● All platforms will have distinct locations.
● v and g will each be between 1 and 100, inclusive.
*/

/*
Examples
0)
{"3 10 7", "5 15 7", "8 9 12" }
2
10
Returns: 14
It is possible to jump from platform 1 to platform 0, thus we can earn 7+7=14 coins. It is
impossible to jump from platform 1 to platform 2.
1)
{"0 0 1", "2 4 1", "4 0 1"}
1
2
Returns: 2
2)
{"0 0 1", "5000 5000 10"}
100
87
Returns: 10
*/

struct Node {
    uint16_t x = 0, y = 0, c = 0;
    vector<shared_ptr<Node>> children;

    Node(uint16_t _x, uint16_t _y, uint16_t _c):
        x(_x), y(_y), c(_c) {
    }
};


int maxCoins(vector<string> & platforms, int v, int g) {
    stringstream ss;
    vector<Node> nodes;

    for(string & str: platforms) {
        uint16_t x,y,c;
        ss << str;
        ss >> x >> y >> c;
        nodes.emplace_back(x,y,c);
    }

    return 0;
}

int main()
{
    vector<string> dd{{"0 0 1"}, {"2 4 1"}, {"4 0 1"}};
    cout << "maxCoins: " << maxCoins(dd, 1, 2) << " for: " << endl;
    return 0;
}
