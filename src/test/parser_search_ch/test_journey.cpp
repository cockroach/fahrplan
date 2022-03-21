#include <iostream>

#include <QObject>
#include <QtTest/QtTest>

#include "../../parser/parser_search_ch.h"

#include "search_ch_tester.h"
#include "test_journey.h"

void SearchCHJourneyTest::testQueryURL()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    Station st;
    p->doSearchJourney(st, st, st, QDateTime(), ParserAbstract::Arrival, 0);

    QCOMPARE(p->lastURL.scheme(), QString("http"));
    QCOMPARE(p->lastURL.host(), QString("timetable.search.ch"));
    QCOMPARE(p->lastURL.path(), QString("/api/route.json"));

    delete p;
}

void SearchCHJourneyTest::testQueryStationFromAndToWithoutVia()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();

    Station bern;
    bern.name = "Bern";

    Station olten;
    olten.name = "Olten";

    Station via;
    via.name = "Nowhere";
    via.valid = false;

    p->doSearchJourney(bern, via, olten, QDateTime(),
            ParserAbstract::Arrival, 0);

    QCOMPARE(p->lastQuery.queryItemValue("from"), QString("Bern"));
    QCOMPARE(p->lastQuery.queryItemValue("to"), QString("Olten"));
    QVERIFY(!p->lastQuery.hasQueryItem("via"));

    delete p;
}

void SearchCHJourneyTest::testQueryStationFromAndToWithVia()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();

    Station bern;
    bern.name = "Bern";

    Station olten;
    olten.name = "Olten";

    Station via;
    via.name = "Nowhere";

    p->doSearchJourney(bern, via, olten, QDateTime(),
            ParserAbstract::Arrival, 0);

    QCOMPARE(p->lastQuery.queryItemValue("from"), QString("Bern"));
    QCOMPARE(p->lastQuery.queryItemValue("to"), QString("Olten"));
    QCOMPARE(p->lastQuery.queryItemValue("via"), QString("Nowhere"));

    delete p;
}

void SearchCHJourneyTest::testQueryDateAndTime()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    Station st;

    QDateTime then;
    then.setMSecsSinceEpoch(1649384042000);

    p->doSearchJourney(st, st, st, then, ParserAbstract::Arrival, 0);

    QCOMPARE(p->lastQuery.queryItemValue("date"), QString("04/08/2022"));
    QCOMPARE(p->lastQuery.queryItemValue("time"), QString("04:14"));

    delete p;
}

void SearchCHJourneyTest::testQueryAsksForDelays()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    Station st;

    p->doSearchJourney(st, st, st, QDateTime(), ParserAbstract::Arrival, 0);

    QCOMPARE(p->lastQuery.queryItemValue("show_delays"), QString("1"));

    delete p;
}

void SearchCHJourneyTest::testDepartureQueryDoesNotIncludeTimeType()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    Station st;

    p->doSearchJourney(st, st, st, QDateTime(), ParserAbstract::Departure, 0);

    QVERIFY(!p->lastQuery.hasQueryItem("time_type"));

    delete p;
}

void SearchCHJourneyTest::testDepartureQueryIncludesTimeType()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    Station st;

    p->doSearchJourney(st, st, st, QDateTime(), ParserAbstract::Arrival, 0);

    QCOMPARE(p->lastQuery.queryItemValue("time_type"), QString("arrival"));

    delete p;
}

void SearchCHJourneyTest::testQueryIncludesRestrictions()
{
    Station st;
    ParserSearchCHTester *p;

    p = new ParserSearchCHTester();
    p->doSearchJourney(st, st, st, QDateTime(), ParserAbstract::Arrival, 0);
    QVERIFY(!p->lastQuery.hasQueryItem("transportation_types"));
    delete p;

    p = new ParserSearchCHTester();
    p->doSearchJourney(st, st, st, QDateTime(), ParserAbstract::Arrival, 1);
    QCOMPARE(p->lastQuery.queryItemValue("transportation_types"), QString("train"));
    delete p;

    p = new ParserSearchCHTester();
    p->doSearchJourney(st, st, st, QDateTime(), ParserAbstract::Arrival, 2);
    QCOMPARE(p->lastQuery.queryItemValue("transportation_types"), QString("tram"));
    delete p;

    p = new ParserSearchCHTester();
    p->doSearchJourney(st, st, st, QDateTime(), ParserAbstract::Arrival, 3);
    QCOMPARE(p->lastQuery.queryItemValue("transportation_types"), QString("ship"));
    delete p;

    p = new ParserSearchCHTester();
    p->doSearchJourney(st, st, st, QDateTime(), ParserAbstract::Arrival, 4);
    QCOMPARE(p->lastQuery.queryItemValue("transportation_types"), QString("bus"));
    delete p;

    p = new ParserSearchCHTester();
    p->doSearchJourney(st, st, st, QDateTime(), ParserAbstract::Arrival, 5);
    QCOMPARE(p->lastQuery.queryItemValue("transportation_types"), QString("cableway"));
    delete p;

    p = new ParserSearchCHTester();
    p->doSearchJourney(st, st, st, QDateTime(), ParserAbstract::Arrival, 6);
    QVERIFY(!p->lastQuery.hasQueryItem("transportation_types"));
    delete p;
}

