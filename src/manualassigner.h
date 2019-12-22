#ifndef MANUAL_ASSIGNER_H
#define MANUAL_ASSIGNER_H

#include "seatassigner.h"

namespace seat_assignment {
    namespace controller {

        /*!
        * \brief Tries to reserve requested seat.
        */
        class ManualAssigner : public SeatAssigner
        {
        public:
            ManualAssigner();
            ~ManualAssigner();

            std::pair<bool, std::string> reserve(seat_assignment::core::Flight* pFlight,
                const seat_assignment::data::Passenger&,
                const std::string& pSeat = "");
        };
    }
}

#endif
