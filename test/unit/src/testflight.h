#ifndef TEST_FLIGHT_H
#define TEST_FLIGHT_H

#include <QtTest/QTest>
#include <QObject>

namespace seat_assignment {

    namespace data {
        struct Passenger;
        struct AirCraft;
    }

    namespace core {
        class Flight;
    }

	namespace test {

		class TestFlight : public QObject
		{
			Q_OBJECT
		public:
			TestFlight();
			~TestFlight();

		private slots:
            void testReserve();
            void testCancelReservation();
            void testIsAvailable();
            void testIsFull();
            void testLabelIndexConversion();

        private:
            seat_assignment::data::Passenger* p1;
            seat_assignment::data::Passenger* p2;

            seat_assignment::data::AirCraft* ac1;
            seat_assignment::data::AirCraft* ac2;
            seat_assignment::data::AirCraft* ac3;

            seat_assignment::core::Flight* fl1;
            seat_assignment::core::Flight* fl2;
            seat_assignment::core::Flight* fl3;
		};
	}
}

#endif

