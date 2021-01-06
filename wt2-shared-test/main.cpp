#include <QTest>

#include "testrunner.h"

int
main(int argc, char* argv[])
{


    QCoreApplication app(argc, argv);
    app.setAttribute(Qt::AA_Use96Dpi, true);

    QTEST_SET_MAIN_SOURCE_PATH;

    return Test::TestRunner::run(argc, argv);
}
