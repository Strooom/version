#include "version.h"
#include "strl.h"
#include "stdio.h"
#include "stdlib.h"

version::version() {}

version::version(const char* aVersion) {
    set(aVersion);
}

version::version(uint32_t major, uint32_t minor, uint32_t bugfix) {
    set(major, minor, bugfix);
}

version::version(uint32_t major, uint32_t minor, uint32_t bugfix, uint32_t candidate) {
    set(major, minor, bugfix, candidate);
}

void version::set(const char* aVersionString) {
    char tmpVersionString[versionStringLength];
    strlcpy(tmpVersionString, aVersionString, versionStringLength);
    stripLeadingV(tmpVersionString);
    replaceDelimitorWithDot(tmpVersionString, '_');

    int tmpMajor{0};
    int tmpMinor{0};
    int tmpBugfix{0};
    int tmpCandidate{0};

    char* firstDot = strchr(tmpVersionString, '.');
    if (firstDot != nullptr) {
        *firstDot       = 0x00;
        tmpMajor        = atoi(tmpVersionString);
        char* secondDot = strchr(firstDot + 1, '.');
        if (secondDot != nullptr) {
            *secondDot     = 0x00;
            tmpMinor       = atoi(firstDot + 1);
            char* thirdDot = strchr(secondDot + 1, '.');
            if (thirdDot != nullptr) {
                *thirdDot    = 0x00;
                tmpBugfix    = atoi(secondDot + 1);
                tmpCandidate = atoi(thirdDot + 1);
                set(tmpMajor, tmpMinor, tmpBugfix, tmpCandidate);
                return;
            } else {
                tmpBugfix = atoi(secondDot + 1);
                set(tmpMajor, tmpMinor, tmpBugfix);
                return;
            }
        } else {
            tmpMinor = atoi(firstDot + 1);
            set(tmpMajor, tmpMinor, 0);
            return;
        }
    } else {
        tmpMajor = atoi(tmpVersionString);
        set(tmpMajor, 0, 0);
        return;
    }
}

void version::set(uint32_t newMajor, uint32_t newMinor, uint32_t newBugfix) {
    major      = constrain(newMajor);
    minor      = constrain(newMinor);
    bugfix     = constrain(newBugfix);
    candidate  = 0;
    production = true;
    snprintf(versionString, versionStringLength, "V%d.%d.%d", major, minor, bugfix);
}

void version::set(uint32_t newMajor, uint32_t newMinor, uint32_t newBugfix, uint32_t newCandidate) {
    major      = constrain(newMajor);
    minor      = constrain(newMinor);
    bugfix     = constrain(newBugfix);
    candidate  = constrain(newCandidate);
    production = false;
    snprintf(versionString, versionStringLength, "V%d.%d.%d.%d", major, minor, bugfix, candidate);
}

const char* version::asCharPtr() const {
    return versionString;
}

uint32_t version::getMajor() const {
    return major;
}

uint32_t version::getMinor() const {
    return minor;
}

uint32_t version::getBugfix() const {
    return bugfix;
}

uint32_t version::getCandidate() const {
    return candidate;
}

bool version::operator==(version const& aVersion) {
    return (
        (major == aVersion.major) &&
        (minor == aVersion.minor) &&
        (bugfix == aVersion.bugfix) &&
        (candidate == aVersion.candidate) &&
        (production == aVersion.production));
}

// bool version::operator!=(version const& aVersion) {
//     return !(this == aVersion);
// }

bool version::isValid(const char* versionAsString) {
    bool result{false};
    char tmpVersionAsString[versionStringLength];
    strlcpy(tmpVersionAsString, versionAsString, versionStringLength);
    uint32_t length = strnlen(tmpVersionAsString, versionStringLength);

    if (length == 0) {
        return false;
    }
    if (length >= versionStringLength) {
        return false;
    }

    char firstChar = tmpVersionAsString[0];
    if (firstChar < '0' || firstChar > '9') {
        if ((firstChar != 'V') &&
            (firstChar != 'v')) {
            return false;
        } else {
            // strip leading V
        }
    }

    replaceDelimitorWithDot(tmpVersionAsString, '_');        // could replace more delimitors with dots, eg '/', '-'
    return true;
}

bool version::isProduction() const {
    return production;
}

uint32_t version::constrain(uint32_t aValue) {
    if (aValue > maxVersionNmbr) {
        return maxVersionNmbr;
    }
    return aValue;
}

void version::replaceDelimitorWithDot(char* theString, char theDelimitor) {
    for (uint32_t index = 0; index < versionStringLength; index++) {
        if (theString[index] == 0) {
            return;
        }
        if (theString[index] == theDelimitor) {
            theString[index] = '.';
        }
    }
}

void version::stripLeadingV(char* theString) {
    if ((theString[0] == 'V') || (theString[0] == 'v')) {
        for (uint32_t index = 0; index < versionStringLength; index++) {
            theString[index] = theString[index + 1];
            if (theString[index] == 0) {
                return;
            }
        }
        theString[versionStringLength - 1] = 0;
    }
}