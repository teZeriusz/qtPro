#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>

using namespace std;


// https://www.youtube.com/watch?v=2olsGf6JIkU


void heap_playground() {
    vector<int> vec(10);
    iota(begin(vec), end(vec), 0);

    make_heap(begin(vec), end(vec));
    copy(cbegin(vec), cend(vec), ostream_iterator<int>(cout, " "));
    cout << "\n";

    vec.push_back(11);
    push_heap(begin(vec), end(vec));

    copy(cbegin(vec), cend(vec), ostream_iterator<int>(cout, " "));
    cout << "\n";

    pop_heap(begin(vec), end(vec));
    vec.pop_back();

    copy(cbegin(vec), cend(vec), ostream_iterator<int>(cout, " "));
    cout << "\n";

//TODO pop_heap on all - sorted collection
    sort_heap(begin(vec), end(vec));

    copy(cbegin(vec), cend(vec), ostream_iterator<int>(cout, " "));
    cout << "\n";
}

void sort_playground() {
//sort
//partial_sort
//nth_element
{
    std::vector<int> v{5, 6, 4, 3, 2, 6, 7, 9, 3};

    std::nth_element(v.begin(), v.begin() + v.size()/2, v.end());
    std::cout << "The median is " << v[v.size()/2] << '\n';

    copy(cbegin(v), cend(v), ostream_iterator<int>(cout, " "));
    cout << "\n";

    std::nth_element(v.begin(), v.begin()+1, v.end(), std::greater<int>());
    std::cout << "The second largest element is " << v[1] << '\n';
    copy(cbegin(v), cend(v), ostream_iterator<int>(cout, " "));
    cout << "\n";

}
//inplace_merge
}

void partition_playground() {
//partition
//partition_point
}

void permutation_playground() {
//rotate
{
    vector<int> v{4,6,3,8,1,5,9,0};
    // insertion sort
    for (auto i = v.begin(); i != v.end(); ++i) {
        std::rotate(std::upper_bound(v.begin(), i, *i), i, i+1);
    }
}
//shuffle
{
    array<int, 10> a{0};
    iota(begin(a), end(a), 1);

    random_shuffle(begin(a), end(a));
    copy(begin(a), end(a), ostream_iterator<int>(cout, " "));
    cout << "\n";
}
//next_permutation
//prev_permutation
//reverse
}

void numer_playground() {
//count
//accumulate COMPARE //transform_reduce
{
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int sum = std::accumulate(v.begin(), v.end(), 0);
    int product = std::accumulate(v.begin(), v.end(), 1, std::multiplies<int>());

    cout << "accumulate sum:" << sum << " product:" << product << "\n";
}
//partial_sum
//    transform_inclusive_scan
//      transform_exclusive_scan
//inner_product
{
    std::vector<int> a{0, 1, 2, 3, 4};
    std::vector<int> b{5, 4, 2, 3, 1};

    int r1 = std::inner_product(a.begin(), a.end(), b.begin(), 0); // a1 * b1 + aN * bN
    std::cout << "Inner product of a and b: " << r1 << '\n';

    int r2 = std::inner_product(a.begin(), a.end(), b.begin(), 0,
                                std::plus<>(), std::equal_to<>());
    std::cout << "Number of pairwise matches between a and b: " <<  r2 << '\n';
}
//adjacent_difference
{
    std::array<int, 10> a {1};
//    adjacent_difference(begin(a), std::prev(end(a)), std::next(begin(a)), std::plus<> {});
    adjacent_difference(begin(a), end(a) - 1, begin(a) + 1, std::plus<> {});

    copy(begin(a), end(a), ostream_iterator<int>(cout, " "));
    cout << "\n";
}
//sample :D
}

void querying_playground() {
//    all_of
//    any_of
//    none_of

//    equal
//    lexicographical_compare
//    mismatch

}

void search_playground() {
//sorted
//    equal_range
      //lower_bound
//    upper_bound
    //binary_search

//not sorted
    //find
//    adjacent_find

    //search //find_end //find_first_of


//relative value
//max_element
    //min_element
//    minmax_element
}


void algos_on_sets_playgroud() {
//set is ANY sorted collection
//    set_difference

//    set_intersection

//    set_union

//    set_symmetric_difference

//    includes

//    merge
}


void movers_playgournd() {
    //copy

    //move

//    swap_ranges

//    copy_backward
}

void value_mod_playground() {
//    fill

//    iota

//    generate

//    replace
}


void structure_changes_playground() {
    //remove

    //unique

//    erase/remove
}


void lonley_island_playground() {
    //for_each

    //transform
}

void raw_memory_plaground() {//objects not constructed
//    uninitialized_move/copy/fill

//    uninitialized_default_construct
    //...

//    destroy

}

//ADD COMPLEXITY !
// ranges v3 combine algos with pipe | looka at https://www.youtube.com/watch?v=sEvYmb3eKsw
int main()
{
//    heap_playground();

cout << "NUMERIC\n";
numer_playground();
cout << "SORT\n";
sort_playground();
    cout << "Hello World!" << endl;
    return 0;
}