void SearchCHJourneyTest::testRouteDepartureStation()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    Station st;

    QFile f("fixtures/route-bern-aarau.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    st.name = "Bern";
    p->setLastStationFrom(st);
    p->doParseSearchJourney(&f);

    QVERIFY(!p->error);
    QCOMPARE(p->journeys->departureStation(), QString("Bern"));
    delete p;
}

void SearchCHJourneyTest::testRouteViaStation()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    Station st;

    QFile f("fixtures/route-bern-aarau.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    st.name = "Fribourg";
    st.valid = true;
    p->setLastStationVia(st);
    p->doParseSearchJourney(&f);

    QVERIFY(!p->error);
    QCOMPARE(p->journeys->viaStation(), QString("Fribourg"));
    delete p;
}

void SearchCHJourneyTest::testRouteViaInvalidStation()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    Station st;

    QFile f("fixtures/route-bern-aarau.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    st.name = "Fribourg";
    st.valid = false;
    p->setLastStationVia(st);
    p->doParseSearchJourney(&f);

    QVERIFY(!p->error);
    QCOMPARE(p->journeys->viaStation(), QString(""));
    delete p;
}

void SearchCHJourneyTest::testRouteArrivalStation()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    Station st;

    QFile f("fixtures/route-bern-aarau.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    st.name = "Aarau";
    p->setLastStationTo(st);
    p->doParseSearchJourney(&f);

    QVERIFY(!p->error);
    QCOMPARE(p->journeys->arrivalStation(), QString("Aarau"));
    delete p;
}

void SearchCHJourneyTest::testRouteDepartureTimeInfo()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QDateTime then;
    then.setMSecsSinceEpoch(1648346918000);

    QFile f("fixtures/route-bern-aarau.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->setLastSearchTime(then);
    p->setLastSearchMode(ParserAbstract::Departure);
    p->doParseSearchJourney(&f);

    QVERIFY(!p->error);
    QCOMPARE(p->journeys->timeInfo(), QString("Departures Sun Mar 27, 04:08"));
    delete p;
}

void SearchCHJourneyTest::testRouteArrivalTimeInfo()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QDateTime then;
    then.setMSecsSinceEpoch(1648346918000);

    QFile f("fixtures/route-bern-aarau.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->setLastSearchTime(then);
    p->setLastSearchMode(ParserAbstract::Arrival);
    p->doParseSearchJourney(&f);

    QVERIFY(!p->error);
    QCOMPARE(p->journeys->timeInfo(), QString("Arrivals Sun Mar 27, 04:08"));
    delete p;
}

void SearchCHJourneyTest::testRouteNumberOfEntries()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-bern-aarau.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);

    QVERIFY(!p->error);
    QCOMPARE(p->journeys->itemcount(), qreal(8));

    delete p;
}

void SearchCHJourneyTest::testRouteItemId()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-bern-aarau.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);

    QVERIFY(!p->error);
    QCOMPARE(p->journeys->itemcount(), qreal(8));

    JourneyResultItem *row = p->journeys->getItem(0);
    QCOMPARE(row->id(), QString("0"));

    row = p->journeys->getItem(1);
    QCOMPARE(row->id(), QString("1"));

    row = p->journeys->getItem(2);
    QCOMPARE(row->id(), QString("2"));

    row = p->journeys->getItem(3);
    QCOMPARE(row->id(), QString("3"));

    row = p->journeys->getItem(4);
    QCOMPARE(row->id(), QString("4"));

    row = p->journeys->getItem(5);
    QCOMPARE(row->id(), QString("5"));

    row = p->journeys->getItem(6);
    QCOMPARE(row->id(), QString("6"));

    row = p->journeys->getItem(7);
    QCOMPARE(row->id(), QString("7"));

    delete p;
}

