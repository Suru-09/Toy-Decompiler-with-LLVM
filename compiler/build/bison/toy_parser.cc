// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "toy_parser.hh"


// Unqualified %code blocks.
#line 97 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"


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

#line 125 "toy_parser.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 217 "toy_parser.cc"

  /// Build a parser object.
  toy_parser::toy_parser (toy_context& ctx_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      ctx (ctx_yyarg)
  {}

  toy_parser::~toy_parser ()
  {}

  toy_parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  toy_parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  toy_parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  toy_parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  toy_parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  toy_parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  toy_parser::symbol_kind_type
  toy_parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  toy_parser::stack_symbol_type::stack_symbol_type ()
  {}

  toy_parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_param_decl: // param_decl
      case symbol_kind::S_decl_vars: // decl_vars
      case symbol_kind::S_decl_var: // decl_var
      case symbol_kind::S_stm_compound: // stm_compound
      case symbol_kind::S_stmt_h: // stmt_h
      case symbol_kind::S_cl_paren_h: // cl_paren_h
      case symbol_kind::S_p_expr_h: // p_expr_h
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_expr_h: // expr_h
      case symbol_kind::S_c_expr_h: // c_expr_h
      case symbol_kind::S_exprs_h: // exprs_h
      case symbol_kind::S_exprs: // exprs
      case symbol_kind::S_expr: // expr
        value.YY_MOVE_OR_COPY< expression > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMCONST: // NUMCONST
        value.YY_MOVE_OR_COPY< long > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRINGCONST: // STRINGCONST
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  toy_parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_param_decl: // param_decl
      case symbol_kind::S_decl_vars: // decl_vars
      case symbol_kind::S_decl_var: // decl_var
      case symbol_kind::S_stm_compound: // stm_compound
      case symbol_kind::S_stmt_h: // stmt_h
      case symbol_kind::S_cl_paren_h: // cl_paren_h
      case symbol_kind::S_p_expr_h: // p_expr_h
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_expr_h: // expr_h
      case symbol_kind::S_c_expr_h: // c_expr_h
      case symbol_kind::S_exprs_h: // exprs_h
      case symbol_kind::S_exprs: // exprs
      case symbol_kind::S_expr: // expr
        value.move< expression > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMCONST: // NUMCONST
        value.move< long > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRINGCONST: // STRINGCONST
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  toy_parser::stack_symbol_type&
  toy_parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_param_decl: // param_decl
      case symbol_kind::S_decl_vars: // decl_vars
      case symbol_kind::S_decl_var: // decl_var
      case symbol_kind::S_stm_compound: // stm_compound
      case symbol_kind::S_stmt_h: // stmt_h
      case symbol_kind::S_cl_paren_h: // cl_paren_h
      case symbol_kind::S_p_expr_h: // p_expr_h
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_expr_h: // expr_h
      case symbol_kind::S_c_expr_h: // c_expr_h
      case symbol_kind::S_exprs_h: // exprs_h
      case symbol_kind::S_exprs: // exprs
      case symbol_kind::S_expr: // expr
        value.copy< expression > (that.value);
        break;

      case symbol_kind::S_NUMCONST: // NUMCONST
        value.copy< long > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRINGCONST: // STRINGCONST
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  toy_parser::stack_symbol_type&
  toy_parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_param_decl: // param_decl
      case symbol_kind::S_decl_vars: // decl_vars
      case symbol_kind::S_decl_var: // decl_var
      case symbol_kind::S_stm_compound: // stm_compound
      case symbol_kind::S_stmt_h: // stmt_h
      case symbol_kind::S_cl_paren_h: // cl_paren_h
      case symbol_kind::S_p_expr_h: // p_expr_h
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_expr_h: // expr_h
      case symbol_kind::S_c_expr_h: // c_expr_h
      case symbol_kind::S_exprs_h: // exprs_h
      case symbol_kind::S_exprs: // exprs
      case symbol_kind::S_expr: // expr
        value.move< expression > (that.value);
        break;

      case symbol_kind::S_NUMCONST: // NUMCONST
        value.move< long > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRINGCONST: // STRINGCONST
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  toy_parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  toy_parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  toy_parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  toy_parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  toy_parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  toy_parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  toy_parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  toy_parser::debug_level_type
  toy_parser::debug_level () const
  {
    return yydebug_;
  }

  void
  toy_parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  toy_parser::state_type
  toy_parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  toy_parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  toy_parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  toy_parser::operator() ()
  {
    return parse ();
  }

  int
  toy_parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (ctx));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_param_decl: // param_decl
      case symbol_kind::S_decl_vars: // decl_vars
      case symbol_kind::S_decl_var: // decl_var
      case symbol_kind::S_stm_compound: // stm_compound
      case symbol_kind::S_stmt_h: // stmt_h
      case symbol_kind::S_cl_paren_h: // cl_paren_h
      case symbol_kind::S_p_expr_h: // p_expr_h
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_expr_h: // expr_h
      case symbol_kind::S_c_expr_h: // c_expr_h
      case symbol_kind::S_exprs_h: // exprs_h
      case symbol_kind::S_exprs: // exprs
      case symbol_kind::S_expr: // expr
        yylhs.value.emplace< expression > ();
        break;

      case symbol_kind::S_NUMCONST: // NUMCONST
        yylhs.value.emplace< long > ();
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRINGCONST: // STRINGCONST
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // $@1: %empty
#line 200 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
             {++ctx; }
