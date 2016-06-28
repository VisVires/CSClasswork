#!/usr/bin/python
import random

print "Random Strings Passed To File:\n"
#make three files
for j in range(0, 3):
	#name files
	i = str(j) 
	fileNameIn = "file"+i+".txt"
	#open files
	file_in = open(fileNameIn ,"w+")
	#print fileNum.name
	#build a word
	word = ""
	#generate words
	for k in range(0, 10):
		#create random letter in lower case ascii range
		letter = random.randint(97,122)
		#convert to char
		word = word + str(unichr(letter))
	#output word
	file_in.write("%s\n" % (word))
	print word
	file_in.close()

print "\nRandom Strings read from File: \n"
	
for f in range(0,3):
	l = str(f)
	#set file name
	fileNameOut = "file" + l + ".txt"
	#open file to be read
	file_out = open(fileNameOut, "r+")
	#get string from file
	randString = file_out.read()
	#output string
	print "10 letter string from "+ fileNameOut +" is: ", randString
	#close file
	file_out.close

print "Print two numbers and their product: \n"

nums = []
for s in range(0,2):
	num = random.randint(1,42)
	nums.append(num)
	
product = nums[0] * nums[1]

print "%d * %d = %d" % (nums[0], nums[1], product)
