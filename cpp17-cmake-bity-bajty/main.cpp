#include <iostream>
#include <cstddef>

using namespace std;

bool isLittleEndian(){
    int testNum=1;
    byte *ptr = reinterpret_cast<byte *>(&testNum);
//    return (*ptr); /* Zwraca bajt o najniższym adresie. */
    return to_integer<bool>(*ptr);
}

bool isLittleEndian2(){
    union {
        int theInteger;
        byte singleByte;
    } endianTest;
    endianTest.theInteger = 1;
    return to_integer<bool>(endianTest.singleByte);
}


int main()
{

    std::byte a {0};
    std::byte b {0xFF};
    std::byte d {0b011};
    int i = std::to_integer<int>(b); // 0xFF
    std::byte c = a & b;
    int j = std::to_integer<int>(c); // 0

    cout << "Hello World!" << isLittleEndian() << " : " << isLittleEndian2() << endl;
    return 0;
}
