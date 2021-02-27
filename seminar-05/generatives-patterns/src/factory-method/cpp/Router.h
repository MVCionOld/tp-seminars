#ifndef SEMINAR_03_ROUTER_H
#define SEMINAR_03_ROUTER_H

class Router {
public:
    virtual std::shared_ptr<Router> CreateRoute() const = 0;
    std::string ConnectToNet();
};

std::string Router::ConnectToNet() {
    auto route = CreateRoute();
    return route->Connect();
}

#endif //SEMINAR_03_ROUTER_H
