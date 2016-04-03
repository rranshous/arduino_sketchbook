
WRITER_PATH=ENV['WRITE_SERIAL']

def write_serial text
  system("#{WRITER_PATH} \"#{text}\"")
end

Shoes.app {
  @note = para "Status Here", size: 'x-large'
  flow {
    image("smile.png").click do
      @note.replace "smiling"
      write_serial("smile") or @note.replace "failed to smile"
    end
    image("frown.png").click do
      @note.replace "frowning"
      write_serial("frown") or @note.replace "failed to frown"
    end
  }
  #stack { }
}

