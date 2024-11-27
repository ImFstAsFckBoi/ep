# ep - editor project

a (VERY!) work in progress just for fun terminal editor

meant to be like "emacs but python" instead of elisp (editor is an interactive interpreter session)

built with python (of course) and C++ with [pybind11](https://github.com/pybind/pybind11)

## build & run

```sh
make venv
source .venv/bin/activate
make dev
python3 -m ep.main
```