#include <iostream>

#include <QObject>
#include <QtTest/QtTest>

#include "../../parser/parser_search_ch.h"

#include "search_ch_tester.h"
#include "test_stations.h"

void SearchCHFindStationsTest::ignoreBusinessEntries()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/stations-with-tel-business.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseStations(&f);

    QVERIFY(!p->error);
    QCOMPARE(p->stationsReceived.length(), 1);
    QCOMPARE(p->stationsReceived[0].name, QString("Basel, Bankverein"));
    QCOMPARE(p->stationsReceived[0].id.toString(),QString("Basel, Bankverein"));

    delete p;
}

void SearchCHFindStationsTest::ignoreAddressEntries()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/stations-with-bus-ship-cablecar-and-address.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseStations(&f);

    QVERIFY(!p->error);
    QCOMPARE(p->stationsReceived.length(), 8);
    QCOMPARE(p->stationsReceived[0].name, QString("Beckenried, Post"));
    QCOMPARE(p->stationsReceived[1].name, QString("Beckenried (See)"));
    QCOMPARE(p->stationsReceived[2].name, QString("Beckenried (Klewenalpbahn)"));
    QCOMPARE(p->stationsReceived[3].name, QString("Beckenried, Boden"));
    QCOMPARE(p->stationsReceived[4].name, QString("Beckenried, Nidwaldnerhof"));
    QCOMPARE(p->stationsReceived[5].name, QString("Beckenried, Hungacher"));
    QCOMPARE(p->stationsReceived[6].name, QString("Beckenried, Fellerwil"));
    QCOMPARE(p->stationsReceived[7].name, QString("Beckenried, Niederdorf"));

    delete p;
}

void SearchCHFindStationsTest::resultWithBusStop()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/stations-with-bus-ship-cablecar-and-address.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseStations(&f);

    QVERIFY(!p->error);
    QVERIFY(p->stationsReceived.length() >= 1);
    QCOMPARE(p->stationsReceived[0].name, QString("Beckenried, Post"));
    QCOMPARE(p->stationsReceived[0].id.toString(),QString("Beckenried, Post"));
    QCOMPARE(p->stationsReceived[0].miscInfo, QString("Bus stop"));

    delete p;
}

void SearchCHFindStationsTest::resultWithTramStop()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/stations-with-tel-business.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseStations(&f);

    QVERIFY(!p->error);
    QVERIFY(p->stationsReceived.length() >= 1);
    QCOMPARE(p->stationsReceived[0].name, QString("Basel, Bankverein"));
    QCOMPARE(p->stationsReceived[0].id.toString(),QString("Basel, Bankverein"));
    QCOMPARE(p->stationsReceived[0].miscInfo, QString("Tram stop"));

    delete p;
}

void SearchCHFindStationsTest::resultWithPort()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/stations-with-bus-ship-cablecar-and-address.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseStations(&f);

    QVERIFY(!p->error);
    QVERIFY(p->stationsReceived.length() >= 2);
    QCOMPARE(p->stationsReceived[1].name, QString("Beckenried (See)"));
    QCOMPARE(p->stationsReceived[1].id.toString(),QString("Beckenried (See)"));
    QCOMPARE(p->stationsReceived[1].miscInfo, QString("Port"));

    delete p;
}

void SearchCHFindStationsTest::resultWithCablecar()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/stations-with-bus-ship-cablecar-and-address.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseStations(&f);

    QVERIFY(!p->error);
    QVERIFY(p->stationsReceived.length() >= 3);
    QCOMPARE(p->stationsReceived[2].name,
            QString("Beckenried (Klewenalpbahn)"));
    QCOMPARE(p->stationsReceived[2].id.toString(),
            QString("Beckenried (Klewenalpbahn)"));
    QCOMPARE(p->stationsReceived[2].miscInfo, QString("Cablecar"));

    delete p;
}

