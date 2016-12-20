
#include "sell.cpp"

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
            if(!guest->sell_params.myplace->around[i]->free)
                k++;
        if(!(k == 4||k == 3)) {
            guest->sell_params.alive = false;
        }

    }

    place(){
        free = true;
        guest = nullptr;
        for(int i = 0; i < 9;i++)
            around[i] = nullptr;
    }

    int addToPlace(){
        if(!free)
            return 1;
        guest = new sell;
        guest->sell_params.myplace = this;
        free = false;
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