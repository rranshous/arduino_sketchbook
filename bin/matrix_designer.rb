#!/usr/bin/env shoes
#
# goal is to throw up a matrix simulation which you can
# interact with to design a picture and than generate the
# ardiuno code to produce that picture

RADIUS=35
OFFSET=5
ACTIVE=:ACTIVE
INACTIVE=:INACTIVE

def other_state state
  state == ACTIVE ? INACTIVE : ACTIVE
end

draw_oval = lambda { |x, y, state|
  lambda {
    new_stroke = state == ACTIVE ? red : black
    puts "drawing oval: #{x}:#{y} #{state} #{new_stroke}"
    stroke new_stroke
    oval(x, y, RADIUS).click {
      puts "handlng click #{self}"
      instance_exec &draw_oval.call(x, y, other_state(state))
    }
  }
}

Shoes.app {
  fill black
  16.times do |j|
    puts "j: #{j}"
    24.times do |i|
      puts "i: #{i}"
      x = i * (OFFSET + RADIUS)
      y = j * (OFFSET + RADIUS)
      puts "#{x}:#{y}"
      instance_exec &draw_oval.call(x, y, INACTIVE)
    end
  end
}
