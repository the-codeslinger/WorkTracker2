#pragma once

#include <worktracker2_global.h>
#include <data/taskrepository.h>
#include <data/sql/sqldatasource.h>

namespace Data::Sql {

/**
 * Implementation of the `Data::TaskRepository` interface for a SQLite database engine.
 */
class WT2_EXPORT SqlTaskRepository final : Data::TaskRepository
{
public:
    /**
     * Create a new `SqlTaskRepository` for a given database.
     *
     * @param dataSource
     *      A database connection object that has its database loaded.
     */
    SqlTaskRepository(SqlDataSource dataSource);

    /**
     * @see TaskRepository::countTasks() const
     */
    int countTasks() const override;

    /**
     * @see TaskRepository::findTaskById(int) const
     */
    std::optional<Model::Task> findTaskById(int id) const override;

    /**
     * @see TaskRepository::findTaskByName() const
     */
    std::optional<Model::Task> findTaskByName(const QString& name) const override;

    /**
     * @see TaskRepository::listTasksSortedByLastUsed() const
     */
    QList<Model::Task> listTasksSortedByLastUsed() const override;

    /**
     * @see TaskRepository::saveTask(Model::Task&)
     */
    Model::Task saveTask(Model::Task& task) override;

private:
    SqlDataSource dataSource_;
};

}
