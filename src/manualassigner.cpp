#include "manualassigner.h"

#include "flight.h"

using namespace std;

using namespace seat_assignment::controller;
using namespace seat_assignment::core;
using namespace seat_assignment::data;

ManualAssigner::ManualAssigner()
{

}

ManualAssigner::~ManualAssigner()
{

}

pair<bool, string> ManualAssigner::reserve(Flight* pFlight, const Passenger& pPassenger, const std::string& pSeat)
{
    if (pFlight == nullptr) {
        return make_pair(false, "");
    }

    pFlight->reserve(pSeat, pPassenger);
    return make_pair(true, pSeat);
}
