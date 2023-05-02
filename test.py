import os

os.chdir('build')

with open('../IGN_time.txt', 'w') as f:
    f.write('')

i_list = os.listdir('../images/images')

for e in i_list:
    i_path = os.path.join('../images/images', e)
    o_path = os.path.join('./', e)

    os.system('example_lab6_BilateralFiltering_and_shader_toys_4.exe {} {} 2>> ../IGN_time.txt'.format(i_path, o_path))