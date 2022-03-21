#include <iostream>

#include <QObject>
#include <QtTest/QtTest>

#include "../../parser/parser_search_ch.h"

#include "test_train_type_list.h"

using namespace parser_search_ch;

void SearchCHTrainTypeListTest::testAppendBus()
{
    TrainTypeList t;

    t.append(QString("B"));
    QCOMPARE(t.toString(), QString("Bus"));
}

void SearchCHTrainTypeListTest::testAppendNightBus()
{
    TrainTypeList t;

    t.append(QString("BN"));
    QCOMPARE(t.toString(), QString("Bus"));
}

void SearchCHTrainTypeListTest::testAppendTram()
{
    TrainTypeList t;

    t.append(QString("T"));
    QCOMPARE(t.toString(), QString("Tram"));
}

void SearchCHTrainTypeListTest::testAppendFunicular()
{
    TrainTypeList t;

    t.append(QString("FUN"));
    QCOMPARE(t.toString(), QString("Funi"));
}

void SearchCHTrainTypeListTest::testAppendGondola()
{
    TrainTypeList t;

    t.append(QString("GB"));
    QCOMPARE(t.toString(), QString("Gondola"));
}

void SearchCHTrainTypeListTest::testAppendCableway()
{
    TrainTypeList t;

    t.append(QString("PB"));
    QCOMPARE(t.toString(), QString("Cableway"));
}

void SearchCHTrainTypeListTest::testAppendShip()
{
    TrainTypeList t;

    t.append(QString("BAT"));
    QCOMPARE(t.toString(), QString("Ship"));
}

void SearchCHTrainTypeListTest::testAppendSomeOtherString()
{
    TrainTypeList t;

    t.append(QString("Lorem Ipsum"));
    QCOMPARE(t.toString(), QString("Lorem Ipsum"));
}

void SearchCHTrainTypeListTest::testToStringNoItems()
{
    TrainTypeList t;

    QCOMPARE(t.toString(), QString("Walk"));
}

void SearchCHTrainTypeListTest::testToStringSingleItem()
{
    TrainTypeList t;

    t.append(QString("B"));
    QCOMPARE(t.toString(), QString("Bus"));
}

void SearchCHTrainTypeListTest::testToStringMultipleItems()
{
    TrainTypeList t;

    t.append(QString("B"));
    t.append(QString("T"));
    t.append(QString("IR"));
    QCOMPARE(t.toString(), QString("Bus Tram IR"));
}

void SearchCHTrainTypeListTest::skipConsecutiveIdentical()
{
    TrainTypeList t;

    t.append(QString("B"));
    t.append(QString("B"));
    t.append(QString("T"));
    QCOMPARE(t.toString(), QString("Bus Tram"));
}

void SearchCHTrainTypeListTest::skipIdentical()
{
    TrainTypeList t;

    t.append(QString("B"));
    t.append(QString("T"));
    t.append(QString("B"));
    t.append(QString("B"));
    t.append(QString("B"));
    t.append(QString("T"));
    t.append(QString("IR"));
    t.append(QString("T"));
    QCOMPARE(t.toString(), QString("Bus Tram IR"));
}

QTEST_MAIN(SearchCHTrainTypeListTest)
