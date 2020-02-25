
#include <algorithm>

#include "../core/helper.h"
#include "worktask.h"

using namespace Core;
using namespace Model;

WorkTask::WorkTask(const Task& task)
    : task_{task}
{
}

Task
WorkTask::task() const
{
    return task_;
}

void
WorkTask::setTask(const Task& task)
{
    task_ = task;
}

void
WorkTask::addTimeslot(const Timeslot& time)
{
    timeslots_.append(time);
}

QList<Timeslot>
WorkTask::timeSlots() const
{
    return timeslots_;
}

Core::Duration
WorkTask::duration() const
{
    auto totalTime = Duration{};

    forEach(timeslots_, [&totalTime](const auto& time) {
        totalTime += time.duration();
    });

    return totalTime;
}

bool
WorkTask::isActiveTask() const
{
    return std::end(timeslots_) != findIf(timeslots_, [](const auto& time) {
        return time.stop().isNull();
    });
}

Timeslot
WorkTask::activeTime() const
{
    return firstOrDefault<QList<Timeslot>>(timeslots_, [](const auto& time) {
        return time.stop().isNull();
    });
}

bool
WorkTask::merge(const WorkTask& other)
{
    if (task_ != other.task()) {
        return false;
    }

    timeslots_.append(other.timeSlots());
    return true;
}
