
#include <iostream>
#include <fstream>
#include <string>


struct Node {
    char m_letter;
    bool m_visited;
    Node * m_nodes[8];//8 max connections

    Node():m_letter('\0'), m_visited(false) {
    }

    bool has_letter(char ch) {
        return m_letter == ch;
    }

    bool check_all(const std::string & line, int idx, std::string & result) {
        std::cout << "line:" << line << " idx:" << idx << " node letter:" << m_letter << " Node:" << this << " result:" << result << std::endl;

        if(line[idx] == m_letter) {//we have it here
            result[idx] = m_letter;
            idx = idx + 1;
            m_visited = true;

            for(int i = 0; i < 8; ++i) {
                Node * node = m_nodes[i];

                if(node != NULL && node->m_visited == false) {//do not want to visit visited nodes

                    node->check_all(line, idx, result);
                    if(result == line) {
                        return true;
                    }
                }
            }
        }

        m_visited = false;
        return false;
    }


    bool check_all(const std::string & line, int idx) {
        std::string result;
        result.resize(line.size(), '\0');

        return check_all(line, idx, result);
    }
};

struct Matrix {
    Node m_all_nodes[16];

    bool find_in_matrix(const std::string & line) {
        //find first char
        Node * fist_letter_matched = NULL;

        for(int i = 0; i < 16; ++i) {
            if(m_all_nodes[i].has_letter(line[0])) {
                fist_letter_matched = &m_all_nodes[i];
                if(fist_letter_matched->check_all(line, 0) == true) {
                    return true;
                }
            }//we have first node that have first letter
            for(int j = 0; j < 16; ++j) {
                m_all_nodes[j].m_visited = false;
            }
        }

        return false;
    }
};


Matrix* create_matrix(const std::string in_matrix) {
    Matrix * matrix = new Matrix();

    for(int i = 0; i < 16; ++i) {
        //-5 -4 -3 -1 +1 +3 +4 +5
        //[0] 1  2  3  4  5  6  7 <-- index
        Node * current_node = &matrix->m_all_nodes[i];
        current_node->m_letter = in_matrix[i];

        if(i - 5 >= 0) {//can connect to node up/left
            if(! (i == 0 || i == 4 || i == 8 || i == 12)) {
                current_node->m_nodes[0] = &matrix->m_all_nodes[i - 5];
            }
        }
        if(i - 4 >= 0) {//can connect to node up
            current_node->m_nodes[1] = &matrix->m_all_nodes[i - 4];
        }
        if(i - 3 >= 0) {//can connect to node up/right
            if(! (i == 3 || i == 7 || i == 11 || i == 15)) {
                current_node->m_nodes[2] = &matrix->m_all_nodes[i - 3];
            }
        }
        if(i - 1 >= 0) {//can connect to node left
            if(! (i == 0 || i == 4 || i == 8 || i == 12)) {
                current_node->m_nodes[3] = &matrix->m_all_nodes[i - 1];
            }
        }
        if(i + 1 <= 16) {//can connect to node right
            if(! (i == 3 || i == 7 || i == 11 || i == 15)) {
                current_node->m_nodes[4] = &matrix->m_all_nodes[i + 1];
            }
        }
        if(i + 3 <= 16) {//can connect to node down/left
            if(! (i == 0 || i == 4 || i == 8 || i == 12)) {
                current_node->m_nodes[5] = &matrix->m_all_nodes[i + 3];
            }
        }
        if(i + 4 <= 16) {//can connect to node down
            current_node->m_nodes[6] = &matrix->m_all_nodes[i + 4];
        }
        if(i + 5 <= 16) {//can connect to node down/right
            if(! (i == 3 || i == 7 || i == 11 || i == 15)) {
                current_node->m_nodes[7] = &matrix->m_all_nodes[i + 5];
            }
        }
    }

    return matrix;
}


bool find_in_matrix(const std::string & line, const char * matrix) {
//find first letter
//find if there next letter 'near'

    Matrix * mat = create_matrix(matrix);

    if(mat->find_in_matrix(line)) {
        std::cout << line << std::endl;

    }

    delete mat;//this can be tweaked to awaid new
    return false;
}


int main(int argc, char *argv[]) {
    if(argc != 3) {
        fprintf(stderr, "Usage: %s <words file> <chars 4x4 matrix>\n", argv[0]);
        return 1;
    }

    std::ifstream stream(argv[1], std::fstream::in);
    if(! stream.is_open()) {
        perror("fopen");
        return 1;
    }

//    std::string test1_line("abandon");
//    const char *test1_matrix = "abanzqzdrrorrnrr";
//    find_in_matrix(test1_line, test1_matrix);


//    std::string test2_line("hah");
//    const char *test2_matrix = "zzzzzzbzhzezazzz";
//    find_in_matrix(test2_line, test2_matrix);

//    std::string test3_line("bard");
//    const char *test3_matrix = "nabadzqzrorrrnrr";
//    find_in_matrix(test3_line, test3_matrix);


//    std::string test1_line("abandon");
//    const char *test1_matrix = "aban"
//                               "bxdo"
//                               "anxx"
//                               "xxxx";
//    const char *test1_matrix = "xxxxanxxbxdoaban";
//    const char *test1_matrix = "xabaxnxbxxdaxxon";
//    const char *test1_matrix = "xxonxxdaxnxbxaba";
//    const char *test1_matrix = "xxxxxxnaodxbnaba";
//    const char *test1_matrix = "nabaodxbxxnaxxxx";
//    const char *test1_matrix = "noxxadxxbxnxabax";
//    const char *test1_matrix = "abaxbxnxadxxnoxx";


//    find_in_matrix(test1_line, test1_matrix);


    std::string line;
    while (std::getline(stream, line)) {
        if(line.size() <= 16) {
//            Your program should be tolerant of word files that contain a mixture of upper and lower case words
//            and of words that contain punctuation. Your program can deal with such words in some reasonable way.
//            Note that different word list files can be alphabetized differently.
            //I just do not know exactly what you want me to do but lets asume that you want me do be more 'not-friendly' for somekind invalid inputs

            find_in_matrix(line, argv[2]);
        }
    }


    return 0;
}
