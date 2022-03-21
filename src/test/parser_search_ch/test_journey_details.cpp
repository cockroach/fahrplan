#include <iostream>

#include <QObject>
#include <QtTest/QtTest>

#include "../../parser/parser_search_ch.h"

#include "search_ch_tester.h"
#include "test_journey_details.h"

void SearchCHJourneyDetailsTest::testDetailsId()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-bern-aarau.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QVERIFY(p->getLastSearchNumberOfHits() >= 3);

    JourneyDetailResultList *hit = p->getSearchResult(0);
    QCOMPARE(hit->id(), QString("0"));

    hit = p->getSearchResult(1);
    QCOMPARE(hit->id(), QString("1"));

    hit = p->getSearchResult(2);
    QCOMPARE(hit->id(), QString("2"));

    delete p;
}

void SearchCHJourneyDetailsTest::testDetailsDepartureStationIsFromLastSearch()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-bern-aarau.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    Station s;
    s.name = "Lugano";
    p->setLastStationFrom(s);

    p->doParseSearchJourney(&f);
    QVERIFY(p->getLastSearchNumberOfHits() >= 3);

    JourneyDetailResultList *hit = p->getSearchResult(0);
    QCOMPARE(hit->departureStation(), QString("Lugano"));

    hit = p->getSearchResult(1);
    QCOMPARE(hit->departureStation(), QString("Lugano"));

    hit = p->getSearchResult(2);
    QCOMPARE(hit->departureStation(), QString("Lugano"));

    delete p;
}

void SearchCHJourneyDetailsTest::testDetailsArrivalStationIsFromLastSearch()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-bern-aarau.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    Station s;
    s.name = "Vevey";
    p->setLastStationTo(s);

    p->doParseSearchJourney(&f);
    QVERIFY(p->getLastSearchNumberOfHits() >= 3);

    JourneyDetailResultList *hit = p->getSearchResult(0);
    QCOMPARE(hit->arrivalStation(), QString("Vevey"));

    hit = p->getSearchResult(1);
    QCOMPARE(hit->arrivalStation(), QString("Vevey"));

    hit = p->getSearchResult(2);
    QCOMPARE(hit->arrivalStation(), QString("Vevey"));

    delete p;
}

void SearchCHJourneyDetailsTest::testDetailsViaStationIsFromLastSearch()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-bern-aarau.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    Station s;
    s.name = "Turgi";
    p->setLastStationVia(s);

    p->doParseSearchJourney(&f);
    QVERIFY(p->getLastSearchNumberOfHits() >= 3);

    JourneyDetailResultList *hit = p->getSearchResult(0);
    QCOMPARE(hit->viaStation(), QString("Turgi"));

    hit = p->getSearchResult(1);
    QCOMPARE(hit->viaStation(), QString("Turgi"));

    hit = p->getSearchResult(2);
    QCOMPARE(hit->viaStation(), QString("Turgi"));

    delete p;
}

void SearchCHJourneyDetailsTest::testDetailsViaStationEmpty()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-bern-aarau.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QVERIFY(p->getLastSearchNumberOfHits() >= 3);

    JourneyDetailResultList *hit = p->getSearchResult(0);
    QCOMPARE(hit->viaStation(), QString(""));

    hit = p->getSearchResult(1);
    QCOMPARE(hit->viaStation(), QString(""));

    hit = p->getSearchResult(2);
    QCOMPARE(hit->viaStation(), QString(""));

    delete p;
}

void SearchCHJourneyDetailsTest::testDetailsDuration()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-bern-aarau.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QVERIFY(p->getLastSearchNumberOfHits() >= 3);

    JourneyDetailResultList *hit = p->getSearchResult(0);
    QCOMPARE(hit->duration(), QString("0:53"));

    hit = p->getSearchResult(1);
    QCOMPARE(hit->duration(), QString("1:04"));

    hit = p->getSearchResult(2);
    QCOMPARE(hit->duration(), QString("0:56"));

    delete p;
}

