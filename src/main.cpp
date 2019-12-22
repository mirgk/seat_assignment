#include <iostream>

#include "flight.h"

#include "seatassigner.h"
#include "manualassigner.h"
#include "sequentialassigner.h"
#include "randomassigner.h"

#include "exceptions.h"

using namespace std;

using namespace seat_assignment::controller;
using namespace seat_assignment::core;
using namespace seat_assignment::data;
using namespace seat_assignment::exception;

#ifndef UNIT_TESTING

Flight* getFlight()
{
    string f_no, dep, arr, dt;
    cout << "Flight no: ";
    cin >> f_no;

    cout << "Departure: ";
    cin >> dep;

    cout << "Arrival: ";
    cin >> arr;

    cout << "Date: ";
    cin >> dt;

    AirCraft ac;

    cout << "Aircraft ID: ";
    cin >> ac.mID;

    cout << "No. of Row: ";
    cin >> ac.mRowCount;

    cout << "No. of Column: ";
    cin >> ac.mColumnCount;

    return new Flight(f_no, dep, arr, dt, ac);
}

SeatAssigner* getSeatAssigner()
{
    cout << "[1] MANUAL" << endl;
    cout << "[2] SEQUENTIAL" << endl;
    cout << "[3] RANDOM" << endl;

    int type;
    cin >> type;

    if (type == 2) {
        return new SequentialAssigner();
    }
    else if (type == 3) {
        return new RandomAssigner();
    }

    return new ManualAssigner();
}

void reserve(SeatAssigner* pSeatAssigner, Flight* pFlight)
{
    Passenger psg;
    cout << "Passenger ID: ";
    cin >> psg.mID;

    cout << "Passenger name: ";
    cin >> psg.mName;

    cout << "Passenger surname: ";
    cin >> psg.mSurname;

    string seat;

    ManualAssigner* man_assigner = dynamic_cast<ManualAssigner*> (pSeatAssigner);
    if (man_assigner != nullptr) {
        cout << "Seat: ";
        cin >> seat;
    }

    try {
        pSeatAssigner->reserve(pFlight, psg, seat);
    }
    catch(Exception& e) {
        cout << e.what() << endl;
    }

    pFlight->print();
}

void cancelReservation(SeatAssigner* pSeatAssigner, Flight* pFlight)
{
    string seat;
    cout << "Seat: ";
    cin >> seat;

    try {
        pSeatAssigner->cancelReservation(pFlight, seat);
    }
    catch(Exception& e) {
        cout << e.what() << endl;
    }

    pFlight->print();
}

int main()
{
    int operation;

    Flight* fl = nullptr;
    SeatAssigner* sa = nullptr;

    do {
        cout << "[1] New Flight" << endl;
        cout << "[2] Seat Assigner" << endl;
        cout << "[3] Reserve" << endl;
        cout << "[4] Cancel Reservation" << endl;
        cout << "[5] Quit" << endl;

        cin >> operation;
        cout << operation << endl;

        if (operation == 1) {
            delete fl;
            fl = getFlight();
        }
        else if (operation == 2) {
            delete sa;
            sa = getSeatAssigner();
        }
        else if (operation == 3) {
            if (fl == nullptr) {
                cout << "No flight" << endl;
                continue;
            }
            if (sa == nullptr) {
                cout << "No seat assigner" << endl;
                continue;
            }
            reserve(sa, fl);
        }
        else if (operation == 4) {
            if (fl == nullptr) {
                cout << "No flight" << endl;
                continue;
            }
            if (sa == nullptr) {
                cout << "No seat assigner" << endl;
                continue;
            }
            cancelReservation(sa, fl);
        }

    } while(operation < 5);

    return 0;
}

#endif

#ifdef UNIT_TESTING

#include "testflight.h"
#include "testsequentialassigner.h"
#include "testrandomassigner.h"
#include "testmanualassigner.h"

using namespace seat_assignment::test;

int main(int argc, char** argv)
{
   int status = 0;
   {
      TestFlight tf;
      status |= QTest::qExec(&tf, argc, argv);
   }
   {
      TestSequentialAssigner tsa;
      status |= QTest::qExec(&tsa, argc, argv);
   }
   {
      TestRandomAssigner tra;
      status |= QTest::qExec(&tra, argc, argv);
   }
   {
      TestManualAssigner tma;
      status |= QTest::qExec(&tma, argc, argv);
   }

   return status;
}

#endif
