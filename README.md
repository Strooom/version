![ArduinoLint](https://github.com/strooom/version/workflows/Arduino%20Library%20Checks/badge.svg)
![UnitTestNative](https://github.com/strooom/version/workflows/Unit%20Tests%20Generic/badge.svg)
![GitHub release (latest by date)](https://img.shields.io/github/v/release/strooom/version?color=green)

# version
simplify managing the version of a SW or firmware


1 Release candidates on Staging : X.Y.Z.W (Beta versions, for internal testing only)
  * X = major release, currently 2. 1 refers to Davids code before refactoring by Pascal
  * Y = minor release, which has NEW end-user functionality. This almost always implicates also BackEnd changes : Broker, Tenant and/or Tower
  * Z = bug fix or refactoring with ONLY MCU impact, ie. no changes on the Broker, Tenant or Tower
  * W = release candidate : W
four-level version, each level 2 digits + 3 dot/underscore separators -> maximum length is 11

2 Released for customers X.Y.Z : release candidate index W is omitted