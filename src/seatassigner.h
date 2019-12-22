#ifndef SEAT_ASSIGNER_H
#define SEAT_ASSIGNER_H

#include <string>

#include "commondata.h"

namespace seat_assignment {
	namespace core {
		class Flight;
	}

    namespace controller {

		/*!
        * \brief Base class for any seat assignment strategy.
        *        This class and derivates are meant to be designed stateless.
		*/
        class SeatAssigner
        {
        public:
            SeatAssigner();
            virtual ~SeatAssigner();

            virtual std::pair<bool, std::string> reserve(seat_assignment::core::Flight* pFlight, 
				const seat_assignment::data::Passenger&,
                const std::string& pSeat = "") = 0;

            virtual bool cancelReservation(seat_assignment::core::Flight* pFlight,
				const std::string& pSeat);
        };
    }
}

#endif 
