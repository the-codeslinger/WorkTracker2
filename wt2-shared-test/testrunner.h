#pragma once

#include <memory>
#include <vector>
#include <algorithm>

#include <QTest>
#include <QString>

namespace Test
{
    class TestRunner
    {
    public:
        static void add(std::unique_ptr<QObject> newTest)
        {
            auto& allTests = testList();
            auto exists = std::any_of(allTests.cbegin(), allTests.cend(),
                                      [&newTest](const auto& knownTest) {
                return knownTest->objectName() == newTest->objectName();
            });

            if (!exists) {
                allTests.push_back(std::move(newTest));
            }
        }

        static int run(int argc, char* argv[])
        {
            auto ret = 0;

            for (const std::unique_ptr<QObject>& test : testList()) {
                ret += QTest::qExec(test.get(), argc, argv);
            }

            return ret;
        }

    private:
        TestRunner() = delete;

        static std::vector<std::unique_ptr<QObject>>& testList()
        {
            static std::vector<std::unique_ptr<QObject>> list;
            return list;
        }
    };

    template <class T>
    class UnitTest
    {
    public:
        UnitTest(const QString& name)
        {
            auto testObject = new T();
            testObject->setObjectName(name);
            TestRunner::add(std::unique_ptr<T>(testObject));
        }
    };
}

#define DECLARE_TEST(className) static Test::UnitTest<className> t(#className);
