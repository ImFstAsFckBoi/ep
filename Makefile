ifeq ($(OS), Windows_NT)
	PY = python
else
	PY = python3
endif

PIP = ${PY} -m pip


CLEAN_LIST = *.so build/ dist/ *.egg-info/ .mypy_cache/ .pytest_cache/ *.pyi .ruff_cache __pycache__

dev:
	${PIP} install -e . --no-build-isolation --verbose
	pybind11-stubgen epcore -o .

install:
	${PIP} install .

venv:
	${PY} -m venv .venv

test:
	${PY} -m pytest tests/ -W ignore::DeprecationWarning

clean:
	rm -rf ${CLEAN_LIST}

full-clean: clean
	rm -rf .venv/
