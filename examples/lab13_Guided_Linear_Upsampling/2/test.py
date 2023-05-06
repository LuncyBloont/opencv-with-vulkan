import os

print('start')

res_path = 'D:/tmp/input_training_highres/input_training_highres'
out_path = 'D:/tmp/input_training_highres/glu_gp_out'
log_path = '..\\glu_plain_time.ignore.txt'

os.chdir('build')

with open(log_path, 'w'):
    pass

all = os.listdir(res_path)

for e in all:
    ipath = os.path.join(res_path, e)
    opath = os.path.join(out_path, e)
    os.system('example_lab13_Guided_Linear_Upsampling_2.exe {} {} 2>> {}'.format(ipath, opath, log_path))