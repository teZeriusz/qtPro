#include <iostream>
#include <chrono>
#include <functional>
#include <set>
#include <unordered_set>

// http://wordsandbuttons.online/challenge_your_performance_intuition_with_cpp_magic_squares.html

using namespace std;



bool check_if_magic(const std::string& square) {
    // add your code here
    // (or above if you need global stuff)

    return false;
}


function<bool(string)> generate_test(int round) {
    switch(round) {
    case 1://direct solution
    {
        auto c15 = '5' * 3;
        uint_fast64_t ideal_char_map = static_cast<uint_fast64_t>(0x1FF) << 49;
        uint_fast64_t char_map_one = 1u;

        return [=] (const std::string& sq) {
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
        };
    }
        break;

    case 2:// the oddity heuristic
    {
        auto c15 = '5' * 3;
        uint_fast64_t ideal_char_map = static_cast<uint_fast64_t>(0x1FF) << 49;
        uint_fast64_t char_map_one = 1u;

        return [=] (const std::string& sq) {
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
        };
    }
        break;

    case 3:// central 5
    {
        auto magic_number = '5' * 3;
        auto not_so_magic_number = '5' * 2;
        uint_fast64_t ideal_char_map = static_cast<uint_fast64_t>(0x1FF) << 49;
        uint_fast64_t char_map_one = 1u;

        return [=] (const std::string& sq) {
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
        };
    }
        break;

    case 4://no shift
    {
        auto magic_number = '5' * 3;
        auto not_so_magic_number = '5' * 2;
        const std::array<uint16_t, 58> bit_shifts {
            0, 0, 0, 0,   0, 0, 0, 0,
            0, 0, 0, 0,   0, 0, 0, 0,
            0, 0, 0, 0,   0, 0, 0, 0,
            0, 0, 0, 0,   0, 0, 0, 0,

            0, 0, 0, 0,   0, 0, 0, 0,
            0, 0, 0, 0,   0, 0, 0, 0,
            0, 1, 2, 4,   8, 16, 32, 64,
            128, 256
        };

        return [=] (const std::string& sq) {
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
        };
    }
        break;

    case 5: //precached answers
    {
        const std::array<std::string, 8>
                all_magic_squares = {
            "816357492", "492357816",
            "618753294", "294753618",
            "834159672", "672159834",
            "438951276", "276951438"
        };

        return [=] (const std::string& sq) {
            for(auto i = 0u; i < 8; ++i)
                if(sq == all_magic_squares[i])
                    return true;

            return false;
        };
    }
        break;

    case 6://string set
    {
        const std::set<std::string>
                all_magic_squares = {
            "816357492", "492357816",
            "618753294", "294753618",
            "834159672", "672159834",
            "438951276", "276951438"
        };

        return [=] (const std::string& sq) {
            return all_magic_squares.find(sq) != all_magic_squares.end();
        };
    }
        break;

    case 7://string unordered
    {
        const std::unordered_set<std::string>
                all_magic_squares = {
            "816357492", "492357816",
            "618753294", "294753618",
            "834159672", "672159834",
            "438951276", "276951438"
        };

        return [=] (const std::string& sq) {
            return all_magic_squares.find(sq) != all_magic_squares.end();
        };
    }
        break;

    case 8://string array plus
    {
        const std::array<std::string, 8>
          all_magic_squares = {
          "816357492", "492357816",
          "618753294", "294753618",
          "834159672", "672159834",
          "438951276", "276951438"
        };

        return [=] (const std::string& sq) {
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
        };
    }
        break;

    case 9://answers in uint64_t
    {
        const std::array<uint64_t, 8> magic_numbers
        {
            3545515123101087289, 3690191062107239479,
            3544956562637535289, 3978984379655991859,
            3689073941180135479, 4123101758198592049,
            3977867258728887859, 4122543197735040049
        };

        return [=] (const std::string& sq) {
            if(sq[4] != '5')
                return false;

            uint64_t magic_number = *(reinterpret_cast<const uint32_t*>(sq.data()));
            magic_number <<= 32;
            magic_number += *(reinterpret_cast<const uint32_t*>(sq.data()+5));

            for(auto i = 0u; i < 8; ++i)
                if(magic_number == magic_numbers[i])
                    return true;

            return false;
        };
    }
        break;

    case 10://set of uint64_t
    {
        const std::set<uint64_t> magic_numbers
        {
            3545515123101087289, 3690191062107239479,
            3544956562637535289, 3978984379655991859,
            3689073941180135479, 4123101758198592049,
            3977867258728887859, 4122543197735040049
        };

        return [=] (const std::string& sq) {
            if(sq[4] != '5')
                return false;

            uint64_t magic_number = *(reinterpret_cast<const uint32_t*>(sq.data()));
            magic_number <<= 32;
            magic_number += *(reinterpret_cast<const uint32_t*>(sq.data()+5));

            return magic_numbers.find(magic_number)
                    != magic_numbers.end();
        };
    }
        break;

    case 11://unordered set of uint64_t
    {
        const std::unordered_set<uint64_t> magic_numbers
        {
            3545515123101087289, 3690191062107239479,
            3544956562637535289, 3978984379655991859,
            3689073941180135479, 4123101758198592049,
            3977867258728887859, 4122543197735040049
        };

        return [=] (const std::string& sq) {
            if(sq[4] != '5')
                return false;

            uint64_t magic_number = *(reinterpret_cast<const uint32_t*>(sq.data()));
            magic_number <<= 32;
            magic_number += *(reinterpret_cast<const uint32_t*>(sq.data()+5));

            return magic_numbers.find(magic_number)
                    != magic_numbers.end();
        };
    }
        break;

    default:
        cerr << "dude focus\n";
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

struct Result {
    std::string name;
    int numer = -1;
    int count = 0;
    double time = 0;
};


int main(int argc, char * argv[]) {

    if(argc != 2) {
        cout << "program magic_sqare_numer\n";
        return 1;
    }

    std::string sequance(argv[1]);
    auto start = std::chrono::system_clock::now();


//    auto t1 = generate_test();
//    t1(sequance);

    auto end = std::chrono::system_clock::now();
    chrono::duration<double> difference = end - start;
    cout << difference.count() << "\n\n";

    return 0;
}
