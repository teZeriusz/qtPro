#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>


template<typename T, typename L>
void stable(T arr, L is_even) {
    std::cout << "stable partition elems:\n";
    std::copy(arr.begin(), arr.end(), std::ostream_iterator<int>(std::cout, " "));
    std::stable_partition(arr.begin(), arr.end(), is_even);
    std::cout << "\nafter stable partition elems:\n";
    std::copy(arr.begin(), arr.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    test_partition(arr, is_even);
}


template<typename T, typename L>
void partition(T arr, L is_even) {
    std::cout << "partition elems:\n";
    std::copy(arr.begin(), arr.end(), std::ostream_iterator<int>(std::cout, " "));
    std::partition(arr.begin(), arr.end(), is_even);
    std::cout << "\nafter partition elems:\n";
    std::copy(arr.begin(), arr.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    test_partition(arr, is_even);
}

template<typename T, typename L>
void test_partition(T arr, L is_even) {
    std::cout << "is partitioned: " << std::is_partitioned(arr.begin(), arr.end(), is_even) << '\n';

    auto p = std::partition_point(arr.begin(), arr.end(), is_even);

    std::cout << "Before partition:\n    ";
    std::copy(arr.begin(), p, std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\nAfter partition:\n    ";
    std::copy(p, arr.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}


int main()
{
    std::array<int, 9> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    auto is_even = [](int i){ return i % 2 == 0; };
    std::cout.setf(std::ios_base::boolalpha);


    stable(v, is_even);
    partition(v, is_even);

    return 0;
}
