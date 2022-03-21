#ifndef SEARCH_CH_STATIONBOARD_TEST_H
#define SEARCH_CH_STATIONBOARD_TEST_H

#include <QObject>

#include "../../parser/parser_search_ch.h"

class SearchCHJourneyTest: public QObject
{
    Q_OBJECT

private slots:
    void testQueryURL();
    void testQueryStationFromAndToWithoutVia();
    void testQueryStationFromAndToWithVia();
    void testQueryDateAndTime();
    void testQueryAsksForDelays();
    void testDepartureQueryDoesNotIncludeTimeType();
    void testDepartureQueryIncludesTimeType();
    void testQueryIncludesRestrictions();
    void testRouteDepartureStation();
    void testRouteViaStation();
    void testRouteViaInvalidStation();
    void testRouteArrivalStation();
    void testRouteDepartureTimeInfo();
    void testRouteArrivalTimeInfo();
    void testRouteNumberOfEntries();
    void testRouteItemId();
    void testRouteItemDate();
    void testRouteItemDepartureTime();
    void testRouteItemDepartureTimeDelayed();
    void testRouteItemDepartureTimeDelayedZeroMinutes();
    void testRouteItemArrivalTime();
    void testRouteItemArrivalTimeDelayed();
    void testRouteItemArrivalTimeDelayedZeroMinutes();
    void testTrainTypeICandS();
    void testTrainTypeIRandIR();
    void testTrainTypeWalkOnly();
    void testTrainTypeBus();
    void testTrainTypeNightBus();
    void testTrainTypeFunicular();
    void testTrainTypeGondola();
    void testTrainTypeCableway();
    void testTrainTypeTram();
    void testTrainTypeShip();
    void testTrainTypeExcludesShortWalks();
    void testTrainTypeIncludesLongWalks();
    void testCountNoTransfers();
    void testCountSingleTransfer();
    void testShortWalksDoNotCountAsTransfers();
    void testLongWalksDoNotCountAsTransfers();
    void testCancelledRoutesSetMiscinfo();
    void testRouteItemDuration();
    void searchLaterJourneyQuery();
    void searchLaterJourneyQueryIfNoHitsWereFound();
    void searchLaterJourneyQueryStandardParameters();
    void searchLaterJourneyQueryAfterArrivalSearch();
    void searchLaterJourneyQueryAroundMidnight();
    void searchLaterJourneyQueryStartsAfterLastResult();
    void searchLaterJourneyQueryStartsAnHourAfterLastSearchIfNoHits();
    void searchEarlierJourneyQuery();
    void searchEarlierJourneyQueryIfNoHitsWereFound();
    void searchEarlierJourneyQueryStandardParameters();
    void searchEarlierJourneyQueryAfterDepartureSearch();
    void searchEarlierJourneyQueryAroundMidnight();
    void searchEarlierJourneyQueryStartsBeforeFirstResult();
    void searchEarlierJourneyQueryStartsAnHourBeforeLastSearchIfNoHits();
    void rememberLastJourneySearchRestrictions();
    void rememberLastJourneySearchSingleHit();
    void rememberLastJourneySearchMultipleHits();
    void rememberLastJourneySearchNoHits();
    void clearLastJourneySearchResult();
};

#endif
