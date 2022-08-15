#include <algorithm>
#include <vector>
#include <iostream>
#include <ranges>
#include <iomanip>
/*
https://www.cppstories.com/2022/ranges-alg-part-two/
*/

void basic_range_algo() {
    const std::vector nums = {1, 2, 3, -4, 5, 6, 7, 8 };

    auto is_positive = [](const auto& v) { return v > 0; };

    // standard version:
    auto res = std::all_of(begin(nums), end(nums), is_positive);
    std::cout << std::boolalpha << "std::all_of: " << res << '\n';

    res = std::any_of(begin(nums), end(nums), is_positive);
    std::cout << "std::any_of: " << res << '\n';
    // ranges version:
    res = std::ranges::all_of(nums, is_positive);
    std::cout << "std::ranges::all_of: " << res << '\n';

    res = std::ranges::any_of(nums, is_positive);
    std::cout << "std::ranges::any_of: " << res << '\n';
}

struct Product {
    std::string name_;
    double value_ { 0.0 };
    Product& operator=(int i) { name_ += std::to_string(i); return *this; }
    friend bool operator==(const Product& a, const Product& b) {
        return a.name_ == b.name_ && std::abs(a.value_ - b.value_) < 0.0001;
    }
};
std::ostream& operator<<(std::ostream& os, const Product& p) {
    os << p.name_ << ", " << p.value_;
    return os;
}

void copy_if_range() {
    const std::vector<Product> prods {
        { "box", 10.0 }, {"tv", 100.0}, {"rocket", 10000.0},
        { "car", 1000.0 }, {"toy", 40.0}, {"none", 0.0}
    };

    // standard version:
    std::copy_if(begin(prods), end(prods),
              std::ostream_iterator<Product>(std::cout, "; "),
              [](const Product& p){
        return !p.name_.starts_with("none");
    });
    std::cout << '\n';

    // ranges version:
    std::ranges::copy_if(prods,
              std::ostream_iterator<Product>(std::cout, "; "),
              [](const Product& p){
        return !p.name_.starts_with("none");
    });

    std::cout << std::endl;
    std::ranges::copy_if(prods,
              std::ostream_iterator<Product>(std::cout, "; "),
              [](const std::string& name){
                  return !name.starts_with("none");
              },
              &Product::name_);

    std::cout << std::endl;
}

void fill_range() {
    std::vector<Product> prods{7, {"Box ", 1.0}};

    // standard version:
    std::fill(begin(prods), end(prods), 4);
    std::ranges::copy(prods, std::ostream_iterator<Product>(std::cout, "; "));
    std::cout << std::endl;

    // ranges version:
    std::ranges::fill(prods, 2);
    std::ranges::copy(prods, std::ostream_iterator<Product>(std::cout, "; "));
    std::cout << std::endl;
}

void generate_range() {
    std::vector<Product> prods{7, {"Box ", 1.0}};

    // standard version:
    std::generate(begin(prods), end(prods), [v = 0]() mutable {
        return v++;
    });
    std::ranges::copy(prods, std::ostream_iterator<Product>(std::cout, "; "));
    std::cout << std::endl;

    // ranges version:
    std::ranges::generate(prods, [v = 0]() mutable {
        return ++v;
    });
    std::ranges::copy(prods, std::ostream_iterator<Product>(std::cout, "; "));
    std::cout << std::endl;
}

void transform_range() {
    std::vector<Product> prods{7, {"Box ", 1.0}};

    // standard version:
    std::transform(begin(prods), end(prods), begin(prods), [v = 0](const Product &p) mutable {
        return Product { p.name_ + std::to_string(v++), 1.0};
    });
    for (auto &p : prods) std::cout << p.name_ << ", ";
    std::cout << std::endl;

    // ranges version:
    std::ranges::transform(prods, begin(prods), [v = 0](const std::string &n) mutable {
        return Product { n + std::to_string(v++), 1.0};
    }, &Product::name_);
    for (auto &p : prods) std::cout << p.name_ << ", ";
    std::cout << std::endl;
}

