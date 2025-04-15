# Huffman File Compressor

A C++ implementation of Huffman coding to compress and decompress text files. This project supports both compression and decompression via command-line, handles binary I/O, and includes a custom header format for storing the Huffman code map.

---

## 🚀 Features

- Compresses plain text files using Huffman coding
- Supports decompression using the compressed file
- Efficient for medium to large text files (38-52% compression typical)
- Custom header encoding for storing Huffman trees
- Fully bit-level accurate encoding and decoding

---

## 🛠️ Build Instructions

Compile with `g++`:

```bash
make all
```

Or directly:

```bash
g++ -std=c++17 main.cpp -o huffman
```

> Ensure all `.h` and `.cpp` files are in proper folders as per the include paths

---

## 📦 Usage

### Compress a file

```bash
./huffman -c input.txt
```

This will generate `input.compressed`

### Decompress a file

```bash
./huffman -d input.compressed
```

This will generate `input.decompressed`

### Specify output filename manually

```bash
./huffman -c input.txt custom_name.huff
./huffman -d custom_name.huff original.txt
```

---

## 🧪 Example

Input: `sample.txt` (1200 bytes)  
Compressed: `sample.compressed` (648 bytes)  
Compression: ~46%

---

## 📁 File Structure

| File                     | Description                               |
| ------------------------ | ----------------------------------------- |
| `main.cpp`               | Entry point and CLI handling              |
| `file.h`                 | Compression and decompression class logic |
| `huffman_tree.h/.func.h` | Tree structure and generation             |
| `utils.h`                | Binary conversion utilities               |
| `types.h`                | Type aliases                              |
| `common.h`               | Includes, constants                       |

---

## ⚠️ Notes

- For very small files, compression may increase size due to header overhead
- Compressed files are binary — do not edit them manually
- Padding is handled internally and trimmed correctly during decompression

---

## 📈 Compression Ratios Observed

| File Type               | Original Size | Compressed | Compression %   |
| ----------------------- | ------------- | ---------- | --------------- |
| Repetitive ("aaaaa...") | 99 bytes      | 12 bytes   | ~88%            |
| Natural English text    | 1.2 KB        | 650 B      | ~46%            |
| ASCII random            | 300 B         | 310 B      | -3% (increased) |

---

## ✅ To Do / Improvements

- Add support for raw/uncompressed fallback when compression fails
- Compress the header using further encoding
- Implement block-based Huffman for large files

---

## 🧑 Author

Built with love by Zed 🙌
