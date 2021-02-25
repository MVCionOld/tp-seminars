#ifndef SEMINAR_03_WIFIROUTER_H
#define SEMINAR_03_WIFIROUTER_H

#include <routers/Router.h>

class WifiRouter : public Router {
public:
    std::shared_ptr<Route> CreateRoute() const override;
};

std::shared_ptr <Route> WifiRouter::CreateRoute() const {
    return std::make_shared<WifiRoute>();
}

#endif //SEMINAR_03_WIFIROUTER_H
