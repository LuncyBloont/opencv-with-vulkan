
from genericpath import isdir
import os
import re
import time

compiler_path = 'Path to glslc'

with open('./glslcPath.txt', 'r') as f:
    exec('compiler_path = ' + f.read())

flags = [
    '-V',
    '-I' + './shaderLib/'
]

folders = [
    './defaultVS/',
    './shaders/'
]

lastCompile = {}

template = './shaderLib/fragTemplate.stp'
tmp_file = './build-shader/.tmp.frag'

if not os.path.exists(tmp_file[:tmp_file.rfind('/')]):
    os.mkdir(tmp_file[:tmp_file.rfind('/')])

def compile(path: str):
    global compile_path
    global flags
    if re.match('.*\.spv$', path):
        print('Skip binary file: {}\n'.format(path))
        return

    global lastCompile

    if re.match('.*\.glsl$', path):
        print('Skip but mark include file: {}',format(path))
        lastCompile[path] = os.path.getmtime(path)
        return

    output = path[:path.rfind('.')]

    print('compile file: {}'.format(path))

    command = '{} {} {} -o {}'.format(compiler_path, ' '.join(flags), path, output + '.spv')

    print('run: ' + command)

    lastCompile[path] = os.path.getmtime(path)

    result = os.system(command)

    if result != 0:
        print('Failed to compile...')
        print('\n----------ENTER---!!!!!!!!!!!!!---ENTER------------\a')
        input()

    print('Done\n')

def compile_folder(dirname):
    shaderSources = os.listdir(dirname)
    for source in shaderSources:
        path = os.path.join(dirname, source)
        if os.path.isdir(path):
            compile_folder(path)
            continue
        compile(path)

for dir in folders:
    compile_folder(dir)

t = 60

while True:
    time.sleep(1)
    hasNew = False
    for f in lastCompile:
        if os.path.getmtime(f) > lastCompile[f]:
            lastCompile[f] = os.path.getmtime(f)
            hasNew = True 
            break
    
    if hasNew or t <= 0:
        for dir in folders:
            compile_folder(dir)
        t = 60
    t -= 1