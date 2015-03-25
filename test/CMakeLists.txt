SET(SRCDIR "../src")

INCLUDE_DIRECTORIES(
  ${SRCDIR}
  )

ADD_EXECUTABLE(
  testStrangeAttractor
  testStrangeAttractor.cpp
  ${SRCDIR}/StrangeAttractor.cpp
  )