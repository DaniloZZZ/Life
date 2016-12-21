#include "header.h"
#ifdef PLATFORM_MAC
    #include <SFML/OpenGL.hpp>
    #include <SFML/Audio.hpp>
    #include <SFML/Graphics.hpp>
#endif


void DisplayMac(){
     *AMirrow = new int[height*width];
    field A(height, width);
    float n = 0.1;
    A.fill_field(n);
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
        for(int i = 0; i < width*height; i++)
            if(!A.lone[i].free)
                AMirrow[i] = 1;
            else
                AMirrow[i] = 0;

        for(int i = 0; i < width*height; i++) {
            if(AMirrow[i] == 1) {
                sf::RectangleShape c;
                c.setFillColor(sf::Color::Red);
                c.setPosition(2*(i%height), (2*(int)((float)i / width)));
                c.setSize(sf::Vector2f(2,-2));
                window.draw(c);
            }
        }
        A.sellput(rand()%width, rand()%height);
        usleep(20000);
        A.field_update();
        // end the current frame
        window.display();
    }
    delete[] AMirrow;
    return 0;
}