#pragma once

#include <optional>

#include <QList>

#include "../../worktracker2_global.h"
#include "../../model/task.h"
#include "../taskrepository.h"
#include "xmldatasource.h"
#include "xmlrepository.h"

namespace Data::Xml {

/**
 * Implements the `Data::TaskRepository` for use with an XML database file.
 */
class WT2_EXPORT XmlTaskRepository : XmlRepository, TaskRepository {
public:
    XmlTaskRepository(const XmlDataSource& dataSource);

    virtual ~XmlTaskRepository() override;

    virtual int countTasks() const override;

    virtual std::optional<Model::Task> findTaskById(int id) const override;

    virtual std::optional<Model::Task> findTaskByName(const QString& name) const override;

    virtual QList<Model::Task> listTasksSortedByLastUsed() const override;

    virtual Model::Task saveTask(Model::Task& task) override;

private:
    std::optional<Model::Task> taskFromElement(const QDomElement& taskElement) const;
    QDomElement elementFromTask(const Model::Task& task) const;
    QDomElement updateElement(const Model::Task& task, QDomElement& element) const;
};

}
