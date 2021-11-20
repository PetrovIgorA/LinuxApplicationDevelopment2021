# 08_Regexps

Build binary files:
```shell
mkdir build && cd build
cmake .. && make
```

Run tests:
```shell
make test
```

For genertes removing enough remove `build` directory:
```shell
rm -rf build
```

Typical workflow:
```
mkdir build && cd build && cmake ..
make tests
cd - && rm -rf build
```
