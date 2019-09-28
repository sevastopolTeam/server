#include <httplib.h>
#include <iostream>

int main(void)
{
    using namespace httplib;

    Server svr;

    std::cout << "111" << std::endl;

    svr.Get("/hi", [](const Request& req, Response& res) {
        res.set_content("Hello World!", "text/plain");
    });

    svr.Get(R"(/numbers/(\d+))", [&](const Request& req, Response& res) {
        auto numbers = req.matches[1];
        res.set_content(numbers, "text/plain");
    });

    svr.Get("/stop", [&](const Request& req, Response& res) {
        svr.stop();
    });

    svr.listen("0.0.0.0", 1234);
}

