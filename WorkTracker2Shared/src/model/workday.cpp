#include <core/helper.h>
#include <model/workday.h>

using namespace Core;
using namespace Model;

Workday::Workday(const QDateTime& start)
    : start_(start)
{
}

Workday::Workday(
        int id, const QDateTime& start, const QDateTime& stop,
        const QList<WorkTask>& workTasks)
    : id_(id)
    , start_(start)
    , stop_(stop)
{
    for (const auto& workTask : workTasks) {
        addWorkTask(workTask);
    }
}

int
Workday::id() const
{
    return id_;
}

void
Workday::setId(int id)
{
    id_ = id;
}

QDateTime
Workday::start() const
{
    return start_;
}

void
Workday::setStart(const QDateTime& start)
{
    start_ = start;
}

QDateTime
Workday::stop() const
{
    return stop_;
}

void
Workday::setStop(const QDateTime& stop)
{
    stop_ = stop;
}

void
Workday::addWorkTask(const WorkTask& workTask)
{
    auto found = workTasks_.find(workTask.task());
    if (found != workTasks_.end()) {
        found->merge(workTask);
    } else {
        workTasks_.insert(workTask.task(), workTask);
    }
}

QList<WorkTask>
Workday::workTasks() const
{
    return workTasks_.values();
}

std::optional<WorkTask>
Workday::findWorkTask(const Task& task) const
{
    return findValueIf(workTasks_.keys(), [&task](const auto& t) {
        return t == task;
    });
}

std::optional<WorkTask>
Workday::activeWorkTask() const
{
    return findValueIf(workTasks_.values(), [](const auto& wt) {
        return wt.isActiveTask();
    });
}

QList<Task>
Workday::distinctTasks() const
{
    return workTasks_.keys();
}

Core::Duration
Workday::duration() const
{
    auto totalTime = Duration{};

    forEach(workTasks_, [&totalTime](const auto& wt) {
        totalTime += wt.duration();
    });

    return totalTime;
}
