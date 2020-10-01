#pragma once

#include <QList>

#include "../worktracker2_global.h"
#include "../core/duration.h"
#include "task.h"
#include "timeslot.h"

namespace Model {

/*!
 * Combines a `Task` with one or more `Timeslot`s. The sum of all timeslots combined
 * amount to the total time of work spent on a single task.
 */
class WT2_EXPORT WorkTask
{
public:
    /**
     * Create a new `WorkTask` instance without any values.
     */
    WorkTask() = default;

    /**
     * Creates a new instance with a task and the parent to assign the node to.
     */
    WorkTask(const Task& task);

    /**
     * @return
     *      Returns the task that is assigned.
     */
    Task task() const;

    /**
     * Set a new `task`.
     */
    void setTask(const Task& task);

    /**
     * Append a time element to the work-task's list of times.
     */
    void addTimeslot(const Timeslot& time);

    /**
     * Append all the time elements in the list to the work-task's list of times.
     */
    void addTimeslots(const QList<Timeslot> timeslots);

    /**
     * @return
     *      Returns the list of work-times that are part of this work-task.
     */
    QList<Timeslot> timeSlots() const;

    /**
     * @return
     *      Return the total duration from start to stop of all work-times combined.
     */
    Core::Duration duration() const;

    /**
     * @return
     *      Returns `true` if this work-task contains an work-time without a stop
     *      timestamp or `false` if all work-times have a stop timestamp.
     */
    bool isActiveTask() const;

    /**
     * @return
     *      Returns the currently active work-time or a null-work-time if there is none
     *      without a stop timestamp.
     */
    std::optional<Timeslot> activeTime() const;

    /**
     * Merges all timeslots of `other` into `this` if both reference the same `Task`.
     *
     * @return
     *      Returns `true` if the timeslots have been added or `false` if `this` and
     *      `other` do not reference the same `Task`. In that case no changes will be
     *      made to `this`.
     */
    bool merge(const WorkTask& other);

private:
    Task task_;
    QList<Timeslot> timeslots_;
};

}
