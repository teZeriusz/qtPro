#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Receiver {
public:
    void action1(const string &s) { cout << "Receiver::action1: " << s << endl; }
    void action2(int arg) { cout << "Receiver::action2: " << arg << endl; }
};


class Command {
public:
    virtual void execute() = 0;
};

class ConcreteCommand1 : public Command {
    Receiver & receiver;
    string arg;
public:
    ConcreteCommand1(Receiver & r, const string & a) : receiver(r), arg(a) {}
    void execute() override {
        receiver.action1(arg);
    }
};

class ConcreteCommand2 : public Command {
    Receiver & receiver;
    int arg;
public:
    ConcreteCommand2(Receiver & r, int a) : receiver(r), arg(a) {}
    void execute() override {
        receiver.action2(arg);
    }
};
// Macro is set of Commands but is also a Command (Composite pattern)
class Macro : public Command {
    vector<Command*> commands;
public:
    void addCommand(Command *c) { commands.push_back(c); }
    void execute() override {
        for (auto &c : commands) {
            c->execute();
        }
    }
};


class Invoker {
    Command &cmd;
public:
    Invoker(Command &command) : cmd(command) {}
    void executeCommand() { cmd.execute(); }
};


int main() {
    Receiver receiver;
    ConcreteCommand1 command1(receiver, "Command");
    ConcreteCommand2 command2(receiver, 1);
    Macro macro;
    macro.addCommand(&command1);
    macro.addCommand(&command2);
    Invoker invoker(macro);
    invoker.executeCommand();
    return 0;
}
