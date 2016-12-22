#include "header.h"
#include <cstdlib> 
class sell_data{
public:
    int moving_vector[2];
    int age;
    bool alive, alert;
    place * view[9];
    place * myplace;
};

class predator_data{
public:
    int moving_vector[2];
    int age, hunger;
    bool alive, alert;
    place * view[9];
    place * myplace;
};

class pred{
public:
    pred_brain *core;
    predator_data params;
    pred(){
        for(int i = 0; i < 9; i++)
            params.view[i] = nullptr;
        params.alive = true;
    }
    ~pred(){
        for(int i = 0; i < 9; i++)
            params.view[i] = nullptr;
    }

    friend void pred_ask_for_params(pred* asker);

    friend void pred_brain_processing(pred * me);

    void params_updata(){
        pred_brain_processing(this);
    }

    void set(){
        pred_ask_for_params(this);
    }


};

class sell{
public:
    sell_brain *core;
    sell_data params;


    sell(){
        for(int i = 0; i < 9; i++)
            params.view[i] = nullptr;
        params.alive = true;
    }

    ~sell(){
        for(int i = 0; i < 9; i++)
            params.view[i] = nullptr;
    }
    friend void sell_ask_for_params(sell* asker);

    friend void sell_brain_processing(sell * me);

    void params_updata(){
        sell_brain_processing(this);
    }

    void set(){
        sell_ask_for_params(this);
    }

};

class place{
public:
    bool free;
    sell* guest;
    pred* hunter;
    place* around[9];
    bool plant;

    void place_seed(){
        int n = 0;
        if(!free)
            return;
        for(int i = 0; i < 9; i++)
            if(around[i]->guest != nullptr)
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
            add_sell_to_place();
        }
    }

    void unit_status_update(){
        if(guest!= nullptr) {
            int k = 0;
            for (int i = 0; i < 9; i++)
                if (!guest->params.myplace->around[i]->free)
                    k++;
            if (!(k == 4 || k == 3))
                guest->params.alive = false;
            guest->params.age++;
        }
        if(hunter!= nullptr){
            hunter->params.age++;
            hunter->params.hunger++;
        }
    }

    place(){
        free = true;
        guest = nullptr;
        hunter = nullptr;
        for(int i = 0; i < 9;i++)
            around[i] = nullptr;
    }

    friend void add_brain_to_sell(sell* me);
    friend void add_brain_to_pred(pred* me);

    int add_sell_to_place(){
        if(!free)
            return 1;
        guest = new sell;
        guest->params.myplace = this;
        guest->set();
        free = false;
        add_brain_to_sell(guest);
        guest->params.moving_vector[0] = 0;
        guest->params.moving_vector[1] = 0;
        guest->params.age = 1;
        return 0;
    }

    int add_pred_to_place(){
        if(!free)
            return 1;
        hunter = new pred;
        hunter->params.myplace = this;
        hunter->set();
        free = false;
        add_brain_to_pred(hunter);
        hunter->params.moving_vector[0] = 0;
        hunter->params.moving_vector[1] = 0;
        hunter->params.age = 1;
        return 0;
    }

    void killguest(){
        if(guest != nullptr)
            delete guest;
        if(hunter == nullptr)
            free = true;
        guest = nullptr;
    }

    void killhunter(){
        if(hunter != nullptr)
            delete hunter;
        if(guest == nullptr)
            free = true;
        hunter = nullptr;
    }

    ~place(){
        delete guest;
        for(int i = 0; i < 9; i++)
            around[i] = nullptr;
    }

};

class sell_brain {
public:
    sell *owner;
    sell_brain(){
        owner = nullptr;
    }
    sell_brain(sell * newowner){
        if(newowner!= nullptr)
            owner = newowner;
    }

    bool is_alert(){
        int n = 0;
        for(int i = 0; i < 9; i++) {
            if (owner->params.view[i]->hunter != nullptr)
                return true;
            if (!owner->params.view[i]->free)
                n++;
        }
        if(!(n== 3|| n == 4))
            return true;
        return false;
    }

    void set_moving_vector(){
        if(!owner->params.alert)
            return;
        int n = 0, i;
        do {
            i = (int) rand();
        }while(i%9 != 4);
        owner->params.moving_vector[0] = (i%9) % 3 - 1;
        owner->params.moving_vector[1] = (i%9) / 3 - 1;
        while(n < 9) {
            if (owner->params.view[i % 9]->free) {
                owner->params.moving_vector[0] = (i%9) % 3 - 1;
                owner->params.moving_vector[1] = (i%9) / 3 - 1;
                break;
            }
            n++;
            i++;
        }
        owner->params.alert=false;

    }

    ~sell_brain(){
        owner = nullptr;
    }
};

class pred_brain {
public:
    pred * owner;
    
    pred_brain(){
        owner = nullptr;
    }
    
    pred_brain(pred * newowner){
        if(newowner!= nullptr)
            owner = newowner;
    }

