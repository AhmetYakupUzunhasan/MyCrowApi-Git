#include <crow.h>
#include "crow/json.h"
#include <string>

struct User
{
    std::string name;
    std::string email;
    std::string password;
};

struct Request
{
    std::string name;
    std::string type;
};

struct SystemInfo
{
    uint32_t currentMoisture = 0;
    uint32_t currentWaterLevel = 0;
    bool isActive = false;
};

int main()
{
    crow::SimpleApp app;

    SystemInfo systemInfo;
    std::vector<Request> requests;
    requests.emplace_back("/getUsers", "GET");
    requests.emplace_back("/getInfo", "GET");
    requests.emplace_back("/postInfo", "POST");
    std::vector<User> users;
    users.emplace_back("Eymen Taha", "eymentaha@gmail.com", "12345678");
    users.emplace_back("Ahmet Kaya", "ahmet.kaya@example.com", "pass1234");



    CROW_ROUTE(app, "/")
    ([&requests]()
    {
        crow::json::wvalue res = crow::json::wvalue::list();
        for (int i = 0; i < requests.size(); i++)
        {
            crow::json::wvalue json;
            json["Name"] = requests[i].name;
            json["Type"] = requests[i].type;

            res[i] = std::move(json);
        }

        return crow::response{res};
    });

    CROW_ROUTE(app, "/getUsers")
    ([&users]()
    {
        crow::json::wvalue res;
        res = crow::json::wvalue::list();
        for (int i = 0; i < users.size(); i++)
        {
            crow::json::wvalue userJson;
            userJson["Name"] = users[i].name;
            userJson["Email"] = users[i].email;
            userJson["Password"] = users[i].password;

            res[i] = std::move(userJson);
        }

        return crow::response{res};
    });

    CROW_ROUTE(app, "/getInfo")
    ([&systemInfo]()
    {
        crow::json::wvalue res = crow::json::wvalue();
        res["Nem"] = systemInfo.currentMoisture;
        res["SuSeviye"] = systemInfo.currentWaterLevel;
        res["status"] = systemInfo.isActive;

        return crow::response{res};
    });

    CROW_ROUTE(app, "/postInfo").methods(crow::HTTPMethod::POST)
    ([&systemInfo](const crow::request& req)
    {
        auto body = crow::json::load(req.body);
        if (!body)
        {
            return crow::response(400,"Invalid Json");
        }
        systemInfo.currentMoisture = body["Nem"].i();
        systemInfo.currentWaterLevel = body ["SuSeviye"].i();
        systemInfo.isActive = body["Status"].b();

        return crow::response(200, "Okay is everything");

    });

    // Start server on port 18080
    app.port(18080).run(); //.multithreded
}