#include "duration.h"

using namespace Core;

Duration::Duration(qint64 seconds)
{
    seconds_ = seconds;
}

Duration::Duration(const Duration& other)
{
    seconds_ = other.seconds_;
}

Duration&
Duration::operator=(const Duration& other)
{
    seconds_ = other.seconds_;
    return *this;
}