#line 736 "toy_parser.cc"
    break;

  case 3: // unit: unit $@1 decl
#line 200 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                            {--ctx; }
#line 742 "toy_parser.cc"
    break;

  case 5: // $@2: %empty
#line 203 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                { ++ctx; }
#line 748 "toy_parser.cc"
    break;

  case 6: // decl: "def" "struct" IDENTIFIER $@2 stmt_h
#line 203 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                                  {   --ctx; }
#line 754 "toy_parser.cc"
    break;

  case 7: // $@3: %empty
#line 204 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                         { ctx.def_fun(yystack_[3].value.as < std::string > ()); ++ctx; }
#line 760 "toy_parser.cc"
    break;

  case 8: // decl: "def" IDENTIFIER '(' param_decls ')' $@3 stmt_h
#line 204 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                                                            {  ctx.add_fun(M(yystack_[5].value.as < std::string > ()), M(yystack_[0].value.as < expression > ())); --ctx; }
#line 766 "toy_parser.cc"
    break;

  case 11: // param_decl: param_decl ',' IDENTIFIER
#line 207 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   ctx.def_params(yystack_[0].value.as < std::string > ());  }
#line 772 "toy_parser.cc"
    break;

  case 12: // param_decl: IDENTIFIER
#line 208 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   ctx.def_params(yystack_[0].value.as < std::string > ());  }
#line 778 "toy_parser.cc"
    break;

  case 13: // decl_vars: "var" decl_var
#line 210 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = e_comma(M(yystack_[0].value.as < expression > ()));  }
#line 784 "toy_parser.cc"
    break;

  case 14: // decl_vars: decl_vars ',' decl_var
#line 211 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = M(yystack_[2].value.as < expression > ()); yylhs.value.as < expression > ().params.push_back(M(yystack_[0].value.as < expression > ())); }
#line 790 "toy_parser.cc"
    break;

  case 15: // decl_var: IDENTIFIER '=' expr_h
#line 212 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = ctx.def_var(yystack_[2].value.as < std::string > ()) += M(yystack_[0].value.as < expression > ());    }
#line 796 "toy_parser.cc"
    break;

  case 16: // decl_var: IDENTIFIER
#line 213 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = ctx.def_var(yystack_[0].value.as < std::string > ()) += 0l;    }
#line 802 "toy_parser.cc"
    break;

  case 17: // stm_compound: "{"
#line 215 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = e_comma(); ++ctx;  }
#line 808 "toy_parser.cc"
    break;

  case 18: // stm_compound: stm_compound stmt
#line 216 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = M(yystack_[1].value.as < expression > ());    yylhs.value.as < expression > ().params.push_back(M(yystack_[0].value.as < expression > ()));    }
#line 814 "toy_parser.cc"
    break;

  case 19: // stmt_h: stmt
#line 218 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
        { yylhs.value.as < expression > () = yystack_[0].value.as < expression > (); }
#line 820 "toy_parser.cc"
    break;

  case 23: // p_expr_h: '(' exprs_h cl_paren_h
#line 227 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = M(yystack_[1].value.as < expression > ());                 }
#line 826 "toy_parser.cc"
    break;

  case 24: // stmt: stm_compound cl_brace_h
#line 229 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = M(yystack_[1].value.as < expression > ()); --ctx;          }
#line 832 "toy_parser.cc"
    break;

  case 25: // stmt: "while" p_expr_h stmt_h
