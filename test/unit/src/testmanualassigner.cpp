#include "testmanualassigner.h"

#include <iostream>

#include "manualassigner.h"

#include "commondata.h"
#include "flight.h"

#include "exceptions.h"

using namespace std;

using namespace seat_assignment::controller;
using namespace seat_assignment::core;
using namespace seat_assignment::data;
using namespace seat_assignment::exception;
using namespace seat_assignment::test;

TestManualAssigner::TestManualAssigner()
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

TestManualAssigner::~TestManualAssigner()
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

void TestManualAssigner::testReserve()
{
    ManualAssigner man_assigner;

    QCOMPARE(man_assigner.reserve(nullptr, *p1).first, false);

    //invalid index for reservation
    try {
        QVERIFY_EXCEPTION_THROWN(man_assigner.reserve(fl1, *p1, "1"), UnknownLabelFormat);
    }
    catch(Exception& e) {
        cout << e.what() << endl;
    }

    //invalid seat
    try {
        QVERIFY_EXCEPTION_THROWN(man_assigner.reserve(fl1, *p1, "24A"), IndexOutOfRange);
    }
    catch(Exception& e) {
        cout << e.what() << endl;
    }

    //OK
    try {
        QCOMPARE(man_assigner.reserve(fl1, *p1, "2A").first, true);
    }
    catch(Exception& e) {
        cout << e.what() << endl;
    }

    //Second reservation for same passenger
    try {
        QVERIFY_EXCEPTION_THROWN(man_assigner.reserve(fl1, *p1, "1A"), AlreadyHasReservation);
    }
    catch(Exception& e) {
        cout << e.what() << endl;
    }

    //Second reservation for same seat
    try {
        QVERIFY_EXCEPTION_THROWN(man_assigner.reserve(fl1, *p2, "2A"), SeatAlreadyReserved);
    }
    catch(Exception& e) {
        cout << e.what() << endl;
    }

    //No seat
    try {
        QVERIFY_EXCEPTION_THROWN(man_assigner.reserve(fl3, *p1, "1A"), IndexOutOfRange);
    }
    catch(Exception& e) {
        cout << e.what() << endl;
    }
}
