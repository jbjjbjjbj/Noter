#!/usr/bin/env ruby
require 'open3'
require 'optparse'

filename = ARGV[0]
outname = ARGV[1]

page = 1
File.open(outname, "w") do |out|
  File.readlines(filename).each do |line|
    if line.start_with? "\xC"
      line[0] = ''
      page += 1
    end

    out.puts "#{page}   #{line}"
  end
end