    void set_moving_vector(){
        int n = 0;
        int i;
        do{
           i = (int)rand();
        }while(i%9 == 4);
        owner->params.moving_vector[0] = (i%9) % 3 - 1;
        owner->params.moving_vector[1] = (i%9) / 3 - 1;
        while(n < 9) {
            if (owner->params.view[i % 9]->guest!= nullptr && owner->params.view[i%9]->hunter == nullptr) {
                owner->params.moving_vector[0] = (i%9) % 3 - 1;
                owner->params.moving_vector[1] = (i%9) / 3 - 1;
                break;
            }
            n++;
            i++;
        }
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
            return lone[x + y * width].add_sell_to_place();
        return 1;
    }

    int pred_put(int x, int y){
        if (IsOnField(x, y) && lone[x + y * width].hunter == nullptr)
            return lone[x + y * width].add_pred_to_place();
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

    void move_sell(int x, int y){
        if(lone[x + y * width].guest == nullptr)
            return;
        if(lone[x + y * width].guest->params.moving_vector[0] == 0 && lone[x + y * width].guest->params.moving_vector[1] == 0)
            return;
        int dx = lone[x + y * width].guest->params.moving_vector[0];
        int dy = lone[x + y * width].guest->params.moving_vector[1];
        int a = (x + dx + width)%width;
        int b = (y + dy + height)%height;
        if(lone[a + b*width].free) {
            lone[a + b * width].guest = lone[x + y * width].guest;
            lone[a + b * width].guest->params.myplace = &lone[a + b * width];
            lone[a + b * width].free = false;
            lone[a + b* width].guest->set();
            lone[x + y * width].guest = nullptr;
            lone[x + y * width].free = true;
            lone[a + b * width].guest->params.alert = false;
            lone[a + b * width].guest->params.moving_vector[0] = 0;
            lone[a + b * width].guest->params.moving_vector[1] = 0;
        }
    }

    void move_pred(int x, int y){
        if(lone[x + y * width].hunter == nullptr)
            return;
        if(lone[x + y * width].hunter->params.moving_vector[0] == 0 && lone[x + y * width].hunter->params.moving_vector[1] == 0)
            return;
        int dx = lone[x + y * width].hunter->params.moving_vector[0];
        int dy = lone[x + y * width].hunter->params.moving_vector[1];
        int a = (x + dx + width)%width;
        int b = (y + dy + height)%height;
        if(lone[a + b*width].hunter == nullptr) {
            lone[a + b * width].hunter = lone[x + y * width].hunter;
            lone[a + b * width].hunter->params.myplace = &lone[a + b * width];
            lone[a + b * width].free = false;
            lone[a + b* width].hunter->set();
            lone[x + y * width].hunter = nullptr;
            if(lone[x+y*width].guest == nullptr)
                lone[x + y * width].free = true;
            lone[a + b * width].hunter->params.moving_vector[0] = 0;
            lone[a + b * width].hunter->params.moving_vector[1] = 0;
            if(lone[a + b * width].guest!= nullptr){
                lone[a +b*width].killguest();
                lone[a+ b*width].hunter->params.hunger--;
            }
        }
    }

    void field_update() {

        //thinking

        for (int i = 0; i < height * width; i++) {
            if(lone[i].guest!= nullptr)
                lone[i].guest->params_updata();
            if(lone[i].hunter!= nullptr)
                lone[i].hunter->params_updata();
        }
        //moving
      for(int i = 0; i < width; i++)
          for(int j = 0; j < height; j++){
              move_sell(i, j);
              move_pred(i, j);
          }

        //marking

        for (int i = 0; i < height * width; i++) {
            lone[i].unit_status_update();
        }

        // seeding

        for (int i = 0; i < height * width; i++) {
            lone[i].place_seed();
        }

        // cleaning

        for (int i = 0; i < height * width; i++) {
            if (lone[i].guest != nullptr) {
                if (!lone[i].guest->params.alive)
                    lone[i].killguest();
            }
        }

        // growing

        for (int i = 0; i < height * width; i++) {
            lone[i].place_update();
        }


    }

    int fill_field(float n, int m) {
        int k = 0, l = 0;
        for (int i = 0; i < this->width; i++)
            for (int j = 0; j < this->width; j++)
                if ((float) (rand() % 100) / 100 <= n) {
                    this->sellput(i, j);
                    k++;
                }
        int i, j;
        while(m > l){
            i = rand()%width;
            j = rand()%height;
            if (!pred_put(i, j))
                l++;
        }
    }

    ~field() {
        delete[] lone;
    }
};

void sell_ask_for_params(sell* asker){
    if(asker == nullptr)
        return;
    for(int i = 0; i < 9; i++){
        asker->params.view[i] = asker->params.myplace->around[i];
    }
}

void pred_ask_for_params(pred* asker){
    if(asker == nullptr)
        return;
    for(int i = 0; i < 9; i++){
        asker->params.view[i] = asker->params.myplace->around[i];
    }
}

void sell_brain_processing(sell * me){
    me->params.alert = me->core->is_alert();
    me->core->set_moving_vector();
}

void pred_brain_processing(pred * me){
    me->core->set_moving_vector();
}

void add_brain_to_sell(sell* me){
    if(me == nullptr)
        return;
    me->core = new sell_brain;
    me->core->owner= me;
}

void add_brain_to_pred(pred* me){
    if(me == nullptr)
        return;
    me->core = new pred_brain;
    me->core->owner= me;
}