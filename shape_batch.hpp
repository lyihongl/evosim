#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

class octogon_batch {
public:
  octogon_batch(){};
  std::vector<sf::Vertex> vertices;
  //const sf::Texture &texture;
  void add(const sf::Vector2f &position);
  void reposition(const sf::Vector2f &position, const std::size_t &index);
};

void octogon_batch::add(const sf::Vector2f &position) {
  vertices.push_back(
      sf::Vertex(sf::Vector2f(10, 10) + position, sf::Color(255, 0, 0)));
  vertices.push_back(
      sf::Vertex(sf::Vector2f(20, 10) + position, sf::Color(0, 255, 120)));
  vertices.push_back(
      sf::Vertex(sf::Vector2f(15, 18.66) + position, sf::Color(0, 0, 255)));

  // triangle 2
  vertices.push_back(
      sf::Vertex(sf::Vector2f(10, 10) + position, sf::Color(255, 0, 0)));
  vertices.push_back(
      sf::Vertex(sf::Vector2f(5, 18.66) + position, sf::Color(0, 255, 120)));
  vertices.push_back(
      sf::Vertex(sf::Vector2f(15, 18.66) + position, sf::Color(0, 0, 255)));

  // triangle 3
  vertices.push_back(
      sf::Vertex(sf::Vector2f(5, 18.66) + position, sf::Color(0, 255, 120)));
  vertices.push_back(
      sf::Vertex(sf::Vector2f(15, 18.66) + position, sf::Color(0, 0, 255)));
  vertices.push_back(
      sf::Vertex(sf::Vector2f(10, 27.32) + position, sf::Color(255, 0, 0)));

  // triangle 4
  vertices.push_back(
      sf::Vertex(sf::Vector2f(20, 10) + position, sf::Color(0, 255, 120)));
  vertices.push_back(
      sf::Vertex(sf::Vector2f(25, 18.66) + position, sf::Color(255, 0, 0)));
  vertices.push_back(
      sf::Vertex(sf::Vector2f(15, 18.66) + position, sf::Color(0, 0, 255)));
}

void octogon_batch::reposition(const sf::Vector2f &position, const std::size_t &index) {
  //std::size_t internal_index = index*12;
  //vertices[internal_index].position 
  //vertices.push_back(
  //    sf::Vertex(sf::Vector2f(10, 10) + position, sf::Color(255, 0, 0)));
  //vertices.push_back(
  //    sf::Vertex(sf::Vector2f(20, 10) + position, sf::Color(0, 255, 120)));
  //vertices.push_back(
  //    sf::Vertex(sf::Vector2f(15, 18.66) + position, sf::Color(0, 0, 255)));

  //// triangle 2
  //vertices.push_back(
  //    sf::Vertex(sf::Vector2f(10, 10) + position, sf::Color(255, 0, 0)));
  //vertices.push_back(
  //    sf::Vertex(sf::Vector2f(5, 18.66) + position, sf::Color(0, 255, 120)));
  //vertices.push_back(
  //    sf::Vertex(sf::Vector2f(15, 18.66) + position, sf::Color(0, 0, 255)));

  //// triangle 3
  //vertices.push_back(
  //    sf::Vertex(sf::Vector2f(5, 18.66) + position, sf::Color(0, 255, 120)));
  //vertices.push_back(
  //    sf::Vertex(sf::Vector2f(15, 18.66) + position, sf::Color(0, 0, 255)));
  //vertices.push_back(
  //    sf::Vertex(sf::Vector2f(10, 27.32) + position, sf::Color(255, 0, 0)));

  //// triangle 4
  //vertices.push_back(
  //    sf::Vertex(sf::Vector2f(20, 10) + position, sf::Color(0, 255, 120)));
  //vertices.push_back(
  //    sf::Vertex(sf::Vector2f(25, 18.66) + position, sf::Color(255, 0, 0)));
  //vertices.push_back(
  //    sf::Vertex(sf::Vector2f(15, 18.66) + position, sf::Color(0, 0, 255)));
}