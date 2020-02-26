#pragma once

#include <optional>

#include <QMap>
#include <QList>
#include <QDateTime>

#include "../worktracker2_global.h"
#include "../core/duration.h"
#include "worktask.h"

namespace Model {

/**
 * A workday is a collection of all the tasks the user has performed throughout a day of
 * work, identified by a start-timestamp. Each task itself is represented by a `WorkTask`
 * item that collects the specific `Task` and the start and stop timestamps.
 */
class WT2_EXPORT Workday {
public:
    /**
     * Default constructor.
     */
    Workday() = default;

    /**
     * Create a new `Workday` with a starting timestamp. Use this to start a new day.
     */
    Workday(const QDateTime& start);

    /**
     * Create a new `Workday` with both start and stop timestamps and the list of
     * work-tasks. You'll likely use this when creating an object from a day in the past.
     */
    Workday(int id, const QDateTime& start, const QDateTime& stop,
            const QList<WorkTask>& workTasks);

    /**
     * @return
     *      Returns the database id of the workday or `Core::invalidId` if it is yet to
     *      be saved to database.
     */
    int id() const;

    /**
     * Set a new database `id`.
     */
    void setId(int id);

    /**
     * @return
     *      Returns the start timestamp.
     */
    QDateTime start() const;

    /**
     * Set a new `start` timestamp.
     */
    void setStart(const QDateTime& start);

    /**
     * @return
     *      Returns the stop timestamp.
     */
    QDateTime stop() const;

    /**
     * Set a new `stop` timestamp.
     */
    void setStop(const QDateTime& stop);

    /**
     * Add a `workTask` to the workday. If the task already exists (based on `Task.id()`,
     * the existing work-task will be overwritten.
     */
    void addWorkTask(const WorkTask& workTask);

    /**
     * @return
     *      Returns a copy of the list of all work-tasks.
     */
    QList<WorkTask> workTasks() const;

    /**
     * Retrieve a specific work-task.
     *
     * @param task
     *      Specifies the work-task's referencing task.
     *
     * @return
     *      If found, the work-task is returned or a null-instance otherwise.
     */
    std::optional<WorkTask> findWorkTask(const Task& task) const;

    /**
     * Searches the list of tasks to find one that is not yet finished.
     *
     * @return
     *      If there's a running task (one with an invalid stop-date) then this task is
     *      returned, otherwise a null-task.
     */
    std::optional<WorkTask> activeWorkTask() const;

    /**
     * @return
     *      Returns a list of distinct tasks this workday is comprised of.
     */
    QList<Task> distinctTasks() const;

    /**
     * @return
     *      Returns the total duration that has been spent on all tasks combined.
     */
    Core::Duration duration() const;

private:
    int id_;
    QDateTime start_;
    QDateTime stop_;
    QMap<Task, WorkTask> workTasks_;
    std::vector<WorkTask> myTasks;
};

}
