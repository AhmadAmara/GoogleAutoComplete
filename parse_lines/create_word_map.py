import re
import os
import json
from tqdm import tqdm


def process_line(line: str):
    line = line.replace('\n', '')
    line = re.sub(r'[^\w]', ' ', line)
    line = line.lstrip()
    line_tokens = re.split(r'\s+', line)
    line = " ".join(line_tokens)
    return line


def get_line_substr(line: str):
    sub_strs = set()
    for j in range(len(line) - 1):
        for i in range(j, j + 11):
            sub_strs.add(line[j: i].lower())
            # sub_strs.insert()
    return sub_strs


def lines_substr_to_map(map, filename):
    text_file_name = filename.split('/')[1]
    with open(filename) as f:
        for idx, line in tqdm(enumerate(f)):
            line = process_line(line)
            substrs_of_line = get_line_substr(line)
            for sub_line in substrs_of_line:
                x = map.get(sub_line, [])
                if len(x) > 4:
                    continue
                x = x + [(text_file_name, idx)]
                map[sub_line] = x
    return map


if __name__ == '__main__':
    texts = os.listdir('google')
    texts.reverse()
    lines_map = {}
    for text in texts:
        lines_map = lines_substr_to_map(lines_map, 'google/'+text)

    with open('output.json', 'w') as handle:
        json.dump(lines_map, handle, sort_keys=True, indent=4)


# print(get_line_substr("wealth. He had besides the things before mentioned, twelve marbles, part"))




# def get_close_substr(line:str):
#     lines_list = []
#     orig_line_score = len(line)*2
#     remove_scores = [10, 8, 6, 4]
#     for i in range(len(line)):
#         lines_list.append((line[:i] + line[i+1:], orig_line_score - remove_scores[i] if i < 3 else orig_line_score - 2))
#     return lines_list
