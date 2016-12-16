require 'remedy'
include Remedy

class SerialWriter
  require 'serialport'

  def initialize
    port_str = "/dev/ttyACM0"  #may be different for you
    baud_rate = 9600
    data_bits = 8
    stop_bits = 1
    parity = SerialPort::NONE
    @sp = SerialPort.new(port_str, baud_rate, data_bits, stop_bits, parity)
  end

  def puts str
    @sp.puts str
  end

  def write_percent perc
    puts(perc.to_s.rjust(3, '0'))
  end
end

percent = 50

writer = SerialWriter.new
writer.write_percent percent
puts "Starting"

user_input = Interaction.new
user_input.loop do |key|
  if key == 'a'
    percent += 10
    percent = [percent, 100].min
  elsif key == 'l'
    percent -= 10
    percent = [percent, 0].max
  end
  writer.write_percent percent
  puts percent
end
