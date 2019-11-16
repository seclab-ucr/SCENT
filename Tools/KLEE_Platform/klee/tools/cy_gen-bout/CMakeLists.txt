#===------------------------------------------------------------------------===#
#
#                     The KLEE Symbolic Virtual Machine
#
# This file is distributed under the University of Illinois Open Source
# License. See LICENSE.TXT for details.
#
#===------------------------------------------------------------------------===#
add_executable(cy_gen-bout
  cy_gen-bout.cpp
)

set(KLEE_LIBS kleeBasic)

target_link_libraries(cy_gen-bout ${KLEE_LIBS})

install(TARGETS cy_gen-bout RUNTIME DESTINATION bin)