void SearchCHFindStationsTest::resultWithTrainStation()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/stations-aarau.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseStations(&f);

    QVERIFY(!p->error);
    QVERIFY(p->stationsReceived.length() >= 1);
    QCOMPARE(p->stationsReceived[0].name, QString("Aarau"));
    QCOMPARE(p->stationsReceived[0].id.toString(), QString("Aarau"));
    QCOMPARE(p->stationsReceived[0].miscInfo, QString("Train station"));

    delete p;
}

void SearchCHFindStationsTest::resultWithSTrainStation()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/stations-aarau.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseStations(&f);

    QVERIFY(!p->error);
    QVERIFY(p->stationsReceived.length() >= 2);
    QCOMPARE(p->stationsReceived[1].name, QString("Aarau Torfeld"));
    QCOMPARE(p->stationsReceived[1].id.toString(), QString("Aarau Torfeld"));
    QCOMPARE(p->stationsReceived[1].miscInfo, QString("Train station"));

    delete p;
}

void SearchCHFindStationsTest::resultWithFunicular()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/stations-lugano.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseStations(&f);

    QVERIFY(!p->error);
    QVERIFY(p->stationsReceived.length() >= 2);
    QCOMPARE(p->stationsReceived[1].name,
            QString("Lugano Stazione (funicolare)"));
    QCOMPARE(p->stationsReceived[1].id.toString(),
            QString("Lugano Stazione (funicolare)"));
    QCOMPARE(p->stationsReceived[1].miscInfo, QString("Funicular"));

    delete p;
}

void SearchCHFindStationsTest::resultWithGondola()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/stations-hasliberg.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseStations(&f);

    QVERIFY(!p->error);
    QVERIFY(p->stationsReceived.length() >= 3);
    QCOMPARE(p->stationsReceived[2].name,
            QString("Hasliberg Twing (Gondelbahn)"));
    QCOMPARE(p->stationsReceived[2].id.toString(),
            QString("Hasliberg Twing (Gondelbahn)"));
    QCOMPARE(p->stationsReceived[2].miscInfo, QString("Gondola"));

    delete p;
}

void SearchCHFindStationsTest::resultWithUnknownOrInvalidIcons()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/stations-invalid-icon-types.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseStations(&f);

    QVERIFY(!p->error);
    QCOMPARE(p->stationsReceived.length(), 4);
    QCOMPARE(p->stationsReceived[0].name, QString("Test1"));
    QCOMPARE(p->stationsReceived[0].id.toString(), QString("Test1"));
    QCOMPARE(p->stationsReceived[0].miscInfo, QString(""));

    QCOMPARE(p->stationsReceived[1].name, QString("Test2"));
    QCOMPARE(p->stationsReceived[1].id.toString(), QString("Test2"));
    QCOMPARE(p->stationsReceived[1].miscInfo, QString(""));

    QCOMPARE(p->stationsReceived[2].name, QString("Test3"));
    QCOMPARE(p->stationsReceived[2].id.toString(), QString("Test3"));
    QCOMPARE(p->stationsReceived[2].miscInfo, QString(""));

    QCOMPARE(p->stationsReceived[3].name, QString("Test4"));
    QCOMPARE(p->stationsReceived[3].id.toString(), QString("Test4"));
    QCOMPARE(p->stationsReceived[3].miscInfo, QString("Train station"));

    delete p;
}

void SearchCHFindStationsTest::invalidResult()
{
    ParserSearchCHTester *p = new ParserSearchCHTester();
    QFile f("fixtures/invalid.json");
    QVERIFY(f.open(QIODevice::ReadOnly));

    p->doParseStations(&f);

    QVERIFY(p->error);
    QCOMPARE(p->errorMsg, QString("Cannot parse reply from the server"));
    QCOMPARE(p->stationsReceived.length(), 0);

    delete p;
}

QTEST_MAIN(SearchCHFindStationsTest)
