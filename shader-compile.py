
import os
import re
import time
import tkinter.messagebox as tkbox
import tkinter as tk

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


def compile_it(path: f):
    global compiler_path
    global flags
    if re.match('.*\\.spv$', path):
        print('Skip binary file: {}\n'.format(path))
        return

    global lastCompile

    if re.match('.*\\.glsl$', path):
        print('Skip but mark include file: {}', format(path))
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
        top = tk.Tk()
        top.attributes('-topmost', 1)
        top.geometry('0x0+1000000+10000')
        tkbox.showerror('Multi Stage', 'Shader compile error', )
        top.destroy()

    print('Done\n')


def compile_folder(dirname):
    shader_sources = os.listdir(dirname)
    for source in shader_sources:
        path = os.path.join(dirname, source)
        if os.path.isdir(path):
            compile_folder(path)
            continue
        compile_it(path)


for dirn in folders:
    compile_folder(dirn)

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
        for dirn in folders:
            compile_folder(dirn)
        t = 60
    t -= 1
