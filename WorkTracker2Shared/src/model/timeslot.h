#pragma once

#include <QDateTime>

#include "../worktracker2_global.h"
#include "../core/duration.h"

namespace Model {

class WT2_EXPORT Timeslot {
private:
    QDateTime start_;
    QDateTime stop_;

public:
    Timeslot();

    Timeslot(const QDateTime start);

    Timeslot(const QDateTime start, const QDateTime stop);

    QDateTime start();

    void setStart(const QDateTime start);

    QDateTime stop();

    void setStop(const QDateTime stop);

    Core::Duration duration() const;
};

}
