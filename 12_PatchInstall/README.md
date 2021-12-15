# 12_PatchInstall

### Building

Build binary files:
```shell
mkdir build && cd build
cmake .. && make
```

### Generates removing

For genertes removing enough remove `build` directory:
```shell
rm -rf build
```

### Running

Run english version:
```shell
make run_english
```

Run english version in roman format:
```shell
make run_english_roman
```

Run russian version:
```shell
make run_russian
```

Run russian version in roman format:
```shell
make run_russian_roman
```

Show man:
```shell
make show_man
```

Update `po/ru.po`:
```
make update_translation
# Update po/ru.po manually (fuzzy, etc)
```

Typical workflow:
```
mkdir build && cd build && cmake ..
make run_english
make run_english_roman
make run_russian
make run_russian_roman
make show_man
cd - && rm -rf build
```

### Installation

```shell
make
make DESTDIR=install_dir install # default DESTDIR=/ (need sudo)
```

Typical workflow:
```
mkdir build && cd build && cmake ..
make
make DESTDIR=../install install
ll ../install/usr && ll ../install/usr/share
man ../install/usr/share/man/man1/guess.l
cd ../install/usr/bin
./guess
./guess -r
LANGUAGE=ru_RU ./guess
LANGUAGE=ru_RU ./guess -r
cd ../../.. && rm -rf build
```
