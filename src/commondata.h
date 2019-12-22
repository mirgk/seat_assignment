#ifndef COMMON_DATA_H
#define COMMON_DATA_H

#include <string>

namespace seat_assignment {
    namespace data {

        /*!
         * \brief Represents a passenger.
         *        Uses compiler generated copy constructor and assignment operator.
         */
        struct Passenger
        {
            std::string mID;
            std::string mName;
            std::string mSurname;

            Passenger() : mID(""), mName(""), mSurname("")
            {}

			Passenger(const Passenger&) = default;
			Passenger& operator=(const Passenger&) = default;
        };

        /*!
         * \brief Represents an aircraft.
         *        Default constructor creates an aircraft without any id and seats.
         *        Uses compiler generated copy constructor and assignment operator.
         */
        struct AirCraft
        {
            std::string mID;

            int mRowCount;
            int mColumnCount;

            AirCraft() : mID(""), mRowCount(0), mColumnCount(0)
            {}

			AirCraft(const AirCraft&) = default;
			AirCraft& operator=(const AirCraft&) = default;
        };
    }
}

#endif
