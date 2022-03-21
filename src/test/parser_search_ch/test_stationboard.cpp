#include <iostream>

#include <QObject>
#include <QtTest/QtTest>

#include "../../parser/parser_search_ch.h"

#include "search_ch_tester.h"
#include "test_stationboard.h"

void SearchCHStationboardTest::loadMultipleEntries()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/stationboard-with-delays-and-cancelations.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseTimetable(&f);

    QVERIFY(!p->error);
    QCOMPARE(p->timetable.length(), 11);
    QCOMPARE(p->timetable[0].destinationStation, QString("Chur"));
    QCOMPARE(p->timetable[0].time, QTime(21, 38));
    QCOMPARE(p->timetable[1].destinationStation, QString("Aarau"));
    QCOMPARE(p->timetable[1].time, QTime(21, 38));
    QCOMPARE(p->timetable[2].destinationStation, QString("St. Gallen"));
    QCOMPARE(p->timetable[2].time, QTime(21, 39));
    QCOMPARE(p->timetable[3].destinationStation, QString("Rapperswil SG"));
    QCOMPARE(p->timetable[3].time, QTime(21, 39));
    QCOMPARE(p->timetable[4].destinationStation, QString("Schlieren"));
    QCOMPARE(p->timetable[4].time, QTime(21, 39));
    QCOMPARE(p->timetable[5].destinationStation, QString("Feldkirch"));
    QCOMPARE(p->timetable[5].time, QTime(21, 40));
    QCOMPARE(p->timetable[7].destinationStation, QString("Hinwil"));
    QCOMPARE(p->timetable[7].time, QTime(21, 42));
    QCOMPARE(p->timetable[9].destinationStation, QString("Brugg AG"));
    QCOMPARE(p->timetable[9].time, QTime(21, 44));
    QCOMPARE(p->timetable[10].destinationStation,QString("Effretikon"));
    QCOMPARE(p->timetable[10].time, QTime(21, 44));

    delete p;
}

void SearchCHStationboardTest::loadTypeExpressTrain()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/stationboard-with-delays-and-cancelations.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseTimetable(&f);

    QVERIFY(!p->error);
    QVERIFY(p->timetable.length() >= 1);
    QCOMPARE(p->timetable[0].destinationStation, QString("Chur"));
    QCOMPARE(p->timetable[0].time, QTime(21, 38));
    QCOMPARE(p->timetable[0].trainType, QString("IC 3"));

    delete p;
}

void SearchCHStationboardTest::loadTypeSTrain()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/stationboard-with-delays-and-cancelations.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseTimetable(&f);

    QVERIFY(!p->error);
    QVERIFY(p->timetable.length() >= 5);
    QCOMPARE(p->timetable[4].destinationStation, QString("Schlieren"));
    QCOMPARE(p->timetable[4].time, QTime(21, 39));
    QCOMPARE(p->timetable[4].trainType, QString("S5"));

    delete p;
}

void SearchCHStationboardTest::loadTypeTrain()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/stationboard-martigny-with-train.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseTimetable(&f);

    QVERIFY(!p->error);
    QVERIFY(p->timetable.length() >= 4);
    QCOMPARE(p->timetable[3].time, QTime(5, 18));
    QCOMPARE(p->timetable[3].trainType, QString("R"));

    delete p;
}

void SearchCHStationboardTest::loadTypeBus()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/stationboard-zytglogge-with-bus-and-tram.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseTimetable(&f);

    QVERIFY(!p->error);
    QVERIFY(p->timetable.length() >= 4);
    QCOMPARE(p->timetable[3].destinationStation, QString("Spiegel, Blinzern"));
    QCOMPARE(p->timetable[3].time, QTime(22, 22));
    QCOMPARE(p->timetable[3].trainType, QString("Bus 19"));

    delete p;
}

void SearchCHStationboardTest::loadTypeTram()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/stationboard-zytglogge-with-bus-and-tram.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseTimetable(&f);

    QVERIFY(!p->error);
    QVERIFY(p->timetable.length() >= 2);
    QCOMPARE(p->timetable[1].destinationStation, QString("Bern, Ostring"));
    QCOMPARE(p->timetable[1].time, QTime(22, 21));
    QCOMPARE(p->timetable[1].trainType, QString("Tram 7"));

    delete p;
}

void SearchCHStationboardTest::loadTypePostauto()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/stationboard-mittelstrasse-with-bus-and-postauto.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseTimetable(&f);

    QVERIFY(!p->error);
    QVERIFY(p->timetable.length() >= 4);
    QCOMPARE(p->timetable[3].destinationStation, QString("Uettligen, Dorf"));
    QCOMPARE(p->timetable[3].time, QTime(22, 37));
    QCOMPARE(p->timetable[3].trainType, QString("Bus 107"));

    delete p;
}

void SearchCHStationboardTest::loadTypeShipWithNoLine()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/stationboard-beckenried.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseTimetable(&f);

    QVERIFY(!p->error);
    QVERIFY(p->timetable.length() >= 1);
    QCOMPARE(p->timetable[0].destinationStation, QString("Brunnen (See)"));
    QCOMPARE(p->timetable[0].time, QTime(10, 27));
    QCOMPARE(p->timetable[0].trainType, QString("Ship"));

    delete p;
}

