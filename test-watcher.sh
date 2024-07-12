function run_tests {
  cmake -S . -B build
  cmake --build build
  (cd build && ctest --output-on-failure)
}

run_tests
fswatch -o kid-car-controller/ test/ | (while read; do run_tests; done)