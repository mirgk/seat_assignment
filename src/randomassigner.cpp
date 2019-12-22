#include "randomassigner.h"

#include "flight.h"

using namespace std;

using namespace seat_assignment::controller;
using namespace seat_assignment::core;
using namespace seat_assignment::data;

RandomAssigner::RandomAssigner()
{

}

RandomAssigner::~RandomAssigner()
{

}

pair<bool, string> RandomAssigner::reserve(Flight* pFlight, const Passenger& pPassenger, const std::string& pSeat)
{
    (void)pSeat; // unused

	if (pFlight == nullptr) {
		return make_pair(false, "");
	}

	vector<pair<int, int> > avail_seats;

	for (int row = 0; row < pFlight->getAirCraft().mRowCount; ++row) {
		for (int column = 0; column < pFlight->getAirCraft().mColumnCount; ++column) {
			if (pFlight->isAvailable(row, column)) {
				avail_seats.push_back(make_pair(row, column));
			}
		}
	}

    if (avail_seats.size() == 0) {
        return make_pair(false, "");
    }

	int index = (rand() % avail_seats.size());
	int row = avail_seats.at(index).first;
	int column = avail_seats.at(index).second;

    pFlight->reserve(row, column, pPassenger);
    return make_pair(true, pFlight->labelFromIndex(row, column));
}
