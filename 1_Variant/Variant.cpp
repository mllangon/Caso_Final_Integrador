#include <iostream>
#include <variant>
#include <string>
#include <vector>
#include <sstream>
#include <nlohmann/json.hpp>

class Variant{
public:
    enum class Type { Number, String, List };
    explicit Variant(double num) : value(num), type(Type::Number) {}
    explicit Variant(std::string str) : value(str), type(Type::String) {}
    explicit Variant(std::vector<Variant> list) : value(list), type(Type::List) {}

    std::string to_string() const {
        switch (type) {
            case Type::Number:
                return std::to_string(std::get<double>(value));
            case Type::String:
                return std::get<std::string>(value);
            case Type::List:
                return list_to_string();
        }
        return "";
    }

    std::string to_json_string() const {
        nlohmann::json j;
        switch (type) {
            case Type::Number:
                j = std::get<double>(value);
                break;
            case Type::String:
                j = std::get<std::string>(value);
                break;
            case Type::List:
                for (const auto& elem : std::get<std::vector<Variant>>(value)) {
                    j.push_back(nlohmann::json::parse(elem.to_json_string()));
                }
                break;
        }
        return j.dump();
    }

    static Variant from_json_string(const std::string& json_str) {
        // Implementación esquemática
        nlohmann::json j = nlohmann::json::parse(json_str);
        // Lógica para construir un Variant basado en el contenido de j
    }

private:
    std::variant<double, std::string, std::vector<Variant>> value;
    Type type;

    std::string list_to_string() const {
        std::ostringstream oss;
        oss << "[";
        bool first = true;
        for (const auto& elem : std::get<std::vector<Variant>>(value)) {
            if (!first) {
                oss << ", ";
            }
            first = false;
            oss << elem.to_string();
        }
        oss << "]";
        return oss.str();
    }


};

int main() {
    Variant num(123.45);
    Variant str("Hello, world!");
    Variant list({num, str});

    std::cout << "Number to String: " << num.to_string() << std::endl;
    std::cout << "String to String: " << str.to_string() << std::endl;
    std::cout << "List to String: " << list.to_string() << std::endl;

    std::cout << "Number to JSON: " << num.to_json_string() << std::endl;
    std::cout << "String to JSON: " << str.to_json_string() << std::endl;
    std::cout << "List to JSON: " << list.to_json_string() << std::endl;

    return 0;
}