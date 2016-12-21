#include <cstdlib> 
#include "header.h"

class data{
public:
    int moving_vector[2];
    bool alive, alert;
    place * view[9];
};

class sell{
public:
    brain *core;
    data sell_params;


    sell(){
        for(int i = 0; i < 9; i++)
            sell_params.view[i] = nullptr;
        sell_params.alive = true;
    }

    ~sell(){
        for(int i = 0; i < 9; i++)
            sell_params.view[i] = nullptr;
    }
    friend void ask_for_params(sell* asker);

    friend void brain_processing(sell * me);

    void params_updata(){
        brain_processing(this);
    }

    void set(){
        ask_for_params(this);
    }

};

class place{
public:
    bool free;
    sell* guest;
    place* around[9];
    bool plant;

    void place_seed(){
        int n = 0;
        if(!free) {
            return;
        }
        for(int i = 0; i < 9; i++)
            if(!around[i]->free)
                n++;
        if(n == 3)
            plant = true;
    }

    void place_update(){
        if(!free) {
            return;
        }
        if(plant){
            plant = false;
            addToPlace();
        }
    }

    void guest_status_update(){
        int k = 0;
        if(free)
            return;

        for(int i = 0; i < 9; i++)
            if(!guest->sell_params.view[4]->around[i]->free)
                k++;
        if(!(k == 4||k == 3)) {
            guest->sell_params.alive = false;
        }

    }

    void guest_thinks(){

    }

    place(){
        free = true;
        guest = nullptr;
        for(int i = 0; i < 9;i++)
            around[i] = nullptr;
    }

    friend void add_brain(sell* me);

    int addToPlace(){
        if(!free)
            return 1;
        guest = new sell;
        guest->sell_params.view[4] = this;
        guest->set();
        free = false;
        add_brain(guest);
        return 0;
    }

    void killguest(){
        if(guest != nullptr)
            delete guest;
        free = true;
        guest = nullptr;
    }


    ~place(){
        delete guest;
        for(int i = 0; i < 9; i++)
            around[i] = nullptr;
    }
};

class brain {
public:
    sell *owner;
    brain(){
        owner = nullptr;
    }
    brain(sell * newowner){
        if(newowner!= nullptr)
            owner = newowner;
    }

    bool is_alert(){
        int n = 0;
        for(int i = 0; i < 9; i++)
            if(!owner->sell_params.view[i]->free)
                n++;
        if( n!= 3 && n != 4)
            return true;
        return false;
    }

    void set_moving_vector(){
        if(!owner->sell_params.alert)
            return;
        int n = 0;
        int i = rand()%9;
        while(n < 9) {
            if (owner->sell_params.view[i % 9]->free) {
                owner->sell_params.moving_vector[0] = i % 3 - 1;
                owner->sell_params.moving_vector[1] = i / 3 - 1;
                break;
            }
            n++;
            i++;
        }

    }

    ~brain(){
        owner = nullptr;
    }
};

class field {
public:
    int height, width;
    place *lone;


    field(int H, int W) {
        height = H;
        width = W;
        lone = new place[H * W];
        for (int i = 0; i < W; i++)
            for (int j = 0; j < H; j++)
                placeInit(i, j);
    }

    int sellput(int x, int y) {
        if (IsOnField(x, y) && lone[x + y * width].free)
            return lone[x + y * width].addToPlace();
        return 1;
    }

    bool IsOnField(int x, int y) {
        return !(x < 0 || x > width || y < 0 || y > height);
    }

    void placeInit(int x, int y) {
        for (int j = -1; j < 2; j++)
            for (int i = -1; i < 2; i++) {
                int b = (width + x + i) % width, a = (height + y + j) % height;
                lone[x + y * width].around[i + 1 + (j + 1) * 3] = &(lone[b + a * width]);
            }
    }

    void field_update() {

        //thinking

        for (int i = 0; i < height * width; i++) {
            if(!lone[i].free)
                lone[i].guest->params_updata();
        }

        //moving


        //marking

        for (int i = 0; i < height * width; i++) {
            lone[i].guest_status_update();
        }

        // seeding

        for (int i = 0; i < height * width; i++) {
            lone[i].place_seed();
        }

        // cleaning

        for (int i = 0; i < height * width; i++) {
            if (lone[i].guest != nullptr) {
                if (!lone[i].guest->sell_params.alive)
                    lone[i].killguest();
            }
        }

        // growing

        for (int i = 0; i < height * width; i++) {
            lone[i].place_update();
        }

        // initialize

        for (int i = 0; i < width; i++)
            for (int j = 0; j < height; j++)
                placeInit(i, j);

    }

    int fill_field(float n) {
        int k = 0;
        for (int i = 0; i < this->width; i++)
            for (int j = 0; j < this->width; j++)
                if ((float) (rand() % 100) / 100 <= n) {
                    this->sellput(i, j);
                    k++;
                }
        return k;
    }

    ~field() {
        delete[] lone;
    }
};

void ask_for_params(sell* asker){
    if(asker == nullptr)
        return;
    for(int i = 0; i < 9; i++){
        asker->sell_params.view[i] = asker->sell_params.view[4]->around[i];
    }
}

void brain_processing(sell * me){
    me->sell_params.alert = me->core->is_alert();
    me->core->set_moving_vector();
}

void add_brain(sell* me){
    if(me == nullptr)
        return;
    me->core = new brain;
    me->core->owner= me;
}