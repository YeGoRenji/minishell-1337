## A not so *mini* shell 🐚
This is a Project of The 42 Cursus Common Core in 1337 school that I worked on with my Teammate [@Jeffy](https://github.com/0x00Jeff)

The project consists of making an almost complete POSIX shell (Bash'ish) using barebone C (No External libraries).
## The Features ✨
Our Shell69 has the following features :
- Commands with absolute and relative paths
- Single and double quotes
- Redirections `<, >, << and >>`
- Pipes `|`
- Environment variables (and special ones such as `$?`)
- Signals (CTRL-\\, CTRL-C, CTRL-D)
- Bash builtins `echo, cd, pwd, export, unset and exit`
- Here_doc with signals
- Exit statuses follows bash conventions
- **BONUS**: 
  - `&&` and `||` with parenthesis for priorities
  - Wildcards \* in the current director
  - Subshells ! (*Yes not a part of subject but why not*)

## How it works ⚙️

The project follows this pipeline to make the code as organized as possible :
`Lexer` -> `Parser` -> `Expander` \*-> `Executor`

(\*) in case of precedence `Expanding` and `Executing` are done interchangeably.  
	Ex: `export TEST=42 && echo $TEST`
### The Lexer (Tokenizer) 🧩 :
This is where the baby steps start.
The main role of this step is :
- Identify Tokens :
  ![Tokenizer display](resources/Tokenizer.png)using a linked list that has two ends one for token next *after space* and *after no space*.
  - Checks for Lexing errors :
    TODO: work in progress