from os import listdir
from os.path import isfile, join
from shutil import copyfile
import random

def read_files(path):
    return [f for f in listdir(path) if isfile(join(path, f))]

def copy_and_append(files, guide):
    for i in range(0, len(files)):
        copyfile("./UNCOMPRESSED/" + files[i], "./SHUFFLED/" + str(guide[i]) + ".ppm")
filenames = read_files("./UNCOMPRESSED/")
shuffler = [i for i in range(0, len(filenames))]
random.shuffle(shuffler)
copy_and_append(filenames, shuffler)
