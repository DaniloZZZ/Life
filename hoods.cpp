namespace sf{
    namespace Event{
        class Closed{
            int a;
        };
    }
    class VideoMode{
        int a;
    };
    class  Event{
    int a;
    type = Event::Closed;
    };
    class RenderWindow{
        RenderWindow(VideoMode a,char *[] b){

        }
        bool isOpen(){ return  false;}
        bool pollEvent(Event e);
        void clear();
    };

}