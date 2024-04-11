"""Read the game records"""
import re

def game_id(line):
    """Return the number between 'Game ' and ':'
    Game 1: 4 green, 3 blue, 11 red; 7 red, 5 green, 10 blue; 3 green, 8 blue, 8 red; 4 red, 12 blue; 15 red, 3 green, 10 blue"""
    id_part = re.search("Game.*:", line).group() 
    return int(re.search("\d+", id_part).group())

def number_of_color(sets:str, color:str)->list:
    """get the numbers from the part '<number> <color>' as a list that is sorted"""
    result = re.findall(f"\d+ {color}", sets)
    return sorted([int(number.split(" ")[0]) for number in result])

def draw_combos(line, cube_colors):
    cube_color_numbers_dict = {}
    for color in cube_colors:
        cube_color_numbers_dict[color] = number_of_color(line, color)
    return cube_color_numbers_dict
        

def read_records(path_to_record_file, cube_colors):
    """Example lines in the record txt:
    Game 1: 4 green, 3 blue, 11 red; 7 red, 5 green, 10 blue; 3 green, 8 blue, 8 red; 4 red, 12 blue; 15 red, 3 green, 10 blue
    Game 2: 3 red, 1 blue, 2 green; 1 blue, 9 green; 1 red, 10 green

    Create dict in this format:
    {
        1: {
            "green": [4, 5, 3, 3],
            "red" : [11, 7, 8, 4, 15]
            "blue" : [3, 10, 8, 12, 10]
        }
        2:
    }
    """
    with open(path_to_record_file, "r") as file:
        record_str = file.read()
    record_dict = {}
    
    for line in record_str.split("\n"):
        id = game_id(line)
        drawn_colors = draw_combos(line, cube_colors)
        record_dict[id] = drawn_colors
    return record_dict


def game_matches_configuration(configuration, drawn_colors, game_id):
    match = False
    #print(f"game_id: {game_id} drawn_colors: {drawn_colors}")
    for color, configuration_max in configuration.items():
        drawn_max = drawn_colors[color][-1]
        if drawn_max <= configuration_max:
            match = True
        else:
            #print(f"exceeds; game_id: {game_id} and color: {color} by: {drawn_max}")
            match = False
            break
    #print(match)
    return match