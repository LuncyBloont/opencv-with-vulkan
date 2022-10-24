
from operator import index
import os

compiler_path = 'C:/VulkanSDK/1.3.224.1/Bin/glslangValidator.exe'

flags = [
    '-V'
]

folders = [
    './defaultVS/',
    './shaders/'
]

template = './shaderLib/fragTemplate.glsl'

def compile(path: str):
    global compile_path
    global flags
    if path.rfind('.spv') == len(path) - 4:
        return
    output = path[:path.rfind('.')]
    command = '{} {} {} -o {}'.format(compiler_path, ' '.join(flags), path, output + '.spv')
    print('run: ' + command)
    result = os.system(command)
    if result != 0:
        print('Failed to compile...')
        exit(-1)

def compile_folder(dirname):
    shaderSources = os.listdir(dirname)
    for source in shaderSources:
        compile(os.path.join(dirname, source))

for dir in folders:
    compile_folder(dir)

