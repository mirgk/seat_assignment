#ifndef FLIGHT_H
#define FLIGHT_H

#include <vector>
#include <unordered_map>

#include "commondata.h"

namespace seat_assignment {
	namespace core {

		/*!
		* \brief Represents a flight containing necessary information.
        *        Holds all basic necessary operations for reservation management.
        *        Non-copyable, non-assignable
        *        Contains utility functions for mapping between indices and human readable label (00<->1A).
		*/
		class Flight
		{
		public:
			Flight(const std::string& pNumber,
				const std::string& pDeparture,
				const std::string& pArrival,
				const std::string& pDate,
				const seat_assignment::data::AirCraft& pAirCraft);

			virtual ~Flight();

			Flight(const Flight&) = delete;
			Flight& operator=(const Flight&) = delete;

			const seat_assignment::data::AirCraft& getAirCraft() const;

			void print() const;

			bool isAvailable(int pRow, int pColumn) const;
			bool isFull() const;

            void reserve(int pRow, int pColumn, const seat_assignment::data::Passenger&);
            void reserve(const std::string&, const seat_assignment::data::Passenger&);

            void cancelReservation(int pRow, int pColumn);
            void cancelReservation(const std::string& pSeat);

			std::string labelFromIndex(int pRow, int pColumn) const;
			std::pair<int, int> indexFromLabel(const std::string& pLabel) const;

		private:
            void checkIndex(int pRow, int pColumn) const;

			std::string mNumber;
			std::string mDeparture;
			std::string mArrival;
			std::string mDate;

			seat_assignment::data::AirCraft mAirCraft;

            std::vector<std::vector<seat_assignment::data::Passenger*> > mSeatAssignments;
            std::unordered_map<std::string, std::pair<int, int> > mPassengerDict;
		};
	}
}

#endif 
