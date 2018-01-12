#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <chrono>
#include <functional>
#include <limits>
#include <random>


enum class EmploymentType { FullTime, PartTime };

struct Employee {
    std::string firstName;
    std::string lastName;
    EmploymentType employmentType;
    unsigned int salary;
};

int countFullTimeEmployees(const std::vector<Employee>& employees) {
    int res = 0;
    std::for_each(begin(employees), end(employees), [&res](const Employee & e) {
        if(e.employmentType == EmploymentType::FullTime) {
            res++;
        }
    }
    );

    return res;
}

//Jaka jest złożoność czasowa? a jaka pamięciowa?
int countUniqueNumbers1(const std::vector<int>& v) {
    int res = 0;

    for(auto elem: v) {
        int out = 0;
        for(auto elemIn: v) {
            if(elem == elemIn) {
                ++out;

                if(out > 1) {
                    break;
                }
            }
        }

        if(out == 1) {
            ++res;
        }
    }

    return res;
}//0(n^2) pamieciowa 0(1)

//Załóżmy, że przekazywana w parametrze kolekcja zawiera tylko liczby z zakresu [-­1000, 1000].
//Zaproponuj jak najbardziej optymalną czasowo funkcję countUniqueNumbers2, wykorzystującą ten
//fakt i zliczającą unikalne liczby w kolekcji.
int countUniqueNumbers2(const std::vector<int>& v) {
    std::vector<int> out(2001, 0);//-1000 - 1000

    for(size_t i = 0; i < v.size(); ++i) {
        assert(v[i] >= -1000 && v[i] <= 1000);
        out[ v[i] + 1000 ] += 1;
    }

    int res = 0;
    std::for_each(out.begin(), out.end(), [&res](const int & i) {
        if(i == 1) {
            ++res;
        }
    });

    return res;
}//0(n) pamieciowa 0(1)


std::vector<int> generateRandom(size_t numbersToGenerate) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(-1000, 1000);

    std::vector<int> out(numbersToGenerate);
    for(size_t i = 0; i < numbersToGenerate; ++i) {
        out[i] = dist(mt);
    }

    return out;
}


void mesureTime(std::string name, std::function<int()> callable) {
    auto start = std::chrono::steady_clock::now();

    std::cout << "zad2." << name << ":" << callable() << std::endl;

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;

    std::cout
            << "elapsed time: " << elapsed_seconds.count() << "s for: " << name << "\n";
}

//Napisz funkcję, która przyjmuje 3 liczby całkowite z zakresu 0..2^32-1 i sprawdza czy można zbudować
//trójkąt z boków o takich długościach. Jakie testy można wykonać? Podaj przypadki testowe.
bool canBeTriangle(uint32_t a, uint32_t b, uint32_t c) {
    uint64_t ab = (uint64_t)a + (uint64_t)b;
    uint64_t ac = (uint64_t)a + (uint64_t)c;
    uint64_t bc = (uint64_t)b + (uint64_t)c;

    return (ab > (uint64_t)c) && (ac > (uint64_t)b) && (bc > (uint64_t)a);
}


//zad4
//unsigned int getNumberOfEmployeesEarningAtLeast(const unsigned int& minimumSalary) {
//    std::string query = "SELECT COUNT(*) FROM `Employee` " \
//    "WHERE 'salary'' >= " + std::to_string(minimumSalary); //brak zakonczenia sql'a ';'

//    //sprawdzic g_database
//    //sprawdzic return state
//    //powinno byc mysql_query() - dane nie sa binarne
//    mysql_real_query(g_database, query.c_str(), query.length());

//    auto res = mysql_store_result(g_database);//mysql_error brakuje
//    auto row = mysql_fetch_row(res);//row nie uzyty

//    return boost::lexical_cast<unsigned int>(res[0]);//sprawdzanie czy jest chociaz jeden
//    //uzyc z mysql_fetch_lengths()
//}


int main() {
    std::vector<Employee> testData
    {
        {"zdzichor", "mnich", EmploymentType::FullTime, 500},
        {"fisior", "wojownik", EmploymentType::PartTime, 1500},
        {"pisior", "paladyn", EmploymentType::PartTime, 1600},
        {"wisior", "mag", EmploymentType::FullTime, 1600},
        {"misior", "kleryk", EmploymentType::PartTime, 1502}
    };

    std::cout << "zad1:" << countFullTimeEmployees(testData) << std::endl;

    std::vector<int> testData2
    {
        1, 3, 5,
        1, 2, 4,
        7, 3, 4,
        6, 9, 5
    };// 2 7 6 9

    std::cout << "zad2.t1:" << countUniqueNumbers1(testData2) << std::endl;
    std::cout << "zad2.t2:" << countUniqueNumbers2(testData2) << std::endl;



//zad2 Speed tests
    const std::vector<int> & genData = generateRandom(100000);
    {
        std::function<int()> callable = std::bind(countUniqueNumbers1, genData);
        mesureTime("countUniqueNumbers1", callable);
    }
    {
        std::function<int()> callable = std::bind(countUniqueNumbers2, genData);
        mesureTime("countUniqueNumbers2", callable);
    }

//zad3 tests
    {
        uint32_t max = std::numeric_limits<uint32_t>::max();
        std::cout << "zad3.t1:" << canBeTriangle(max, max, max) << std::endl;

        std::cout << "zad3.t2:" << canBeTriangle(0, max, max) << std::endl;
        std::cout << "zad3.t3:" << canBeTriangle(max, 0, max) << std::endl;
        std::cout << "zad3.t4:" << canBeTriangle(max, max, 0) << std::endl;

        std::cout << "zad3.t5:" << canBeTriangle(0, max, 0) << std::endl;
        std::cout << "zad3.t6:" << canBeTriangle(max, 0, 0) << std::endl;
        std::cout << "zad3.t7:" << canBeTriangle(0, 0, max) << std::endl;

        std::cout << "zad3.t8:" << canBeTriangle(5, 2, 3) << std::endl;
    }
    return 0;
}
