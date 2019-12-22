#ifndef TEST_RANDOM_ASSIGNER_H
#define TEST_RANDOM_ASSIGNER_H

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

        class TestRandomAssigner : public QObject
		{
			Q_OBJECT
		public:
            TestRandomAssigner();
            ~TestRandomAssigner();

		private slots:
            void testReserve();

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