#line 230 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = e_loop(M(yystack_[1].value.as < expression > ()), M(yystack_[0].value.as < expression > ()));  }
#line 838 "toy_parser.cc"
    break;

  case 26: // stmt: "if" p_expr_h stmt_h
#line 231 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = e_cond(M(yystack_[1].value.as < expression > ()), M(yystack_[0].value.as < expression > ()));  }
#line 844 "toy_parser.cc"
    break;

  case 27: // stmt: decl_vars
#line 232 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
        { yylhs.value.as < expression > () = yystack_[0].value.as < expression > (); }
#line 850 "toy_parser.cc"
    break;

  case 28: // stmt: "return" exprs_h ";"
#line 233 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = e_ret(M(yystack_[1].value.as < expression > ()));          }
#line 856 "toy_parser.cc"
    break;

  case 29: // stmt: "break" ";"
#line 234 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = e_brk();               }
#line 862 "toy_parser.cc"
    break;

  case 31: // stmt: exprs_h ";"
#line 236 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                             {   yylhs.value.as < expression > () = M(yystack_[1].value.as < expression > ());                 }
#line 868 "toy_parser.cc"
    break;

  case 32: // stmt: "continue" ";"
#line 237 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = e_conti();             }
#line 874 "toy_parser.cc"
    break;

  case 33: // expr_h: error
#line 239 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
             {}
#line 880 "toy_parser.cc"
    break;

  case 34: // expr_h: expr
#line 239 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                  { yylhs.value.as < expression > () = yystack_[0].value.as < expression > (); }
#line 886 "toy_parser.cc"
    break;

  case 35: // c_expr_h: expr_h
#line 241 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = e_comma(M(yystack_[0].value.as < expression > ()));        }
#line 892 "toy_parser.cc"
    break;

  case 36: // c_expr_h: c_expr_h ',' expr_h
#line 242 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = M(yystack_[2].value.as < expression > ()); yylhs.value.as < expression > ().params.push_back(M(yystack_[0].value.as < expression > ())); }
#line 898 "toy_parser.cc"
    break;

  case 37: // exprs_h: error
#line 247 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
              {}
#line 904 "toy_parser.cc"
    break;

  case 38: // exprs_h: exprs
#line 247 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                   { yylhs.value.as < expression > () = yystack_[0].value.as < expression > (); }
#line 910 "toy_parser.cc"
    break;

  case 39: // exprs: decl_vars
#line 249 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
            { yylhs.value.as < expression > () = yystack_[0].value.as < expression > (); }
#line 916 "toy_parser.cc"
    break;

  case 40: // exprs: expr
#line 250 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
            { yylhs.value.as < expression > () = yystack_[0].value.as < expression > (); }
#line 922 "toy_parser.cc"
    break;

  case 41: // exprs: expr ',' c_expr_h
#line 251 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
            { yylhs.value.as < expression > () = yystack_[2].value.as < expression > (); }
#line 928 "toy_parser.cc"
    break;

  case 42: // expr: NUMCONST
#line 253 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = yystack_[0].value.as < long > ();            }
#line 934 "toy_parser.cc"
    break;

  case 43: // expr: STRINGCONST
#line 254 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = M(yystack_[0].value.as < std::string > ());         }
#line 940 "toy_parser.cc"
    break;

  case 44: // expr: IDENTIFIER
#line 255 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = ctx.use(yystack_[0].value.as < std::string > ());        }
#line 946 "toy_parser.cc"
    break;

  case 45: // expr: '(' exprs_h cl_paren_h
#line 256 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = M(yystack_[1].value.as < expression > ());         }
#line 952 "toy_parser.cc"
    break;

  case 46: // expr: expr '[' exprs_h cl_bracket_h
#line 257 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = e_deref(e_add(M(yystack_[3].value.as < expression > ()), M(yystack_[1].value.as < expression > ())));      }
#line 958 "toy_parser.cc"
    break;

  case 47: // expr: expr '.' expr
#line 258 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            { }
#line 964 "toy_parser.cc"
    break;

  case 48: // expr: expr '(' exprs_h cl_paren_h
#line 262 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = e_fcall(M(yystack_[3].value.as < expression > ()));        }
#line 970 "toy_parser.cc"
    break;

  case 49: // expr: expr '(' ')'
