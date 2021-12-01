# 10_I18n

Build binary files:
```shell
mkdir build && cd build
cmake .. && make
```

Run english version:
```
make run_english
```

Run russian version:
```
make run_russian
```

Update `po/ru.po`:
```
make update_translation
# Update po/ru.po manually (fuzzy, etc)
```

For genertes removing enough remove `build` directory:
```shell
rm -rf build
```

Typical workflow:
```
mkdir build && cd build && cmake ..
make run_english
make run_russian
cd - && rm -rf build
```
