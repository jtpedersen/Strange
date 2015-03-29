SET(SRCDIR "../src")

INCLUDE_DIRECTORIES(
  ${SRCDIR}
  )

ADD_EXECUTABLE(
  testStrangeAttractor
  testStrangeAttractor.cpp
  )

TARGET_LINK_LIBRARIES(
  testStrangeAttractor
  SA
  )

SETUP_TARGET_FOR_COVERAGE(
  basicCoverage
  testStrangeAttractor
  coverage)


ADD_EXECUTABLE(
  perfOne
  perfOne.cpp
  )

TARGET_LINK_LIBRARIES(
  perfOne
  SA
  )