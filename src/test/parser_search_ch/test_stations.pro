HEADERS += \
    src/test/parser_search_ch/search_ch_tester.h \
    src/test/parser_search_ch/test_stations.h \
    src/parser/parser_abstract.h \
    src/parser/parser_definitions.h \ 
    src/parser/parser_search_ch.h

SOURCES += \
    src/test/parser_search_ch/search_ch_tester.cpp \
    src/test/parser_search_ch/test_stations.cpp \
    src/parser/parser_abstract.cpp \
    src/parser/parser_definitions.cpp \
    src/parser/parser_search_ch.cpp

LIBS += -lz

CONFIG += qtestlib
QT += network testlib

lessThan(QT_MAJOR_VERSION, 5) {
    QT += script
} else {
    QT += network
    DEFINES += BUILD_FOR_QT5
}

TARGET = search_ch_stations_test
QMAKE_CXXFLAGS += -g
