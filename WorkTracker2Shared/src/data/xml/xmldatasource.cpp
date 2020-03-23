#include <QStandardPaths>
#include <QDomNode>
#include <QDomElement>
#include <QFile>
#include <QDir>
#include <QDebug>

#include <algorithm>

#include "xmldatasource.h"

using namespace Data::Xml;

XmlDataSource::XmlDataSource(QString location)
    : m_location{std::move(location)}
{ }

XmlDataSource::XmlDataSource(const XmlDataSource& other)
    : m_dom{other.m_dom}
    , m_location{other.m_location}
{ }

XmlDataSource::XmlDataSource(XmlDataSource&& temp)
    : m_dom{std::move(temp.m_dom)}
    , m_location{std::move(temp.m_location)}
{ }

XmlDataSource&
XmlDataSource::operator=(const XmlDataSource& other)
{
    m_dom      = other.m_dom;
    m_location = other.m_location;
    return *this;
}

XmlDataSource&
XmlDataSource::operator=(XmlDataSource&& temp)
{
    m_dom      = std::move(temp.m_dom);
    m_location = std::move(temp.m_location);
    return *this;
}

bool
XmlDataSource::isNull() const
{
    return m_dom.isNull();
}

QDomDocument
XmlDataSource::document() const
{
    return m_dom;
}

bool
XmlDataSource::load()
{
    if (m_location.isEmpty())  {
        // Set up the data source for our application, i.e. load an existing database or,
        // e.g. on the first start, create a new database.
        QString path = QStandardPaths::writableLocation(QStandardPaths::DataLocation);

        QDir dir(path);
        if (!dir.exists()) {
            if (dir.mkpath(path)) {
                qDebug() << "Cannot create database dir: " << path;
                return false;
            }
        }
        m_location = path + "/Database.xml";
    }

    QFile xmlFile(m_location);
    if (!m_dom.setContent(&xmlFile)) {
        qDebug() << "No database file found; Create new";

        QString procInstruction = "version=\"1.0\" encoding=\"UTF-8\"";
        QDomNode xmlNode = m_dom.createProcessingInstruction("xml", procInstruction);
        m_dom.appendChild(xmlNode);

        QDomElement root = m_dom.createElement("worktracker");
        m_dom.appendChild(root);

        QDomElement version = m_dom.createElement("version");
        version.appendChild(m_dom.createTextNode("1.0"));
        root.appendChild(version);

        root.appendChild(m_dom.createElement("tasks"));
        root.appendChild(m_dom.createElement("workdays"));
    }
    xmlFile.close();

    return true;
}

bool
XmlDataSource::save() const
{
    if (!m_dom.isNull()) {
        QFile xmlFile(m_location);
        if (!xmlFile.open(QIODevice::WriteOnly)) {
            qDebug() << "Cannot open XML file for writing.";
            return false;
        }
        else {
            QTextStream out(&xmlFile);
            out.setCodec("UTF-8");
            m_dom.save(out, 2, QDomNode::EncodingFromTextStream);
            xmlFile.close();
            return true;
        }
    }

    return false;
}