#line 263 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = e_fcall(M(yystack_[2].value.as < expression > ()));        }
#line 976 "toy_parser.cc"
    break;

  case 50: // expr: expr '=' expr
#line 264 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = M(yystack_[2].value.as < expression > ())  +=  M(yystack_[0].value.as < expression > ());      }
#line 982 "toy_parser.cc"
    break;

  case 51: // expr: expr '*' expr
#line 265 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = e_mul(M(yystack_[2].value.as < expression > ()), M(yystack_[0].value.as < expression > ()));   }
#line 988 "toy_parser.cc"
    break;

  case 52: // expr: expr '/' expr
#line 266 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = e_div(M(yystack_[2].value.as < expression > ()), M(yystack_[0].value.as < expression > ()));   }
#line 994 "toy_parser.cc"
    break;

  case 53: // expr: expr '+' expr
#line 267 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = e_add(M(yystack_[2].value.as < expression > ()), M(yystack_[0].value.as < expression > ()));   }
#line 1000 "toy_parser.cc"
    break;

  case 54: // expr: expr '-' expr
#line 268 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = e_add(M(yystack_[2].value.as < expression > ()), e_neg(M(yystack_[0].value.as < expression > ())));   }
#line 1006 "toy_parser.cc"
    break;

  case 55: // expr: expr "+=" expr
#line 269 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   if(!yystack_[0].value.as < expression > ().is_immediate_value()) {   yylhs.value.as < expression > () = ctx.temp() += e_addrof(M(yystack_[2].value.as < expression > ())); yystack_[2].value.as < expression > () = yylhs.value.as < expression > ().params.back(); }       
                                                yylhs.value.as < expression > () = e_comma(M(yystack_[2].value.as < expression > ()) += e_add(T(yystack_[2].value.as < expression > ()), M(yystack_[0].value.as < expression > ())) );            
                                            }
#line 1014 "toy_parser.cc"
    break;

  case 56: // expr: expr "-=" expr
#line 273 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   if(!yystack_[0].value.as < expression > ().is_immediate_value()) {   yylhs.value.as < expression > () = ctx.temp() += e_addrof(M(yystack_[2].value.as < expression > ())); yystack_[2].value.as < expression > () = yylhs.value.as < expression > ().params.back(); }       
                                                yylhs.value.as < expression > () = e_comma(M(yystack_[2].value.as < expression > ()) += e_add(T(yystack_[2].value.as < expression > ()), e_neg(M(yystack_[0].value.as < expression > ()))) );     
                                            }
#line 1022 "toy_parser.cc"
    break;

  case 57: // expr: expr "*=" expr
#line 277 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   if(!yystack_[0].value.as < expression > ().is_immediate_value()) {   yylhs.value.as < expression > () = ctx.temp() += e_addrof(M(yystack_[2].value.as < expression > ())); yystack_[2].value.as < expression > () = yylhs.value.as < expression > ().params.back(); }       
                                                yylhs.value.as < expression > () = e_comma(M(yystack_[2].value.as < expression > ()) += e_mul(T(yystack_[2].value.as < expression > ()), M(yystack_[0].value.as < expression > ())) );            
                                            }
#line 1030 "toy_parser.cc"
    break;

  case 58: // expr: expr "/=" expr
#line 281 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   if(!yystack_[0].value.as < expression > ().is_immediate_value()) {   yylhs.value.as < expression > () = ctx.temp() += e_addrof(M(yystack_[2].value.as < expression > ())); yystack_[2].value.as < expression > () = yylhs.value.as < expression > ().params.back(); }       
                                                yylhs.value.as < expression > () = e_comma(M(yystack_[2].value.as < expression > ()) += e_div(T(yystack_[2].value.as < expression > ()), M(yystack_[0].value.as < expression > ())) );            
                                            }
#line 1038 "toy_parser.cc"
    break;

  case 59: // expr: expr '<' expr
#line 285 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   if(!yystack_[0].value.as < expression > ().is_immediate_value()) {   yylhs.value.as < expression > () = ctx.temp() += e_addrof(M(yystack_[2].value.as < expression > ())); yystack_[2].value.as < expression > () = yylhs.value.as < expression > ().params.back(); }       
                                                yylhs.value.as < expression > () = e_less(M(yystack_[2].value.as < expression > ()), M(yystack_[0].value.as < expression > ()));                              
                                            }
#line 1046 "toy_parser.cc"
    break;

  case 60: // expr: expr "<=" expr
