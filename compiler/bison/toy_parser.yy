%skeleton "lalr1.cc"
%define api.parser.class {toy_parser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert
%define parse.error verbose
%locations
%language "C++"

%code requires {

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <list>

#define ENUM_IDENTIFIERS(o) \
        o(undefined)                              /* undefined */ \
        o(function)                               /* a pointer to givenfunction */ \
        o(parameter)                              /* one of the function params */ \
        o(variable)                               /* a local variable */
#define o(n) n,
enum class id_type {  ENUM_IDENTIFIERS(o) };
#undef o

struct identifier {
    id_type type = id_type::undefined;
    size_t index = 0;
    std::string name;
};

#define ENUM_EXPRESSIONS(o) \
        o(nop) o(string) o(number) o(id)    /* string and numbers */ \
        o(add) o(neg) o(mul) o(div) o(eq)           /* operations */    \
        o(less) o(less_eq) o(grt) o(grt_eq)                              \
        o(cor) o(cand)  o(els)                                                    \
        o(loop) o(cond)                             /* loops for while */ \
        o(addrof) o(deref)                          /* pointer operations */ \
        o(brk) o(conti)                             \
        o(fcall)                                    \
        o(copy)                                     \
        o(comma)                                    \
        o(ret)                                      
#define o(n) n,
enum class exp_type { ENUM_EXPRESSIONS(o) };
#undef o

struct expression {
    exp_type type;
    identifier id{};
    std::string str_value{};
    long num_value = 0;
    std::list<expression> params;

    template<typename... T>
    expression(exp_type t, T&& ...args) : type(t), params{  std::forward<T> (args)... } {}

    expression()    : type(exp_type::nop) {}
    expression(const identifier& id) : type(exp_type::id), id(id) {}
    expression(identifier&& id) : type(exp_type::id), id(std::move(id)) {}
    expression(std::string&& s) : type(exp_type::string), str_value(std::move(s)) {}
    expression(long v) : type(exp_type::number), num_value(v) {}

    bool immediate_value(const expression& expr) const;
    bool is_immediate_value() const;

    expression operator +=(expression&& copy) && {  return expression(exp_type::copy, std::move(copy), std::move(*this));   }
};

#define o(n) \
template<typename... T>     \
inline expression e_##n(T&&... args) { return expression(exp_type::n, std::forward<T>(args)...); }
ENUM_EXPRESSIONS(o)
#undef o

struct function {
    std::string name;
    expression code;
    unsigned num_vars = 0, num_params = 0;
};


/***
    - we need scopes for variables, functions and parameters
            - maybe std::vector<std::map<std::string, identifier>>
**/

struct toy_context;

}   // %code requires

%param { toy_context& ctx}  // %param

%code {

struct toy_context {
    const char* cursor;
    yy::location loc;
    /**
        ** Scopes -> vector index is equal to the depth of the scope
        **        -> only identifier saved here, we will use the name as the key in the map
    */
    std::vector<std::map<std::string, identifier>> scopes;
    std::vector<function> func_vec;
    function fun;
    long temp_count = 0;
public:
    /**
        ** You can define either a variable, function, function params.
        * TODO: Introduce functionality for the struct too.
    */
    const identifier& definition(const std::string& name, identifier&& id)
    {
        /**
           ** resp - actually a pair <iterator, bool>
           ** the bool shows if the element was inserted or was a duplicate
        */
        if(scopes.empty()) {
           return id;
        }

        std::cout << name << "\n";
        auto resp = scopes.back().emplace(name, std::move(id));
        if ( !resp.second ) {
            throw yy::toy_parser::syntax_error(loc, "Duplicate definition of <" + name + ">");
        }
        return resp.first->second;
    }

    expression def_var(const std::string& name)     {   return definition(name, identifier{id_type::variable, fun.num_vars++, name});   }
    expression def_fun(const std::string& name)     {   return definition(name, identifier{id_type::function, func_vec.size(), name});   }
    expression def_params(const std::string& name)  {   return definition(name, identifier{id_type::parameter, fun.num_params++, name});  }
    expression temp()   { return def_var("$"  + std::to_string(temp_count++));   }

    expression use(const std::string& name)
    {
        for(auto it = scopes.crbegin(); it != scopes.crend(); ++it) 
        {
            auto res = it->find(name);
            if (res != it->end()) 
            {
                return res->second;
            }
            std::map<std::string, identifier> map = (*it);
            std::cout << map.size() << "\n";
            for(auto m_it : map) 
            {
                std::cout << m_it.first << "\n";
            }
        }
        
        throw yy::toy_parser::syntax_error(loc, "Undefined identifier: <" + name + ">");
    }

    void add_fun(std::string&& name, expression&& code)
    {
        fun.code = e_comma(std::move(code), e_ret(0l));
        fun.name = std::move(name);
        func_vec.push_back(std::move(fun));
        fun = {};
    }

    void operator ++()  {  scopes.emplace_back();   }
    void operator --()  {  scopes.pop_back();       }
};

namespace yy {toy_parser::symbol_type yylex(toy_context& ctx); }

#define M(x) std::move(x)
#define T(x) expression(x)
}



%token END 0
%token RETURN "return" BREAK "break" WHILE "while" CONTINUE "continue" VAR "var" DEF "def" ELSE "else" IF "if"
%token IDENTIFIER NUMCONST STRINGCONST STRUCT "struct"
%token OR "||" AND "&&" EQ "==" NE "!=" PP "++" MM "--" PL_EQ "+=" MI_EQ "-=" MUL_EQ "*=" DIV_EQ "/="
%token SEMICOLON ";" LACC "{" RACC "}"  LESS_EQ "<=" GREATER_EQ ">="

%left ','
%right '?' ':'
%right '=' "+=" "-=" "*=" "/="
%left "||"
%left "&&"
%left "==" "!="
%left '<' "<=" '>' ">="
%left '+' '-'
%left '*' '/'
%right '&' "++" "--" '.'
%nonassoc '(' '['
%type<long> NUMCONST
%type<std::string> IDENTIFIER STRINGCONST
%type<expression> expr expr_h exprs exprs_h p_expr_h c_expr_h stmt_h stmt stm_compound cl_paren_h decl_vars decl_var param_decl
%%  /* Starting Grammar definition */

unit:   unit {++ctx; } decl {--ctx; } 
|       %empty;

decl: "def" "struct" IDENTIFIER { ++ctx; } stmt_h {   --ctx; }
|   "def" IDENTIFIER '(' param_decls ')' { ctx.def_fun($2); ++ctx; } stmt_h {  ctx.add_fun(M($2), M($7)); --ctx; };

param_decls: param_decl | %empty;
param_decl: param_decl ',' IDENTIFIER       {   ctx.def_params($3);  }
|           IDENTIFIER                      {   ctx.def_params($1);  };

decl_vars: "var" decl_var                   {   $$ = e_comma(M($2));  }
|           decl_vars ',' decl_var          {   $$ = M($1); $$.params.push_back(M($3)); };
decl_var:   IDENTIFIER '=' expr_h           {   $$ = ctx.def_var($1) += M($3);    }
|           IDENTIFIER                      {   $$ = ctx.def_var($1) += 0l;    };

stm_compound:   "{"                         {   $$ = e_comma(); ++ctx;  }
|               stm_compound stmt           {   $$ = M($1);    $$.params.push_back(M($2));    };

stmt_h: stmt;            //{   $$ = M($1);    };

/* semicolon_h: error {} | ";";
colon_h: error {} | ':'; */

cl_brace_h: "}";  // used for closing braces (also for error recovery)
cl_paren_h: ')';  // used for closing parenthesis (also for error recovery)
cl_bracket_h:']';    // used for closing brackets (also for error recovery)

p_expr_h: '(' exprs_h cl_paren_h            {   $$ = M($2);                 };

stmt:   stm_compound cl_brace_h             {   $$ = M($1); --ctx;          }
|       "while" p_expr_h stmt_h             {   $$ = e_loop(M($2), M($3));  } 
|       "if" p_expr_h stmt_h                {   $$ = e_cond(M($2), M($3));  }
|       decl_vars                            
|       "return" exprs_h ";"                {   $$ = e_ret(M($2));          }
|       "break" ";"                         {   $$ = e_brk();               }
|       ";"
|       exprs_h ";"                          {   $$ = M($1);                 }
|       "continue" ";"                      {   $$ = e_conti();             };           

expr_h: error{} | expr;

c_expr_h:   expr_h                          {   $$ = e_comma(M($1));        }
|           c_expr_h ',' expr_h             {   $$ = M($1); $$.params.push_back(M($3)); };   

/* c_expr_opt:     expr                        {   $$ = e_comma(M($1));        }
|               c_expr_opt ',' expr        {   $$ = M($1); $$.params.push_back(M($3)); }; */

exprs_h: error{} | exprs;

exprs:      decl_vars
|           expr
|           expr ',' c_expr_h;

expr:   NUMCONST                            {   $$ = $1;            }
|       STRINGCONST                         {   $$ = M($1);         }
|       IDENTIFIER                          {   $$ = ctx.use($1);        }
|       '(' exprs_h cl_paren_h              {   $$ = M($2);         }
|       expr '[' exprs_h cl_bracket_h       {   $$ = e_deref(e_add(M($1), M($3)));      }
|       expr '.' expr                       { }     
                                            /** 
                                                *TODO: Add functionality for accessing the element of a structure(probably a new expression).
                                            */
|       expr '(' exprs_h cl_paren_h         {   $$ = e_fcall(M($1));        }
|       expr '(' ')'                        {   $$ = e_fcall(M($1));        }
|       expr '=' expr                       {   $$ = M($1)  +=  M($3);      }
|       expr '*' expr   %prec '&'           {   $$ = e_mul(M($1), M($3));   }
|       expr '/' expr   %prec '*'           {   $$ = e_div(M($1), M($3));   }
|       expr '+' expr                       {   $$ = e_add(M($1), M($3));   }
|       expr '-' expr    %prec '+'          {   $$ = e_add(M($1), e_neg(M($3)));   }
|       expr "+=" expr                      {   if(!$3.is_immediate_value()) {   $$ = ctx.temp() += e_addrof(M($1)); $1 = $$.params.back(); }       
                                                $$ = e_comma(M($1) += e_add(T($1), M($3)) );            
                                            }

|       expr "-=" expr                      {   if(!$3.is_immediate_value()) {   $$ = ctx.temp() += e_addrof(M($1)); $1 = $$.params.back(); }       
                                                $$ = e_comma(M($1) += e_add(T($1), e_neg(M($3))) );     
                                            }

|       expr "*=" expr                      {   if(!$3.is_immediate_value()) {   $$ = ctx.temp() += e_addrof(M($1)); $1 = $$.params.back(); }       
                                                $$ = e_comma(M($1) += e_mul(T($1), M($3)) );            
                                            }

|       expr "/=" expr                      {   if(!$3.is_immediate_value()) {   $$ = ctx.temp() += e_addrof(M($1)); $1 = $$.params.back(); }       
                                                $$ = e_comma(M($1) += e_div(T($1), M($3)) );            
                                            }

|       expr '<' expr                       {   if(!$3.is_immediate_value()) {   $$ = ctx.temp() += e_addrof(M($1)); $1 = $$.params.back(); }       
                                                $$ = e_less(M($1), M($3));                              
                                            }

|       expr "<=" expr                      {   if(!$3.is_immediate_value()) {   $$ = ctx.temp() += e_addrof(M($1)); $1 = $$.params.back(); }       
                                                $$ = e_less_eq(M($1), M($3));                            
                                            }

|       expr '>' expr                       {   if(!$3.is_immediate_value()) {   $$ = ctx.temp() += e_addrof(M($1)); $1 = $$.params.back(); }       
                                                $$ = e_grt(M($1), M($3));                              
                                            }

|       expr ">=" expr                      {   if(!$3.is_immediate_value()) {   $$ = ctx.temp() += e_addrof(M($1)); $1 = $$.params.back(); }       
                                                $$ = e_grt_eq(M($1), M($3));                              
                                            }

|       "++" expr                           {   if(!$2.is_immediate_value()) {   $$ = ctx.temp() += e_addrof(M($2)); $2 = $$.params.back(); }       
                                                $$ = e_comma(M($2) += e_add(T($2), 1l) );               
                                            }

|       "--" expr   %prec "++"              {   if(!$2.is_immediate_value()) {   $$ = ctx.temp() += e_addrof(M($2)); $2 = $$.params.back(); }       
                                                $$ = e_comma(M($2) += e_add(T($2), -1l) );              
                                            }

|       expr "&&" expr                      {   $$ = e_cand(M($1), M($3));           }
|       expr "||" expr  %prec "&&"          {   $$ = e_cor(M($1), M($3));            }
|       expr "==" expr                      {   $$ = e_eq(M($1), M($3));             }
|       expr "!=" expr   %prec "=="         {   $$ = e_eq(e_eq(M($1), M($3)), 0l);   }
|       '&' expr                            {   $$ = e_addrof(M($2));                }
|       '*' expr    %prec '&'               {   $$ = e_deref(M($2));                 }
|       '-' expr    %prec '&'               {   $$ = e_neg(M($2));                   }
|       '!' expr    %prec '&'               {   $$ = e_eq(M($2), 0l);                }
|       expr '?' expr ':' expr  %prec '='   {   auto tmp = ctx.temp();   $$ = e_comma(e_cor(e_cond(M($1), M($3)), e_cond(e_neg(M($1)), M($5))));  };

%%

bool expression::is_immediate_value() const {
    for(const auto& e : params)
        if(!immediate_value(e))
            return false;
    return true;
}

bool expression::immediate_value(const expression& expr) const {
    switch(expr.type) {
        case exp_type::fcall:
        case exp_type::ret:
        case exp_type::loop:
        case exp_type::copy:
            return false;
        default:
            return true;
    }
}

yy::toy_parser::symbol_type yy::yylex(toy_context& ctx) {

    const char* anchor = ctx.cursor;
    ctx.loc.step();
    auto s = [&](auto func, auto&&... params) { ctx.loc.columns(ctx.cursor - anchor); return func(params..., ctx.loc); };

/*!re2c
re2c:yyfill:enable   = 0;
re2c:define:YYCTYPE  = "char";
re2c:define:YYCURSOR = "ctx.cursor";

// Keywords
"return"            { return s(toy_parser::make_RETURN); }
"break"             { return s(toy_parser::make_BREAK); }
"continue"          { return s(toy_parser::make_CONTINUE); }
"while"             { return s(toy_parser::make_WHILE); }
"var"               { return s(toy_parser::make_VAR); }
"if"                { return s(toy_parser::make_IF); }
"def"               { return s(toy_parser::make_DEF); }
"else"              { return s(toy_parser::make_ELSE); }
"struct"            { return s(toy_parser::make_STRUCT); }

// Identifiers
[a-zA-Z_] [a-zA-Z_0-9]*     { return s(toy_parser::make_IDENTIFIER, std::string(anchor, ctx.cursor)); }

// String and integer literals
"\"" [^"]* "\""         { return s(toy_parser::make_STRINGCONST, std::string(anchor + 1, ctx.cursor - 1)); }
[0-9]+                  { return s(toy_parser::make_NUMCONST, std::stol(std::string(anchor, ctx.cursor))); }

// Whitespace and comments:
"\000"  | "EOF"         { return s(toy_parser::make_END); }
"\r\n" | [\r\n]         { ctx.loc.lines();   return yylex(ctx); }
"//" [^\r\n]*           {                    return yylex(ctx); }
[\t\v\b\f ]             { ctx.loc.columns(); return yylex(ctx); }


// Multi-char operators and any other characters
"&&"                    { return s(toy_parser::make_AND); }
"||"                    { return s(toy_parser::make_OR); }
"++"                    { return s(toy_parser::make_PP); }
"--"                    { return s(toy_parser::make_MM); }
"!="                    { return s(toy_parser::make_NE); }
"=="                    { return s(toy_parser::make_EQ); }
"+="                    { return s(toy_parser::make_PL_EQ); }
"-="                    { return s(toy_parser::make_MI_EQ); }
"*="                    { return s(toy_parser::make_MUL_EQ); }
"/="                    { return s(toy_parser::make_DIV_EQ); }
";"                     { return s(toy_parser::make_SEMICOLON); }
"{"                     { return s(toy_parser::make_LACC); }
"}"                     { return s(toy_parser::make_RACC); }
"<="                     { return s(toy_parser::make_LESS_EQ); }
">="                     { return s(toy_parser::make_GREATER_EQ); }
. 
                      { return s([](auto...s){return toy_parser::symbol_type(s...);}, toy_parser::token_type(ctx.cursor[-1]&0xFF)); } // Returns that character

*/  // END of re2c
}

void yy::toy_parser::error(const location_type& l, const std::string& m)
{
    std::cerr << (l.begin.filename ? l.begin.filename->c_str() : "(undefined)");
    std::cerr << ':' << l.begin.line << ':' << l.begin.column << '-' << l.end.column << ": " << m << '\n';
}