void SearchCHJourneyTest::testRouteItemDate()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-bern-aarau.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);

    QVERIFY(!p->error);
    QVERIFY(p->journeys->itemcount() >= 1);

    JourneyResultItem *row = p->journeys->getItem(0);
    QCOMPARE(row->date(), QDate(2022, 3, 27));

    delete p;
}

void SearchCHJourneyTest::testRouteItemDepartureTime()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-bern-aarau.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);

    QVERIFY(!p->error);
    QVERIFY(p->journeys->itemcount() >= 1);

    JourneyResultItem *row = p->journeys->getItem(0);
    QCOMPARE(row->departureTime(), QString("06:04"));

    delete p;
}

void SearchCHJourneyTest::testRouteItemDepartureTimeDelayed()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-delays.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);

    QVERIFY(!p->error);
    QVERIFY(p->journeys->itemcount() >= 1);

    JourneyResultItem *row = p->journeys->getItem(0);
    QCOMPARE(row->departureTime(), QString("03:59 +1'"));

    delete p;
}

void SearchCHJourneyTest::testRouteItemDepartureTimeDelayedZeroMinutes()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-delays.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);

    QVERIFY(!p->error);
    QVERIFY(p->journeys->itemcount() >= 2);

    JourneyResultItem *row = p->journeys->getItem(1);
    QCOMPARE(row->departureTime(), QString("04:31"));

    delete p;
}

void SearchCHJourneyTest::testRouteItemArrivalTime()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-bern-aarau.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);

    QVERIFY(!p->error);
    QVERIFY(p->journeys->itemcount() >= 1);

    JourneyResultItem *row = p->journeys->getItem(0);
    QCOMPARE(row->arrivalTime(), QString("06:57"));

    delete p;
}

void SearchCHJourneyTest::testRouteItemArrivalTimeDelayed()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-delays.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);

    QVERIFY(!p->error);
    QVERIFY(p->journeys->itemcount() >= 1);

    JourneyResultItem *row = p->journeys->getItem(0);
    QCOMPARE(row->arrivalTime(), QString("05:28 +2'"));

    delete p;
}

void SearchCHJourneyTest::testRouteItemArrivalTimeDelayedZeroMinutes()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-delays.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);

    QVERIFY(!p->error);
    QVERIFY(p->journeys->itemcount() >= 1);

    JourneyResultItem *row = p->journeys->getItem(1);
    QCOMPARE(row->arrivalTime(), QString("06:06"));

    delete p;
}

void SearchCHJourneyTest::testTrainTypeICandS()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-bern-aarau.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);

    QVERIFY(!p->error);
    QVERIFY(p->journeys->itemcount() >= 1);

    JourneyResultItem *row = p->journeys->getItem(0);
    QCOMPARE(row->trainType(), QString("IC S"));

    delete p;
}

void SearchCHJourneyTest::testTrainTypeIRandIR()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-bern-aarau.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);

    QVERIFY(!p->error);
    QVERIFY(p->journeys->itemcount() >= 2);

    JourneyResultItem *row = p->journeys->getItem(1);
    QCOMPARE(row->trainType(), QString("IR"));

    delete p;
}

void SearchCHJourneyTest::testTrainTypeWalkOnly()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-walk-and-tram.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);

    QVERIFY(!p->error);
    QVERIFY(p->journeys->itemcount() >= 1);

    JourneyResultItem *row = p->journeys->getItem(0);
    QCOMPARE(row->trainType(), QString("Walk"));

    delete p;
}

void SearchCHJourneyTest::testTrainTypeBus()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-bus.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);

    QVERIFY(!p->error);
    QVERIFY(p->journeys->itemcount() >= 1);

    JourneyResultItem *row = p->journeys->getItem(0);
    QCOMPARE(row->trainType(), QString("Bus"));

    delete p;
}

void SearchCHJourneyTest::testTrainTypeNightBus()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-night-bus.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);

    QVERIFY(!p->error);
    QVERIFY(p->journeys->itemcount() >= 1);

    JourneyResultItem *row = p->journeys->getItem(0);
    QCOMPARE(row->trainType(), QString("Bus"));

    delete p;
}

