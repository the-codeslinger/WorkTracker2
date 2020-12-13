#pragma once

#include <optional>

#include <QList>

#include "../worktracker2_global.h"
#include "../model/task.h"

namespace Data {

/**
 * The main data access class for `Task` objects. This defines all the find and save
 * methods that are required by the application.
 *
 * It is conceptually comparable to Spring Data repository classes, only with less magic
 * happening in the background.
 */
class WT2_EXPORT TaskRepository {
public:
    virtual ~TaskRepository() = default;

    /**
     * Count the number of tasks in the database.
     */
    virtual int countTasks() const = 0;

    /**
     * Find and return a specific task by its database id.
     *
     * @param id
     *      The tasks database id.
     *
     * @return
     *      Returns the task if found or a `nullopt`.
     */
    virtual std::optional<Model::Task> findTaskById(int id) const = 0;

    /**
     * Find and return a specific task by its name.
     *
     * @param name
     *      The tasks name. Comparison is case-insensitive.
     *
     * @return
     *      Returns the task if found or a `nullopt`.
     */
    virtual std::optional<Model::Task> findTaskByName(const QString& name) const = 0;

    /**
     * Find all tasks and return the sorted by their last-used timestamp.
     *
     * @return
     *      A list is always returned, regardless if tasks exist in the database or not.
     */
    virtual QList<Model::Task> listTasksSortedByLastUsed() const = 0;

    /**
     * Save a new task to the database.
     *
     * @param task
     *      The task to save. If the task has an id then its name is updated.
     *      Note: This value is updated with an id if doesn't already have one.
     *
     * @return
     *      Returns the saved task. This is the same object as the parameter. If the task
     *      is new then the returned value contains the database id in addition to the
     *      name.
     */
    virtual Model::Task saveTask(Model::Task& task) = 0;
};

}