void SearchCHJourneyDetailsTest::testDetailsDepartureTime()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-bern-aarau.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QVERIFY(p->getLastSearchNumberOfHits() >= 3);

    JourneyDetailResultList *hit = p->getSearchResult(0);
    QCOMPARE(hit->departureDateTime(),
            QDateTime(QDate(2022, 3, 27), QTime(6, 4)));

    hit = p->getSearchResult(1);
    QCOMPARE(hit->departureDateTime(),
            QDateTime(QDate(2022, 3, 27), QTime(6, 7)));

    hit = p->getSearchResult(2);
    QCOMPARE(hit->departureDateTime(),
            QDateTime(QDate(2022, 3, 27), QTime(6, 36)));

    delete p;
}

void SearchCHJourneyDetailsTest::testDetailsArrivalTime()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-bern-aarau.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QVERIFY(p->getLastSearchNumberOfHits() >= 3);

    JourneyDetailResultList *hit = p->getSearchResult(0);
    QCOMPARE(hit->arrivalDateTime(),
            QDateTime(QDate(2022, 3, 27), QTime(6, 57)));

    hit = p->getSearchResult(1);
    QCOMPARE(hit->arrivalDateTime(),
            QDateTime(QDate(2022, 3, 27), QTime(7, 11)));

    hit = p->getSearchResult(2);
    QCOMPARE(hit->arrivalDateTime(),
            QDateTime(QDate(2022, 3, 27), QTime(7, 32)));

    delete p;
}

void SearchCHJourneyDetailsTest::testJourneyWithSingleSegment()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-bus.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QVERIFY(p->getLastSearchNumberOfHits() >= 1);

    JourneyDetailResultList *hit = p->getSearchResult(0);
    QCOMPARE(hit->itemcount(), qreal(1));

    JourneyDetailResultItem *segment = hit->getItem(0);
    QCOMPARE(segment->departureStation(), QString("Aarau, Bahnhof"));
    QCOMPARE(segment->direction(), QString("Kreuz"));
    QCOMPARE(segment->departureInfo(), QString("Track B"));
    QCOMPARE(segment->train(), QString("Bus 1"));
    QCOMPARE(segment->arrivalStation(), QString("Aarau, Holzmarkt"));
    QCOMPARE(segment->departureDateTime(),
            QDateTime(QDate(2022, 4, 2), QTime(11, 49)));
    QCOMPARE(segment->arrivalDateTime(),
            QDateTime(QDate(2022, 4, 2), QTime(11, 51)));

    delete p;
}

void SearchCHJourneyDetailsTest::testJourneyWithMultipleSegments()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-bern-aarau.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QVERIFY(p->getLastSearchNumberOfHits() >= 1);

    JourneyDetailResultList *hit = p->getSearchResult(0);
    QCOMPARE(hit->itemcount(), qreal(2));

    JourneyDetailResultItem *segment = hit->getItem(0);
    QCOMPARE(segment->departureStation(), QString("Bern"));
    QCOMPARE(segment->arrivalStation(), QString("Olten"));
    QCOMPARE(segment->direction(), QString("Basel SBB"));
    QCOMPARE(segment->departureInfo(), QString("Track 5"));
    QCOMPARE(segment->arrivalInfo(), QString("Track 7"));
    QCOMPARE(segment->train(), QString("IC 61"));
    QCOMPARE(segment->departureDateTime(),
            QDateTime(QDate(2022, 3, 27), QTime(6, 4)));
    QCOMPARE(segment->arrivalDateTime(),
            QDateTime(QDate(2022, 3, 27), QTime(6, 43)));

    segment = hit->getItem(1);
    QCOMPARE(segment->departureStation(), QString("Olten"));
    QCOMPARE(segment->arrivalStation(), QString("Aarau"));
    QCOMPARE(segment->direction(), QString("Turgi"));
    QCOMPARE(segment->departureInfo(), QString("Track 8"));
    QCOMPARE(segment->arrivalInfo(), QString("Track 3"));
    QCOMPARE(segment->train(), QString("S29"));
    QCOMPARE(segment->departureDateTime(),
            QDateTime(QDate(2022, 3, 27), QTime(6, 49)));
    QCOMPARE(segment->arrivalDateTime(),
            QDateTime(QDate(2022, 3, 27), QTime(6, 57)));

    delete p;
}

