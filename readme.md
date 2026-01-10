# Huffman File Compressor (C++)

## 📌 Overview

This is a **self-implemented Huffman-based file compression tool written in C++**, built to understand **lossless compression**, **binary file formats**, and **bit-level I/O**.

The project implements the full compression → storage → decompression pipeline from scratch, including Huffman tree construction, custom header encoding, and exact bit-level reconstruction of the original file.

No libraries doing the heavy lifting. Just algorithms, bytes, and edge cases.

---

## 🎯 Motivation

This project was built to:

- Implement **Huffman coding end-to-end**, not just the tree
- Work directly with **binary streams and bit packing**
- Design a **custom file format** with headers and padding
- Understand why compression sometimes _fails_ instead of magically improving everything
- Prioritize **correctness and reversibility** over convenience

If the output decompresses to the exact original byte-for-byte, the code did its job. Anything else is a bug.

---

## 🚀 Features

- Lossless compression of text files using **Huffman coding**
- Full **decompression support** via command-line
- Custom binary file format with embedded Huffman metadata
- Bit-level accurate encoding and decoding
- Typical compression ratios of **38–52%** for natural language text
- Clean CLI interface with explicit compress/decompress modes

---

## 🛠️ Build

Compile using `g++`:

```bash
make all
```

Or directly:

```bash
g++ -std=c++17 main.cpp -o huffman
```

> Ensure all `.h` and `.cpp` files are placed according to the include paths.

---

## 📦 Usage

### Compress a file

```bash
./huffman -c input.txt
```

Output:

```
input.compressed
```

---

### Decompress a file

```bash
./huffman -d input.compressed
```

Output:

```
input.decompressed
```

---

### Custom output filenames

```bash
./huffman -c input.txt output.huff
./huffman -d output.huff original.txt
```

---

## 🧪 Example

**Input**

```
sample.txt — 1200 bytes
```

**Compressed**

```
sample.compressed — 648 bytes
```

**Compression ratio**

```
~46%
```

---

## 📁 File Structure

| File             | Responsibility                    |
| ---------------- | --------------------------------- |
| `main.cpp`       | CLI parsing and program entry     |
| `file.h`         | Compression / decompression logic |
| `huffman_tree.h` | Huffman tree structure            |
| `func.h`         | Tree construction and traversal   |
| `utils.h`        | Bit manipulation utilities        |
| `types.h`        | Type aliases                      |
| `common.h`       | Shared includes and constants     |

---

## ⚠️ Design Notes & Limitations

- Very small files may **increase in size** due to header overhead
- Compressed output is binary — manual edits will corrupt it
- Padding bits are tracked and trimmed correctly during decompression
- Designed for **clarity and correctness**, not maximum throughput

---

## 📈 Observed Compression Ratios

| Input Type           | Original | Compressed | Result         |
| -------------------- | -------- | ---------- | -------------- |
| Highly repetitive    | 99 B     | 12 B       | ~88%           |
| Natural English text | 1.2 KB   | 650 B      | ~46%           |
| Random ASCII         | 300 B    | 310 B      | -3% (expected) |

Negative compression is not a bug — it’s reality.

---

## 🔧 Possible Improvements

- Skip compression when output would be larger
- Compress header metadata
- Block-based Huffman encoding for very large files
- Add binary file support beyond plain text

---

## 🧠 What This Project Demonstrates

- Solid understanding of **Huffman coding**
- Bit-level binary I/O in C++
- Custom file format design
- Edge-case handling in compression algorithms
- Focus on correctness over hype
