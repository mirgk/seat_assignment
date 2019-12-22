#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>

namespace seat_assignment {
	namespace exception {

        /*!
         * \brief Base class to derive application specific exceptions from.
         */
		class Exception : public std::exception
		{
		public:
			Exception(std::string pDef) : mInfo(pDef)
			{}
			virtual ~Exception()
			{}

            virtual const char* what() const _NOEXCEPT
			{
				return mInfo.c_str();
			}

		private:
			std::string mInfo;
		};

		#define DEFINE_EXCEPTION(_EXNAME,_DEFINITION) class _EXNAME: public Exception \
		{ \
		public: \
			_EXNAME(std::string pDef=""#_DEFINITION): Exception(pDef){}\
			~_EXNAME() {} \
		};

		DEFINE_EXCEPTION(IndexOutOfRange, Invalid index values)
		DEFINE_EXCEPTION(FlightFull, Flight fully reserved)
		DEFINE_EXCEPTION(SeatAlreadyReserved, Requested seat is already reserved)
		DEFINE_EXCEPTION(SeatNotReserved, Requested seat is currently not reserved)
		DEFINE_EXCEPTION(AlreadyHasReservation, Passenger already has a reservation)
		DEFINE_EXCEPTION(UnknownLabelFormat, Label format is not valid)
	}
}

#endif
