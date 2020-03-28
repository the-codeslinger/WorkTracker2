#pragma once

#include "../../worktracker2_global.h"
#include "../workdayrepository.h"
#include "xmlrepository.h"
#include "xmltaskrepository.h"

namespace Data::Xml {

/**
 * Implements the `Data::WorkdayRepository` for use with an XML database file.
 *
 * *Note:* Methods documented by the interface `WorkdayRepository` are not documented a
 *         second time.
 */
class WT2_EXPORT XmlWorkdayRepository : XmlRepository, WorkdayRepository {
public:
    /**
     * Create a new `XmlWorkdayRepository`.
     *
     * @param dataSource
     *      Specifies the XML database file from which the data is read and saved to.
     *
     * @param taskRepository
     *      A XML task repository from which `Model::Task` objects can be retrieved.
     */
    XmlWorkdayRepository(
            const XmlDataSource& dataSource,
            const XmlTaskRepository& taskRepository);

    virtual int countWorkdays() const override;

    virtual std::optional<Model::Workday> findLastActiveWorkday() const override;

    virtual Model::Workday saveWorkday(Model::Workday& workday) override;

private:
    /**
     * Create a `Model::Workday` from an XML element. This includes creating all
     * `Model::WorkTask` and `Model::Timeslot` objects.
     */
    Model::Workday workdayFromElement(const QDomElement& workdayElement) const;

    /**
     * Create a list of all `Model::WorkTask` objects from a list of XML DOM nodes.
     * This also creates all `Model::Timeslot` objects for each work-task.
     */
    QList<Model::WorkTask> workTasksFromElement(const QDomNodeList& workTaskElements) const;

    /**
     * Create a single `Model::WorkTask` object with all of its `Model::Timeslot` objects
     * from the given XML node.
     */
    Model::WorkTask workTaskFromElement(const QDomElement& workTaskElement) const;

    /**
     * Create a list of all `Model::Timeslot` objects from a list of XML DOM nodes.
     */
    QList<Model::Timeslot> timeslotsFromElement(const QDomNodeList& timeslotElements) const;

    /**
     * Create a `Model::Timeslot` from the given XML node.
     */
    Model::Timeslot timeslotFromElement(const QDomElement& timeslotElement) const;

    /**
     * Create a XML node from a `Model::Workday` including all of its `Model::WorkTask`s
     * and the associated `Model::Timeslot`s.
     */
    QDomElement elementFromWorkday(const Model::Workday& workday) const;

    /**
     * Update the existing XML node with the current values of a `Model::Workday`.
     *
     * *Note:* It is important that the XML node has nothing more than a name for this
     *         method to work properly. All the children must have been removed prior to
     *         calling it.
     */
    QDomElement updateElement(const Model::Workday& workday, QDomElement& element) const;

    XmlTaskRepository taskRepository_;
};

}
