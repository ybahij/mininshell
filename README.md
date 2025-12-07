## 🐚 Minishell: Your Own Command Line Interpreter

**Minishell** is a **42 School** project that involves creating a simple, functional command-line interpreter (shell), much like a miniature version of **Bash**. This project is designed to deepen our understanding of **processes**, **file descriptors**, **pipes**, and **signal handling** in a UNIX-like environment.

---

## 🚀 Features

Our Minishell is implemented in **C** and strives to replicate the core behavior of a real shell.

### 🏗️ Shell Fundamentals

* **Prompt:** Displays a custom prompt (e.g., `minishell$`) when waiting for a new command.
* **Command Execution:** Searches for and executes programs based on the `$PATH` environment variable or an absolute/relative path.
* **Quoting:** Handles both **single quotes (`'`)** and **double quotes (`"`)** to prevent meta-character interpretation.
    * **Single Quotes:** Prevent all interpretation of characters within the quoted sequence.
    * **Double Quotes:** Prevent interpretation except for the dollar sign (`$`) for environment variable expansion.
* **Environment Variables:**
    * Handles **environment variable expansion** (e.g., `$USER`, `$HOME`).
    * Handles the special variable **`$?`** which expands to the exit status of the most recently executed foreground pipeline.
* **Exit Status:** The shell returns the exit status of the last executed command.

### 🔗 Redirections and Pipelines

* **Pipes (`|`):** Implements pipelines, connecting the **standard output** of one command to the **standard input** of the next. 
* **Input Redirection (`< file`):** Redirects the standard input of a command from a specified file.
* **Output Redirection (`> file`):** Redirects the standard output of a command to a specified file (creating or overwriting it).
* **Append Redirection (`>> file`):** Redirects the standard output of a command to a specified file in **append mode** (adding to the end of the file).
* **Here Document (`<< delimiter`):** Reads input from the standard input until a line containing only the specified delimiter is encountered.

### 🛠️ Built-in Commands

The following essential built-in commands are implemented with behavior matching **Bash** (without non-mandated options/arguments):

* **`echo`** with the `-n` option.
* **`cd`** with a relative or absolute path.
* **`pwd`** without any options.
* **`export`** (must manage the environment variables).
* **`unset`** (removes variables from the environment).
* **`env`** (prints the environment).
* **`exit`** with an optional numeric argument.

### 🚦 Signals

* **`ctrl-C` (SIGINT):** Displays a new prompt on a new line.
* **`ctrl-D` (EOF):** Exits the shell (like the `exit` command).
* **`ctrl-\` (SIGQUIT):** Does nothing (prevents the process from quitting).

---

## ⚙️ Architecture

The shell's execution process is typically broken down into a series of steps:

1.  **Lexer (Tokenization):** Takes the raw input line (from `readline`) and breaks it into meaningful tokens.
2.  **Parser (Syntax & Structure):** Analyzes tokens for syntax errors and converts them into a structured data representation (e.g., a linked list of command structures).
3.  **Expander:** Handles environment variable replacement and quote removal.
4.  **Executor:** Uses system calls like **`fork`**, **`execve`**, **`pipe`**, and **`dup2`** to set up redirections, pipelines, and execute commands.

---

## 💻 Installation and Usage

### Prerequisites

* **C Compiler:** GCC or Clang.
* **`make`:** For building the project.
* **GNU `readline` library:** For line editing and history.

### Build

1.  **Clone the repository:**
    ```bash
    git clone <your_repo_url>
    cd minishell
    ```

2.  **Compile the project** using the provided `Makefile`:
    ```bash
    make
    ```

### Run

Execute the `minishell` program from the repository root:

    bash
    ./minishell
    
Example:

    bash
    minishell$ echo "Hello $USER"
    Hello <your-username>
    minishell$ ls -l | grep min
    minishell$ exit 0
    
🤝 Authors:
    Youssef Bahij
    Omar Belhamid
