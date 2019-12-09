/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
// Copyright (C) 2015-2019 German Aerospace Center (DLR) and others.
// This program and the accompanying materials
// are made available under the terms of the Eclipse Public License v2.0
// which accompanies this distribution, and is available at
// http://www.eclipse.org/legal/epl-v20.html
// SPDX-License-Identifier: EPL-2.0
/****************************************************************************/
/// @file    MSParkingArea.cpp
/// @author  Mirco Sturari
/// @author  Jakob Erdmann
/// @date    Tue, 19.01.2016
/// @version $Id$
///
// A area where vehicles can park next to the road
/****************************************************************************/


// ===========================================================================
// included modules
// ===========================================================================
#include <config.h>

#include <cassert>
#include <utils/vehicle/SUMOVehicle.h>
#include <utils/geom/Position.h>
#include <utils/geom/GeomHelper.h>
#include <microsim/MSNet.h>
#include <microsim/MSVehicleType.h>
#include "MSLane.h"
#include "MSTransportable.h"
#include "MSParkingArea.h"

//#define DEBUG_RESERVATIONS
//#define DEBUG_COND2(obj) (obj.getID() == "v.3")
#define DEBUG_COND2(obj) (obj.isSelected())


// ===========================================================================
// method definitions
// ===========================================================================
MSParkingArea::MSParkingArea(const std::string& id,
                             const std::vector<std::string>& lines,
                             MSLane& lane,
                             double begPos, double endPos,
                             int capacity,
                             double width, double length, double angle, const std::string& name,
                             bool onRoad) :
    MSStoppingPlace(id, lines, lane, begPos, endPos, name),
    myCapacity(0),
    myOnRoad(onRoad),
    myWidth(width),
    myLength(length),
    myAngle(angle),
    myEgressBlocked(false),
    myReservationTime(-1),
    myReservations(0),
    myReservationMaxLength(0),
    myNumAlternatives(0) {
    // initialize unspecified defaults
    if (myWidth == 0) {
        myWidth = SUMO_const_laneWidth;
    }
    const double spaceDim = capacity > 0 ? myLane.interpolateLanePosToGeometryPos((myEndPos - myBegPos) / capacity) : 7.5;
    if (myLength == 0) {
        myLength = spaceDim;
    }

    const double offset = MSNet::getInstance()->lefthand() ? -1 : 1;
    myShape = lane.getShape().getSubpart(
                  lane.interpolateLanePosToGeometryPos(begPos),
                  lane.interpolateLanePosToGeometryPos(endPos));
    if (!myOnRoad) {
        myShape.move2side((lane.getWidth() / 2. + myWidth / 2.) * offset);
    }
    // Initialize space occupancies if there is a road-side capacity
    // The overall number of lots is fixed and each lot accepts one vehicle regardless of size
    for (int i = 0; i < capacity; ++i) {
        const Position f = myShape.positionAtOffset(spaceDim * (i));
        const Position s = myShape.positionAtOffset(spaceDim * (i + 1));
        Position pos = myAngle == 0 ? s : (f + s) * 0.5;
        addLotEntry(pos.x(), pos.y(), pos.z(),
                    myWidth, myLength,
                    ((double) atan2((s.x() - f.x()), (f.y() - s.y())) * (double) 180.0 / (double) M_PI) + myAngle);
        mySpaceOccupancies.back().myEndPos = myBegPos + MAX2(POSITION_EPS, spaceDim * (i + 1));
    }
    computeLastFreePos();
}

MSParkingArea::~MSParkingArea() {}

void
MSParkingArea::addLotEntry(double x, double y, double z,
                           double width, double length, double angle) {
    LotSpaceDefinition lsd;
    lsd.index = (int)mySpaceOccupancies.size();
    lsd.vehicle = nullptr;
    lsd.myPosition = Position(x, y, z);
    lsd.myWidth = width;
    lsd.myLength = length;
    lsd.myRotation = angle;
    lsd.myEndPos = myEndPos;
    mySpaceOccupancies.push_back(lsd);
    myCapacity++;
    computeLastFreePos();
}




double
MSParkingArea::getLastFreePos(const SUMOVehicle& forVehicle) const {
    if (myCapacity == (int)myEndPositions.size()) {
        // keep enough space so that  parking vehicles can leave
        return myLastFreePos - forVehicle.getVehicleType().getMinGap() - POSITION_EPS;
    } else {
        // XXX if (forVehicle.getLane() == myLane && forVehicle.getPositionOnLane() > myLastFreePos) {
        //        find freePos beyond vehicle position }
        return myLastFreePos;
    }
}

Position
MSParkingArea::getVehiclePosition(const SUMOVehicle& forVehicle) const {
    for (const auto& lsd : mySpaceOccupancies) {
        if (lsd.vehicle == &forVehicle) {
            return lsd.myPosition;
        }
    }
    return Position::INVALID;
}


double
MSParkingArea::getInsertionPosition(const SUMOVehicle& forVehicle) const {
    for (const auto& lsd : mySpaceOccupancies) {
        if (lsd.vehicle == &forVehicle) {
            return lsd.myEndPos;
        }
    }
    return -1;
}


double
MSParkingArea::getVehicleAngle(const SUMOVehicle& forVehicle) const {
    for (const auto& lsd : mySpaceOccupancies) {
        if (lsd.vehicle == &forVehicle) {
            return (lsd.myRotation - 90.) * (double) M_PI / (double) 180.0;
        }
    }
    return 0;
}


