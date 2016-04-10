#!/usr/bin/env shoes
#
# goal is to throw up a matrix simulation which you can
# interact with to design a picture and than generate the
# ardiuno code to produce that picture

RADIUS=35
OFFSET=5
ACTIVE=:ACTIVE
INACTIVE=:INACTIVE

$matrix_state = {}

def other_state state
  state == ACTIVE ? INACTIVE : ACTIVE
end

def each_cell &blk
  16.times do |j|
    24.times do |i|
      blk.call i, j
    end
  end
end

def write_code
  open('matrix_code.txt', 'w') do |fh|
    each_cell do |i, j|
      state = $matrix_state[[i, j]]
      if state == ACTIVE
        line = "matrix.drawPixel(#{i}, #{j}, 1);"
        fh.puts line
      end
    end
  end
end

draw_oval = lambda { |i, j, state|
  lambda {
    x = i * (OFFSET + RADIUS)
    y = j * (OFFSET + RADIUS)
    new_stroke = state == ACTIVE ? red : black
    puts "drawing oval: #{x}:#{y} #{state} #{new_stroke}"
    fill new_stroke
    $matrix_state[[i,j]] = state
    oval(x, y, RADIUS).click {
      instance_exec &draw_oval.call(i, j, other_state(state))
    }
    write_code
  }
}

Shoes.app {
  each_cell do |i, j|
    instance_exec &draw_oval.call(i, j, INACTIVE)
  end
}
