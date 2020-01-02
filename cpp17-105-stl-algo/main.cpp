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
//inplace_merge
}

void partition_playground() {
//partition
//partition_point
}

void permutation_playground() {
//rotate
//shuffle
//next_permutation
//prev_permutation
//reverse
}

void numer_playground() {
//count
//accumulate COMPARE //transform_reduce
//partial_sum
//    transform_inclusive_scan
//      transform_exclusive_scan
//inner_product
//adjacent_difference
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
    heap_playground();
    cout << "Hello World!" << endl;
    return 0;
}
