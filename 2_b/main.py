"""The Elf would first like to know which games would have been possible,
what is the fewest number of cubes of each color that could have been in the bag to make the game possible?

What is the sum of the power of these sets?"""

from modules.record_reader import read_records, power_of_set


cube_colors = ["red", "green", "blue"]
record_dict = read_records("game_records.txt", cube_colors)
print(record_dict)

configurations = {"red": 0,"green": 0, "blue": 0}

print()
sum_of_powers = 0
for game_id, drawn_colors in record_dict.items():
    sum_of_powers = sum_of_powers + power_of_set(drawn_colors)

print(sum_of_powers)