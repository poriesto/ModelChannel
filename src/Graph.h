//
// Created by Alexander on 27.05.2015.
//
#ifndef DIPLOM_GRAPH_H
#define DIPLOM_GRAPH_H
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "api.hpp"
#include "plot.h"
#include <string>
#include <list>
class Graph : public sf::Drawable, public sf::Transformable
{
public:
    Graph(std::string name, sf::Vector2i location, std::list<Plot> plot);
    void update();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    sf::plot::Plot plot_;
    std::list<Plot> pPlot_;
    std::string name_, curveName_;
};


#endif //DIPLOM_GRAPH_H
