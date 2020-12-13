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

#include <QString>
#include <QDate>
#include <QDateTime>
#include <QDebug>

#include <core/constants.h>
#include <data/xml/xmlrepository.h>

using namespace Data::Xml;

const QString XmlRepository::ID_ATTRIBUTE_NAME = "id";

XmlRepository::XmlRepository(XmlDataSource dataSource, const QString& repoName)
    : dataSource_{std::move(dataSource)}
{
    if (!dataSource_.isNull()) {
        auto root = dataSource_.document().documentElement();
        if (!root.isNull()) {
            repoElement_ = root.firstChildElement(repoName);
            if (repoElement_.isNull()) {
                repoElement_ = dataSource_.document().createElement(repoName);
                root.appendChild(repoElement_);
            }
        } else {
            qDebug() << "Unable to find root element in XML; "
                     << "database file seems to be corrupted; "
                     << dataSource_.location();
        }
    }
}

int
XmlRepository::count() const
{
    return repoElement_.childNodes().size();
}

void
XmlRepository::appendChild(QDomElement child)
{
    if (!child.isNull()) {
        repoElement_.appendChild(child);
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
XmlRepository::attributeString(const QString& name, const QDomNode& node) const
{
    if (node.hasAttributes()) {
        auto attributes = node.attributes();
        auto attrNode = attributes.namedItem(name);
        if (attrNode.isAttr() && !attrNode.isNull()) {
            return attrNode.nodeValue();
        }
    }

    qDebug() << "Node " << node.nodeName() << " does not have attribute " << name
             << "; return empty string";
    return QString{};
}

QDateTime 
XmlRepository::attributeDateTime(const QString& name, const QDomNode& node) const
{
    return QDateTime::fromString(attributeString(name, node), Qt::ISODate);
}

QDate 
XmlRepository::attributeDate(const QString& name, const QDomNode& node) const
{
    return QDate::fromString(attributeString(name, node), Qt::ISODate);
}

int 
XmlRepository::attributeInt(const QString& name, const QDomNode& node) const
{
    auto dt = attributeString(name, node);
    auto ok = false;
    auto number = dt.toInt(&ok);
    return ok ? number : Core::Constants::invalidId;
}

QDomElement
XmlRepository::findFirstElement(std::function<bool(QDomElement)> func) const
{
    if (repoElement_.isNull()) {
        return QDomElement{};
    }

    auto nodes = repoElement_.childNodes();
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

QDomElement
XmlRepository::findElementById(int id) const
{
    return findFirstElement([id](const QDomElement& element) {
        auto value = element.attribute(ID_ATTRIBUTE_NAME);
        if (!value.isNull()) {
            auto ok = false;
            auto foundId = value.toInt(&ok);
            if (ok) {
                return id == foundId;
            }
        }
        return false;
    });
}

QDomElement
XmlRepository::createElement(const QString& elementName) const
{
    if (!dataSource_.isNull()) {
        return dataSource_.document().createElement(elementName);
    } else {
        qDebug() << "No database file loaded; cannot create valid element, return null";
        return QDomElement{};
    }
}
