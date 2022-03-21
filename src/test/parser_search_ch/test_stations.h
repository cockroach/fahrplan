#ifndef SEARCH_CH_STATIONS_TEST_H
#define SEARCH_CH_STATIONS_TEST_H

#include <QObject>

#include "../../parser/parser_search_ch.h"

class SearchCHFindStationsTest: public QObject
{
    Q_OBJECT

private slots:
    void ignoreBusinessEntries();
    void ignoreAddressEntries();
    void resultWithBusStop();
    void resultWithTramStop();
    void resultWithPort();
    void resultWithCablecar();
    void resultWithTrainStation();
    void resultWithSTrainStation();
    void resultWithFunicular();
    void resultWithGondola();
    void resultWithUnknownOrInvalidIcons();
    void invalidResult();
};

#endif
