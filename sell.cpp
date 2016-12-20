//
// Created by Кирилл Голубев on 19/12/2016.
//

#include "data.cpp"


class sell{
public:
    data sell_params;

    sell(){
        sell_params.myplace = nullptr;
        sell_params.alive = true;
    }

    ~sell(){
        sell_params.myplace = nullptr;
    }


};