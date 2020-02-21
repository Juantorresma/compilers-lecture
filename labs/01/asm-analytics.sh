# Homework 01
# A01227885
# Juan Torres

#Declaring the func and instr regular expressions
instr_regex='[0-9a-f]{4}:\s+([0-9a-f]{2} )+\s+(\w+)'
func_regex='^([0-9a-f]+) <(.*)>:$'

#where we are going to put our instructinons and functions
declare -A instr
declare -A func

#we have to read all the lines in our objdump, so we start a while loop to read them
while read line
do
#check if the line belongs to a regular expression of a function or of an instruction
        if [[ $line =~ $func_regex ]]; then
                if [[ ! -v func[${BASH_REMATCH[2]}] ]]; then
                         func[${BASH_REMATCH[2]}]=${BASH_REMATCH[1]}
                fi
        elif [[ $line =~ $instr_regex ]]; then
                if [[ -v instr[${BASH_REMATCH[2]}] ]]; then
                        (( instr[${BASH_REMATCH[2]}]++ ))
                else
                        instr[${BASH_REMATCH[2]}]=1
                fi
        fi
done < $1

#now we just print what we have
echo 'Hi, this is the output of the analysis:'
echo '    You have' ${#instr[@]} 'kind(s) of instructions in this object file:'

for key in "${!instr[@]}"
do
        printf '        %-9s: Executed %d times\n' $key ${instr[$key]}
done

echo '    You have' ${#func[@]} 'functions:'

for key in "${!func[@]}"
do
        printf '        %-25s: Located at %s addr\n' $key ${func[$key]}
done