void SearchCHJourneyTest::testTrainTypeFunicular()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-funicular.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);

    QVERIFY(!p->error);
    QVERIFY(p->journeys->itemcount() >= 1);

    JourneyResultItem *row = p->journeys->getItem(0);
    QCOMPARE(row->trainType(), QString("Funi"));

    delete p;
}

void SearchCHJourneyTest::testTrainTypeGondola()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-gondola.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);

    QVERIFY(!p->error);
    QVERIFY(p->journeys->itemcount() >= 1);

    JourneyResultItem *row = p->journeys->getItem(0);
    QCOMPARE(row->trainType(), QString("Gondola"));

    delete p;
}

void SearchCHJourneyTest::testTrainTypeCableway()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-cableway.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);

    QVERIFY(!p->error);
    QVERIFY(p->journeys->itemcount() >= 1);

    JourneyResultItem *row = p->journeys->getItem(0);
    QCOMPARE(row->trainType(), QString("Cableway"));

    delete p;
}

void SearchCHJourneyTest::testTrainTypeTram()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-walk-and-tram.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);

    QVERIFY(!p->error);
    QVERIFY(p->journeys->itemcount() >= 2);

    JourneyResultItem *row = p->journeys->getItem(1);
    QCOMPARE(row->trainType(), QString("Tram"));

    delete p;
}

void SearchCHJourneyTest::testTrainTypeShip()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-ship.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);

    QVERIFY(!p->error);
    QVERIFY(p->journeys->itemcount() >= 1);

    JourneyResultItem *row = p->journeys->getItem(0);
    QCOMPARE(row->trainType(), QString("Ship"));

    delete p;
}

void SearchCHJourneyTest::testTrainTypeExcludesShortWalks()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-short-walks.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);

    QVERIFY(!p->error);
    QVERIFY(p->journeys->itemcount() >= 1);

    JourneyResultItem *row = p->journeys->getItem(0);
    QCOMPARE(row->trainType(), QString("Tram IC"));

    delete p;
}

void SearchCHJourneyTest::testTrainTypeIncludesLongWalks()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-long-walk.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);

    QVERIFY(!p->error);
    QVERIFY(p->journeys->itemcount() >= 1);

    JourneyResultItem *row = p->journeys->getItem(0);
    QCOMPARE(row->trainType(), QString("Walk IR S"));

    delete p;
}

void SearchCHJourneyTest::testRouteItemDuration()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-bern-aarau.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);

    QVERIFY(!p->error);
    QVERIFY(p->journeys->itemcount() >= 1);

    JourneyResultItem *row = p->journeys->getItem(0);
    QCOMPARE(row->duration(), QString("0:53"));

    delete p;
}

void SearchCHJourneyTest::testCountNoTransfers()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-funicular.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);

    QVERIFY(!p->error);
    QVERIFY(p->journeys->itemcount() >= 1);

    JourneyResultItem *row = p->journeys->getItem(0);
    QCOMPARE(row->transfers(), QString("0"));

    delete p;
}

void SearchCHJourneyTest::testCountSingleTransfer()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-bern-aarau.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);

    QVERIFY(!p->error);
    QVERIFY(p->journeys->itemcount() >= 1);

    JourneyResultItem *row = p->journeys->getItem(0);
    QCOMPARE(row->transfers(), QString("1"));

    delete p;
}

void SearchCHJourneyTest::testShortWalksDoNotCountAsTransfers()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-short-walks.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);

    QVERIFY(!p->error);
    QVERIFY(p->journeys->itemcount() >= 1);

    JourneyResultItem *row = p->journeys->getItem(0);
    QCOMPARE(row->transfers(), QString("2"));

    delete p;
}

void SearchCHJourneyTest::testLongWalksDoNotCountAsTransfers()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-long-walk.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);

    QVERIFY(!p->error);
    QVERIFY(p->journeys->itemcount() >= 1);

    JourneyResultItem *row = p->journeys->getItem(0);
    QCOMPARE(row->transfers(), QString("1"));

    delete p;
}