#line 289 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   if(!yystack_[0].value.as < expression > ().is_immediate_value()) {   yylhs.value.as < expression > () = ctx.temp() += e_addrof(M(yystack_[2].value.as < expression > ())); yystack_[2].value.as < expression > () = yylhs.value.as < expression > ().params.back(); }       
                                                yylhs.value.as < expression > () = e_less_eq(M(yystack_[2].value.as < expression > ()), M(yystack_[0].value.as < expression > ()));                            
                                            }
#line 1054 "toy_parser.cc"
    break;

  case 61: // expr: expr '>' expr
#line 293 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   if(!yystack_[0].value.as < expression > ().is_immediate_value()) {   yylhs.value.as < expression > () = ctx.temp() += e_addrof(M(yystack_[2].value.as < expression > ())); yystack_[2].value.as < expression > () = yylhs.value.as < expression > ().params.back(); }       
                                                yylhs.value.as < expression > () = e_grt(M(yystack_[2].value.as < expression > ()), M(yystack_[0].value.as < expression > ()));                              
                                            }
#line 1062 "toy_parser.cc"
    break;

  case 62: // expr: expr ">=" expr
#line 297 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   if(!yystack_[0].value.as < expression > ().is_immediate_value()) {   yylhs.value.as < expression > () = ctx.temp() += e_addrof(M(yystack_[2].value.as < expression > ())); yystack_[2].value.as < expression > () = yylhs.value.as < expression > ().params.back(); }       
                                                yylhs.value.as < expression > () = e_grt_eq(M(yystack_[2].value.as < expression > ()), M(yystack_[0].value.as < expression > ()));                              
                                            }
#line 1070 "toy_parser.cc"
    break;

  case 63: // expr: "++" expr
#line 301 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   if(!yystack_[0].value.as < expression > ().is_immediate_value()) {   yylhs.value.as < expression > () = ctx.temp() += e_addrof(M(yystack_[0].value.as < expression > ())); yystack_[0].value.as < expression > () = yylhs.value.as < expression > ().params.back(); }       
                                                yylhs.value.as < expression > () = e_comma(M(yystack_[0].value.as < expression > ()) += e_add(T(yystack_[0].value.as < expression > ()), 1l) );               
                                            }
#line 1078 "toy_parser.cc"
    break;

  case 64: // expr: "--" expr
#line 305 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   if(!yystack_[0].value.as < expression > ().is_immediate_value()) {   yylhs.value.as < expression > () = ctx.temp() += e_addrof(M(yystack_[0].value.as < expression > ())); yystack_[0].value.as < expression > () = yylhs.value.as < expression > ().params.back(); }       
                                                yylhs.value.as < expression > () = e_comma(M(yystack_[0].value.as < expression > ()) += e_add(T(yystack_[0].value.as < expression > ()), -1l) );              
                                            }
#line 1086 "toy_parser.cc"
    break;

  case 65: // expr: expr "&&" expr
#line 309 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = e_cand(M(yystack_[2].value.as < expression > ()), M(yystack_[0].value.as < expression > ()));           }
#line 1092 "toy_parser.cc"
    break;

  case 66: // expr: expr "||" expr
#line 310 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = e_cor(M(yystack_[2].value.as < expression > ()), M(yystack_[0].value.as < expression > ()));            }
#line 1098 "toy_parser.cc"
    break;

  case 67: // expr: expr "==" expr
#line 311 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = e_eq(M(yystack_[2].value.as < expression > ()), M(yystack_[0].value.as < expression > ()));             }
#line 1104 "toy_parser.cc"
    break;

  case 68: // expr: expr "!=" expr
#line 312 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = e_eq(e_eq(M(yystack_[2].value.as < expression > ()), M(yystack_[0].value.as < expression > ())), 0l);   }
#line 1110 "toy_parser.cc"
    break;

  case 69: // expr: '&' expr
#line 313 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = e_addrof(M(yystack_[0].value.as < expression > ()));                }
#line 1116 "toy_parser.cc"
    break;

  case 70: // expr: '*' expr
#line 314 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = e_deref(M(yystack_[0].value.as < expression > ()));                 }
#line 1122 "toy_parser.cc"
    break;

  case 71: // expr: '-' expr
#line 315 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = e_neg(M(yystack_[0].value.as < expression > ()));                   }
#line 1128 "toy_parser.cc"
    break;

  case 72: // expr: '!' expr