void transform_range2() {
    std::vector<Product> prods{7, {"Box ", 1.0}};
    std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7};

    std::ranges::transform(prods, numbers, begin(prods),
    [](const Product& p, int v) {
        return Product { p.name_ + std::to_string(v), 1.0};
    });
    for (auto &p : prods) std::cout << p.name_ << ", ";
    std::cout << std::endl;
}

void remove_if_range() {
    const std::vector<Product> prods {
        { "box", 10.0 }, {"tv", 100.0}, {"rocket", 10000.0},
        {"no prod", 0.0}, { "car", 1000.0 }, {"toy", 40.0}, {"none", 0.0}
    };

    auto printCont = [](const std::vector<Product>& cont) {
        for (auto &p : cont) std::cout << p.name_ << ", ";
        std::cout << '\n';
    };
    std::cout << "removing products starting with \"no\"\n";
    printCont(prods);

    auto checkNoPrefix = [&](const Product& p) { return p.name_.starts_with("no"); };

    // standard version:
    auto tempProds = prods;
    tempProds.erase(std::remove_if(tempProds.begin(), tempProds.end(),
        checkNoPrefix), tempProds.end());

    printCont(tempProds);

    // ranges version:
    tempProds = prods;
    tempProds.erase(std::ranges::remove_if(tempProds, checkNoPrefix).begin(), tempProds.end());
    printCont(tempProds);

    // C++20 version:
    tempProds = prods;
    std::erase_if(tempProds, checkNoPrefix);
    printCont(tempProds);
}

void replace_range() {
    std::vector<Product> prods {
        { "box", 10.0 }, {"tv", 100.0}, {"rocket", 10000.0},
        { "car", 1000.0 }, {"toy", 40.0}, {"none", 0.0},
        {"invalid", 0.0}, { "invalid", -10.0 }
    };

    std::ostream_iterator<Product> out_iter(std::cout, "; ");

    // standard version:
    std::cout << "before: \n";
    std::copy(begin(prods), end(prods), out_iter);
    std::replace(begin(prods), end(prods), Product{"none", 0.0}, Product{"default", 10.0});
    std::cout << "\nafter: \n";
    std::copy(begin(prods), end(prods), out_iter);
    std::cout << '\n';

    // ranges version:
    std::cout << "before: \n";
    std::ranges::copy(prods, out_iter);
    std::ranges::replace(prods, "invalid", Product{"default", 10.0}, &Product::name_);
    std::cout << "\nafter: \n";
    std::ranges::copy(prods, out_iter);
    std::cout << '\n';
}

void reverse_range() {
    const std::vector numbers {
        "one", "two", "three", "four", "five", "six"
    };

    auto outStream = std::ostream_iterator<std::string>(std::cout, "; ");

    // standard version:
    std::copy(begin(numbers), end(numbers), outStream);
    std::cout << '\n';
    std::reverse_copy(begin(numbers), end(numbers), outStream);

    // ranges version:
    std::cout << "\nRanges\n";
    std::ranges::copy(numbers, outStream);
    std::cout << '\n';
    std::ranges::reverse_copy(numbers, outStream);
}

void rotate_range() {
    std::vector<std::string> words { "hello", "in", "the",
        "wonderful", "world", "of", "c++", "programming",
    };

    std::ostream_iterator<std::string> out(std::cout, " ");

    // standard version:
    std::ranges::copy(words, out);
    std::cout <<'\n';
    auto firstWord = words[0];
    auto newPos = std::rotate(begin(words), std::next(begin(words), 1), end(words));
    std::ranges::copy(words, out);
    std::cout <<'\n';
    std::cout << std::quoted(firstWord) << " is now at pos "
              << std::distance(begin(words), newPos) << '\n';

    // ranges version:
    auto helloPos = std::ranges::find(words, "hello");
    if (helloPos != end(words)) {
        auto firstWord = words[0];
        auto ret = std::ranges::rotate(words, helloPos);
        std::ranges::copy(words, out);
        std::cout <<'\n';
        std::cout << std::quoted(firstWord) << " is now at pos "
                  << std::distance(begin(words), ret.begin()) << '\n';
    }
}

int main() {
    basic_range_algo();
    copy_if_range();
    fill_range();
    generate_range();
    transform_range();
    transform_range2();
    remove_if_range();
    replace_range();
    reverse_range();
    rotate_range();

    return 0;
}
