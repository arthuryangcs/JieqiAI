# coding: utf-8

import os
import subprocess


if __name__ == '__main__':
    g = os.walk(r"unit_tests")
    for _, _, file_list in g:
        for f in file_list:
            if not f.endswith('test'):
                continue

            with open('unit_tests/{}'.format(f), 'r') as fp, open('unit_tests/{}.out'.format(f[:-5], 'r')) as ans:
                ret = ''
                p = subprocess.Popen(r'../eleeye/cmake-build-debug/eleeye.exe', stdin=fp, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
                for line in iter(p.stdout.readline, b''):
                    l = line.strip().split()
                    if len(l) >= 2 and l[0] == b'bestmove':
                        ret = l[1]
                p.stdout.close()
                p.wait()

                if ret:
                    a = ans.readline().encode(encoding='utf-8')
                    print(ret == a, f, ret, a)
