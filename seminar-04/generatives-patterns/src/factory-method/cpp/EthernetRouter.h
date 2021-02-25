#ifndef SEMINAR_03_HUBROUTER_H
#define SEMINAR_03_HUBROUTER_H

#include <routers/Router.h>

class EthernetRouter: public Router {
public:
    std::shared_ptr<Route> CreateRoute() const override;
};

std::shared_ptr <Route> EthernetRouter::CreateRoute() const {
    return std::make_shared<EthernetRoute>();
}

#endif //SEMINAR_03_HUBROUTER_H
