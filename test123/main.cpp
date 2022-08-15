#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct ServiceEntry {
    string service_id;
    struct HTTPOperation{
        string m_id;
        string m_url;
        HTTPOperation(string oid, string ourl):
            m_id(move(oid)), m_url(move(ourl))
        {}
    };

    vector<HTTPOperation> httpOperations;

    ServiceEntry(string sid, string oid, string ourl):
        service_id(move(sid)) {
        httpOperations.emplace_back(move(oid), move(ourl));
    }
};


int main()
{

    vector<ServiceEntry> serviceEntries;
    serviceEntries.emplace_back("A", "BB", "CCC");

    for(const auto& el: serviceEntries) {
        cout << "first:" << el.service_id;

        for(const auto& nested: el.httpOperations) {
            cout << "\tsecond:" << nested.m_id;
            cout << "\tsecond:" << nested.m_url;
        }
    }

    cout << endl;
    return 0;
}
