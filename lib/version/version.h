#pragma once
#include "stdint.h"

class version {
  public:
    version();                                                                           // empty constructor, use a set() method afterwards..
    version(const char* aVersion);                                                       // constructor, pass (eg.) "V3_0_0" or "V3.0.0" to initialize.
    version(uint32_t major, uint32_t minor, uint32_t bugfix);                            // constructor, pass (1,2,3) to initialize.
    version(uint32_t major, uint32_t minor, uint32_t bugfix, uint32_t candidate);        // constructor, pass (1,2,3, 4) to initialize.

    void set(const char* aVersion);                                                       // set version to a new value,  pass (eg.) "3_0_0" or "3.0.0" to initialize.
    void set(uint32_t major, uint32_t minor, uint32_t bugfix);                            // set version to a new value,  pass (eg.) "3_0_0" or "3.0.0" to initialize.
    void set(uint32_t major, uint32_t minor, uint32_t bugfix, uint32_t candidate);        // set version to a new value,  pass (eg.) "3_0_0" or "3.0.0" to initialize.

    const char* asCharPtr() const;        // returns pointer to cstring holding the version as a string
    uint32_t getMajor() const;
    uint32_t getMinor() const;
    uint32_t getBugfix() const;
    uint32_t getCandidate() const;

    static bool isValid(const char* aVersion);        // check if string holds a valid version string
    bool isProduction() const;                        // X.Y.Z  is production, X.Y.Z.W is development

    bool operator==(version const& aVersion);
    bool operator!=(version const& aVersion);
    bool operator<(version const& aVersion);
    bool operator>(version const& aVersion);
    bool operator<=(version const& aVersion);
    bool operator>=(version const& aVersion);

    static constexpr uint32_t maxVersionNmbr{99U};                  // maximum value for each digit, eg 0 - 99
    static constexpr uint32_t versionStringLength{12U + 1U};        // maximum length of string holding the version, eg "V12.20.30.10"

  private:
    char versionString[versionStringLength];        // string holding the version, eg "3.0.0"
    uint32_t major{0};                              //
    uint32_t minor{0};                              //
    uint32_t bugfix{0};                             //
    uint32_t candidate{0};                          //
    bool production{true};                          // V1.2.3 is production, V1.2.3.4 is development
  
  public:
    static void replaceDelimitorWithDot(char* theString, char theDelimitor);        // as dots as separator are a bit awkward for filenames, we use underscores there. Then we convert the underscores to dots for a uniform representation
    static void stripLeadingV(char* theString);
    static uint32_t constrain(uint32_t aValue);        // constrain aValue to [0, 99], ie. two digits maximum
};
