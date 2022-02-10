#include "Arduino.h"
#include "version.h"

version::version(const char* aVersion) {
    set(aVersion);
}

void version::set(const char* aVersion) {
    strlcpy(theVersion, aVersion, versionLength);
    convertUnderscoresToDots();
}

void version::convertUnderscoresToDots() {
    char* foundPosition = strchr(theVersion, '_');
    while (foundPosition) {
        *foundPosition = '.';
        foundPosition  = strchr(foundPosition, '_');
    }
}

bool version::isValid(const char* aVersion) const {
    return (strnlen(aVersion, versionLength) > 0);
}

bool version::isValid() const {
    return (strnlen(theVersion, versionLength) > 0);
}
