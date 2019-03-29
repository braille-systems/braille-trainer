from collections import defaultdict


def get_mapped(filename):  # filename in the script's directory
    file = open(filename, "r")
    mapped = defaultdict(list)
    for s in file:
        words = s.split()
        for word in words[:-1]:
            mapped[word].append(words[-1])
    return mapped


def find(mapped, text):  # returns empty list if such "text" doesn't exist
    return mapped[text]


def pop(mapped, text):   # doesn't throw exception if there is no such "text" in dictionary
    mapped.pop(text, [])


def push(mapped, text, filename):
    if text not in mapped:
        mapped[text] = filename
    else:
        mapped[text].append(filename)


def smart_find(mapped, charset, freq_char=""):
    ans = []
    for word in mapped.keys():
        if set(word) <= set(charset):
            ans.append(word)
    if not freq_char:
        ans.sort()
    else:
        ans.sort(key=lambda a: a.count(freq_char), reverse=True)
    return ans


# usage:
#
# d =  get_mapped("dict.txt")
# answer = smart_find(d, ...)
# do something with answer...