void SearchCHJourneyDetailsTest::testSegmentByBus()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-bus.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QVERIFY(p->getLastSearchNumberOfHits() >= 1);

    JourneyDetailResultList *hit = p->getSearchResult(0);
    QCOMPARE(hit->itemcount(), qreal(1));

    JourneyDetailResultItem *segment = hit->getItem(0);
    QCOMPARE(segment->train(), QString("Bus 1"));

    delete p;
}

void SearchCHJourneyDetailsTest::testSegmentByBusThatHasLineSetToBus()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-bus-bus.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QVERIFY(p->getLastSearchNumberOfHits() >= 1);

    JourneyDetailResultList *hit = p->getSearchResult(0);
    QCOMPARE(hit->itemcount(), qreal(1));

    JourneyDetailResultItem *segment = hit->getItem(0);
    QCOMPARE(segment->train(), QString("Bus"));

    delete p;
}

void SearchCHJourneyDetailsTest::testSegmentByPostauto()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-postauto.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QVERIFY(p->getLastSearchNumberOfHits() >= 1);

    JourneyDetailResultList *hit = p->getSearchResult(0);
    QCOMPARE(hit->itemcount(), qreal(1));

    JourneyDetailResultItem *segment = hit->getItem(0);
    QCOMPARE(segment->train(), QString("Bus 135"));

    delete p;
}

void SearchCHJourneyDetailsTest::testSegmentByNightBus()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-night-bus-2.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QVERIFY(p->getLastSearchNumberOfHits() >= 2);

    JourneyDetailResultList *hit = p->getSearchResult(1);
    QVERIFY(hit->itemcount() >= 2);

    JourneyDetailResultItem *segment = hit->getItem(1);
    QCOMPARE(segment->train(), QString("Bus N1"));

    delete p;
}

void SearchCHJourneyDetailsTest::testSegmentByTram()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-walk-and-tram.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QVERIFY(p->getLastSearchNumberOfHits() >= 2);

    JourneyDetailResultList *hit = p->getSearchResult(1);
    QVERIFY(hit->itemcount() >= 1);

    JourneyDetailResultItem *segment = hit->getItem(0);
    QCOMPARE(segment->train(), QString("Tram 8"));

    delete p;
}

void SearchCHJourneyDetailsTest::testSegmentByNightSTrain()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-night-strain.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QVERIFY(p->getLastSearchNumberOfHits() >= 1);

    JourneyDetailResultList *hit = p->getSearchResult(0);
    QCOMPARE(hit->itemcount(), qreal(1));

    JourneyDetailResultItem *segment = hit->getItem(0);
    QCOMPARE(segment->train(), QString("SN8"));

    delete p;
}

void SearchCHJourneyDetailsTest::testSegmentBySTrain()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-bern-aarau.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QVERIFY(p->getLastSearchNumberOfHits() >= 1);

    JourneyDetailResultList *hit = p->getSearchResult(0);
    QCOMPARE(hit->itemcount(), qreal(2));

    JourneyDetailResultItem *segment = hit->getItem(1);
    QCOMPARE(segment->train(), QString("S29"));

    delete p;
}

void SearchCHJourneyDetailsTest::testSegmentByExpressTrain()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-bern-aarau.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QVERIFY(p->getLastSearchNumberOfHits() >= 1);

    JourneyDetailResultList *hit = p->getSearchResult(0);
    QCOMPARE(hit->itemcount(), qreal(2));

    JourneyDetailResultItem *segment = hit->getItem(0);
    QCOMPARE(segment->train(), QString("IC 61"));

    delete p;
}

