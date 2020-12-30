import sat
import bdd_sat
import os
import time


def main():
    base_path = 'sat_testcases/input/input0'

    print('Sat')
    for i in range(10):
        start = time.time()
        os.system(f"python3 sat.py < {base_path}{i}.txt > /dev/null")
        end = time.time()
        print(f'Test {i}: {end - start}')

    print('Bdd-Sat')
    for i in range(10):
        start = time.time()
        os.system(f"python3 bdd_sat.py < {base_path}{i}.txt > /dev/null")
        end = time.time()
        print(f'Test {i}: {end - start}')


if __name__ == '__main__':
    main()