void SearchCHStationboardTest::loadTypeCablecarWithNoLine()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/stationboard-klewenalpbahn.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseTimetable(&f);

    QVERIFY(!p->error);
    QVERIFY(p->timetable.length() >= 1);
    QCOMPARE(p->timetable[0].destinationStation, QString("Klewenalp"));
    QCOMPARE(p->timetable[0].time, QTime(8, 5));
    QCOMPARE(p->timetable[0].trainType, QString("Cablecar"));

    delete p;
}

void SearchCHStationboardTest::loadTypeFunicularWithNoLine()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/stationboard-polyterrasse.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseTimetable(&f);

    QVERIFY(!p->error);
    QVERIFY(p->timetable.length() >= 1);
    QCOMPARE(p->timetable[0].time, QTime(6, 30));
    QCOMPARE(p->timetable[0].trainType, QString("Funicular"));

    delete p;
}

void SearchCHStationboardTest::loadTypeGondolaWithNoLine()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/stationboard-hasliberg-twing.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseTimetable(&f);

    QVERIFY(!p->error);
    QVERIFY(p->timetable.length() >= 1);
    QCOMPARE(p->timetable[0].time, QTime(8, 0));
    QCOMPARE(p->timetable[0].trainType, QString("Gondola"));

    delete p;
}

void SearchCHStationboardTest::loadCoordinates()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/stationboard-hasliberg-twing.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseTimetable(&f);

    QVERIFY(!p->error);
    QVERIFY(p->timetable.length() >= 1);
    QCOMPARE(p->timetable[0].latitude, 46.745182);
    QCOMPARE(p->timetable[0].longitude, 8.195055);

    delete p;
}

void SearchCHStationboardTest::loadCoordinatesNoLongitude()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/stationboard-hasliberg-twing-no-longitude.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseTimetable(&f);

    QVERIFY(!p->error);
    QVERIFY(p->timetable.length() >= 1);
    QCOMPARE(p->timetable[0].latitude, 0.0);
    QCOMPARE(p->timetable[0].longitude, 0.0);

    delete p;
}

void SearchCHStationboardTest::loadCoordinatesNoLatitude()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/stationboard-hasliberg-twing-no-latitude.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseTimetable(&f);

    QVERIFY(!p->error);
    QVERIFY(p->timetable.length() >= 1);
    QCOMPARE(p->timetable[0].latitude, 0.0);
    QCOMPARE(p->timetable[0].longitude, 0.0);

    delete p;
}

void SearchCHStationboardTest::loadPlatform()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/stationboard-aarau-with-tracks.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseTimetable(&f);

    QVERIFY(!p->error);
    QVERIFY(p->timetable.length() >= 3);
    QCOMPARE(p->timetable[0].platform, QString("3"));
    QCOMPARE(p->timetable[0].currentStation, QString(""));
    QCOMPARE(p->timetable[1].platform, QString("1"));
    QCOMPARE(p->timetable[1].currentStation, QString(""));
    QCOMPARE(p->timetable[2].platform, QString("5"));
    QCOMPARE(p->timetable[2].currentStation, QString(""));

    delete p;
}

void SearchCHStationboardTest::loadNoPlatformSetsCurrentStation()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/stationboard-hasliberg-twing.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseTimetable(&f);

    QVERIFY(!p->error);
    QVERIFY(p->timetable.length() >= 1);
    QCOMPARE(p->timetable[0].platform, QString(""));
    QCOMPARE(p->timetable[0].currentStation,
            QString("Hasliberg Twing (Gondelbahn)"));

    delete p;
}

void SearchCHStationboardTest::loadConnectionWithDelay()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/stationboard-with-delays-and-cancelations.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseTimetable(&f);

    QVERIFY(!p->error);
    QVERIFY(p->timetable.length() >= 4);
    QCOMPARE(p->timetable[3].miscInfo, QString("Departure delayed: +1'"));

    delete p;
}

void SearchCHStationboardTest::ignoreDelayZeroMinutes()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/stationboard-with-delays-and-cancelations.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseTimetable(&f);

    QVERIFY(!p->error);
    QVERIFY(p->timetable.length() >= 1);
    QCOMPARE(p->timetable[0].miscInfo, QString(""));

    delete p;
}

void SearchCHStationboardTest::loadCancelledConnection()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/stationboard-with-delays-and-cancelations.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseTimetable(&f);

    QVERIFY(!p->error);
    QVERIFY(p->timetable.length() >= 3);
    QCOMPARE(p->timetable[2].miscInfo, QString("Cancelled"));

    delete p;
}

void SearchCHStationboardTest::invalidResult()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/invalid.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseTimetable(&f);

    QVERIFY(p->error);
    QCOMPARE(p->errorMsg, QString("Cannot parse reply from the server"));
    QCOMPARE(p->timetable.length(), 0);

    delete p;
}

QTEST_MAIN(SearchCHStationboardTest)