void SearchCHJourneyDetailsTest::testSegmentWithoutLine()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-funicular.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QVERIFY(p->getLastSearchNumberOfHits() >= 1);

    JourneyDetailResultList *hit = p->getSearchResult(0);
    QCOMPARE(hit->itemcount(), qreal(1));

    JourneyDetailResultItem *segment = hit->getItem(0);
    QCOMPARE(segment->train(), QString("Bergbahn"));

    delete p;
}

void SearchCHJourneyDetailsTest::testSegmentWithoutArrivalTrackInfo()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-bus.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QVERIFY(p->getLastSearchNumberOfHits() >= 1);

    JourneyDetailResultList *hit = p->getSearchResult(0);
    QCOMPARE(hit->itemcount(), qreal(1));

    JourneyDetailResultItem *segment = hit->getItem(0);
    QCOMPARE(segment->departureStation(), QString("Aarau, Bahnhof"));
    QCOMPARE(segment->direction(), QString("Kreuz"));
    QCOMPARE(segment->departureInfo(), QString("Track B"));
    QCOMPARE(segment->train(), QString("Bus 1"));
    QCOMPARE(segment->arrivalStation(), QString("Aarau, Holzmarkt"));
    QCOMPARE(segment->arrivalInfo(), QString(""));
    QCOMPARE(segment->departureDateTime(),
            QDateTime(QDate(2022, 4, 2), QTime(11, 49)));
    QCOMPARE(segment->arrivalDateTime(),
            QDateTime(QDate(2022, 4, 2), QTime(11, 51)));

    delete p;
}

void SearchCHJourneyDetailsTest::testSegmentWithoutDepartureTrackInfo()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-funicular.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QVERIFY(p->getLastSearchNumberOfHits() >= 1);

    JourneyDetailResultList *hit = p->getSearchResult(0);
    QCOMPARE(hit->itemcount(), qreal(1));

    JourneyDetailResultItem *segment = hit->getItem(0);
    QCOMPARE(segment->departureInfo(), QString(""));
    QCOMPARE(segment->train(), QString("Bergbahn"));
    QCOMPARE(segment->departureDateTime(),
            QDateTime(QDate(2022, 4, 2), QTime(11, 45)));

    delete p;
}

void SearchCHJourneyDetailsTest::testCancelledSegment()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-cancellation-and-delays.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QVERIFY(p->getLastSearchNumberOfHits() >= 2);

    JourneyDetailResultList *hit = p->getSearchResult(1);
    QVERIFY(hit->itemcount() >= 1);

    JourneyDetailResultItem *segment = hit->getItem(0);
    QCOMPARE(segment->departureStation(), QString("Bern"));
    QCOMPARE(segment->info(), QString("Train cancelled"));

    delete p;
}

void SearchCHJourneyDetailsTest::testSegmentWithZeroDepartureDelay()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-cancellation-and-delays.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QVERIFY(p->getLastSearchNumberOfHits() >= 1);

    JourneyDetailResultList *hit = p->getSearchResult(0);
    QVERIFY(hit->itemcount() >= 1);

    JourneyDetailResultItem *segment = hit->getItem(0);
    QCOMPARE(segment->departureStation(), QString("Bern"));
    QCOMPARE(segment->info(), QString(""));

    delete p;
}

void SearchCHJourneyDetailsTest::testSegmentWithDepartureDelay()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/route-with-cancellation-and-delays.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseSearchJourney(&f);
    QVERIFY(p->getLastSearchNumberOfHits() >= 4);

    JourneyDetailResultList *hit = p->getSearchResult(3);
    QVERIFY(hit->itemcount() >= 1);

    JourneyDetailResultItem *segment = hit->getItem(0);
    QCOMPARE(segment->departureStation(), QString("Bern"));
    QCOMPARE(segment->info(), QString("Departure delayed: +1'"));

    delete p;
}

#ifdef BUILD_FOR_QT5
QTEST_GUILESS_MAIN(SearchCHJourneyDetailsTest)
#else
QTEST_MAIN(SearchCHJourneyDetailsTest)
#endif
