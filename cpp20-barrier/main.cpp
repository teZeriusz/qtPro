#include <experimental/barrier>
#include <thread>
#include <cstdio>

std::barrier b(2, []{
    puts("Green flag, go!");
});

std::thread tB = std::thread([&b](){
    printf("B is setting up\n");
    b.arrive_and_wait();
    printf("B is running\n");
});

int main() {
    printf("A is setting up\n");
    b.arrive_and_wait();
    printf("A is running");
    tB.join();

    return 0;
}
