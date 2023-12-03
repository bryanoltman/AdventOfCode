# Advent of Code 2023 in C++

This project uses Bazel to build and run the code. To run the code for a given day, run the following command:

```bash
bazel run //XX
```

Where `XX` is the day you want to run. For example, to run day 1, run the following command:

```bash
bazel run //01
```

## Setup

This project uses the vscode [clangd](https://marketplace.visualstudio.com/items?itemName=llvm-vs-code-extensions.vscode-clangd)
extension. To get this working with Bazel, we use [bazel-compile-commands-extractor](https://github.com/hedronvision/bazel-compile-commands-extractor).
To generate a new compile_commands.json file, run the following command:

```bash
bazel run @hedron_compile_commands//:refresh_all
```
