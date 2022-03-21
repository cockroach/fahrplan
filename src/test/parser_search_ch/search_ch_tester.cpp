#include <QObject>

#include "search_ch_tester.h"

ParserSearchCHTester::ParserSearchCHTester()
{
    QObject::connect(this, SIGNAL(errorOccured(QString)),
                    this, SLOT(errorOccured(QString)));
    QObject::connect(this, SIGNAL(stationsResult(const StationsList&)),
                    this, SLOT(setStationsResult(const StationsList&)));
    QObject::connect(this, SIGNAL(timetableResult(const TimetableEntriesList&)),
                    this, SLOT(setTimetableResult(const TimetableEntriesList&)));
    QObject::connect(this, SIGNAL(journeyResult(JourneyResultList*)),
                    this, SLOT(setJourneyResult(JourneyResultList*)));
    error = false;
}

void ParserSearchCHTester::sendRequest(QUrl url)
{
#if defined(BUILD_FOR_QT5)
    lastURL = url;
    lastQuery = QUrlQuery(url);
#else
    lastURL = url;
    lastQuery = url;
#endif
}

void ParserSearchCHTester::errorOccured(QString msg)
{
    error = true;
    errorMsg = msg;
}

void ParserSearchCHTester::setStationsResult(const StationsList& stations)
{
    stationsReceived = stations;
}

void ParserSearchCHTester::setTimetableResult(const TimetableEntriesList& tt)
{
    timetable = tt;
}

void ParserSearchCHTester::setJourneyResult(JourneyResultList* j)
{
    journeys = j;
}

void ParserSearchCHTester::doParseStations(QIODevice *rep)
{
    QNetworkReply *nrep = (QNetworkReply *) rep;
    parseStations(nrep);
}

void ParserSearchCHTester::doParseTimetable(QIODevice *rep)
{
    QNetworkReply *nrep = (QNetworkReply *) rep;
    parseTimeTable(nrep);
}

void ParserSearchCHTester::doParseSearchJourney(QIODevice *rep)
{
    QNetworkReply *nrep = (QNetworkReply *) rep;
    parseSearchJourney(nrep);
}

void ParserSearchCHTester::doSearchJourney(const Station &from,
    const Station &via, const Station &to, const QDateTime &when, Mode mode,
    int restrictions)
{
    searchJourney(from, via, to, when, mode, restrictions);
}

void ParserSearchCHTester::doSearchJourneyLater()
{
    searchJourneyLater();
}

void ParserSearchCHTester::doSearchJourneyEarlier()
{
    searchJourneyEarlier();
}

void ParserSearchCHTester::setLastStationFrom(const Station &st)
{
    lastJourneySearch.from = st;
}

void ParserSearchCHTester::setLastStationVia(const Station &st)
{
    lastJourneySearch.via = st;
}

void ParserSearchCHTester::setLastStationTo(const Station &st)
{
    lastJourneySearch.to = st;
}

void ParserSearchCHTester::setLastSearchTime(const QDateTime &dt)
{
    lastJourneySearch.when = dt;
}

void ParserSearchCHTester::setLastSearchMode(Mode mode)
{
    lastJourneySearch.mode = mode;
}

int ParserSearchCHTester::getRestrictions()
{
    return lastJourneySearch.restrictions;
}

void ParserSearchCHTester::setLastSearchRestrictions(int r)
{
    lastJourneySearch.restrictions = r;
}

int ParserSearchCHTester::getLastSearchNumberOfHits()
{
    return details.length();
}

JourneyDetailResultList* ParserSearchCHTester::getSearchResult(int i)
{
    return details[i];
}
