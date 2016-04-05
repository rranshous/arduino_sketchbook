#!/usr/bin/env shoes
require 'thread'

WRITER_PATH=ENV['WRITE_SERIAL']

def write_serial text
  @serial_mutex ||= Mutex.new
  @serial_mutex.synchronize { system("#{WRITER_PATH} \"#{text}\"") }
end

def set_note note
  @note = note
end

def write_console text
  @write_mutex ||= Mutex.new
  @note.replace text
end

def clear_on_delay
  Thread.new { sleep(5) and write_serial('') }
end

Shoes.app {
  set_note para "Status Here", size: 'x-large'
  flow {
    image("smile.png").click do
      write_console "smiling"
      write_serial("smile") and clear_on_delay or write_console("failed to smile")
    end
    image("frown.png").click do
      write_console "frowning"
      write_serial("frown") and clear_on_delay or write_console("failed to frown")
    end
  }
  #stack { }
}

