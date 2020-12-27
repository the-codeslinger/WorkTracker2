#include <QTest>
#include "testdatasource.h"

DECLARE_TEST(TestDataSource)

void
TestDataSource::testConstructor()
{
    QVERIFY(true == true);
}

void
TestDataSource::testFail()
{
    QVERIFY(true == false);
}