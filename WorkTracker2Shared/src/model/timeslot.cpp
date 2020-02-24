#include "timeslot.h"
#include "../core/constants.h"

using namespace Model;
using namespace Core;

Timeslot::Timeslot(const QDateTime& start)
    : start_{start}
{
}

Timeslot::Timeslot(const QDateTime& start, const QDateTime& stop)
    : start_{start}
    , stop_{stop}
{
}

QDateTime
Timeslot::start() const
{
    return start_;
}

void
Timeslot::setStart(const QDateTime start)
{
    start_ = start;
}

QDateTime
Timeslot::stop() const
{
    return stop_;
}

void
Timeslot::setStop(const QDateTime stop)
{
    stop_ = stop;
}

Duration
Timeslot::duration() const
{
    if (!start_.isValid()) {
        return Duration{};
    }

    if (!stop_.isValid()) {
        return Duration{start_.msecsTo(QDateTime::currentDateTimeUtc())};
    }

    return Duration{start_.msecsTo(stop_)};
}
