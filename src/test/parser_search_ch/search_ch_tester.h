#ifndef SEARCH_CH_TESTER_H
#define SEARCH_CH_TESTER_H

#ifdef BUILD_FOR_QT5
#include <QUrlQuery>
#endif

#include "../../parser/parser_search_ch.h"

class ParserSearchCHTester: public ParserSearchCH
{
    Q_OBJECT

private slots:
    void errorOccured(QString msg);
    void setStationsResult(const StationsList&);
    void setTimetableResult(const TimetableEntriesList&);
    void setJourneyResult(JourneyResultList*);

protected:
    void sendRequest(QUrl url);

public:
    bool error;
    QString errorMsg;
    StationsList stationsReceived;
    TimetableEntriesList timetable;
    JourneyResultList* journeys;
#if defined(BUILD_FOR_QT5)
    QUrl lastURL;
    QUrlQuery lastQuery;
#else
    QUrl lastURL;
    QUrl lastQuery;
#endif

    ParserSearchCHTester();

    void doParseStations(QIODevice *);
    void doParseTimetable(QIODevice *);
    void doParseSearchJourney(QIODevice *);
    void doSearchJourney(const Station &from, const Station &via,
            const Station &to, const QDateTime &when, Mode, int restrictions);
    void doSearchJourneyLater();
    void doSearchJourneyEarlier();

    void setLastStationFrom(const Station &);
    void setLastStationVia(const Station &);
    void setLastStationTo(const Station &);
    void setLastSearchTime(const QDateTime &);
    void setLastSearchMode(Mode mode);
    void setLastSearchRestrictions(int);
    int getRestrictions();
    JourneyDetailResultList *getSearchResult(int i);
    int getLastSearchNumberOfHits();
};

#endif
