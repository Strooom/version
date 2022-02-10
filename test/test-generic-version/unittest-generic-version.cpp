#define unitTest
#include <unity.h>
#include "version.h"


void test_version_initialization() {
    // uLog aLog;
    // aLog.setOutput(0, outputFunction0);
    // TEST_ASSERT_EQUAL(nullptr, aLog.getTime);
    // aLog.setTimeSource(loggingTime);
    // TEST_ASSERT_NOT_EQUAL(nullptr, aLog.getTime);
    // aLog.setLoggingLevel(0, subSystem::general, loggingLevel::Warning);
    // TEST_ASSERT_EQUAL_UINT8(loggingLevel::Warning, aLog.getLoggingLevel(0, subSystem::general));
}


int main(int argc, char** argv) {
    UNITY_BEGIN();
    RUN_TEST(test_version_initialization);
    UNITY_END();
}