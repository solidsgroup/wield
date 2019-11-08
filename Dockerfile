FROM ubuntu:18.04
RUN apt update
RUN apt install -y git
RUN apt install -y make
RUN apt install -y gcc g++
RUN apt install -y libtclap-dev
RUN apt install -y libmuparser-dev
RUN apt install -y libeigen3-dev

RUN echo "#!/bin/bash\n" > /startscript.sh
RUN echo "git clone https://github.com/solidsuccs/wield.git\n" >> /startscript.sh
RUN echo "cd wield\n" >> /startscript.sh
RUN echo "make\n" >> /startscript.sh

RUN chmod +x /startscript.sh

CMD /startscript.sh
