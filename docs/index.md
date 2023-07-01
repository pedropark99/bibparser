# Introducing `bibparser`

Hey! This is the documentation for `bibparser`, a C++ parser for [BibTex](https://www.bibtex.org/) bibliography files, which are the most commom format for bibliography management in the LaTex framework.

## A quick example of use

After you imported the `bibparser` header, you instantiate a new `bibparser::Parser` object using the filesystem path to the BibTex file you want to parse. Now the parser imported the bib file into memory, and is ready for performing the parsing process, you just call the `parse_bib_file()` method, and the parser will produce the abstract syntax tree (AST) that represents your bib file.

```cpp
#include <string>
#include <iostream>

#include "bibparser/parser.hpp"

int main()
{
    std::string path_to_file = './../data/example1.bib'
    bibparser::Parser parser = bibparser::Parser(path_to_file);
    parser.parse_bib_file();

    return 0;
}
```

## How it works

Basically, bibparser contai


