#ifndef SEARCH_CH_JOURNEY_SEGMENTS_TEST_H
#define SEARCH_CH_JOURNEY_SEGMENTS_TEST_H

#include <QObject>

#include "../../parser/parser_search_ch.h"

class SearchCHJourneyDetailsTest: public QObject
{
    Q_OBJECT

private slots:
    void testDetailsId();
    void testDetailsDepartureStationIsFromLastSearch();
    void testDetailsArrivalStationIsFromLastSearch();
    void testDetailsViaStationIsFromLastSearch();
    void testDetailsViaStationEmpty();
    void testDetailsDuration();
    void testDetailsDepartureTime();
    void testDetailsArrivalTime();
    void testJourneyWithSingleSegment();
    void testJourneyWithMultipleSegments();
    void testSegmentByBus();
    void testSegmentByBusThatHasLineSetToBus();
    void testSegmentByPostauto();
    void testSegmentByNightBus();
    void testSegmentByNightSTrain();
    void testSegmentByTram();
    void testSegmentBySTrain();
    void testSegmentByExpressTrain();
    void testSegmentWithoutLine();
    void testSegmentWithoutArrivalTrackInfo();
    void testSegmentWithoutDepartureTrackInfo();
    void testCancelledSegment();
    void testSegmentWithZeroDepartureDelay();
    void testSegmentWithDepartureDelay();
};

#endif
