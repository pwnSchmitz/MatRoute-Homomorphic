# RouteCipher

### Homomorphic Encryption via Numerical Matrix Routing

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++17](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/CMake-3.10+-brightgreen.svg)](https://cmake.org/)
[![Tests](https://img.shields.io/badge/tests-passing-brightgreen.svg)](https://github.com/yourusername/RouteCipher/actions)

**RouteCipher** is an experimental homomorphic encryption scheme that leverages graph-theoretic routing through a numerical matrix. Unlike traditional lattice-based or RSA approaches, arithmetic operations (addition and multiplication) are represented as **path composition** and **overlay** on a 2D grid.

The secret key defines allowable trajectories, and decryption recovers the original value by aggregating the cell weights along the traversed path.

---

## Core Concept

1. **Matrix as Computation Space**  
   A public `n × n` numeric matrix serves as the "playground" for encrypted computation.

2. **Encryption**  
   A plaintext character is encoded as a set of edges (routes) through the matrix, with random perturbations to ensure semantic security.

3. **Homomorphic Properties**  
   - **Addition** → Union / superposition of two routes.
   - **Multiplication** → Composition (traverse route A, then route B with matrix transposition).

4. **Decryption**  
   The secret key (a vector of column/row weights) reconstructs the original character from the path's total weight.

---

## Features

- Matrix-based encryption with intuitive geometric interpretation
- Support for Latin (A-Z) and Cyrillic (А-Я) alphabets
- 150 unique routes per character for enhanced security
- Automatic key rotation after 2 operations (forward secrecy)
- Random route generation with 1-100 points
- UTF-8 character support
- Modular C++ architecture with clean separation of concerns
- CMake-based build system for cross-platform compatibility
- File I/O operations for encrypted/decrypted text

---

## Project Structure

```bash
crypto_system/
├── CMakeLists.txt              # Build configuration
├── README.md                   # This file
├── include/
│   ├── core/
│   │   ├── Matrix.h           # Matrix management
│   │   ├── Route.h            # Route representation
│   │   └── Alphabet.h         # Character mapping
│   ├── crypto/
│   │   ├── Encryptor.h        # Encryption logic
│   │   └── Decryptor.h        # Decryption logic
│   └── utils/
│       ├── FileUtils.h        # File operations
│       └── StringUtils.h      # UTF-8 utilities
├── src/
│   ├── core/
│   │   ├── Matrix.cpp
│   │   ├── Route.cpp
│   │   └── Alphabet.cpp
│   ├── crypto/
│   │   ├── Encryptor.cpp
│   │   └── Decryptor.cpp
│   ├── utils/
│   │   ├── FileUtils.cpp
│   │   └── StringUtils.cpp
│   └── main.cpp               # Application entry point
├── tests/                     # Unit tests (optional)
│   ├── CMakeLists.txt
│   ├── test_matrix.cpp
│   └── test_crypto.cpp
├── data/
│   └── matrix_200x200.txt    # Default matrix file
└── build/                    # Build directory (generated)
```

## 🛠 Installation

```bash
git clone https://github.com/yourusername/RouteCipher.git
cd RouteCipher
pip install -r requirements.txt
