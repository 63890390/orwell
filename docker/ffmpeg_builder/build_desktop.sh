./configure --prefix="/home/ffmpeg/binaries_desktop"\
--enable-cuda-sdk \
--enable-cuvid \
--enable-nvenc \
--enable-nonfree \
--enable-libnpp \
--extra-cflags=-I/usr/local/cuda/include \
--extra-ldflags=-L/usr/local/cuda/lib64
#TODO: add --enable-opengl

make -j4