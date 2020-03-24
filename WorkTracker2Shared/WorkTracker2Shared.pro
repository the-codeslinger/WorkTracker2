QT -= gui
QT += core xml

TEMPLATE = lib
DEFINES += WT2_LIBRARY

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    src/core/duration.cpp \
    src/model/task.cpp \
    src/model/timeslot.cpp \
    src/model/workday.cpp \
    src/model/worktask.cpp \
    src/data/xml/xmldatasource.cpp \
    src/data/xml/xmlrepository.cpp \
    src/data/xml/xmltaskrepository.cpp \
    src/data/xml/xmlworkdayrepository.cpp

HEADERS += \
    src/worktracker2_global.h \
    src/core/constants.h \
    src/core/duration.h \
    src/core/helper.h \
    src/model/task.h \
    src/model/timeslot.h \
    src/model/workday.h \
    src/model/worktask.h \
    src/data/taskrepository.h \
    src/data/workdayrepository.h \
    src/data/xml/xmldatasource.h \
    src/data/xml/xmlrepository.h \
    src/data/xml/xmltaskrepository.h \
    src/data/xml/xmlworkdayrepository.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
