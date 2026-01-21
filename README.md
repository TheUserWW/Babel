# Babel - Multilingual Alphabet Converter


A powerful Qt-based desktop application for converting text between various writing systems and alphabets. Inspired by the Tower of Babel, this tool enables seamless translation between different scripts and writing systems.

## Features

### 🎯 Core Functionality
- **Multi-alphabet Conversion**: Convert text between 30+ different writing systems
- **Bidirectional Conversion**: Convert from any alphabet to any other alphabet
- **Real-time Preview**: See conversion results instantly as you type
- **Phonetic Chart**: Visual reference for all supported alphabets and their mappings

### 🌐 Supported Writing Systems
- **Latin** (English, European languages)
- **Cyrillic** (Russian, Slavic languages)
- **Greek** (Modern Greek)
- **Arabic** (Arabic script)
- **Persian** (Farsi)
- **Hebrew** (Hebrew script)
- **Devanagari** (Hindi, Sanskrit)
- **Tibetan** (Tibetan script)
- **Khmer** (Cambodian)
- **Syriac** (Aramaic)
- **Hangul** (Korean)
- **Kana** (Japanese)
- **Zhuyin** (Chinese Bopomofo)
- **And many more** (30+ systems total)

### 🌍 Internationalization
- **Multi-language UI**: Arabic, Chinese, English, French, Russian, Spanish
- **Persistent Language Settings**: Remembers your preferred language
- **Locale-aware**: Automatically detects system language

### 🎨 User Experience
- **Clean Interface**: Modern Qt-based GUI
- **Font Adaptation**: Automatically adjusts fonts for different scripts
- **Progress Indicators**: Visual feedback for large conversions
- **Cross-platform**: Runs on Windows, Linux, and macOS

## Installation

### Prerequisites
- Qt 5.15+ or Qt 6.x
- C++17 compatible compiler
- CMake or qmake

### Building from Source

1. **Clone the repository**
   ```bash
   git clone <repository-url>
   cd Babel
   ```

2. **Build with qmake**
   ```bash
   qmake Babel.pro
   make
   # or on Windows with MinGW
   mingw32-make
   ```

3. **Build with CMake** (alternative)
   ```bash
   mkdir build && cd build
   cmake ..
   cmake --build .
   ```

4. **Run the application**
   ```bash
   ./Babel  # Linux/macOS
   Babel.exe  # Windows
   ```

### Pre-built Binaries
Check the [Releases](https://github.com/yourusername/Babel/releases) page for pre-compiled binaries for your platform.

## Usage

### Basic Conversion
1. **Select Source Alphabet**: Choose the writing system of your input text
2. **Select Target Alphabet**: Choose the writing system you want to convert to
3. **Enter Text**: Type or paste text in the input field
4. **View Results**: The converted text appears instantly in the output field

### Advanced Features
- **Phonetic Chart**: Access the phonetic reference chart via the menu
- **Language Switching**: Change UI language from the Settings menu
- **Font Adaptation**: The app automatically selects appropriate fonts for each script

### Example Conversions
- **English to Cyrillic**: "Hello" → "Хелло"
- **Latin to Greek**: "Alpha" → "Αλφα"
- **Arabic to Latin**: "مرحبا" → "mrḥbā"

## Project Structure

```
Babel/
├── include/           # Header files
│   ├── MainWindow.h           # Main application window
│   ├── LetterConverter.h      # Core conversion logic
│   ├── aboutdialog.h          # About dialog
│   └── phoneticchartdialog.h  # Phonetic chart dialog
├── src/               # Source files
│   ├── main.cpp               # Application entry point
│   ├── MainWindow.cpp         # Main window implementation
│   ├── LetterConverter.cpp    # Conversion implementation
│   ├── aboutdialog.cpp        # About dialog implementation
│   └── phoneticchartdialog.cpp # Phonetic chart implementation
├── ui/                # Qt Designer UI files
├── resources/         # Application resources
│   ├── mappings.json          # Alphabet conversion mappings
│   ├── app.ico               # Application icon
│   └── res.qrc               # Qt resource file
├── translations/      # Internationalization files
├── Babel.pro          # Qt project file
├── LICENSE            # GNU GPL v3 license
└── README.md          # This file
```

## Technical Details

### Architecture
- **Model-View-Controller**: Clean separation of UI, logic, and data
- **Qt Framework**: Cross-platform GUI development
- **JSON Configuration**: Alphabet mappings stored in external JSON file
- **Plugin-ready**: Designed for easy extension with new alphabets

### Key Components
- **LetterConverter**: Core conversion engine with 30+ alphabet systems
- **MainWindow**: Primary user interface with conversion controls
- **PhoneticChartDialog**: Visual reference for alphabet mappings
- **Internationalization**: Multi-language support via Qt translation system

## Contributing

We welcome contributions! Please see our [Contributing Guidelines](CONTRIBUTING.md) for details.

### Adding New Alphabets
1. Add the alphabet enum to `LetterConverter.h`
2. Add mapping rules to `resources/mappings.json`
3. Update the UI to support the new alphabet
4. Submit a pull request

### Translation Contributions
1. Create new translation files in `translations/`
2. Use Qt Linguist tool for translation
3. Test the translation in the application
4. Submit translation files

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- **Qt Framework**: For providing the excellent cross-platform development environment
- **Unicode Consortium**: For comprehensive character set standards
- **Open Source Community**: For inspiration and shared knowledge

## Support

- **Issues**: Report bugs and request features on our [Issue Tracker](https://github.com/yourusername/Babel/issues)
- **Documentation**: Check the [Wiki](https://github.com/yourusername/Babel/wiki) for detailed guides
- **Community**: Join our [Discussions](https://github.com/yourusername/Babel/discussions) for help and ideas



---
