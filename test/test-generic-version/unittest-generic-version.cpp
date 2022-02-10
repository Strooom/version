#define unitTest
#include <unity.h>
#include "version.h"

void test_version_initialization() {
    version aVersion("");
    TEST_ASSERT_FALSE(aVersion.isValid());
    aVersion.set("V1.2.3");
    TEST_ASSERT_TRUE(aVersion.isValid());
    version anotherVersion("V4_5_6");
    TEST_ASSERT_TRUE(anotherVersion.isValid());
}

void test_version_convert() {
    version aVersion("_._._.");
    TEST_ASSERT_EQUAL_STRING("......", aVersion.get());
}

void test_version_valid_static() {
    TEST_ASSERT_TRUE(version::isValid("V1.2.3"));
    TEST_ASSERT_FALSE(version::isValid(""));
}


void test_version_boundaries() {
    version aVersion("V10.20.30.40.50.60.70.80.90.00");
    TEST_ASSERT_EQUAL_STRING("V10.20.30.40", aVersion.get());
}

int main(int argc, char** argv) {
    UNITY_BEGIN();
    RUN_TEST(test_version_initialization);
    RUN_TEST(test_version_boundaries);
    RUN_TEST(test_version_convert);
    RUN_TEST(test_version_valid_static);
    UNITY_END();
}