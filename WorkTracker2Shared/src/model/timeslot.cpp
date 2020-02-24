#include "timeslot.h"
#include "../core/constants.h"

using namespace Model;
using namespace Core;

Timeslot::Timeslot()
{
    Core::invalidId;
}

Timeslot::Timeslot(const QDateTime start)
{
    start_ = start;
}

Timeslot::Timeslot(const QDateTime start, const QDateTime stop)
{
    start_ = start;
    stop_ = stop;
}

QDateTime
Timeslot::start()
{
    return start_;
}

void
Timeslot::setStart(const QDateTime start)
{
    start_ = start;
}

QDateTime
Timeslot::stop()
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
    return Duration(234);
}
