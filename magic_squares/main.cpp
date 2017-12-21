#include <iostream>
#include <chrono>
#include <functional>
#include <set>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <iomanip>


// http://wordsandbuttons.online/challenge_your_performance_intuition_with_cpp_magic_squares.html

using namespace std;


pair<function<bool(string)>, string> generate_test(int round) {
    switch(round) {
    case 0://direct solution
    {
        auto c15 = '5' * 3;
        uint_fast64_t ideal_char_map = static_cast<uint_fast64_t>(0x1FF) << 49;
        uint_fast64_t char_map_one = 1u;

        return pair<function<bool(string)>, string> (
                    [=] (const string& sq) {
            if ((sq[0] + sq[1] + sq[2] != c15)
                    || (sq[3] + sq[4] + sq[5] != c15)
                    || (sq[6] + sq[7] + sq[8] != c15)

                    || (sq[0] + sq[3] + sq[6] != c15)
                    || (sq[1] + sq[4] + sq[7] != c15)
                    || (sq[2] + sq[5] + sq[8] != c15)

                    || (sq[0] + sq[4] + sq[8] != c15)
                    || (sq[2] + sq[4] + sq[6] != c15))
                return false;

            auto char_map = ideal_char_map;
            for(auto i = 0u; i < 9; ++i)
                char_map ^= char_map_one << sq[i];

            if (char_map != 0)
                return false;

            return true;
        },
        "direct solution"
        );
    }
        break;

    case 1:// the oddity heuristic
    {
        auto c15 = '5' * 3;
        uint_fast64_t ideal_char_map = static_cast<uint_fast64_t>(0x1FF) << 49;
        uint_fast64_t char_map_one = 1u;

        return pair<function<bool(string)>, string> (
                    [=] (const string& sq) {
            if ( (sq[0] & 1) != 0 || (sq[1] & 1) == 0
                 || (sq[2] & 1) != 0 || (sq[3] & 1) == 0
                 || (sq[4] & 1) == 0
                 || (sq[5] & 1) == 0 || (sq[6] & 1) != 0
                 || (sq[7] & 1) == 0 || (sq[8] & 1) != 0)
                return false;

            if ((sq[0] + sq[1] + sq[2] != c15)
                    || (sq[3] + sq[4] + sq[5] != c15)
                    || (sq[6] + sq[7] + sq[8] != c15)

                    || (sq[0] + sq[3] + sq[6] != c15)
                    || (sq[1] + sq[4] + sq[7] != c15)
                    || (sq[2] + sq[5] + sq[8] != c15)

                    || (sq[0] + sq[4] + sq[8] != c15)
                    || (sq[2] + sq[4] + sq[6] != c15))
                return false;

            auto char_map = ideal_char_map;
            for(auto i = 0u; i < 9; ++i)
                char_map ^= char_map_one << sq[i];

            if (char_map != 0)
                return false;

            return true;
        },
        "the oddity heuristic"
        );
    }
        break;

    case 2:// central 5
    {
        auto magic_number = '5' * 3;
        auto not_so_magic_number = '5' * 2;
        uint_fast64_t ideal_char_map = static_cast<uint_fast64_t>(0x1FF) << 49;
        uint_fast64_t char_map_one = 1u;

        return pair<function<bool(string)>, string> (
                    [=] (const string& sq) {
            if(sq[4] != '5')
                return false;

            if ((sq[0] + sq[1] + sq[2] != magic_number)
                    || (sq[3] + sq[5] != not_so_magic_number)
                    || (sq[6] + sq[7] + sq[8] != magic_number)

                    || (sq[0] + sq[3] + sq[6] != magic_number)
                    || (sq[1] + sq[7] != not_so_magic_number)
                    || (sq[2] + sq[5] + sq[8] != magic_number)

                    || (sq[0] + sq[8] != not_so_magic_number)
                    || (sq[2] + sq[6] != not_so_magic_number))
                return false;

            auto char_map = ideal_char_map;
            for(auto i = 0u; i < 9; ++i)
                char_map ^= char_map_one << sq[i];

            if (char_map != 0)
                return false;

            return true;
        },
        "central 5"
        );
    }
        break;

    case 3://no shift
    {
        auto magic_number = '5' * 3;
        auto not_so_magic_number = '5' * 2;
        const array<uint16_t, 58> bit_shifts {
            0, 0, 0, 0,   0, 0, 0, 0,
            0, 0, 0, 0,   0, 0, 0, 0,
            0, 0, 0, 0,   0, 0, 0, 0,
            0, 0, 0, 0,   0, 0, 0, 0,

            0, 0, 0, 0,   0, 0, 0, 0,
            0, 0, 0, 0,   0, 0, 0, 0,
            0, 1, 2, 4,   8, 16, 32, 64,
            128, 256
        };

        return pair<function<bool(string)>, string> (
            [=] (const string& sq) {
            if ((sq[0] + sq[1] + sq[2] != magic_number)
                    || (sq[3] + sq[5] != not_so_magic_number)
                    || (sq[6] + sq[7] + sq[8] != magic_number)

                    || (sq[0] + sq[3] + sq[6] != magic_number)
                    || (sq[1] + sq[7] != not_so_magic_number)
                    || (sq[2] + sq[5] + sq[8] != magic_number)

                    || (sq[0] + sq[4] + sq[8] != magic_number)
                    || (sq[2] + sq[4] + sq[6] != magic_number))
                return false;

            auto char_map = 0u;
            for(auto i = 0u; i < 9; ++i)
                char_map ^= bit_shifts[sq[i]];

            if (char_map != 511)
                return false;

            return true;
        },
        "no shift"
        );
    }
        break;

    case 4: //precached answers
    {
        const array<string, 8>
                all_magic_squares = {
            "816357492", "492357816",
            "618753294", "294753618",
            "834159672", "672159834",
            "438951276", "276951438"
        };

        return pair<function<bool(string)>, string> (
                    [=] (const string& sq) {
            for(auto i = 0u; i < 8; ++i)
                if(sq == all_magic_squares[i])
                    return true;

            return false;
        },
        "precached answers"
        );
    }
        break;

    case 5://string set
    {
        const set<string>
                all_magic_squares = {
            "816357492", "492357816",
            "618753294", "294753618",
            "834159672", "672159834",
            "438951276", "276951438"
        };

        return pair<function<bool(string)>, string> (
                    [=] (const string& sq) {
            return all_magic_squares.find(sq) != all_magic_squares.end();
        },
        "string set"
        );
    }
        break;

    case 6://string unordered
    {
        const unordered_set<string>
                all_magic_squares = {
            "816357492", "492357816",
            "618753294", "294753618",
            "834159672", "672159834",
            "438951276", "276951438"
        };

        return pair<function<bool(string)>, string> (
                    [=] (const string& sq) {
            return all_magic_squares.find(sq) != all_magic_squares.end();
        },
        "string unordered"
        );
    }
        break;

    case 7://string array plus
    {
        const array<string, 8>
                all_magic_squares = {
            "816357492", "492357816",
            "618753294", "294753618",
            "834159672", "672159834",
            "438951276", "276951438"
        };

        return pair<function<bool(string)>, string> (
                    [=] (const string& sq) {
            if ( (sq[0] & 1) != 0 || (sq[1] & 1) == 0
                 || (sq[2] & 1) != 0 || (sq[3] & 1) == 0
                 || (sq[4] & 1) == 0
                 || (sq[5] & 1) == 0 || (sq[6] & 1) != 0
                 || (sq[7] & 1) == 0 || (sq[8] & 1) != 0)
                return false;

            for(auto i = 0u; i < 8; ++i)
                if(sq == all_magic_squares[i])
                    return true;

            return false;
        },
        "string array plus"
        );
    }
        break;

    case 8://answers in uint64_t
    {
        const array<uint64_t, 8> magic_numbers
        {
            3545515123101087289, 3690191062107239479,
            3544956562637535289, 3978984379655991859,
            3689073941180135479, 4123101758198592049,
            3977867258728887859, 4122543197735040049
        };

        return pair<function<bool(string)>, string> (
                    [=] (const string& sq) {
            if(sq[4] != '5')
                return false;

            uint64_t magic_number = *(reinterpret_cast<const uint32_t*>(sq.data()));
            magic_number <<= 32;
            magic_number += *(reinterpret_cast<const uint32_t*>(sq.data()+5));

            for(auto i = 0u; i < 8; ++i)
                if(magic_number == magic_numbers[i])
                    return true;

            return false;
        },
        "answers in uint64_t"
        );
    }
        break;

    case 9://set of uint64_t
    {
        const set<uint64_t> magic_numbers
        {
            3545515123101087289, 3690191062107239479,
            3544956562637535289, 3978984379655991859,
            3689073941180135479, 4123101758198592049,
            3977867258728887859, 4122543197735040049
        };

        return pair<function<bool(string)>, string> (
                    [=] (const string& sq) {
            if(sq[4] != '5')
                return false;

            uint64_t magic_number = *(reinterpret_cast<const uint32_t*>(sq.data()));
            magic_number <<= 32;
            magic_number += *(reinterpret_cast<const uint32_t*>(sq.data()+5));

            return magic_numbers.find(magic_number)
                    != magic_numbers.end();
        },
        "set of uint64_t"
        );
    }
        break;

    case 10://unordered set of uint64_t
    {
        const unordered_set<uint64_t> magic_numbers
        {
            3545515123101087289, 3690191062107239479,
            3544956562637535289, 3978984379655991859,
            3689073941180135479, 4123101758198592049,
            3977867258728887859, 4122543197735040049
        };

        return pair<function<bool(string)>, string> (
                    [=] (const string& sq) {
            if(sq[4] != '5')
                return false;

            uint64_t magic_number = *(reinterpret_cast<const uint32_t*>(sq.data()));
            magic_number <<= 32;
            magic_number += *(reinterpret_cast<const uint32_t*>(sq.data()+5));

            return magic_numbers.find(magic_number)
                    != magic_numbers.end();
        },
        "unordered set of uint64_t"
        );
    }
        break;

    default:
        cerr << "dude focus passed:" << round << std::endl;
        exit(2);
    };

}


