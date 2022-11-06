#include "unity.h"
#include "version.h"

void setUp() {}
void tearDown() {}

void test_stripLeadingV() {
    char testString[] = "V1.2.3.4";
    version::stripLeadingV(testString);
    TEST_ASSERT_EQUAL_STRING("1.2.3.4", testString);
    char testString2[] = "V10.20.30.40.50";
    version::stripLeadingV(testString2);
    TEST_ASSERT_EQUAL_STRING("10.20.30.40.", testString2);
}

void test_replaceDelimitorWithDot() {
    char testString[] = "xx_yy_zz";
    version::replaceDelimitorWithDot(testString, '_');
    TEST_ASSERT_EQUAL_STRING("xx.yy.zz", testString);
}

void test_isValid() {
    TEST_ASSERT_FALSE(version::isValid("this string is too long so it is invalid"));
    TEST_ASSERT_FALSE(version::isValid(""));
    TEST_ASSERT_TRUE(version::isValid("V1.2.3"));
    TEST_ASSERT_TRUE(version::isValid("v1.2.3"));
    TEST_ASSERT_TRUE(version::isValid("1.2.3"));
    TEST_ASSERT_FALSE(version::isValid(" "));
}

void test_initialization() {
    version aVersion;
    TEST_ASSERT_EQUAL(0, aVersion.getMajor());
    TEST_ASSERT_EQUAL(0, aVersion.getMinor());
    TEST_ASSERT_EQUAL(0, aVersion.getBugfix());
    TEST_ASSERT_EQUAL(0, aVersion.getCandidate());
    TEST_ASSERT_TRUE(aVersion.isProduction());
}

void test_setFromString() {
    version aVersion;
    aVersion.set("V1.2.3");
    TEST_ASSERT_EQUAL(1, aVersion.getMajor());
    TEST_ASSERT_EQUAL(2, aVersion.getMinor());
    TEST_ASSERT_EQUAL(3, aVersion.getBugfix());
    TEST_ASSERT_TRUE(aVersion.isProduction());
    TEST_ASSERT_EQUAL(0, aVersion.getCandidate());

    aVersion.set("V1.2.3.0");
    TEST_ASSERT_EQUAL(1, aVersion.getMajor());
    TEST_ASSERT_EQUAL(2, aVersion.getMinor());
    TEST_ASSERT_EQUAL(3, aVersion.getBugfix());
    TEST_ASSERT_EQUAL(0, aVersion.getCandidate());
    TEST_ASSERT_FALSE(aVersion.isProduction());

    aVersion.set("V10.20.30.40");
    TEST_ASSERT_EQUAL(10, aVersion.getMajor());
    TEST_ASSERT_EQUAL(20, aVersion.getMinor());
    TEST_ASSERT_EQUAL(30, aVersion.getBugfix());
    TEST_ASSERT_EQUAL(40, aVersion.getCandidate());
    TEST_ASSERT_FALSE(aVersion.isProduction());

    aVersion.set("1_2_3");
    TEST_ASSERT_EQUAL(1, aVersion.getMajor());
    TEST_ASSERT_EQUAL(2, aVersion.getMinor());
    TEST_ASSERT_EQUAL(3, aVersion.getBugfix());
    TEST_ASSERT_TRUE(aVersion.isProduction());
    TEST_ASSERT_EQUAL(0, aVersion.getCandidate());

    aVersion.set("V1");
    TEST_ASSERT_EQUAL(1, aVersion.getMajor());
    TEST_ASSERT_EQUAL(0, aVersion.getMinor());
    TEST_ASSERT_EQUAL(0, aVersion.getBugfix());
    TEST_ASSERT_TRUE(aVersion.isProduction());
    TEST_ASSERT_EQUAL(0, aVersion.getCandidate());

    aVersion.set("V1.2");
    TEST_ASSERT_EQUAL(1, aVersion.getMajor());
    TEST_ASSERT_EQUAL(2, aVersion.getMinor());
    TEST_ASSERT_EQUAL(0, aVersion.getBugfix());
    TEST_ASSERT_TRUE(aVersion.isProduction());
    TEST_ASSERT_EQUAL(0, aVersion.getCandidate());
}

void test_compare() {
    version first(1, 2, 3);
    version second(1, 2, 3);
    TEST_ASSERT_TRUE(first == second);
    first.set("V1.2.3.4");
    second.set("V01.02.03.04");
    TEST_ASSERT_TRUE(first == second);
    second.set("V01.02.03");
    TEST_ASSERT_FALSE(first == second);
}

void test_boundaries() {
    version aVersion("V10.20.30.40.50.60.70.80.90.00");
    TEST_ASSERT_EQUAL_STRING("V10.20.30.40", aVersion.asCharPtr());
}

void test_isProduction() {
    version theVersion("1.2.3");
    TEST_ASSERT_TRUE(theVersion.isProduction());
    theVersion.set("1.2.3.4");
    TEST_ASSERT_FALSE(theVersion.isProduction());
    theVersion.set("1.2");
    TEST_ASSERT_TRUE(theVersion.isProduction());
}

void test_maximumLength() {
    version theVersion("12.34.56.78");
    TEST_ASSERT_EQUAL_STRING("V12.34.56.78", theVersion.asCharPtr());
    theVersion.set("V12.34.56.78");
    TEST_ASSERT_EQUAL_STRING("V12.34.56.78", theVersion.asCharPtr());
    theVersion.set("V12.34.56.7890");
    TEST_ASSERT_EQUAL_STRING("V12.34.56.78", theVersion.asCharPtr());
}

int main(int argc, char** argv) {
    UNITY_BEGIN();
    RUN_TEST(test_stripLeadingV);
    RUN_TEST(test_replaceDelimitorWithDot);
    RUN_TEST(test_isValid);
    RUN_TEST(test_initialization);
    RUN_TEST(test_setFromString);
    RUN_TEST(test_compare);
    RUN_TEST(test_boundaries);
    RUN_TEST(test_isProduction);
    RUN_TEST(test_maximumLength);
    UNITY_END();
}
