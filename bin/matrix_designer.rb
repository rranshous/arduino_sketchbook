#!/usr/bin/env shoes
#
# goal is to throw up a matrix simulation which you can
# interact with to design a picture and than generate the
# ardiuno code to produce that picture

RADIUS=35
OFFSET=2
ACTIVE=:ACTIVE
INACTIVE=:INACTIVE

$matrix_state = Hash.new(INACTIVE)

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

Shoes.app {
  each_cell do |i, j|
    x = i * (OFFSET + RADIUS)
    y = j * (OFFSET + RADIUS)
    fill black
    dot = oval(x, y, RADIUS)
    dot.click {
      puts "click #{i} #{j}"
      current_state = $matrix_state[[i, j]]
      new_state = other_state(current_state)
      puts "current state: #{current_state}"
      puts "new state: #{new_state}"
      new_fill = new_state == ACTIVE ? red : black
      puts "new fill: #{new_fill}"
      $matrix_state[[i,j]] = new_state
      puts "redrawing oval: #{x}:#{y} #{new_state} #{new_fill}"
      puts "dot: #{dot}"
      dot.style fill: new_fill
      write_code
    }
  end
}
