//#include "header.h"
#include <iostream>
#include <unistd.h>
#ifdef PLATFORM_MAC
    #include <SFML/OpenGL.hpp>
    #include <SFML/Audio.hpp>
    #include <SFML/Graphics.hpp>
#else
    #include "hoods.cpp"
#endif


int DisplayMac(){
   srand (time(NULL));
    int width = 250, height = 250 ,t = 0;
    field A(height, width);
    float n = 0.1;
    A.fill_field(n, 1000);
    // create the window
    sf::RenderWindow window(sf::VideoMode(600, 600), "My window");
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);
        sf::RectangleShape c;
        sf::Color color;
        for(int i = 0; i < width*height; i++) {
            if(!A.lone[i].free) {
                if (A.lone[i].guest != nullptr) {
                    color.r = (int) ((255 * 4) / log(pow(2.71, 4) + (A.lone[i].guest->params.age)));
                    color.g = 10 * (int) log(1 + (A.lone[i].guest->params.age));
                    c.setFillColor(color);
                    c.setPosition(2 * (i % height), (2 * (int) ((float) i / width)));
                    c.setSize(sf::Vector2f(2, -2));
                    window.draw(c);
                }
                if (A.lone[i].hunter != nullptr) {
                    color.g = (int) ((255 * 4) / log(pow(2.71, 4) + (A.lone[i].hunter->params.age)));
                    color.r = 10 * (int) log(1 + (A.lone[i].hunter->params.age));
                    c.setFillColor(color);
                    c.setPosition(2 * (i % height), (2 * (int) ((float) i / width)));
                    c.setSize(sf::Vector2f(2, -2));
                    window.draw(c);
                }
            }
        }
        //A.sellput(rand()%width, rand()%height);
        usleep(10000);
        A.field_update();
        // end the current frame
        window.display();
        t++;
        std::cout<< t << "\n";

    }
    return 0;
}