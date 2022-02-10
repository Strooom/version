#pragma once

class version {
  public:
    static constexpr uint32_t versionLength{11U + 1U};        // maximum length of string holding the version, eg "12.20.30.10"
    char theVersion[versionLength];                           // string holding the version, eg "3.0.0"
    version(const char* aVersion);                            // constructor, pass (eg.) "3_0_0" or "3.0.0" to initialize.
    void set(const char* aVersion);                           // set version to a new value,  pass (eg.) "3_0_0" or "3.0.0" to initialize.
    bool isValid(const char* aVersion) const;                 // check if aVersion string is a valid format - currently only checking for non-empty string
    bool isValid() const;                                     // check if version object holds a valid version string - currently only checking for non-empty string

  private:
    void convertUnderscoresToDots();    // as dots as separator are a bit awkward for filenames, we use underscores there. Then we convert the underscores to dots for a uniform representation
};