void SearchCHJourneyTest::testCancelledRoutesSetMiscinfo()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-cancellation-and-delays.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);

    QVERIFY(!p->error);
    QVERIFY(p->journeys->itemcount() >= 3);

    JourneyResultItem *row = p->journeys->getItem(0);
    QCOMPARE(row->miscInfo(), QString(""));

    row = p->journeys->getItem(1);
    QCOMPARE(row->miscInfo(), QString("Cancelled"));

    row = p->journeys->getItem(2);
    QCOMPARE(row->miscInfo(), QString(""));

    row = p->journeys->getItem(3);
    QCOMPARE(row->miscInfo(), QString(""));

    delete p;
}

void SearchCHJourneyTest::searchLaterJourneyQuery()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-bern-aarau.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QCOMPARE(p->getLastSearchNumberOfHits(), 8);

    Station bern;
    bern.name = "Bern";

    Station olten;
    olten.name = "Olten";

    Station basel;
    basel.name = "Basel";

    p->setLastStationFrom(bern);
    p->setLastStationVia(olten);
    p->setLastStationTo(basel);
    p->setLastSearchTime(QDateTime(QDate(2022, 3, 30), QTime(10, 35)));
    p->setLastSearchMode(ParserAbstract::Departure);

    p->doSearchJourneyLater();

    QCOMPARE(p->lastQuery.queryItemValue("from"), QString("Bern"));
    QCOMPARE(p->lastQuery.queryItemValue("via"), QString("Olten"));
    QCOMPARE(p->lastQuery.queryItemValue("to"), QString("Basel"));
    QCOMPARE(p->lastQuery.queryItemValue("date"), QString("03/27/2022"));
    QCOMPARE(p->lastQuery.queryItemValue("time"), QString("07:39"));
    QVERIFY(!p->lastQuery.hasQueryItem("time_type"));

    delete p;
}

void SearchCHJourneyTest::searchLaterJourneyQueryIfNoHitsWereFound()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-no-hits.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QCOMPARE(p->getLastSearchNumberOfHits(), 0);

    p->setLastSearchTime(QDateTime(QDate(2022, 3, 30), QTime(14, 20)));
    p->setLastSearchMode(ParserAbstract::Departure);

    p->doSearchJourneyLater();

    QCOMPARE(p->lastQuery.queryItemValue("date"), QString("03/30/2022"));
    QCOMPARE(p->lastQuery.queryItemValue("time"), QString("15:20"));
    QVERIFY(!p->lastQuery.hasQueryItem("time_type"));

    delete p;
}

void SearchCHJourneyTest::searchLaterJourneyQueryStandardParameters()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();

    p->setLastSearchTime(QDateTime(QDate(2022, 3, 30), QTime(10, 35)));
    p->setLastSearchMode(ParserAbstract::Departure);

    p->doSearchJourneyLater();

    QCOMPARE(p->lastQuery.queryItemValue("show_delays"), QString("1"));
    QVERIFY(!p->lastQuery.hasQueryItem("num"));

    delete p;
}

void SearchCHJourneyTest::searchLaterJourneyQueryAfterArrivalSearch()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-bern-aarau.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QCOMPARE(p->getLastSearchNumberOfHits(), 8);

    Station bern;
    bern.name = "Bern";

    Station olten;
    olten.name = "Olten";

    Station basel;
    basel.name = "Basel";

    p->setLastStationFrom(bern);
    p->setLastStationVia(olten);
    p->setLastStationTo(basel);
    p->setLastSearchTime(QDateTime(QDate(2022, 3, 30), QTime(10, 35)));
    p->setLastSearchMode(ParserAbstract::Arrival);

    p->doSearchJourneyLater();

    QCOMPARE(p->lastQuery.queryItemValue("from"), QString("Bern"));
    QCOMPARE(p->lastQuery.queryItemValue("via"), QString("Olten"));
    QCOMPARE(p->lastQuery.queryItemValue("to"), QString("Basel"));
    QCOMPARE(p->lastQuery.queryItemValue("date"), QString("03/27/2022"));
    QCOMPARE(p->lastQuery.queryItemValue("time"), QString("07:39"));
    QVERIFY(!p->lastQuery.hasQueryItem("time_type"));

    delete p;
}

