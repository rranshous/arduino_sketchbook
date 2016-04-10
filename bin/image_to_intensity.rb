#!/usr/bin/env

require 'RMagick'
include Magick

img_path = File.absolute_path(ARGV.shift)
puts "loading: #{img_path}"
img = ImageList.new(img_path)
puts "IMG: #{img}"

img.each_pixel.map { |pixel, c, r| pixel.intensity }
