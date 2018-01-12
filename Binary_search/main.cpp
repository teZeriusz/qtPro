#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>


template<class ForwardIt, class T, class Compare=std::less<>>
ForwardIt binary_find(ForwardIt first, ForwardIt last, const T& value, Compare comp={})
{
    // Note: BOTH type T and the type after ForwardIt is dereferenced
    // must be implicitly convertible to BOTH Type1 and Type2, used in Compare.
    // This is stricter than lower_bound requirement (see above)

    first = std::lower_bound(first, last, value, comp);
    return first != last && !comp(value, *first) ? first : last;
}

int main2()
{
    std::vector<int> data = { 1, 1, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 6 };

    auto lower = std::lower_bound(data.begin(), data.end(), 4);
    auto upper = std::upper_bound(data.begin(), data.end(), 4);

    std::copy(data.begin(), data.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\nlower distance: " << std::distance(data.begin(), lower) << " val:" << *lower << std::endl;
    std::cout << "upper distance: " << std::distance(data.begin(), upper) << " val:" << *upper << std::endl;

    std::copy(lower, upper, std::ostream_iterator<int>(std::cout, " "));

    std::cout << '\n';

    // classic binary search, returning a value only if it is present

    std::cout << "\n equal_range:\n";

    auto equal = std::equal_range(data.begin(), data.end(), 3);
    for(auto i = equal.first; i != equal.second; ++i)
        std::cout << *i << ' ';
    std::cout << std::endl;

    data = { 1, 2, 4, 6, 9, 10 };

    auto it = binary_find(data.cbegin(), data.cend(), 4); //< choosing '5' will return end()

    if(it != data.cend())
        std::cout << *it << " found at index "<< std::distance(data.cbegin(), it);


    return 0;
}


int main()
{
    std::vector<int> haystack {1, 3, 4, 5, 9};
    std::vector<int> needles {1, 2, 3};

    for (auto needle : needles) {
        std::cout << "Searching for " << needle << '\n';
        if (std::binary_search(haystack.begin(), haystack.end(), needle)) {
            std::cout << "Found " << needle << '\n';
        } else {
            std::cout << "no dice!\n";
        }
    }

    main2();
}
