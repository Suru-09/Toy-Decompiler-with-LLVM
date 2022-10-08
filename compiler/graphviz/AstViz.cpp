#include "AstViz.hpp"

#include <deque>
#include <string>

AstViz::AstViz(const std::vector<function>& ast)
: ast(ast), node_counter(0)
{
}

void AstViz::init_viz() 
{
    render<<"digraph AST {\n";
    render << "\trankdir=\"LR\";\n";
    render << "\tnode [shape = \"box\"];\n";
    
}

std::string quote_string(const std::string& str) 
{
    return "\"" + str + "\"";
}

void AstViz::draw() 
{
    const std::string render_path = "../graphviz/astPNG/render.dot";
    for(const auto& fun : ast) {
        render.open(render_path);

        init_viz();
        create_subgraph(fun);
        render << "\n}";
        render.close();

        std::string command = 
            std::string("dot -Tpng ../graphviz/astPNG/render.dot -o ../graphviz/astPNG/render_") + 
            fun.name + ".png";
        
        system(command.c_str());
    }
}

void AstViz::create_subgraph(const function& fun) 
{
    draw_connections(fun.code, node_counter, 0);
    render << create_node(fun.name, node_counter++);
    std::deque<std::pair<expression, long>> Q;
    create_Q(Q, fun.code);
}

std::string AstViz::create_node(const std::string& label, const long& num) 
{
    return "\tnode_" + std::to_string(num) + "[label = " + quote_string(label) + "];\n";
}

std::string AstViz::create_edge(const long& node1_cnt, const long& node2_cnt) 
{
    return "\tnode_" + std::to_string(node1_cnt) + " -> node_" + std::to_string(node2_cnt) + "\n";
}

void AstViz::draw_connections(const expression& e, const long& cnt, const long& level_width)
{
    long offset = 0;
    for(const auto& p : e.params)
    {
        std::cout << "Edge: " << cnt << " -> " << cnt + level_width + offset + 1 << "\n";
        render << create_edge(cnt, cnt + level_width + offset + 1);
        offset++;
    }
}

std::string AstViz::exp_to_string(const expression& e, bool stmt, const std::string& fun_name) 
{
    switch(e.type) 
    {
        case exp_type::nop:
            return "";
        case exp_type::string:
            return e.str_value;
        case exp_type::number:
            return std::to_string(e.num_value);
        case exp_type::id:
            return e.id.name;
        case exp_type::less:
            return "less";
        case exp_type::less_eq:
            return "less_eq";
        case exp_type::grt:
            return "grt";
        case exp_type::grt_eq:
            return "grt_eq";
        case exp_type::add:
            return "add";
        case exp_type::neg:
            return "neg";
        case exp_type::mul:
            return "mul";
        case exp_type::div:
            return "div";
        case exp_type::eq:
            return "eq";
        case exp_type::cor:
            return "cor";
        case exp_type::cand:
            return "cand";
        case exp_type::cond:
            return "if";
        case exp_type::els:
            return "else";
        case exp_type::loop:
            return "while";
        case exp_type::fcall:
            return "Function call";
        case exp_type::copy:
            return "copy";
        case exp_type::comma:
            return "comma";
        case exp_type::ret:
            return "return";
    }
}

void AstViz::create_Q(std::deque<std::pair<expression, long>>& Q, const expression& e)
{
    for(const auto& p : e.params) 
    {
        Q.push_back(std::make_pair(p, e.params.size()));
    }

    while(!Q.empty()) 
    {
        auto exp = Q.front().first;
        std::cout << exp_to_string(exp) <<  "[" << node_counter << "]\n";
        std::cout << "-------\n";

        auto count_depth = Q.front().second > 1 ? Q.front().second - 1 : Q.front().second;
        Q.size() == 1 ? count_depth-- : count_depth;

        draw_connections(exp, node_counter, count_depth);
        
        if(Q.size() > 1)
        {
            std::cout << exp.params.size() << "\n";
            Q[1].second = Q[0].second + exp.params.size() - 1;
        }
        render << create_node(exp_to_string(exp), node_counter++);
        Q.pop_front();

        if(!exp.params.empty())
        {
            create_Q(Q, exp);
        }
    }
}