void
MSParkingArea::enter(SUMOVehicle* what, double beg, double end) {
    assert(myLastFreePos >= 0);
    assert(myLastFreeLot < (int)mySpaceOccupancies.size());
    mySpaceOccupancies[myLastFreeLot].vehicle = what;
    myEndPositions[what] = std::pair<double, double>(beg, end);
    computeLastFreePos();
}


void
MSParkingArea::leaveFrom(SUMOVehicle* what) {
    assert(myEndPositions.find(what) != myEndPositions.end());
    for (auto& lsd : mySpaceOccupancies) {
        if (lsd.vehicle == what) {
            lsd.vehicle = nullptr;
            break;
        }
    }
    myEndPositions.erase(myEndPositions.find(what));
    computeLastFreePos();
}


void
MSParkingArea::computeLastFreePos() {
    myLastFreeLot = -1;
    myLastFreePos = myBegPos;
    myEgressBlocked = false;
    for (auto& lsd : mySpaceOccupancies) {
        if (lsd.vehicle == nullptr
                || (getOccupancy() == getCapacity()
                    && lsd.vehicle->remainingStopDuration() <= 0
                    && !lsd.vehicle->isStoppedTriggered())) {
            if (lsd.vehicle == nullptr) {
                myLastFreeLot = lsd.index;
                myLastFreePos = lsd.myEndPos;
            } else {
                // vehicle wants to exit the parking area
                myLastFreeLot = lsd.index;
                myLastFreePos = lsd.myEndPos - lsd.vehicle->getVehicleType().getLength() - POSITION_EPS;
                myEgressBlocked = true;
            }
            break;
        } else {
            myLastFreePos = MIN2(myLastFreePos,
                                 lsd.myEndPos - lsd.vehicle->getVehicleType().getLength() - NUMERICAL_EPS);
        }
    }
}


double
MSParkingArea::getLastFreePosWithReservation(SUMOTime t, const SUMOVehicle& forVehicle) {
    if (forVehicle.getLane() != &myLane) {
        // for different lanes, do not consider reservations to avoid lane-order
        // dependency in parallel simulation
#ifdef DEBUG_RESERVATIONS
        if (DEBUG_COND2(forVehicle)) {
            std::cout << SIMTIME << " pa=" << getID() << " freePosRes veh=" << forVehicle.getID() << " other lane\n";
        }
#endif
        if (myNumAlternatives > 0 && getOccupancy() == getCapacity()) {
            // ensure that the vehicle reaches the rerouter lane
            return MAX2(myBegPos, MIN2(POSITION_EPS, myEndPos));
        } else {
            return getLastFreePos(forVehicle);
        }
    }
    if (t > myReservationTime) {
#ifdef DEBUG_RESERVATIONS
        if (DEBUG_COND2(forVehicle)) {
            std::cout << SIMTIME << " pa=" << getID() << " freePosRes veh=" << forVehicle.getID() << " first reservation\n";
        }
#endif
        myReservationTime = t;
        myReservations = 1;
        myReservationMaxLength = forVehicle.getVehicleType().getLength();
        for (const auto& lsd : mySpaceOccupancies) {
            if (lsd.vehicle != nullptr) {
                myReservationMaxLength = MAX2(myReservationMaxLength, lsd.vehicle->getVehicleType().getLength());
            }
        }
        return getLastFreePos(forVehicle);
    } else {
        if (myCapacity > getOccupancy() + myReservations) {
#ifdef DEBUG_RESERVATIONS
            if (DEBUG_COND2(forVehicle)) {
                std::cout << SIMTIME << " pa=" << getID() << " freePosRes veh=" << forVehicle.getID() << " res=" << myReservations << " enough space\n";
            }
#endif
            myReservations++;
            myReservationMaxLength = MAX2(myReservationMaxLength, forVehicle.getVehicleType().getLength());
            return getLastFreePos(forVehicle);
        } else {
            if (myCapacity == 0) {
                return getLastFreePos(forVehicle);
            } else {
#ifdef DEBUG_RESERVATIONS
                if (DEBUG_COND2(forVehicle)) std::cout << SIMTIME << " pa=" << getID() << " freePosRes veh=" << forVehicle.getID()
                                                           << " res=" << myReservations << " resTime=" << myReservationTime << " reserved full, maxLen=" << myReservationMaxLength << " endPos=" << mySpaceOccupancies[0].myEndPos << "\n";
#endif
                return (mySpaceOccupancies[0].myEndPos
                        - myReservationMaxLength
                        - forVehicle.getVehicleType().getMinGap()
                        - NUMERICAL_EPS);
            }
        }
    }
}


double
MSParkingArea::getWidth() const {
    return myWidth;
}


double
MSParkingArea::getLength() const {
    return myLength;
}


double
MSParkingArea::getAngle() const {
    return myAngle;
}


int
MSParkingArea::getCapacity() const {
    return myCapacity;
}


int
MSParkingArea::getOccupancy() const {
    return (int)myEndPositions.size() - (myEgressBlocked ? 1 : 0);
}


int
MSParkingArea::getOccupancyIncludingBlocked() const {
    return (int)myEndPositions.size();
}

void
MSParkingArea::notifyEgressBlocked() {
    computeLastFreePos();
}

/****************************************************************************/
