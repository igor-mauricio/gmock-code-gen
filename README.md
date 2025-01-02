# Welcome to the gmock-code-gen wiki!

## Quick Start

1. Install zed-platformio package

```bash
go install github.com/igor-mauricio/gmock-code-gen@latest
```

1. Run the generate command with either the path to the root folder of the source files or the path to the source file that contains the class to be mocked.

```bash
gmock-code-gen <path/to/the/root/folder>
```

### uninstall

```bash
rm -f $(which gmock-code-gen)
```
