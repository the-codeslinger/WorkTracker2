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
 *
 * *Note:* Methods documented by the interface `TaskRepository` are not documented a
 *         second time.
 */
class WT2_EXPORT XmlTaskRepository : XmlRepository, TaskRepository {
public:
    /**
     * Create a new `XmlTaskRepository`.
     *
     * @param dataSource
     *      Specifies the XML database file from which the data is read and saved to.
     */
    XmlTaskRepository(const XmlDataSource& dataSource);

    virtual int countTasks() const override;

    virtual std::optional<Model::Task> findTaskById(int id) const override;

    virtual std::optional<Model::Task> findTaskByName(const QString& name) const override;

    virtual QList<Model::Task> listTasksSortedByLastUsed() const override;

    virtual Model::Task saveTask(Model::Task& task) override;

private:
    /**
     * Create a `Model::Task` from an XML element.
     */
    Model::Task taskFromElement(const QDomElement& taskElement) const;

    /**
     * Create a XML node from a `Model::Task`.
     */
    QDomElement elementFromTask(const Model::Task& task) const;

    /**
     * Update the existing XML node with the current values of a `Model::Task`.
     */
    QDomElement updateElement(const Model::Task& task, QDomElement& element) const;
};

}
