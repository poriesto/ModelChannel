//
// Created by Alexander on 27.05.2015.
//

#include "Graph.h"

Graph::Graph(std::string name, sf::Vector2i location, std::list<Plot> plot) :
name_(name), pPlot_(plot){
        plot_.setSize(sf::Vector2f(600,400));
        plot_.setTitle(name);
        plot_.setFont("font.ttf");
        plot_.setXLabel("Frame Size, bits");
        plot_.setYLabel("Transfer Rate");
        plot_.setBackgroundColor(sf::Color(rand()%255,rand()%255,rand()%255));
        plot_.setTitleColor(sf::Color::Black);
        plot_.setPosition(sf::Vector2f(600*location.x,400*location.y));
       for(auto value : pPlot_) {
            sf::plot::Curve &curve = plot_.createCurve(
                    Code_toStr(value.code), sf::Color::Red);
            curve.setFill(false);
            curve.setThickness(2);
            curve.setColor(sf::Color(rand()%255,rand()%255,rand()%255)
            		);
            curve.setLimit(value.speed.size());
            curve.setLabel(Code_toStr(value.code));
        }
        plot_.prepare();
}
void Graph::update() {

    for (auto value : pPlot_) {
        for (auto value : pPlot_) {
            sf::plot::Curve &curve = plot_.getCurve(
                    Code_toStr(value.code));
            for (auto va : value.speed) {
                curve.addValue(va);
            }
            curve.setLabel("Code");
        }
        sf::Vector2f xrange(0, value.FrameSize.back());
        sf::Vector2f yrange(0, value.speed.back());
        plot_.prepare(xrange,yrange);
    }
}
void Graph::draw(sf::RenderTarget &target, sf::RenderStates states) const{
   target.draw(plot_,states);
}
