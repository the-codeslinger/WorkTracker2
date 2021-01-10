#include <optional>

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDatabase>

#include <core/logging.h>
#include <core/constants.h>
#include <data/sql/sqltaskrepository.h>
#include <model/task.h>

using namespace Data::Sql;

SqlTaskRepository::SqlTaskRepository(SqlDataSource dataSource)
    : dataSource_(std::move(dataSource))
{
}

int
SqlTaskRepository::countTasks() const
{
    auto db = dataSource_.database();
    auto query = QSqlQuery{db};

    if (!query.prepare("SELECT COUNT(id) FROM task") && query.exec()) {
        qCritical() << "Could not get task-count - " << db.lastError().text();
        return Core::Constants::invalidId;
    }

    if (query.first())  {
        auto ok = false;
        auto count = query.value(0).toInt(&ok);

        if (!ok) {
            qCritical() << "Could not convert count-value to int - " << query.value(0);
            return Core::Constants::invalidId;
        } else {
            return count;
        }
    } else {
        return 0;
    }
}

std::optional<Model::Task>
SqlTaskRepository::findTaskById(int id) const
{
    auto db = dataSource_.database();
    auto query = QSqlQuery{db};

    if (!query.prepare("SELECT id, name, last_used FROM task WHERE id = :tid")) {
        qCritical() << "Could not prepare get task by id (" << id << ") query - "
                    << db.lastError().text();
        return std::optional<Model::Task>{};
    }

    query.bindValue(":tid", id);
    if (!query.exec()) {
        qCritical() << "Could not get task by id (" << id << ") - "
                    << db.lastError().text();
        return std::optional<Model::Task>{};
    }

    // TODO Extract Task creation to helper method.
    if (query.first()) {
        auto idValue = query.value("id");
        auto nameValue = query.value("name");
        auto lastUsedValue = query.value("last_used");

        if (!idValue.isValid()) {
            qCritical() << "Task by id (" << id << ") id-value is invalid - "
                        << idValue;
            return std::optional<Model::Task>{};
        }

        if (!nameValue.isValid()) {
            qCritical() << "Task by id (" << id << ") name-value is invalid - "
                        << nameValue;
            return std::optional<Model::Task>{};
        }

        if (!lastUsedValue.isValid()) {
            qCritical() << "Task by id (" << id << ") last-used-value is invalid - "
                        << lastUsedValue;
            return std::optional<Model::Task>{};
        }

        return std::optional{Model::Task{
                idValue.toInt(), nameValue.toString(), lastUsedValue.toDateTime()}
        };
    } else {
        return std::optional<Model::Task>{};
    }
}

std::optional<Model::Task>
SqlTaskRepository::findTaskByName(const QString& name) const
{

}

QList<Model::Task>
SqlTaskRepository::listTasksSortedByLastUsed() const
{

}

Model::Task
SqlTaskRepository::saveTask(Model::Task& task)
{

}
