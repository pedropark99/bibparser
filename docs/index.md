# Introducing `bibparser`

Hey! This is the documentation for `bibparser`, a C++ parser for [BibTex](https://www.bibtex.org/) bibliography files, which are the most commom format for bibliography management in the LaTex framework.

## A quick example of use

```cpp
#include <string>
#include <iostream>

#include "bibparser/parser.hpp"

int main()
{
    string path_to_file = './../data/example1.bib'
    Parser parser = Parser(path_to_file);
    parser.parse_bib_file();

    return 0;
}
```

## How it works

Basically, bibparser contai


