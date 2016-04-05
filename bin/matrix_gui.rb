#!/usr/bin/env shoes
require 'thread'

WRITER_PATH=ENV['WRITE_SERIAL']

def write_serial text
  system("#{WRITER_PATH} \"#{text}\"")
end

def set_note note
  @note = note
end

def write_console text
  @note.replace text
end

def clear_on_delay
  Thread.new {
    sleep(2)
    write_serial('')
    write_console('-')
  }
end

Shoes.app {
  set_note para "init", size: 'x-large'
  flow {
    image("smile.png").click do
      write_console "smiling"
      puts "SMILING"
      write_serial("smile") and clear_on_delay or write_console("failed to smile")
    end
    image("frown.png").click do
      write_console "frowning"
      write_serial("frown") and clear_on_delay or write_console("failed to frown")
    end
  }
  #stack { }
}

