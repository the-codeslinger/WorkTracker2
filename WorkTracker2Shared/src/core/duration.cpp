#include "duration.h"
#include "constants.h"

using namespace Core;

static qint64 SEC = 1000;
static qint64 MIN = 60;

Duration::Duration()
    : Duration{Constants::invalidId}
{
}

Duration::Duration(qint64 milliseconds)
    : milliseconds_{milliseconds}
{
}

Duration
Duration::operator+(const Duration& other) const
{
    if (!isValid() && !other.isValid()) {
        return Duration{};
    }

    if (!isValid() && other.isValid()) {
        return other;
    }

    if (isValid() && !other.isValid()) {
        return *this;
    }

    return Duration{milliseconds_ + other.milliseconds_};
}

Duration&
Duration::operator+=(const Duration& other)
{
    *this = *this + other;
    return *this;
}

qint64
Duration::toMilliseconds() const
{
    return milliseconds_;
}

qint64
Duration::toSeconds() const
{
    return milliseconds_ / SEC;
}

qint64
Duration::toMinutes() const
{
    return milliseconds_ / SEC / MIN;
}

bool
Duration::isValid() const
{
    return Constants::invalidId < milliseconds_;
}
