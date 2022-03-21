#ifndef SEARCH_CH_TRAIN_TYPE_TEST_H
#define SEARCH_CH_TRAIN_TYPE_TEST_H

#include <QObject>

#include "../../parser/parser_search_ch.h"

class SearchCHTrainTypeListTest : public QObject
{
    Q_OBJECT

private slots:
    void testAppendBus();
    void testAppendNightBus();
    void testAppendTram();
    void testAppendFunicular();
    void testAppendGondola();
    void testAppendCableway();
    void testAppendShip();
    void testAppendSomeOtherString();
    void testToStringNoItems();
    void testToStringSingleItem();
    void testToStringMultipleItems();
    void skipConsecutiveIdentical();
    void skipIdentical();
};

#endif