void SearchCHJourneyTest::searchLaterJourneyQueryAroundMidnight()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-that-departs-shortly-before-midnight.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QCOMPARE(p->getLastSearchNumberOfHits(), 1);

    Station bern;
    bern.name = "Bern";

    Station olten;
    olten.name = "Olten";

    Station basel;
    basel.name = "Basel";

    p->setLastStationFrom(bern);
    p->setLastStationVia(olten);
    p->setLastStationTo(basel);
    p->setLastSearchTime(QDateTime(QDate(2022, 3, 30), QTime(10, 35)));
    p->setLastSearchMode(ParserAbstract::Departure);

    p->doSearchJourneyLater();

    QCOMPARE(p->lastQuery.queryItemValue("from"), QString("Bern"));
    QCOMPARE(p->lastQuery.queryItemValue("via"), QString("Olten"));
    QCOMPARE(p->lastQuery.queryItemValue("to"), QString("Basel"));
    QCOMPARE(p->lastQuery.queryItemValue("date"), QString("04/09/2022"));
    QCOMPARE(p->lastQuery.queryItemValue("time"), QString("00:00"));
    QVERIFY(!p->lastQuery.hasQueryItem("time_type"));

    delete p;
}

void SearchCHJourneyTest::searchLaterJourneyQueryStartsAfterLastResult()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-cancellation-and-delays.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QCOMPARE(p->getLastSearchNumberOfHits(), 8);

    QCOMPARE(p->journeys->itemcount(), qreal(8));
    JourneyResultItem *row = p->journeys->getItem(7);
    QCOMPARE(row->departureTime(), QString("09:07"));

    p->doSearchJourneyLater();
    QCOMPARE(p->lastQuery.queryItemValue("time"), QString("09:08"));

    delete p;
}

void SearchCHJourneyTest::searchLaterJourneyQueryStartsAnHourAfterLastSearchIfNoHits()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-no-hits.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->setLastSearchTime(QDateTime(QDate(2022, 3, 30), QTime(10, 35)));

    p->doParseSearchJourney(&f);
    QCOMPARE(p->getLastSearchNumberOfHits(), 0);

    p->doSearchJourneyLater();
    QCOMPARE(p->lastQuery.queryItemValue("time"), QString("11:35"));

    delete p;
}

void SearchCHJourneyTest::searchEarlierJourneyQuery()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-bern-aarau.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QVERIFY(!p->error);
    QVERIFY(p->journeys->itemcount() >= 1);

    Station bern;
    bern.name = "Bern";

    Station olten;
    olten.name = "Olten";

    Station basel;
    basel.name = "Basel";

    p->setLastStationFrom(bern);
    p->setLastStationVia(olten);
    p->setLastStationTo(basel);
    p->setLastSearchTime(QDateTime(QDate(2022, 3, 30), QTime(10, 35)));
    p->setLastSearchMode(ParserAbstract::Departure);
    p->setLastSearchRestrictions(14);

    p->doSearchJourneyEarlier();

    QCOMPARE(p->lastQuery.queryItemValue("from"), QString("Bern"));
    QCOMPARE(p->lastQuery.queryItemValue("via"), QString("Olten"));
    QCOMPARE(p->lastQuery.queryItemValue("to"), QString("Basel"));
    QCOMPARE(p->lastQuery.queryItemValue("date"), QString("03/27/2022"));
    QCOMPARE(p->lastQuery.queryItemValue("time"), QString("06:56"));
    QCOMPARE(p->lastQuery.queryItemValue("time_type"), QString("arrival"));

    delete p;
}

void SearchCHJourneyTest::searchEarlierJourneyQueryIfNoHitsWereFound()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-no-hits.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QVERIFY(!p->error);
    QCOMPARE(p->journeys->itemcount(), qreal(0));

    Station bern;
    bern.name = "Bern";

    Station olten;
    olten.name = "Olten";

    Station basel;
    basel.name = "Basel";

    p->setLastStationFrom(bern);
    p->setLastStationVia(olten);
    p->setLastStationTo(basel);
    p->setLastSearchTime(QDateTime(QDate(2022, 3, 30), QTime(14, 20)));
    p->setLastSearchMode(ParserAbstract::Departure);
    p->setLastSearchRestrictions(14);

    p->doSearchJourneyEarlier();

    QCOMPARE(p->lastQuery.queryItemValue("from"), QString("Bern"));
    QCOMPARE(p->lastQuery.queryItemValue("via"), QString("Olten"));
    QCOMPARE(p->lastQuery.queryItemValue("to"), QString("Basel"));
    QCOMPARE(p->lastQuery.queryItemValue("date"), QString("03/30/2022"));
    QCOMPARE(p->lastQuery.queryItemValue("time"), QString("13:20"));
    QCOMPARE(p->lastQuery.queryItemValue("time_type"), QString("arrival"));

    delete p;
}

