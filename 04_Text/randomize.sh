#!/bin/bash

DELAY=0.01
MAX_ARGUMENTS_COUNT=1

if [[ ${#} -eq 1 ]]
then
    DELAY=${1}
fi

if [[ ${#} -gt ${MAX_ARGUMENTS_COUNT} ]]
then
    echo "Usage:"
    echo "${0} [DELAY]"
    exit 2
fi

# Read input data as arrays of strings
readarray -t lines

# Save characters coordinates in arrays
positions_count=0
for i in "${!lines[@]}"
do
    line="${lines[${i}]}"
    j=0
    while [[ ${j} -lt ${#line} ]]
    do
        # Save char coordinates in arrays (for rows and columns)
        row_positions[${positions_count}]=${i}
        column_positions[${positions_count}]=${j}
        j=$((${j} + 1))
        positions_count=$((${positions_count} + 1))
    done
done

# Generate random sequence of positions
random_positions=$(seq 0 $((${positions_count} - 1)) | shuf)

tput init
tput clear

# Print input data with delay
for position in ${random_positions}
do
    row_pos=${row_positions[${position}]}
    column_pos=${column_positions[${position}]}
    line=${lines[${row_pos}]}
    symbol=${line:${column_pos}:1}
    tput cup ${row_pos} ${column_pos} && echo -n ${symbol}
    sleep ${DELAY}
done

tput cup ${#lines[@]} 0
tput sgr0
