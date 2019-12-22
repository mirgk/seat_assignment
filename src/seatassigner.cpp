#include "seatassigner.h"

#include "flight.h"

using namespace std;

using namespace seat_assignment::controller;
using namespace seat_assignment::core;
using namespace seat_assignment::data;

SeatAssigner::SeatAssigner()
{

}

SeatAssigner::~SeatAssigner()
{

}

bool SeatAssigner::cancelReservation(Flight* pFlight, const std::string& pSeat)
{
    if (pFlight == nullptr) {
        return false;
    }

    pFlight->cancelReservation(pSeat);

    return true;
}
