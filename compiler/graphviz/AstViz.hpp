#ifndef AST_VIZ_HPP
#define AST_VIZ_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <deque>

#include "bison/toy_parser.hh"
// #include <graphviz/gvc.h>

class AstViz {
private:
    std::vector<function> ast;
    long node_counter;
    std::ofstream render;

    void init_viz();
    void draw_connections(const expression& e, const long& cnt, const long& ini_offset);
    void create_Q(std::deque<std::pair<expression, long>>& Q, const expression& e);

    void create_subgraph(const function& fun);
    std::string exp_to_string(const expression& e, bool stmt = false, const std::string& fun_name="");
    std::string create_node(const std::string& label, const long& num);
    std::string create_edge(const long& node1, const long& node2);

public:
    AstViz(const std::vector<function>& ast);
    void draw();
};

#endif  // AST_VIZ_HPP