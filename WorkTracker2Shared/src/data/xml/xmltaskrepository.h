#pragma once

#include <optional>

#include <QList>

#include "../../worktracker2_global.h"
#include "../../model/task.h"
#include "../taskrepository.h"
#include "xmldatasource.h"

namespace Data::Xml {

/**
 * Implements the `Data::TaskRepository` for use with an XML database file.
 */
class WT2_EXPORT XmlTaskRepository : TaskRepository {
public:
    XmlTaskRepository(const XmlDataSource& dataSource);

    virtual ~XmlTaskRepository() override;

    virtual int countTasks() const override;

    virtual std::optional<Model::Task> findTaskById(int id) const override;

    virtual std::optional<Model::Task> findTaskByName(const QString& name) const override;

    virtual QList<Model::Task> listTasksSortedByLastUsed() const override;

    virtual Model::Task saveTask(const Model::Task& task) override;
};

}
