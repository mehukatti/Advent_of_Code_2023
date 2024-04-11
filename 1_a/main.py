"""Main of the shitty_input.txt solver"""

import os
import re

def find_first_and_last_digits(input_str)->int:
    """Find the first and last digits in the string. Return as integer."""
    

# read the file
with open("shitty_input.txt", "r") as file:
    calib_input = file.read()

lines_in_list = calib_input.split("\n")

calibration_values = []
for line in lines_in_list:
    match = re.findall('\d', line)
    try:
        calibration_value = match[0] + match[-1]
        calibration_value = int(calibration_value)
        calibration_values.append(calibration_value)
    except Exception:
        print(f"No digits in str'{line}'")
        

sum_of_values = sum(calibration_values)
print(sum_of_values)
