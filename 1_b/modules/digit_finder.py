"""Digit finder"""

import re

class DigitFinder:
    def __init__(self, path_to_input_str):
        self.input_str = self.read_file(path_to_input_str)
        self.calibration_values = []
        self.spelled_digit_dict = {
            "thousand":"1000",
            "hundred":"100",
            "ninety":"90",
            "eighty":"80",
            "seventy":"70",
            "sixty":"60",
            "fifty":"50",
            "forty":"40",
            "thirty":"30",
            "twenty":"20",
            "nineteen":"19",
            "eighteen":"18",
            "seventeen":"17",
            "sixteen":"16",
            "fifteen":"15",
            "fourteen":"14",
            "thirteen":"13",
            "twelve":"12",
            "eleven":"11",
            "ten":"10",
            "nine":"9",
            "eight":"8",
            "seven":"7",
            "six":"6",
            "five":"5",
            "four":"4",
            "three":"3",
            "two":"2",
            "one":"1",
        }

    def read_file(self, path_to_input_str):
        with open(path_to_input_str, "r") as file:
            return file.read()
    
    def first_spelled_digit(self,line:str):
        """Find the first spelled digit from a line"""
        spelled_list = list(self.spelled_digit_dict.keys())
        first = re.findall("\d|"+'|'.join(spelled_list),line)[0]
        if first in self.spelled_digit_dict.keys():
            first = self.spelled_digit_dict[first]
        return first

    def find_numeric_or_spelled_digit(self, line:str, i:int):
        #easy to check if the one char at 
        one_char = line[i:i+1]
        if one_char.isnumeric():
            return one_char
        
        #check if a spelled digit is found in this position
        for spelled, digit in self.spelled_digit_dict.items():
            if i + len(spelled) > len(line): # would not match
                continue
            sub = line[i:i+len(spelled)]
            if sub == spelled:
                return digit
            
    def last_digit(self,line):
        for i in range(len(line),0,-1):
            digit = self.find_numeric_or_spelled_digit(line, i-1)
            if digit:
                return digit
        
    def first_digit(self, line):
        for i in range(len(line)):
            digit = self.find_numeric_or_spelled_digit(line, i)
            if digit:
                return digit


    def find_calibration_values(self):
        lines_in_list = self.input_str.split("\n")
        
        for line in lines_in_list:
            try:
                first = self.first_digit(line)
                last = self.last_digit(line)
                calibration_value = first + last
                calibration_value = int(calibration_value)
                self.calibration_values.append(calibration_value)
            except Exception:
                print(f"No digits in str'{line}'")

        print(self.calibration_values)
                
    def sum_calibration_values(self):
        return sum(self.calibration_values)
