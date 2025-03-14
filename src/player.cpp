#include "player.h"
#include <godot_cpp/classes/input.hpp>
#include "godot_cpp/classes/collision_object2d.hpp"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/classes/display_server.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <algorithm>
#include <iostream>

using namespace godot;

void Player::_bind_methods() {
  ClassDB::bind_method(D_METHOD("get_speed"), &Player::get_speed);
	ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &Player::set_speed);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed", PROPERTY_HINT_RANGE, "0,20,0.01"), "set_speed", "get_speed"); 
}

Player::Player() {
  time_passed = 0.0;
  speed = 400;
}

Player::~Player() {
}

Vector2 Player::get_screen_size() {
  Vector2i screen_size_i = DisplayServer::get_singleton()->window_get_size();
  return Vector2(screen_size_i.x, screen_size_i.y);
}

void Player::_ready() {
  // hide();
  screen_size = get_screen_size();
}

void Player::_process(double delta) {
  //Handle user input
  Vector2 velocity = Vector2(0,0);
  Input *current_input = Input::get_singleton();
  if (current_input->is_action_pressed("move_right")) {
    velocity.x += 1;
  }
  if (current_input->is_action_pressed("move_left")) {
    velocity.x -= 1;
  }
  if (current_input->is_action_pressed("move_down")) {
    velocity.y += 1;
  }
  if (current_input->is_action_pressed("move_up")) {
    velocity.y -= 1;
  }

  // Normalize Diagonal Movement
  AnimatedSprite2D *player_animation = get_node<AnimatedSprite2D>("AnimatedSprite2D");
  if (velocity.length() > 0) {
    velocity = velocity.normalized() * speed;
    player_animation->play();
  }
  else {
    player_animation->stop();
  }
  // Set player's new position and ensure it stays within the screen.
  std::cout << delta << std::endl;
  set_position(get_position() + velocity * delta);
  Vector2 position = get_position();
  set_position(position.clamp(Vector2(0, 0), screen_size));

  if (velocity.x != 0) {
    player_animation->set_animation("walk");
    player_animation->set_flip_v(false);
    player_animation->set_flip_h(velocity.x < 0);
  }
  else if (velocity.y != 0) {
    player_animation->set_animation("up");
    player_animation->set_flip_v(velocity.y > 0);
    
  }
}

void Player::set_speed(const double p_speed) {
  speed = p_speed;
}

double Player::get_speed() const {
  return speed;
}
