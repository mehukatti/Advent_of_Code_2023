"""Main of the shitty_input.txt solver"""

import os
import re
from modules.digit_finder import DigitFinder
    

finder = DigitFinder("shitty_input.txt")
finder.find_calibration_values()
sum_of_values = finder.sum_calibration_values()
print(sum_of_values)