#pragma once

#include <algorithm>

#include <QTest>
#include <QList>
#include <QString>
#include <QSharedPointer>

namespace Test
{
    class TestRunner
    {
    public:
        static void add(QSharedPointer<QObject> newTest)
        {
            auto& allTests = testList();
            auto exists = std::any_of(allTests.cbegin(), allTests.cend(),
                                      [newTest](const auto& knownTest) {
                return knownTest->objectName() == newTest->objectName();
            });

            if (!exists) {
                allTests.append(newTest);
            }
        }

        static int run(int argc, char* argv[])
        {
            auto ret = 0;

            for (QSharedPointer<QObject> test : testList()) {
                ret += QTest::qExec(test.data(), argc, argv);
            }

            return ret;
        }

    private:
        TestRunner() = delete;

        static QList<QSharedPointer<QObject>>& testList()
        {
            static QList<QSharedPointer<QObject>> list;
            return list;
        }
    };

    template <class T>
    class UnitTest
    {
    public:
        QSharedPointer<T> child;

        UnitTest(const QString& name)
            : child{new T}
        {
            child->setObjectName(name);
            TestRunner::add(child);
        }
    };
}

#define DECLARE_TEST(className) static Test::UnitTest<className> t(#className);
