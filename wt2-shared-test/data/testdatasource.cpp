#include <QDir>
#include <QTest>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QStandardPaths>

#include <testdatasource.h>
#include <data/sql/sqldatasource.h>

DECLARE_TEST(TestDataSource)

void
TestDataSource::init()
{
    Data::Sql::SqlDataSource::init();

    const auto dbName = QString{"WorkTracker2.db"};

    expectedDefaultDbFilePath_ =
            QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
            + QDir::separator()
            + dbName;
    expectedSpecificDbFilePath_ = QDir::currentPath() + QDir::separator() + dbName;
}

void
TestDataSource::cleanup()
{
    Data::Sql::SqlDataSource::cleanup();

    auto defaultDbFile = QFile{expectedDefaultDbFilePath_};
    if (defaultDbFile.exists()) {
        if (!defaultDbFile.remove()) {
            qDebug() << "WARN: Could not cleanup default database at "
                     << expectedDefaultDbFilePath_
                     << " - "
                     << defaultDbFile.errorString();
        }
    }

    auto specificDbFile = QFile{expectedSpecificDbFilePath_};
    if (specificDbFile.exists()) {
        if (!specificDbFile.remove()) {
            qDebug() << "WARN: Could not cleanup specific database at "
                     << expectedSpecificDbFilePath_
                     << " - "
                     << specificDbFile.errorString();
        }
    }
}

void
TestDataSource::loadDefaultLocationCreateNewSuccess()
{
    // Given
    auto dataSource = Data::Sql::SqlDataSource{};

    // When
    auto success = dataSource.load();

    // Then
    QVERIFY(success);
    QVERIFY(QFile::exists(expectedDefaultDbFilePath_));
}

void
TestDataSource::loadSpecificLocationCreateNewSuccess()
{
    // Given
    auto dataSource = Data::Sql::SqlDataSource{QDir::currentPath()};

    // When
    auto success = dataSource.load();

    // Then
    QVERIFY(success);
    QVERIFY(QFile::exists(expectedSpecificDbFilePath_));
}

void
TestDataSource::loadExistingInvalidDbError()
{
    // Given
    auto invalidDbFile = QFile{expectedSpecificDbFilePath_};
    if (!invalidDbFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QFAIL("Cannot create invalid test database file");
    }
    auto stream = QTextStream{&invalidDbFile};
    stream << "This is not a valid SQL database file";
    invalidDbFile.close();

    auto dataSource = Data::Sql::SqlDataSource{QDir::currentPath()};

    // When
    auto success = dataSource.load();

    // Then
    QVERIFY(!success);
}

void
TestDataSource::loadExistingValidDbSuccess()
{
    // Given
    {
        // Simulate first application start that creates initial database file.
        auto dataSource = Data::Sql::SqlDataSource{QDir::currentPath()};
        QVERIFY(dataSource.load());
        QVERIFY(QFile::exists(expectedSpecificDbFilePath_));
    }

    // Simulate subsequent application start.
    auto dataSource = Data::Sql::SqlDataSource{QDir::currentPath()};

    // When
    auto success = dataSource.load();

    // Then
    QVERIFY(success);
    QVERIFY(QFile::exists(expectedSpecificDbFilePath_));
}
