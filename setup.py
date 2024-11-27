from pybind11.setup_helpers import Pybind11Extension
from setuptools import setup
from os import path
from glob import glob

__version__ = "0.1.0"


def include(rel: str):
    return "-I" + path.abspath(rel)


epcore = Pybind11Extension(
    "epcore",
    list(sorted(glob("epcore/src/*.cc"))),
    define_macros=[("VERSION_INFO", __version__)],
    cxx_std=17,
    extra_compile_args=[include("epcore/include")],
)

setup(
    name="ep",
    requires=["pybind11"],
    extras_require= {
        "dev": [
          "pybind11",
          "pybind11-stubgen",
          "setuptools"
      ]
    },
    version=__version__,
    ext_modules=[epcore],
)