// this generates all possible combinations
// of 1-9 digits that may or may not
// form a magic square
static string buffer = "000000000";
void generate_or_check(int index_or_check = 8) {
    if(index_or_check == -1){
        if(check_if_magic(buffer))
            cout << buffer << " ";
        return;
    }

    for(auto i = 1u; i < 10; ++i){
        buffer[index_or_check] = '0' + i;
        generate_or_check(index_or_check-1);
    }
}


vector<string> generate_numbers() {
    string in("123456789");
    int i = 0;
    vector<string> out(362880);

    do {
        out[i] = in;
        i++;
    } while(next_permutation(in.begin(), in.end()));//362880

    return out;
}

struct Result {
    string name;
    int size_t = 0;
    chrono::duration<double> time;
    function<bool(string)> algo;
    vector<bool> magic_squares_result;
};


//TODO add some simple algo to test it
void validate(array<Result, 11> & results, const vector<string> & out) {
    for(auto & res: results) {
        res.magic_squares_result.reserve(out.size());
        for(size_t i = 0; i < out.size(); ++i) {
            res.magic_squares_result[i] = res.algo(out[i]);
        }
    }
    //compare magic_seq_results
}


void measure(Result & res, const vector<string> & out, uint32_t repeat = 1) {
    auto start = chrono::system_clock::now();

    for(const auto & seq: out) {
        for(uint32_t i = 0; i < repeat; ++i) {
            res.algo(seq);
        }
    }

    res.time = chrono::system_clock::now() - start;
}


int main() {
    const vector<string> & out = generate_numbers();

    array<Result, 11> results;

    for(size_t i = 0; i < 11; ++i) {
        auto [algo, name] = generate_test(i);
        results[i].algo = algo;
        results[i].name = name;
        results[i].number = i;//needed

        measure(results[i], out, 1000);
        cout << "name: " << results[i].name <<
                "\n\t\t\ttime: " << results[i].time.count() << endl;
    }

    return 0;
}
