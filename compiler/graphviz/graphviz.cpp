#include <iostream>
#include <fstream>
#include <graphviz/gvc.h>


#include "bison/toy_parser.cpp"


int main(int argc, char** argv) {
    std::ofstream render("render.dot");

    render<<"digraph btree{\n";

    render << "rankdir=\"LR\";\n";
    render << "node [color = \"purple\"]\n";

    render << "\"wtf(a,b,c)\" -> {\"while(true)\", \"if(1 || 2)\"};\n";
    render<<"}\n";

    render.close();
}