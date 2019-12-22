#include "flight.h"

#include <iostream>

#include "exceptions.h"

using namespace std;

using namespace seat_assignment::core;
using namespace seat_assignment::data;
using namespace seat_assignment::exception;

Flight::Flight(const std::string& pNumber,
               const std::string& pDeparture,
               const std::string& pArrival,
               const std::string& pDate,
               const AirCraft& pAirCraft) :
    mNumber(pNumber),
    mDeparture(pDeparture),
    mArrival(pArrival),
    mDate(pDate),
    mAirCraft(pAirCraft)
{
    mSeatAssignments.reserve(mAirCraft.mRowCount);

    for(int row = 0; row < mAirCraft.mRowCount; ++row) {
        vector<Passenger*> columnVec;
        columnVec.reserve(mAirCraft.mColumnCount);

        for(int column = 0; column < mAirCraft.mColumnCount; ++column) {
            columnVec.push_back(nullptr);
        }

        mSeatAssignments.push_back(columnVec);
    }
}

Flight::~Flight()
{
    for(int row = 0; row < mAirCraft.mRowCount; ++row) {
        for(int column = 0; column < mAirCraft.mColumnCount; ++column) {
            delete mSeatAssignments[row][column];
        }
    }
}

void Flight::print() const
{
    cout << "Flight #: " << mNumber << endl;
    cout << "From: " << mDeparture << endl;
    cout << "To: " << mArrival << endl;
    cout << "Date: " << mDate << endl;

    for(int row = 0; row < mAirCraft.mRowCount; ++row) {
        for(int column = 0; column < mAirCraft.mColumnCount; ++column) {
			
			string pas_id = "-";
            if (mSeatAssignments[row][column] != nullptr) {
                pas_id = mSeatAssignments[row][column]->mID;
			}

            cout << labelFromIndex(row, column) << ":" << pas_id << "\t";
        }

        cout << endl;
    }
}

const AirCraft& Flight::getAirCraft() const
{
	return mAirCraft;
}

bool Flight::isAvailable(int pRow, int pColumn) const
{
    checkIndex(pRow, pColumn);

    return (mSeatAssignments[pRow][pColumn] == nullptr);
}

bool Flight::isFull() const
{
    return ((int) mPassengerDict.size() == mAirCraft.mRowCount * mAirCraft.mColumnCount);
}

void Flight::reserve(int pRow, int pColumn, const Passenger& pPassenger)
{
    checkIndex(pRow, pColumn);

	if (isFull()) {
		throw FlightFull();
	}

	if (isAvailable(pRow, pColumn) == false) {
		throw SeatAlreadyReserved();
	}

    if (mPassengerDict.find(pPassenger.mID) != mPassengerDict.end()) {
		throw AlreadyHasReservation();
	}

    Passenger* passenger = new Passenger(pPassenger);

    mPassengerDict[passenger->mID] = make_pair(pRow, pColumn);
    mSeatAssignments[pRow][pColumn] = passenger;
}

void Flight::reserve(const std::string& pSeat, const Passenger& pPassenger)
{
	pair<int, int> row_column = indexFromLabel(pSeat);

    reserve(row_column.first, row_column.second, pPassenger);
}

void Flight::cancelReservation(int pRow, int pColumn)
{
    checkIndex(pRow, pColumn);

	if (isAvailable(pRow, pColumn) == true) {
		throw SeatNotReserved();
	}

    Passenger* passenger = mSeatAssignments[pRow][pColumn];
    mPassengerDict.erase(passenger->mID);
    delete passenger;

    mSeatAssignments[pRow][pColumn] = nullptr;
}

void Flight::cancelReservation(const std::string& pSeat)
{
	pair<int, int> row_column = indexFromLabel(pSeat);

    cancelReservation(row_column.first, row_column.second);
}

string Flight::labelFromIndex(int pRow, int pColumn) const
{
    string ret_val = "";

    checkIndex(pRow, pColumn);

    ret_val = to_string(pRow + 1) + (char) ('A' + pColumn);
    return ret_val;
}

std::pair<int, int> Flight::indexFromLabel(const string &pLabel) const
{
	if (pLabel.size() < 2) {
		throw UnknownLabelFormat();
	}

	string row_str = pLabel.substr(0, pLabel.size() - 1);
    string col_str = pLabel.substr(pLabel.size() - 1, pLabel.size());

    int row = (stoi(row_str) - 1);
    int column = (col_str[0] - 'A');

    checkIndex(row, column);

    return make_pair(row, column);
}

void Flight::checkIndex(int pRow, int pColumn) const
{
	if (pRow < 0 || pRow >= mAirCraft.mRowCount || pColumn < 0 || pColumn >= mAirCraft.mColumnCount) {
		throw IndexOutOfRange();
	}
}
