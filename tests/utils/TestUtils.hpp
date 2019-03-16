#ifndef TELEGRAMQT_TEST_UTILS_HPP
#define TELEGRAMQT_TEST_UTILS_HPP

#include <QTest>

#ifndef TEST_TIMEOUT
#define TEST_TIMEOUT 200
#endif

#define TRY_COMPARE(expr, expected) QTRY_COMPARE_WITH_TIMEOUT(expr, expected, TEST_TIMEOUT)
#define TRY_VERIFY(expr) QTRY_VERIFY_WITH_TIMEOUT(expr, TEST_TIMEOUT)
#define TRY_VERIFY2(expr, messageExpression) QTRY_VERIFY2_WITH_TIMEOUT(expr, messageExpression, TEST_TIMEOUT)
#define COMPARE_PEERS(actual, expected) \
    do {\
        if (!QTest::qCompare(actual.toString(), expected.toString(), #actual, #expected, __FILE__, __LINE__))\
            return;\
    } while (false)

#endif // TELEGRAMQT_TEST_UTILS_HPP
