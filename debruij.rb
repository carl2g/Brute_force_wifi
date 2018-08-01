#!/usr/bin/ruby
# @Author: carl
# @Date:   2018-08-01 15:14:53
# @Last Modified by:   carl
# @Last Modified time: 2018-08-01 16:46:15

def get_content_file(file_name)
	str = ""
	File.open(file_name, "r") do |infile|
	    while (line = infile.gets)
	        str += line.chomp
	    end
	end
	return str
end

def file_exist(file_name)
	res = ""
	if File.exist?(file_name)
		res = get_content_file(file_name)
	else
		return res
	end
	return res
end

def debrujGenerator alpha, len
	i = len
	puts ".key_#{alpha}_#{len}"
	key = file_exist(".key_#{alpha}_#{len}")
	return key if !key.empty?
	key = alpha[0] * i
	key_len = alpha.size ** len
	begin
		alpha.split("").each_index do |it|
			new_key = key[(i - (len - 1))..i] + alpha[it]
			if !key.include?(new_key)
				key += alpha[it]
				i += 1
			end
			new_key = key[(i - (len - 1))..i] + alpha[it]
			if key[(i - (len - 1))..i].count(alpha[it]) == len - 1 && !key.include?(new_key)
				key += alpha[it]
				i += 1
			end
		end
		puts "#{key.length} == #{key_len}"
		raise if key.length != key_len
	rescue
		retry
	end
	File.open(".key_#{alpha}_#{len}", 'w+') { |file| file.write("#{key}\n") }
	return key
end

# puts debrujGenerator(ARGV[0], ARGV[1].to_i)