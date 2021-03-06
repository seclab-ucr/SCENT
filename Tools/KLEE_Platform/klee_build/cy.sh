cmake \
  -DENABLE_SOLVER_Z3=ON \
  -DENABLE_SOLVER_STP=OFF \
  -DENABLE_POSIX_RUNTIME=ON \
  -DENABLE_KLEE_UCLIBC=ON \
  -DKLEE_UCLIBC_PATH=../klee-uclibc\
  -DGTEST_SRC_DIR=../googletest-release-1.7.0 \
  -DENABLE_SYSTEM_TESTS=ON \
  -DENABLE_UNIT_TESTS=ON \
  ../klee
