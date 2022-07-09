#ifndef __WIDGETS_HPP__
#define __WIDGTES_HPP__

#include "State.hpp"

namespace complexmos
{

    struct TestWidget
    {
        float y_data[1000];
        float x_data[1000];

        TestWidget();
        void operator()(State& state);
    };

    struct OtherWidget 
    {   
        float f;
        int counter;

        void operator()(State& state);
    };

}

#endif