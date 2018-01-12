#include <iostream>
#include <string>
#include <map>


using namespace std;
class Mediator {
public:
    virtual void send(const string& id, const string& message) = 0;
};
class Colleague {
    Mediator* mediator;
    string id;
public:
    Colleague(const string& cid) { id = cid; }
    string getId() { return id; }
    void registerMediator(Mediator &m) { mediator = &m; }
    void receive(const string & msg) {
        cout << "Message received by " + id + ": " + msg << endl;
    }
    void send(const string & ids, const string & msg) {
        cout << id + " send message to " + ids + " : " + msg << endl;
        mediator->send(ids, msg);
    }
};

class ConcreteMediator : public Mediator {
    map<string, Colleague*> colleagues;
    bool isRegistered(string id) {
        return colleagues.find(id) != colleagues.end();
    }
public:
    void registerColleague(Colleague& c) {
        if (!isRegistered(c.getId())) {
            c.registerMediator(*this);
            colleagues[c.getId()] = &c;
        }
    }
    void send(const string& id, const string& message) override {
        if (isRegistered(id)) {
            Colleague *c = colleagues[id];
            c->receive(message);
        }
    }
};

int main() {
    Colleague peter("Peter");
    Colleague paul("Paul");
    Colleague kate("Kate");
    ConcreteMediator mediator;
    mediator.registerColleague(peter);
    mediator.registerColleague(paul);
    mediator.registerColleague(kate);
    peter.send("Paul", "wu"); //whats up?
    paul.send("Peter", "aas"); //alive and smiling
    kate.send("Paul", "diku"); //do I know you?
    paul.send("Kate", "ydkm"); //you don't know me
    return 0;
}
