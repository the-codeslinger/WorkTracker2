#include "../testrunner.h"

class TestDataSource : public QObject
{
    Q_OBJECT

private slots:
    void testConstructor();
    void testFail();
};
