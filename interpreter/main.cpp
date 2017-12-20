#include <iostream>
#include <vector>
#include <string>

using namespace std;
// Casual structure with getters and setters
class Context {
    string input;
    string output;
public:
    Context(const string & in) { input = in; }
    void setInput(const string & in) { input = in; }
    string getInput() { return input; }
    void setOutput(const string & out) { output = out; }
    string getOutput() { return output; }
};

class AbstractExpresion {
    string replaceString(const string& str, const string& search, const string& replace) {
        string s = str;
        size_t pos = 0;
        while ((pos = s.find(search, pos)) != string::npos) {
            s.replace(pos, search.length(), replace);
            pos += replace.length();
        }
        return s;
    }
public:
    virtual void interpret(Context & context) {
        string output = replaceString(context.getInput(), search(), replase());
        context.setInput(output);
        context.setOutput(output);
    }
    virtual string search() = 0;
    virtual string replase() = 0;
};
class AExpression : public AbstractExpresion {
public:
    string search() override { return "A"; }
    string replase() override { return "AA"; }
};

class BExpression : public AbstractExpresion {
public:
    string search() override { return "B"; }
    string replase() override { return "BB"; }
};

int main() {
    Context context("A*B+C");
    AExpression ae;
    BExpression be;

    // usually gramma in reprezented as tree structure (composite) here for simplicity as vector
    vector<AbstractExpresion*> expressions { &ae, &be };

    for (auto &e : expressions)
        e->interpret(context);
    cout << context.getOutput();
    return 0;
}