#line 316 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   yylhs.value.as < expression > () = e_eq(M(yystack_[0].value.as < expression > ()), 0l);                }
#line 1134 "toy_parser.cc"
    break;

  case 73: // expr: expr '?' expr ':' expr
#line 317 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"
                                            {   auto tmp = ctx.temp();   yylhs.value.as < expression > () = e_comma(e_cor(e_cond(M(yystack_[4].value.as < expression > ()), M(yystack_[2].value.as < expression > ())), e_cond(e_neg(M(yystack_[4].value.as < expression > ())), M(yystack_[0].value.as < expression > ()))));  }
#line 1140 "toy_parser.cc"
    break;


#line 1144 "toy_parser.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  toy_parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  toy_parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  toy_parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // toy_parser::context.
  toy_parser::context::context (const toy_parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  toy_parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  toy_parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  toy_parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char toy_parser::yypact_ninf_ = -89;

  const signed char toy_parser::yytable_ninf_ = -1;

  const short
  toy_parser::yypact_[] =
  {
     -89,    11,   -89,     4,    -1,   -89,   -28,     5,     6,   -89,
     -89,   -11,     8,   120,   -89,    23,   -89,   152,    10,    18,
      36,    51,    18,   -89,   -89,   -89,   194,   194,   -89,   -89,
     194,   194,   194,   152,   194,    39,    76,   -89,   -89,    47,
     -89,   226,   120,   -89,    39,    48,   -89,   152,   120,   -89,
      41,   -89,   120,   -21,   -21,   -21,   -21,   -21,    34,   -21,
      51,   -89,   -89,   -89,   -89,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   184,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   136,   152,   -89,   -89,    34,
     -89,   184,   -89,   -89,   -89,   -89,   340,   340,   356,   356,
     313,   313,   313,   313,   -12,   -12,   -89,   -89,    54,   284,
     255,   313,   -12,   -12,    25,    25,   -21,   -21,   -21,   -89,
      34,    40,   -89,   -89,   184,   194,   -89,   -89,   -89,   -89,
     313
  };

  const signed char
  toy_parser::yydefact_[] =
  {
       4,     2,     1,     0,     0,     3,     0,     0,    10,     5,
      12,     0,     9,     0,     7,     0,    37,     0,     0,     0,
       0,     0,     0,    44,    42,    43,     0,     0,    30,    17,
       0,     0,     0,     0,     0,    27,     0,     6,    19,     0,
      38,    40,     0,    11,    39,     0,    29,     0,     0,    32,
      16,    13,     0,    63,    64,    71,    70,    69,     0,    72,
       0,    20,    24,    18,    31,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     8,    28,     0,
      25,     0,    26,    21,    45,    14,    66,    65,    67,    68,
      55,    56,    57,    58,    60,    62,    33,    35,    41,    34,
       0,    50,    59,    61,    53,    54,    51,    52,    47,    49,
       0,     0,    23,    15,     0,     0,    48,    22,    46,    36,
      73
  };

  const signed char
  toy_parser::yypgoto_[] =
  {
     -89,   -89,   -89,   -89,   -89,   -89,   -89,   -89,   -15,    30,
     -89,   -33,   -89,   -61,   -89,    69,    56,   -88,   -89,   -10,
     -89,   -26
  };

  const unsigned char
  toy_parser::yydefgoto_[] =
  {
       0,     1,     3,     5,    13,    42,    11,    12,    35,    51,
      36,    37,    62,    94,   128,    48,    38,   107,   108,    39,
      40,    41
  };

  const unsigned char
  toy_parser::yytable_[] =
  {
      53,    54,    44,   123,    55,    56,    57,    45,    59,    87,
       6,     2,     4,     7,     8,    90,     9,    10,    44,    92,
      84,    85,    86,    58,    80,    81,    82,    83,   122,    84,
      85,    86,    44,    14,    43,    46,   129,    89,    15,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   126,
      47,    49,    50,    82,    83,   109,    84,    85,    86,    60,
      44,    44,    64,    88,    91,   120,   121,    16,    93,    17,
      18,    19,    20,    21,   124,   127,    22,    23,    24,    25,
      95,    52,    63,     0,     0,    26,    27,     0,   109,   130,
       0,    28,    29,    61,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    30,    31,     0,    32,     0,    33,     0,
       0,    16,    34,    17,    18,    19,    20,    21,     0,     0,
      22,    23,    24,    25,     0,     0,     0,    16,     0,    26,
      27,     0,     0,    21,     0,    28,    29,    23,    24,    25,
       0,     0,     0,    16,     0,    26,    27,    30,    31,    21,
      32,     0,    33,    23,    24,    25,    34,     0,     0,     0,
       0,    26,    27,    30,    31,     0,    32,     0,    33,     0,
     119,     0,    34,     0,     0,   106,     0,     0,     0,    30,
      31,     0,    32,     0,    33,    23,    24,    25,    34,     0,
       0,     0,     0,    26,    27,    23,    24,    25,     0,     0,
       0,     0,     0,    26,    27,     0,     0,     0,     0,     0,
       0,    30,    31,     0,    32,     0,    33,     0,     0,     0,
      34,    30,    31,     0,    32,     0,    33,     0,     0,     0,
      34,    65,    66,    67,    68,     0,     0,    69,    70,    71,
      72,     0,     0,     0,    73,    74,    75,    76,     0,    77,
      78,    79,    80,    81,    82,    83,     0,    84,    85,    86,
      65,    66,    67,    68,     0,     0,    69,    70,    71,    72,
       0,     0,     0,    73,    74,     0,    76,   125,    77,    78,
      79,    80,    81,    82,    83,     0,    84,    85,    86,    65,
      66,    67,    68,     0,     0,    69,    70,    71,    72,     0,
       0,     0,    73,    74,     0,    76,     0,    77,    78,    79,
      80,    81,    82,    83,     0,    84,    85,    86,    65,    66,
      67,    68,     0,     0,    69,    70,    71,    72,     0,     0,
       0,    73,    74,     0,     0,     0,    77,    78,    79,    80,
      81,    82,    83,     0,    84,    85,    86,    67,    68,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    73,    74,
       0,     0,     0,     0,    78,    79,    80,    81,    82,    83,
       0,    84,    85,    86,    73,    74,     0,     0,     0,     0,
      78,    79,    80,    81,    82,    83,     0,    84,    85,    86
  };

  const signed char
  toy_parser::yycheck_[] =
  {
      26,    27,    17,    91,    30,    31,    32,    17,    34,    42,
      11,     0,     8,    14,    42,    48,    11,    11,    33,    52,
      41,    42,    43,    33,    36,    37,    38,    39,    89,    41,
      42,    43,    47,    44,    11,    25,   124,    47,    30,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,   120,
      42,    25,    11,    38,    39,    91,    41,    42,    43,    30,
      85,    86,    25,    25,    33,    85,    86,     1,    44,     3,
       4,     5,     6,     7,    30,    45,    10,    11,    12,    13,
      60,    22,    36,    -1,    -1,    19,    20,    -1,   124,   125,
      -1,    25,    26,    27,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    37,    38,    -1,    40,    -1,    42,    -1,
      -1,     1,    46,     3,     4,     5,     6,     7,    -1,    -1,
      10,    11,    12,    13,    -1,    -1,    -1,     1,    -1,    19,
      20,    -1,    -1,     7,    -1,    25,    26,    11,    12,    13,
      -1,    -1,    -1,     1,    -1,    19,    20,    37,    38,     7,
      40,    -1,    42,    11,    12,    13,    46,    -1,    -1,    -1,
      -1,    19,    20,    37,    38,    -1,    40,    -1,    42,    -1,
      44,    -1,    46,    -1,    -1,     1,    -1,    -1,    -1,    37,
      38,    -1,    40,    -1,    42,    11,    12,    13,    46,    -1,
      -1,    -1,    -1,    19,    20,    11,    12,    13,    -1,    -1,
      -1,    -1,    -1,    19,    20,    -1,    -1,    -1,    -1,    -1,
      -1,    37,    38,    -1,    40,    -1,    42,    -1,    -1,    -1,
      46,    37,    38,    -1,    40,    -1,    42,    -1,    -1,    -1,
      46,    15,    16,    17,    18,    -1,    -1,    21,    22,    23,
      24,    -1,    -1,    -1,    28,    29,    30,    31,    -1,    33,
      34,    35,    36,    37,    38,    39,    -1,    41,    42,    43,
      15,    16,    17,    18,    -1,    -1,    21,    22,    23,    24,
      -1,    -1,    -1,    28,    29,    -1,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    -1,    41,    42,    43,    15,
      16,    17,    18,    -1,    -1,    21,    22,    23,    24,    -1,
      -1,    -1,    28,    29,    -1,    31,    -1,    33,    34,    35,
      36,    37,    38,    39,    -1,    41,    42,    43,    15,    16,
      17,    18,    -1,    -1,    21,    22,    23,    24,    -1,    -1,
      -1,    28,    29,    -1,    -1,    -1,    33,    34,    35,    36,
      37,    38,    39,    -1,    41,    42,    43,    17,    18,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,
      -1,    -1,    -1,    -1,    34,    35,    36,    37,    38,    39,
      -1,    41,    42,    43,    28,    29,    -1,    -1,    -1,    -1,
      34,    35,    36,    37,    38,    39,    -1,    41,    42,    43
  };

  const signed char
  toy_parser::yystos_[] =
  {
       0,    48,     0,    49,     8,    50,    11,    14,    42,    11,
      11,    53,    54,    51,    44,    30,     1,     3,     4,     5,
       6,     7,    10,    11,    12,    13,    19,    20,    25,    26,
      37,    38,    40,    42,    46,    55,    57,    58,    63,    66,
      67,    68,    52,    11,    55,    66,    25,    42,    62,    25,
      11,    56,    62,    68,    68,    68,    68,    68,    66,    68,
      30,    27,    59,    63,    25,    15,    16,    17,    18,    21,
      22,    23,    24,    28,    29,    30,    31,    33,    34,    35,
      36,    37,    38,    39,    41,    42,    43,    58,    25,    66,
      58,    33,    58,    44,    60,    56,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,     1,    64,    65,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    44,
      66,    66,    60,    64,    30,    32,    60,    45,    61,    64,
      68
  };

  const signed char
  toy_parser::yyr1_[] =
  {
       0,    47,    49,    48,    48,    51,    50,    52,    50,    53,
      53,    54,    54,    55,    55,    56,    56,    57,    57,    58,
      59,    60,    61,    62,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    64,    64,    65,    65,    66,    66,    67,
      67,    67,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68
  };

  const signed char
  toy_parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     0,     5,     0,     7,     1,
       0,     3,     1,     2,     3,     3,     1,     1,     2,     1,
       1,     1,     1,     3,     2,     3,     3,     1,     3,     2,
       1,     2,     2,     1,     1,     1,     3,     1,     1,     1,
       1,     3,     1,     1,     1,     3,     4,     3,     4,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     3,     3,     3,     3,     2,
       2,     2,     2,     5
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const toy_parser::yytname_[] =
  {
  "END", "error", "\"invalid token\"", "\"return\"", "\"break\"",
  "\"while\"", "\"continue\"", "\"var\"", "\"def\"", "\"else\"", "\"if\"",
  "IDENTIFIER", "NUMCONST", "STRINGCONST", "\"struct\"", "\"||\"",
  "\"&&\"", "\"==\"", "\"!=\"", "\"++\"", "\"--\"", "\"+=\"", "\"-=\"",
  "\"*=\"", "\"/=\"", "\";\"", "\"{\"", "\"}\"", "\"<=\"", "\">=\"", "','",
  "'?'", "':'", "'='", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'&'",
  "'.'", "'('", "'['", "')'", "']'", "'!'", "$accept", "unit", "$@1",
  "decl", "$@2", "$@3", "param_decls", "param_decl", "decl_vars",
  "decl_var", "stm_compound", "stmt_h", "cl_brace_h", "cl_paren_h",
  "cl_bracket_h", "p_expr_h", "stmt", "expr_h", "c_expr_h", "exprs_h",
  "exprs", "expr", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  toy_parser::yyrline_[] =
  {
       0,   200,   200,   200,   201,   203,   203,   204,   204,   206,
     206,   207,   208,   210,   211,   212,   213,   215,   216,   218,
     223,   224,   225,   227,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   239,   239,   241,   242,   247,   247,   249,
     250,   251,   253,   254,   255,   256,   257,   258,   262,   263,
     264,   265,   266,   267,   268,   269,   273,   277,   281,   285,
     289,   293,   297,   301,   305,   309,   310,   311,   312,   313,
     314,   315,   316,   317
  };

  void
  toy_parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  toy_parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 1754 "toy_parser.cc"

#line 319 "/Users/suru/Documents/GitCloning/BisonParser/bison/toy_parser.yy"


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
