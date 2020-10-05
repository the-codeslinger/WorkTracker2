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

INCLUDEPATH += include/

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
    include/data/json/jsondatasource.h \
    include/worktracker2_global.h \
    include/core/constants.h \
    include/core/duration.h \
    include/core/helper.h \
    include/model/task.h \
    include/model/timeslot.h \
    include/model/workday.h \
    include/model/worktask.h \
    include/data/taskrepository.h \
    include/data/workdayrepository.h \
    include/data/xml/xmldatasource.h \
    include/data/xml/xmlrepository.h \
    include/data/xml/xmltaskrepository.h \
    include/data/xml/xmlworkdayrepository.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
    INCLUDEPATH += /usr/lib/gcc/x86_64-linux-gnu/9/include
}
!isEmpty(target.path): INSTALLS += target
