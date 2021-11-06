# 07_Environmental

Build binary files:
```shell
mkdir build && cd build
cmake ..
make
```

Build with libreadline:
```
mkdir build && cd build
cmake -DUSE_READLINE=ON ..
make
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
mkdir build && cd build && cmake .. # or cmake -DUSE_READLINE=ON ..
make tests
cd - && rm -rf build
```
