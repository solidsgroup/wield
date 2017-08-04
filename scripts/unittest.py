import sys
import subprocess
import filecmp

print(sys.argv[1]+"...........",end='')
with open(sys.argv[1]+"/run.stdout","w") as stdoutfile:
    if subprocess.call(["./bin/wield",sys.argv[1]+"/input.in","-DOutFile="+sys.argv[1]+"/output.dat"],stdout=stdoutfile):
        print('\033[31m\033[1mFAIL\033[0m')
        sys.exit(0)

if not filecmp.cmp(sys.argv[1]+"/output.dat",sys.argv[1]+"/output.ref"):
    print('\033[31m\033[1mFAIL\033[0m')
    sys.exit(0)

print('\033[32m\033[1mPASS\033[0m')
sys.exit(0)
