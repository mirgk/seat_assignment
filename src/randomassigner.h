#ifndef RANDOM_ASSIGNER_H
#define RANDOM_ASSIGNER_H

#include "seatassigner.h"

namespace seat_assignment {
	namespace controller {

		/*!
		* \brief Randomly assigns a seat between available ones.
		*/
		class RandomAssigner : public SeatAssigner
		{
		public:
			RandomAssigner();
			~RandomAssigner();

			std::pair<bool, std::string> reserve(seat_assignment::core::Flight* pFlight,
				const seat_assignment::data::Passenger&,
				const std::string& pSeat = "");
		};
	}
}

#endif 
