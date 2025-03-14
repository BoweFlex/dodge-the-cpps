#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/area2d.hpp>

namespace godot {
  class Player : public Area2D {
    GDCLASS(Player, Area2D)

    private:
      double time_passed;
      double speed;
      Vector2 screen_size;
      Vector2 get_screen_size();

    public:
      static void _bind_methods();

    public:
      Player();
      ~Player();

      void _process(double delta) override;
      void _ready() override;
    	void set_speed(const double p_speed);
    	double get_speed() const;
  };
}
#endif
