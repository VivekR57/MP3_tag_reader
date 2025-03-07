# 🎵 MP3 Tag Reader and Editor

The **MP3 Tag Reader and Editor** is a **C-based** command-line tool designed to read and modify **ID3 tags** in **MP3 files**. ID3 tags store metadata such as **title**, **artist**, **album**, **year**, **genre**, and **comments**, enabling efficient management of music collections. The project emphasizes **file handling**, **bitwise operations**, and **command-line interface (CLI)** for robust and user-friendly metadata management.

---

## 🛠 Project Features

- **Read MP3 Metadata:** Extract and display **ID3 tag** information.
- **Edit MP3 Metadata:** Modify fields like **title**, **artist**, **album**, **year**, **genre**, and **comments**.
- **ID3v2 Tag Support:** Compatible with **ID3v2** metadata standard.
- **Command-Line Interface:** Simple and efficient usage through terminal commands.
- **Error Handling & Validation:** Processes only **valid MP3 files**, ensuring data integrity.

---

## 🧰 Technology Stack

- **Programming Language:** C
- **Key Concepts:**
  - **File Handling:** Reading and writing **MP3 tags** using **fopen()**, **fread()**, **fwrite()**, and **fclose()**.
  - **Bitwise Operations:** Data conversion between **big-endian** and **little-endian** formats.
  - **Command-Line Parsing:** Using **argc** and **argv** for input arguments.
  - **Structs and Enums:** Efficient data management and metadata representation.

---

## 🔄 Project Workflow

### 1. **Viewing MP3 Metadata:**

```bash
./a.out -v sample.mp3
```

**Example Output:**

```bash
TITLE    :   Song Name
ARTIST   :   Artist Name
ALBUM    :   Album Name
YEAR     :   2021
MUSIC    :   Genre
COMMENT  :   Sample Comment
```

### 2. **Editing MP3 Metadata:**

```bash
./a.out -e -y 2023 sample.mp3
```

**Example Output:**

```bash
YEAR: 2023
YEAR CHANGED SUCCESSFULLY
```

---

## 📂 File Structure

- `main.c` - Main program logic and **CLI parsing**.
- `id3_reader.c` - Extracts and displays **ID3 tag** information.
- `id3_editor.c` - Modifies specific **ID3 tag** fields.
- `file_operations.c` - Manages **file I/O** and **metadata updates**.
- `validation.c` - Ensures **file integrity** and **input validation**.
- `bitwise_utils.c` - Handles **bitwise operations** for data conversion.
- `id3v2.h` - **Header file** with **struct definitions** and **function prototypes**.

---

## 🚀 Future Enhancements

- **GUI Support:** Develop a **graphical interface** for easier use.
- **Batch Processing:** Allow **editing metadata** of multiple **MP3 files** simultaneously.
- **ID3v1 Tag Support:** Add **backward compatibility** with older **MP3 formats**.
- **Streaming Integration:** Fetch **metadata updates** from **music streaming services**.
- **Advanced Editing:** Add support for **album art** and **extended metadata** fields.

---

## 📧 Contact

For any questions, feel free to reach out:

- **Vivek**
- Email: [gopivivek57@gmail.com](mailto:gopivivek57@gmail.com)
- LinkedIn: [Vivek](https://www.linkedin.com/in/vivek57/)

