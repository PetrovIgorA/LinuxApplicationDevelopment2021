# 11_Documenting

Help:
```
Usage: guess [OPTION...]
Guess number in arabic or roman format from 0 to 100

  -r, --roman                Guess numbers in roman format;
  -?, --help                 Give this help list;
      --usage                Give a short usage message;
  -V, --version              Print program version;

Report bugs to petrov.igor.a@gmail.com.
```

Build binary files:
```shell
mkdir build && cd build
cmake .. && make
```

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

Generate man file (in `build/guess.l`) and show this file via man:
```shell
make generate_and_show_man
```

Generate documentation (`build/doc`), you can to show in browser (`build/doc/html/index.html`):
```shell
make doc
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
make run_english_roman
make run_russian
make run_russian_roman
make generate_and_show_man
make doc # Show in build/doc/html/index.html
cd - && rm -rf build
```
