#include <QStandardPaths>
#include <QDomNode>
#include <QDomElement>
#include <QFile>
#include <QDir>
#include <QDebug>

#include <algorithm>

#include <data/xml/xmldatasource.h>

using namespace Data::Xml;

// TODO Improve dataSource handling; right now every repo has its own data source
//      -> Data inconsistencies.

XmlDataSource::XmlDataSource(QString location)
    : location_{std::move(location)}
{ }

XmlDataSource::XmlDataSource(const XmlDataSource& other)
    : document_{other.document_}
    , location_{other.location_}
{ }

XmlDataSource::XmlDataSource(XmlDataSource&& temp)
    : document_{std::move(temp.document_)}
    , location_{std::move(temp.location_)}
{ }

XmlDataSource&
XmlDataSource::operator=(const XmlDataSource& other)
{
    document_      = other.document_;
    location_ = other.location_;
    return *this;
}

XmlDataSource&
XmlDataSource::operator=(XmlDataSource&& temp)
{
    document_      = std::move(temp.document_);
    location_ = std::move(temp.location_);
    return *this;
}

bool
XmlDataSource::isNull() const
{
    return document_.isNull();
}

QDomDocument
XmlDataSource::document() const
{
    return document_;
}

bool
XmlDataSource::load()
{
    if (location_.isEmpty())  {
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
        location_ = path + "/Database.xml";
    }

    QFile xmlFile(location_);
    if (!document_.setContent(&xmlFile)) {
        qDebug() << "No database file found; Create new";

        QString procInstruction = "version=\"1.0\" encoding=\"UTF-8\"";
        QDomNode xmlNode = document_.createProcessingInstruction("xml", procInstruction);
        document_.appendChild(xmlNode);

        QDomElement root = document_.createElement("worktracker");
        document_.appendChild(root);

        QDomElement version = document_.createElement("version");
        version.appendChild(document_.createTextNode("1.0"));
        root.appendChild(version);

        root.appendChild(document_.createElement("tasks"));
        root.appendChild(document_.createElement("workdays"));
    }
    xmlFile.close();

    return true;
}

bool
XmlDataSource::save() const
{
    if (!document_.isNull()) {
        QFile xmlFile(location_);
        if (!xmlFile.open(QIODevice::WriteOnly)) {
            qDebug() << "Cannot open XML file for writing.";
            return false;
        }
        else {
            QTextStream out(&xmlFile);
            out.setCodec("UTF-8");
            document_.save(out, 2, QDomNode::EncodingFromTextStream);
            xmlFile.close();
            return true;
        }
    }

    return false;
}

QString
XmlDataSource::location() const
{
    return location_;
}
