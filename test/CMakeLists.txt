SET(SRCDIR "../src")

INCLUDE_DIRECTORIES(
  ${SRCDIR}
  )

ADD_EXECUTABLE(
  testStrangeAttractor
  testStrangeAttractor.cpp
  ${SRCDIR}/StrangeAttractor.cpp
  ${SRCDIR}/aabb.cpp
  ${SRCDIR}/StrangeSearcher.cpp
  ${SRCDIR}/StrangeGenerator.cpp
  ${SRCDIR}/Util.cpp
  )