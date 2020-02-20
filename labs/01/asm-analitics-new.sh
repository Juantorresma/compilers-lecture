# Homework 01
# A01227885
# Juan Torres

import sys

def main():

  print("Hi, this is the output of the analysis: ")

	funcs = []
  scriptRoute =  sys.argv[1]
	command = {}
  
	with open(scriptRoute) as file:
		for line in file:
			if line[0]=='0':
				words =  line.split(" ")
				funcs.append(words)
			else:
				words = line.split("\t")
				if len(words)>2:
					commands = words[2].split(" ")
					if len(commands) >0: 
						if commands[0] in command:
							command[commands[0]] = command[commands[0]]+1
						else:
							command[commands[0]] = 1

	print("You have {0} kind of instructions in this obj. file:".format(len(command)))
	for comm in command:
		print("  {0}\t: Executed {1} times ".format(comm, command[comm]))
	print("You have {0} functions:".format(len(funcs)))
	for x in  funcs:
		print("  {0}".format( x[1][1:-3] ), end='' )
		space =(24-len(x[1][1:-3])) * ' '
		print(space, end='')
		print(": Located at {0} addr".format(x[0][-4:] ))

main()
