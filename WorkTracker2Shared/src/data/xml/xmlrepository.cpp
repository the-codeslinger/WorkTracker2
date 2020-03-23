/*
 * Copyright 2014 Robert Lohr
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "xmlrepository.h"
#include "../../core/constants.h"

#include <QString>
#include <QDate>
#include <QDateTime>

using namespace Data::Xml;

XmlRepository::XmlRepository(XmlDataSource dataSource, const QString& name)
    : dataSource_{std::move(dataSource)}
{
    if (!dataSource.isNull()) {
        dom_ = dataSource_.document().createElement(name);
    }
}

void
XmlRepository::setAttribute(
        const QString& name,
        const QString& value,
        QDomElement& element) const
{
    element.setAttribute(name, value);
}

void 
XmlRepository::setAttribute(
        const QString& name,
        const QDateTime& value,
        QDomElement& element) const
{
    auto string = QString{};
    if (!value.isNull()) {
        string = value.toUTC().toString(Qt::ISODate);
    }
    
    setAttribute(name, string, element);
}

void 
XmlRepository::setAttribute(
        const QString& name,
        const QDate& value,
        QDomElement& element) const
{
    auto string = QString{};
    if (!value.isNull()) {
        string = value.toString(Qt::ISODate);
    }
    
    setAttribute(name, string, element);
}

void 
XmlRepository::setAttribute(
        const QString& name,
        int value,
        QDomElement& element) const
{
    setAttribute(name, QString::number(value), element);
}

QString 
XmlRepository::attributeString(const QString& name, const QDomElement& element) const
{
    return element.attribute(name);
}

QDateTime 
XmlRepository::attributeDateTime(const QString& name, const QDomElement& element) const
{
    return QDateTime::fromString(attributeString(name, element), Qt::ISODate);
}

QDate 
XmlRepository::attributeDate(const QString& name, const QDomElement& element) const
{
    return QDate::fromString(attributeString(name, element), Qt::ISODate);
}

int 
XmlRepository::attributeInt(const QString& name, const QDomElement& element) const
{
    auto dt = attributeString(name, element);
    auto ok = false;
    auto number = dt.toInt(&ok);
    return ok ? number : Core::Constants::invalidId;
}

QDomElement
XmlRepository::findFirstNode(std::function<bool(QDomElement)> func) const
{
    if (dom_.isNull()) {
        return QDomElement{};
    }

    auto nodes = dom_.childNodes();
    for (int c = 0; c < nodes.length(); c++) {
        auto node = nodes.item(c);
        if (node.isElement()) {
            auto element = node.toElement();
            if (func(element)) {
                return element;
            }
        }
    }
    return QDomElement{};
}