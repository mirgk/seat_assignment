#ifndef SEQUENTIAL_ASSIGNER_H
#define SEQUENTIAL_ASSIGNER_H

#include "seatassigner.h"

namespace seat_assignment {
    namespace controller {

		/*!
		* \brief Assigns next available seat in turn.
		*/
        class SequentialAssigner : public SeatAssigner
        {
        public:
            SequentialAssigner();
            ~SequentialAssigner();

			std::pair<bool, std::string> reserve(seat_assignment::core::Flight* pFlight,
				const seat_assignment::data::Passenger&,
				const std::string& pSeat = "");
        };
    }
}

#endif
