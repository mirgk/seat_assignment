#include "sequentialassigner.h"

#include "flight.h"

using namespace std;

using namespace seat_assignment::controller;
using namespace seat_assignment::core;
using namespace seat_assignment::data;

SequentialAssigner::SequentialAssigner()
{

}

SequentialAssigner::~SequentialAssigner()
{

}

pair<bool, string> SequentialAssigner::reserve(Flight* pFlight, const Passenger& pPassenger, const std::string& pSeat)
{
    (void)pSeat; //unused

	if (pFlight == nullptr) {
		return make_pair(false, "");
	}

	for (int row = 0; row < pFlight->getAirCraft().mRowCount; ++row) {
		for (int column = 0; column < pFlight->getAirCraft().mColumnCount; ++column) {
			if (pFlight->isAvailable(row, column) == false) {
				continue;
			}

            pFlight->reserve(row, column, pPassenger);
            return make_pair(true, pFlight->labelFromIndex(row, column));
		}
	}

	return make_pair(false, "");
}
