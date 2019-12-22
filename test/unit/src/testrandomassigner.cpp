#include "testrandomassigner.h"

#include <iostream>

#include "randomassigner.h"

#include "commondata.h"
#include "flight.h"

#include "exceptions.h"

using namespace std;

using namespace seat_assignment::controller;
using namespace seat_assignment::core;
using namespace seat_assignment::data;
using namespace seat_assignment::exception;
using namespace seat_assignment::test;

TestRandomAssigner::TestRandomAssigner()
{
    p1 = new Passenger();
    p2 = new Passenger();

    p1->mID = "111";
    p1->mName = "John";
    p1->mSurname = "Foe";

    p2->mID = "222";
    p2->mName = "Sue";
    p2->mSurname = "Doe";

    ac1 = new AirCraft();
    ac2 = new AirCraft();
    ac3 = new AirCraft();

    ac1->mColumnCount = 6;
    ac1->mRowCount = 4;

    ac2->mRowCount = 1;
    ac2->mColumnCount = 1;

    ac3->mRowCount = 0;
    ac3->mColumnCount = 0;

    fl1 = new Flight("TK7300", "IST", "OSL", "2018-08-01 14:00:00", *ac1); // 24 seats
    fl2 = new Flight("TK7300", "IST", "OSL", "2018-08-01 14:00:00", *ac2); // 1 seat
    fl3 = new Flight("TK7300", "IST", "OSL", "2018-08-01 14:00:00", *ac3); // no seats
}

TestRandomAssigner::~TestRandomAssigner()
{
    delete p1;
    delete p2;

    delete ac1;
    delete ac2;
    delete ac3;

    delete fl1;
    delete fl2;
    delete fl3;
}

void TestRandomAssigner::testReserve()
{
    RandomAssigner rand_assigner;

    QCOMPARE(rand_assigner.reserve(nullptr, *p1).first, false);
    QCOMPARE(rand_assigner.reserve(fl3, *p1).first, false);

    QCOMPARE(rand_assigner.reserve(fl1, *p1).first, true);

    //Second reservation for same passenger
    try {
        QVERIFY_EXCEPTION_THROWN(rand_assigner.reserve(fl1, *p1), AlreadyHasReservation);
    }
    catch(Exception& e) {
        cout << e.what() << endl;
    }

    QCOMPARE(rand_assigner.reserve(fl2, *p1).first, true);
    QCOMPARE(rand_assigner.reserve(fl2, *p2).first, false);
}
