# 09_Testing

How install Googletest:
```shell
sudo apt-get install libgtest-dev
cd /usr/src/gtest
sudo cmake CMakeLists.txt && sudo make
sudo cp lib/*.a /usr/lib
```

Build binary files:
```shell
mkdir build && cd build
cmake .. && make
```

Build binary files with coverage:
```
mkdir build && cd build
cmake .. -DENABLE_COVERAGE=ON && make
```

Run tests via ctest:
```shell
make test
```

Run tests from binary:
```
make run_tests
```

Coverage (also generate html-s for code coverage viewing from browser):
```shell
make coverage
```

For genertes removing enough remove `build` directory:
```shell
rm -rf build
```

Typical workflow:
```
mkdir build && cd build && cmake .. # -DENABLE_COVERAGE=ON
make
make test
# make coverage
cd - && rm -rf build
```