void SearchCHJourneyTest::searchEarlierJourneyQueryStandardParameters()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    p->doSearchJourneyEarlier();

    QCOMPARE(p->lastQuery.queryItemValue("show_delays"), QString("1"));
    QVERIFY(!p->lastQuery.hasQueryItem("num"));

    delete p;
}

void SearchCHJourneyTest::searchEarlierJourneyQueryAfterDepartureSearch()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-no-hits.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QVERIFY(!p->error);
    QCOMPARE(p->journeys->itemcount(), qreal(0));

    p->setLastSearchTime(QDateTime(QDate(2022, 3, 30), QTime(10, 35)));
    p->setLastSearchMode(ParserAbstract::Departure);

    p->doSearchJourneyEarlier();

    QCOMPARE(p->lastQuery.queryItemValue("date"), QString("03/30/2022"));
    QCOMPARE(p->lastQuery.queryItemValue("time"), QString("09:35"));
    QCOMPARE(p->lastQuery.queryItemValue("time_type"), QString("arrival"));

    delete p;
}

void SearchCHJourneyTest::searchEarlierJourneyQueryAroundMidnight()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-that-arrives-at-midnight.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QVERIFY(!p->error);
    QVERIFY(p->journeys->itemcount() >= 1);

    p->setLastSearchTime(QDateTime(QDate(2022, 3, 30), QTime(10, 35)));
    p->setLastSearchMode(ParserAbstract::Departure);

    p->doSearchJourneyEarlier();

    QCOMPARE(p->lastQuery.queryItemValue("date"), QString("04/08/2022"));
    QCOMPARE(p->lastQuery.queryItemValue("time"), QString("23:59"));

    delete p;
}

void SearchCHJourneyTest::searchEarlierJourneyQueryStartsBeforeFirstResult()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-cancellation-and-delays.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QCOMPARE(p->getLastSearchNumberOfHits(), 8);

    QCOMPARE(p->journeys->itemcount(), qreal(8));
    JourneyResultItem *row = p->journeys->getItem(0);
    QCOMPARE(row->arrivalTime(), QString("08:48"));

    p->doSearchJourneyEarlier();
    QCOMPARE(p->lastQuery.queryItemValue("time"), QString("08:47"));

    delete p;
}

void SearchCHJourneyTest::searchEarlierJourneyQueryStartsAnHourBeforeLastSearchIfNoHits()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-no-hits.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->setLastSearchTime(QDateTime(QDate(2022, 3, 30), QTime(10, 35)));

    p->doParseSearchJourney(&f);
    QCOMPARE(p->getLastSearchNumberOfHits(), 0);

    p->doSearchJourneyEarlier();
    QCOMPARE(p->lastQuery.queryItemValue("time"), QString("09:35"));

    delete p;
}

void SearchCHJourneyTest::rememberLastJourneySearchRestrictions()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    p->searchJourney(Station(), Station(), Station(), QDateTime(),
                ParserAbstract::Arrival, 14);

    QCOMPARE(p->getRestrictions(), 14);

    delete p;
}

void SearchCHJourneyTest::rememberLastJourneySearchSingleHit()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-long-walk.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QCOMPARE(p->getLastSearchNumberOfHits(), 1);

    delete p;
}

void SearchCHJourneyTest::rememberLastJourneySearchMultipleHits()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-cancellation-and-delays.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QCOMPARE(p->getLastSearchNumberOfHits(), 8);

    delete p;
}

void SearchCHJourneyTest::rememberLastJourneySearchNoHits()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-no-hits.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QCOMPARE(p->getLastSearchNumberOfHits(), 0);

    delete p;
}

void SearchCHJourneyTest::clearLastJourneySearchResult()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f1("fixtures/route-with-cancellation-and-delays.json");
    QFile f2("fixtures/route-with-no-hits.json");

    QVERIFY(f1.open(QIODevice::ReadOnly));
    QVERIFY(f2.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f1);
    QCOMPARE(p->getLastSearchNumberOfHits(), 8);

    p->doParseSearchJourney(&f2);
    QCOMPARE(p->getLastSearchNumberOfHits(), 0);

    delete p;
}

#ifdef BUILD_FOR_QT5
QTEST_GUILESS_MAIN(SearchCHJourneyTest)
#else
QTEST_MAIN(SearchCHJourneyTest)
#endif
