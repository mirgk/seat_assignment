#include "testflight.h"

#include <iostream>

#include "commondata.h"
#include "flight.h"

#include "exceptions.h"

using namespace std;

using namespace seat_assignment::core;
using namespace seat_assignment::data;
using namespace seat_assignment::exception;
using namespace seat_assignment::test;

TestFlight::TestFlight()
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

    fl1 = new Flight("TK7300", "IST", "OSL", "2019-08-01 14:00:00", *ac1); // 24 seats
    fl2 = new Flight("TK7300", "IST", "OSL", "2019-08-01 14:00:00", *ac2); // 1 seat
    fl3 = new Flight("TK7300", "IST", "OSL", "2019-08-01 14:00:00", *ac3); // no seats
}

TestFlight::~TestFlight()
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

void TestFlight::testReserve()
{
    //invalid index for reservation
    try {
        //cout << "Calling reserve with invalid index" << endl;
        QVERIFY_EXCEPTION_THROWN(fl1->reserve(-1, 0, *p1), IndexOutOfRange);
    }
    catch(Exception& e) {
        cout << e.what() << endl;
    }

    //invalid label for reservation
    try {
        //cout << "Calling reserve with invalid label" << endl;
        QVERIFY_EXCEPTION_THROWN(fl1->reserve("1", *p1), UnknownLabelFormat);
    }
    catch(Exception& e) {
        cout << e.what() << endl;
    }

    //invalid seat
    try {
        //cout << "Calling reserve with invalid seat" << endl;
        QVERIFY_EXCEPTION_THROWN(fl1->reserve("24A", *p1), IndexOutOfRange);
    }
    catch(Exception& e) {
        cout << e.what() << endl;
    }

    //OK
    try {
        //cout << "Calling reserve with valid seat" << endl;
        fl1->reserve("2A", *p1);
    }
    catch(Exception& e) {
        cout << e.what() << endl;
    }

    //Second reservation for same passenger
    try {
        //cout << "Calling reserve for passenger with reservation" << endl;
        QVERIFY_EXCEPTION_THROWN(fl1->reserve("1A", *p1), AlreadyHasReservation);
    }
    catch(Exception& e) {
        cout << e.what() << endl;
    }

    //Second reservation for same seat
    try {
        //cout << "Calling reserve for already reserved seat" << endl;
        QVERIFY_EXCEPTION_THROWN(fl1->reserve("2A", *p2), SeatAlreadyReserved);
    }
    catch(Exception& e) {
        cout << e.what() << endl;
    }

    //No seat
    try {
        //cout << "Calling reserve for no seat" << endl;
        QVERIFY_EXCEPTION_THROWN(fl3->reserve("1A", *p1), IndexOutOfRange);
    }
    catch(Exception& e) {
        cout << e.what() << endl;
    }
}

void TestFlight::testCancelReservation()
{
    //invalid index for cancel reservation
    try {
        //cout << "Calling cancel reservation with invalid index" << endl;
        QVERIFY_EXCEPTION_THROWN(fl1->cancelReservation(-1, 0), IndexOutOfRange);
    }
    catch(Exception& e) {
        cout << e.what() << endl;
    }

    //cancel for no reserved
    try {
        //cout << "Calling cancel reservation with unreserved seat" << endl;
        QVERIFY_EXCEPTION_THROWN(fl1->cancelReservation(3, 0), SeatNotReserved);
    }
    catch(Exception& e) {
        cout << e.what() << endl;
    }

    //OK
    try {
        //cout << "Calling cancel reservation with valid reservation" << endl;
        fl1->cancelReservation(1, 0);
    }
    catch(Exception& e) {
        cout << e.what() << endl;
    }
}

void TestFlight::testIsAvailable()
{
    QVERIFY_EXCEPTION_THROWN(fl3->isAvailable(0, 0), IndexOutOfRange);

    QCOMPARE(fl1->isAvailable(3, 2), true);

    QCOMPARE(fl2->isAvailable(0, 0), true);
    fl2->reserve(0, 0, *p1);
    QCOMPARE(fl2->isAvailable(0, 0), false);
    fl2->cancelReservation(0, 0);
    QCOMPARE(fl2->isAvailable(0, 0), true);
}

void TestFlight::testIsFull()
{
    QCOMPARE(fl3->isFull(), true);

    QCOMPARE(fl2->isFull(), false);
    fl2->reserve(0, 0, *p1);
    QCOMPARE(fl2->isFull(), true);
    fl2->cancelReservation(0, 0);
    QCOMPARE(fl2->isFull(), false);
}

void TestFlight::testLabelIndexConversion()
{
    QVERIFY_EXCEPTION_THROWN(fl3->labelFromIndex(0, 0), IndexOutOfRange);
    QVERIFY_EXCEPTION_THROWN(fl3->indexFromLabel("1A"), IndexOutOfRange);

    QVERIFY_EXCEPTION_THROWN(fl2->labelFromIndex(2,0), IndexOutOfRange);
    QCOMPARE(fl2->labelFromIndex(0, 0), "1A");
    QCOMPARE(fl2->indexFromLabel("1A"), make_pair(0, 0));

    string label = fl1->labelFromIndex(3, 2);
    QCOMPARE(fl1->indexFromLabel(label), make_pair(3, 2));
}
