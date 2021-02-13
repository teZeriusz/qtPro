#include <map>
#include <string>
#include <atomic>
#include <memory>


using ConfigMap = std::map<std::string, std::string>;
std::atomic<std::shared_ptr<const ConfigMap>> g_config;//cpp20

void SetDefaultHostname(const std::string& value) {
    std::shared_ptr<const ConfigMap> blue = g_config.load();

    do{
        std::shared_ptr<ConfigMap> green = std::make_shared<ConfigMap>(*blue);
        green->insert_or_assign("Default.hostname", value);
    }
    while(g_config.compare_exchange_strong(blue, std::move(green)));
}

std::shared_ptr<const std::string> GetDefaultHostname() {
    std::shared_ptr<const ConfigMap> blue = g_config.load();
    const std::string& value = blue.at("default.hostname");
    return std::shared_ptr<const std::string>(std::move(blue), &value); //aliasing constructor
}


int main(){
    return 0;
}
