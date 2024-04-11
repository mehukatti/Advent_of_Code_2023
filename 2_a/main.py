"""The Elf would first like to know which games would have been possible,
if the bag contained only 12 red cubes, 13 green cubes, and 14 blue cubes?

What is the sum of the IDs of those games?"""

from modules.record_reader import read_records, game_matches_configuration


cube_colors = ["red", "green", "blue"]
record_dict = read_records("game_records.txt", cube_colors)
print(record_dict)

configuration = {"red": 12,"green": 13, "blue": 14}

print()
possible_games = []
for game_id, drawn_colors in record_dict.items():
    if game_matches_configuration(configuration, drawn_colors, game_id):
        possible_games.append(game_id)

print(sum(possible_games))