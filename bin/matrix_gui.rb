
WRITER_PATH=ENV['WRITE_SERIAL']

def write_serial text
  system("#{WRITER_PATH} \"#{text}\"")
end

Shoes.app {
  @note = para "Status Here", size: 'x-large'
  flow {
    image("smile.png").click do
      @note.replace "smiling"
      write_serial "smile"
    end
    image("frown.png").click do
      @note.replace "frowning"
      write_serial "frown"
    end
  }
  stack {
    para "custom text (6 char 2 lines)", size: 'x-large'
    flow do
      @input = edit_line
      button("show").click do
        @note.replace "showing: #{@input.text}"
        write_serial @input.text
      end
    end
  }
}

