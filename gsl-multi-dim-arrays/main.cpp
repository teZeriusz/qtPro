#include <iostream>
#include <vector>
#include <algorithm>
#include <gsl/gsl>
#include <gsl/multi_span>


#define M 4
#define N 2
#define K 3

int main() {
    auto A = std::vector<float> (M*N*K);
    auto C = std::vector<float> (M*N*K);

    std::iota(std::begin(A), std::end(A), 0.0);
    std::iota(std::begin(C), std::end(C), 10.0);

    auto vA = gsl::as_multi_span(gsl::as_multi_span(A), gsl::dim(M), gsl::dim(N), gsl::dim(K));
    auto vC = gsl::as_multi_span(gsl::as_multi_span(C), gsl::dim(M), gsl::dim(K), gsl::dim(N));

    std::for_each(std::begin(vA.bounds()), std::end(vA.bounds()),
                  [&](gsl::index<3> const & i)
    {
        vC[{i[0], i[2], i[1]}] = vA[{i[0], i[1], i[2]}];
    } );

    for(auto & a: vA) {
        std::cout << " a:" << a;
    }
    std::cout << std::endl;


    for(auto & c: vC) {
        std::cout << " c:" << c;
    }
    std::cout << std::endl;



    return 0;
}
