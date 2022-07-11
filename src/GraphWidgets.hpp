#ifndef __GRAPH_WIDGETS_HPP__
#define __GRAPH_WIDGETS_HPP__

#include "State.hpp"
#include "../parse/Parser.hpp"

#include <complex>

namespace complexmos
{

    struct GraphWidget
    {
        void operator()(State& state);
    };

    struct GraphSettingsWidget
    {
        parse::Parser::TokenTable _token_table;
        parse::Parser::MakeNumber _to_complex;

        parse::Node parse(const std::string&) const;

        char function_text[128];
        
        GraphSettingsWidget();
        
        void operator()(State&);
    };

}

#endif