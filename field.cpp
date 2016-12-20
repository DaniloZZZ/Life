
#include "place.cpp"


class field{
public:
    int height, width;
    place* lone;

    field(int H,int  W){
        height = H;
        width = W;
        lone = new place[H*W];
        for(int i = 0; i < W; i++)
            for(int j = 0; j < H; j++ )
                placeInit(i,j);
    }

    int sellput(int x, int y){
        if(IsOnField(x,y) && lone[x + y*width].free)
            return lone[x+y*width].addToPlace();
        return 1;
    }

    bool IsOnField(int x,int y){
        return !(x < 0 || x > width || y < 0 || y > height);
    }

    void placeInit(int x, int y){
        for(int j= -1; j < 2;j++)
            for(int i = -1; i < 2; i++) {
                int b = (width + x + i)%width, a = (height + y + j)%height;
                lone[x+y*width].around[i+1+(j+1)*3] = &(lone[b + a*width]);
            }
    }

    void field_update(){

        for(int i = 0; i < height*width; i++){
            lone[i].guest_status_update();
        }

        for(int i = 0; i < height*width; i++) {
            lone[i].place_seed();
        }

        for(int i = 0; i < height*width; i++){
            if(lone[i].guest != nullptr) {
                if (!lone[i].guest->sell_params.alive)
                    lone[i].killguest();
            }
        }

        for(int i = 0; i < height*width; i++) {
            lone[i].place_update();
        }

        for(int i = 0; i < width; i++)
            for(int j = 0; j < height; j++ )
                placeInit(i,j);

    }

    int fill_field(float n){
        int k = 0;
        for(int i = 0; i< this->width; i++)
            for(int j = 0; j< this->width;j++)
                if((float)(rand()%100)/100 <= n) {
                    this->sellput(i, j);
                    k++;
                }
        return k;
    }

    ~field(){
        delete[] lone;
    }
};