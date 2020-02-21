# Homework 01
# A01227885
# Juan Torres

import sys
import re

#Declaring the func, instr and addr regular expressions
instr_regex = re.compile(r'<.+>:')
func_regex = re.compile(r' \t[a-z]+[0-9]*[a-z]* [a-z]+[0-9]*[a-z]*\s' '| \t[a-z]+[0-9]*[a-z]*\s')
addr_regex = re.compile(r'[0-9a-fA-F]{16} ')

#we have to read all the lines in our objdump, so we create the function asmAnalytics receiving the file
def asmAnalytics(file):

#we open and read the file into "lines"
        f=open(file,"r")
        lines=f.read()
        instr = [i.strip() for i in instr_regex.findall(lines)]
        func = [i.strip("<.>:") for i in func_regex.findall(lines)]
        addr = [i.strip() for i in addr_regex.findall(lines)]
        
#we now have to count the number of functions and of the differnet kind of intructions
        instr_count = len([[x,instructions.count(x)] for x in set(instructions)])
        func_count=len(func)
  
#now we just print what we have
        print("Hi, this is the output of the analysis:","\n\tYou have " , inst_count," kind of instructions in this object file:")
        for x in inst_count:
            print("\t\t",x[0], "\t: Executed ", x[1], " times")
 
        print("\tYou have ", func_count, " functions:")
        for x,y in zip(functions,address):
                print("\t\t",x,"\t: Located at ",y," addr")

        

asmAnalytics(sys.argv[1])
