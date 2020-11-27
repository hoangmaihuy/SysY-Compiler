#!/usr/bin/python3

import os
from os import path
import subprocess
import sys


# =========== configurable parameters ===========
# you should modify these parameters if necessary
# NOTE: all paths are relative to script path!

# directories that storing test cases
dirs = [
    './functional_test',
    './custom_test',
#     'sysyruntimelibrary/section1/performance_test',
#    'sysyruntimelibrary/section2/performance_test',
]
# path to SysY compiler
compiler = '../build/compiler'
# path to MiniVM
minivm = '../MiniVM/build/minivm'
# temporary Eeyore file
eeyore_file = 'test.eeyore'

# ===================== end =====================


# print to stderr
def eprint(*args, **kwargs):
  print(*args, file=sys.stderr, **kwargs)
  sys.stderr.flush()


# run single test case
def run_case(sy_file, in_file, out_file):
  # compile to executable
  eeyore_cmd = compiler.split(' ') + ['-S -e', sy_file, '-o', eeyore_file]
  subprocess.run(eeyore_cmd, stdout=subprocess.PIPE)
  # run compiled file
  if in_file:
    with open(in_file) as f:
      inputs = f.read().encode('utf-8')
  else:
    inputs = None
  result = subprocess.run([minivm, eeyore_file], input=inputs, stdout=subprocess.PIPE)
  out = f'{result.stdout.decode("utf-8").strip()}\n{result.returncode}'
  out = out.strip()
  # compare to reference
  with open(out_file) as f:
    ref = f.read().strip()
  return out == ref


# run all test cases
def run_test(cases):
  total = 0
  passed = 0
  try:
    for sy_file, in_file, out_file in cases:
      # run test case
      eprint(f'running test "{sy_file}" ... ', end='')
      if run_case(sy_file, in_file, out_file):
        eprint(f'\033[0;32mPASS\033[0m')
        passed += 1
      else:
        eprint(f'\033[0;31mFAIL\033[0m')
      total += 1
  except KeyboardInterrupt:
    eprint(f'\033[0;33mINTERRUPT\033[0m')
  except Exception as e:
    eprint(f'\033[0;31mERROR\033[0m')
    eprint(e)
    exit(1)
  # remove temporary file
  # if path.exists(eeyore_file):
  #  os.unlink(eeyore_file)
  # print result
  if passed == total:
    eprint(f'\033[0;32mPASS\033[0m ({passed}/{total})')
  else:
    eprint(f'\033[0;31mFAIL\033[0m ({passed}/{total})')


# get single test case by '*.sy' file
def get_case(sy_file):
  in_file = f'{sy_file[:-3]}.in'
  out_file = f'{sy_file[:-3]}.out'
  if not path.exists(in_file):
    in_file = None
  return sy_file, in_file, out_file


# scan & collect test cases
def scan_cases(dirs):
  cases = []
  # scan directories
  for i in dirs:
    for root, _, files in os.walk(i):
      for f in sorted(files):
        # find all '*.sy' files
        if f.endswith('.sy'):
          sy_file = path.join(root, f)
          # add to list of cases
          cases.append(get_case(sy_file))
  return cases


if __name__ == '__main__':
  import argparse
  # initialize argument parser
  parser = argparse.ArgumentParser()
  parser.formatter_class = argparse.RawTextHelpFormatter
  parser.description = 'An auto-test tool for MimiC project.'
  parser.add_argument('-i', '--input', default='',
                      help='specify input SysY source file, ' +
                           'default to empty, that means run ' +
                           'files in script configuration')
  # parse arguments
  args = parser.parse_args()
  # check if is cross-compile mode
  # start running
  if args.input:
    # check if input test cast is valid
    if not args.input.endswith('.sy'):
      eprint('input must be a SysY source file')
      exit(1)
    if not path.exists(args.input):
      eprint(f'file "{args.input}" does not exist')
      exit(1)
    # get absolute path & change cwd
    sy_file = path.abspath(args.input)
    os.chdir(path.dirname(path.realpath(__file__)))
    # get test case
    case = get_case(sy_file)
    if not path.exists(case[2]):
      eprint(f'output file "{case[2]}" does not exist')
      exit(1)
    # run test case
    run_test([case])
  else:
    # change cwd to script path
    os.chdir(path.dirname(path.realpath(__file__)))
    # run test cases in configuration
    run_test(scan_cases(dirs))
