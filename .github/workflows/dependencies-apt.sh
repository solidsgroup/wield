set -eu -o pipefail
sudo apt update
sudo apt install -y --no-install-recommends build-essential g++ libpython3-dev libeigen3-dev 
sudo apt install -y python3-numpy python3-matplotlib python3-pybind11 
