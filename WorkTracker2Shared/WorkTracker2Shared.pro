QT -= gui
QT += core xml sql

TEMPLATE = lib
DEFINES += WT2_LIBRARY

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += /usr/lib/gcc/x86_64-linux-gnu/9/include \
    include/

SOURCES += \
    src/core/duration.cpp \
    src/core/logging.cpp \
    src/model/task.cpp \
    src/model/timeslot.cpp \
    src/model/workday.cpp \
    src/model/worktask.cpp \
    src/data/datasource.cpp \
    src/data/sql/sqldatasource.cpp

HEADERS += \
    include/core/logging.h \
    include/data/datasource.h \
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
    include/data/sql/sqldatasource.h \
    include/data/sql/sqltaskrepository.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
    LIBS += -lsqlite3
}
!isEmpty(target.path): INSTALLS += target
