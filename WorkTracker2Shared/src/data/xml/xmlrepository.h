#pragma once

#include "xmldatasource.h"

#include <QDomElement>

class QString;
class QDate;
class QDateTime;

namespace Data::Xml {

/**
 * WorkTracker stores its data in an XML database file. `XmlRepository` is the base class
 * for the specific repository classes and provides some convenient methods for accessing
 * and manipulating the XML DOM.
 */
class XmlRepository
{
protected:
    static const QString ID_ATTRIBUTE_NAME;

    /**
     * Creates a new instance with a data source and a DOM element with the specified 
     * name.
     */
    XmlRepository(XmlDataSource dataSource, const QString& repoName);
    
    /**
     * Gets the given element's attribute value as a string. 
     */
    QString attributeString(const QString& name, const QDomElement& element) const;
    
    /**
     * Gets the given element's attribute value as a date-time. 
     */
    QDateTime attributeDateTime(const QString& name, const QDomElement& element) const;
    /**
     * Gets the given element's attribute value as a date. 
     */
    QDate attributeDate(const QString& name, const QDomElement& element) const;
    
    /**
     * Gets the given element's attribute value as an integer. 
     */
    int attributeInt(const QString& name, const QDomElement& element) const;

    /**
     * Add a new attribute to the element or assign a new value to an already existing
     * attribute.
     *
     * @param name
     *      The name of the attribute.
     *
     * @param value
     *      The attribute's (new) value.
     *
     * @param element
     *      The XML element to set the value on.
     */
    void setAttribute(
            const QString& name,
            const QString& value,
            QDomElement& element) const;
    
    /**
     * Add a new attribute to the element or assign a new value to an already existing
     * attribute.
     *
     * @param name
     *      The name of the attribute.
     *
     * @param value
     *      The attribute's (new) date-time value. If this is an invalid date then the
     *      attribute will be set to an empty value.
     *
     * @param element
     *      The XML element to set the value on.
     */
    void setAttribute(
            const QString& name,
            const QDateTime& value,
            QDomElement& element) const;
    
    /**
     * Add a new attribute to the element or assign a new value to an already existing
     * attribute.
     *
     * @param name
     *      The name of the attribute.
     *
     * @param value
     *      The attribute's (new) date value. If this is an invalid date then the
     *      attribute will be set to an empty value.
     *
     * @param element
     *      The XML element to set the value on.
     */
    void setAttribute(
            const QString& name,
            const QDate& value,
            QDomElement& element) const;
    
    /**
     * Add a new attribute to the element or assign a new value to an already existing
     * attribute.
     *
     * @param name
     *      The name of the attribute.
     *
     * @param value
     *      The attribute's (new) integer value. If this is -1 then the attribute is not
     *      created / updated.
     *
     * @param element
     *      The XML element to set the value on.
     */
    void setAttribute(
            const QString& name,
            int value,
            QDomElement& element) const;

    /**
     * Iterates `dom_` until `func` returns `true`. The found element is
     * returned or a null-element.
     */
    QDomElement findFirstElement(std::function<bool(QDomElement)> func) const;

    /**
     * Iterates `dom_` to find the element with the given id. This works for all types
     * of WorkTracker types that have an "id" attribute.
     */
    QDomElement findElementById(int id) const;

    /**
     * The DOM document that represents the XML database file.
     */
    XmlDataSource dataSource_;
    /**
     * The link to the DOM element that represents the root of a repository's list of
     * elements. It's somewhat equivalent to a database table.
     */
    QDomElement repoElement_;
};

}
