import os
from setuptools import setup, Extension
import pybind11

# Get the absolute path of the directory containing this setup.py file
ROOT_DIR = os.path.dirname(os.path.abspath(__file__))

# Define absolute paths for source and include directories
# This now points to 'include' as specified in your CMakeLists.txt
SRC_DIR = os.path.join(ROOT_DIR, 'src')
BINDINGS_DIR = os.path.join(ROOT_DIR, 'bindings')
INCLUDE_DIR = os.path.join(ROOT_DIR, 'include') # <-- CORRECTED PATH

# --- Verification Step (Optional) ---
# You can uncomment the lines below to print the paths and verify they are correct
# print(f"--- Using ROOT_DIR: {ROOT_DIR}")
# print(f"--- Using INCLUDE_DIR: {INCLUDE_DIR}")
# print(f"--- Does INCLUDE_DIR exist? {'Yes' if os.path.isdir(INCLUDE_DIR) else 'No'}")
# print(f"--- Using SRC_DIR: {SRC_DIR}")
# ------------------------------------

# Automatically find all .cpp files to compile and link
sources = [os.path.join(BINDINGS_DIR, 'bindings.cpp')]
if os.path.isdir(SRC_DIR):
    for root, _, files in os.walk(SRC_DIR):
        for file in files:
            if file.endswith('.cpp'):
                sources.append(os.path.join(root, file))

# Compiler arguments for Linux
cpp_args = ['-std=c++11']

sfc_module = Extension(
    'maptio',
    sources=sources,
    include_dirs=[
        pybind11.get_include(),
        INCLUDE_DIR, # Use the corrected absolute path
        SRC_DIR      # Added src dir as it's in your CMake include paths
    ],
    language='c++',
    extra_compile_args=cpp_args,
)

setup(
    name='maptio',
    version='1.0',
    description='Python package with C++ extension for maptio',
    ext_modules=[sfc_module],
)