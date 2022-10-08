#include <iostream>
#include <fstream>

#include "bison/toy_parser.cpp"
#include "graphviz/AstViz.hpp"


int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Try giving a file name like this: " << argv[0] << " <file_name> \n";
        exit(3); 
    }

    std::string filename = argv[1];
    std::ifstream f(filename);
    std::string buffer(std::istreambuf_iterator<char>(f), {});
    
    toy_context ctx;
    ctx.cursor = buffer.c_str();

    yy::toy_parser parser(ctx);
    parser.parse();
    f.close();

    AstViz ast(std::move(ctx.func_vec));
    ast.draw();
}