QT -= gui

TEMPLATE = lib
DEFINES += WT2_LIBRARY

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/core/duration.cpp \
    src/model/task.cpp \
    src/model/timeslot.cpp \
    src/model/workday.cpp \
    src/model/worktask.cpp

HEADERS += \
    src/worktracker2_global.h \
    src/core/constants.h \
    src/core/duration.h \
    src/core/helper.h \
    src/data/taskrepository.h \
    src/data/workdayrepository.h \
    src/model/task.h \
    src/model/timeslot.h \
    src/model/workday.h \
    src/model/worktask.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
