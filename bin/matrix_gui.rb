
WRITER_PATH=ENV['WRITE_SERIAL']

def write_serial text
  system("#{WRITER_PATH} \"#{text}\"")
end

Shoes.app {
  @note = para "Status Here"
  stack {
    button("Smile").click do
      @note.replace "smiling"
      write_serial "smile"
    end
    button("Frown").click do
      @note.replace "frowning"
      write_serial "frown"
    end
    para "custom text (6 char 2 lines)"
    flow do
      @input = edit_line
      button("show").click do
        @note.replace "showing: #{@input.text}"
        write_serial @input.text
      end
    end
  }
}

