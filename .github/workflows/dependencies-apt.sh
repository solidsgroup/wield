set -eu -o pipefail

sudo apt-get update

sudo apt-get install -y --no-install-recommends build-essential g++ libpython3-dev libeigen3-dev

# Requirements for regression test scripts
#pip3 install yt matplotlib numpy pandas

# Requirements for building documentation
#pip3 install sphinx breathe m2r sphinx_rtd_theme linuxdoc sphinx_design sphinx-copybutton

#npm install -g eclint
