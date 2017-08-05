import os
import sys
import subprocess
import filecmp

termsize=os.get_terminal_size().columns
print(sys.argv[1] + "."*(termsize-4-len(sys.argv[1])),end='')
sys.stdout.flush()
try:
    subprocess.call(["rm","-rf",sys.argv[1]+"output.dat"])
    subprocess.call(["rm","-rf",sys.argv[1]+"run.stdout"])
    subprocess.call(["rm","-rf",sys.argv[1]+"run.error"])
    with open(sys.argv[1]+"run.stdout","w") as stdoutfile:
        err=subprocess.call(["./bin/wield",sys.argv[1]+"input.in","-DOutFile="+sys.argv[1]+"output.dat"],stdout=stdoutfile);
        if err:
            print('\033[31m\033[1mFAIL\033[0m')
            raise Exception('Executable failed with error code '.str(err))

    if not filecmp.cmp(sys.argv[1]+"output.dat",sys.argv[1]+"output.ref"):
        raise Exception("File comparison failed")
        sys.exit(0)

    print('\033[32m\033[1mPASS\033[0m')
    sys.exit(0)
except Exception  as e:
    print('\033[31m\033[1mFAIL\033[0m')
    with open(sys.argv[1]+"run.error","a") as stderrfile:
        stderrfile.write(str(e))
    sys.exit(0)
