#ifndef SEARCH_CH_STATIONBOARD_TEST_H
#define SEARCH_CH_STATIONBOARD_TEST_H

#include <QObject>

#include "../../parser/parser_search_ch.h"

class SearchCHStationboardTest: public QObject
{
    Q_OBJECT

private slots:
    void loadMultipleEntries();
    void loadTypeExpressTrain();
    void loadTypeSTrain();
    void loadTypeTrain();
    void loadTypeBus();
    void loadTypeTram();
    void loadTypePostauto();
    void loadTypeShipWithNoLine();
    void loadTypeCablecarWithNoLine();
    void loadTypeFunicularWithNoLine();
    void loadTypeGondolaWithNoLine();
    void loadCoordinates();
    void loadCoordinatesNoLongitude();
    void loadCoordinatesNoLatitude();
    void loadPlatform();
    void loadNoPlatformSetsCurrentStation();
    void loadConnectionWithDelay();
    void ignoreDelayZeroMinutes();
    void loadCancelledConnection();
    void invalidResult();
};

#endif
