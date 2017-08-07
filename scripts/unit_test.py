import os
import sys
import subprocess
import filecmp

termsize=os.get_terminal_size().columns
print('\033[34m\033[1m'+sys.argv[1] + '\033[0m' + "."*(termsize-6-len(sys.argv[1])),end='')
sys.stdout.flush()
try:
    subprocess.call(["rm","-rf",sys.argv[1]+"output.dat"])
    subprocess.call(["rm","-rf",sys.argv[1]+"run.stdout"])
    subprocess.call(["rm","-rf",sys.argv[1]+"run.error"])
    with open(sys.argv[1]+"run.stdout","w") as stdoutfile:
        err=subprocess.call(["./bin/wield",sys.argv[1]+"input.in","-DOutFile="+sys.argv[1]+"output.dat"],stdout=stdoutfile);
        if err:
            print('\033[31m\033[1mFAILED\033[0m')
            raise Exception('Executable failed with error code '.str(err))

    if not filecmp.cmp(sys.argv[1]+"output.dat",sys.argv[1]+"output.ref"):
        raise Exception("File comparison failed")
        sys.exit(0)

    print('\033[32m\033[1mPASSED\033[0m')
    sys.exit(0)
except Exception as e:
    print('\033[31m\033[1mFAILED\033[0m')
    with open(sys.argv[1]+"run.error","a") as stderrfile:
        stderrfile.write(str(e))
    sys.exit(0)

except KeyboardInterrupt:
    print('\b\b\033[33m\033[1mKILLED\033[0m')
    #with open(sys.argv[1]+"run.error","a") as stderrfile:
    #    stderrfile.write(str(e))
    sys.exit(0)
