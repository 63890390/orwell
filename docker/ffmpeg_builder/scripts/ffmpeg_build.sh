#!/usr/bin/env bash

#https://github.com/Javernaut/ffmpeg-android-maker

FFMPEG_VERSION=4.1.4

# Assuming the script is used on macOS or Linux machine
case "$OSTYPE" in
  darwin*)  HOST_TAG="darwin-x86_64" ;;
  linux*)   HOST_TAG="linux-x86_64" ;;
esac

# Directories used by the script
BASE_DIR="$( cd "$( dirname "$0" )" && pwd )"
SOURCES_DIR=${BASE_DIR}/sources
#FFMPEG_SOURCES=${SOURCES_DIR}/ffmpeg-${FFMPEG_VERSION}
FFMPEG_SOURCES=/home/sources/ffmpeg
OUT="/home/deps/ffmpeg"
OUTPUT_DIR=${OUT}/output
BUILD_DIR=${OUT}/build
STATS_DIR=${OUT}/stats
ANDROID_NDK_HOME=$NDK

# No incremental compilation here. Just drop what was built previously
rm -rf ${BUILD_DIR}
rm -rf ${STATS_DIR}
rm -rf ${OUTPUT_DIR}
mkdir -p ${STATS_DIR}
mkdir -p ${OUTPUT_DIR}

# Test if sources of the FFmpeg exist. If not - download them
function ensureSources() {
  if [[ ! -d "$FFMPEG_SOURCES" ]]; then
    TARGET_FILE_NAME=ffmpeg-${FFMPEG_VERSION}.tar.bz2
    TARGET_FILE_PATH=${SOURCES_DIR}/${TARGET_FILE_NAME}

    mkdir -p ${SOURCES_DIR}
    curl https://www.ffmpeg.org/releases/${TARGET_FILE_NAME} --output ${TARGET_FILE_PATH}
    tar xvjf ${TARGET_FILE_PATH} -C ${SOURCES_DIR}
    rm ${TARGET_FILE_PATH}
  fi
}

# Actual magic of configuring and compiling of FFmpeg for a certain architecture.
# Supported architectures are: armeabi-v7a, arm64-v8a, x86 and x86_64
function assemble() {
  cd ${FFMPEG_SOURCES}

  ARCH=$1
  API_LEVEL=$2
  TYPE=$3

  TOOLCHAIN_PATH=${ANDROID_NDK_HOME}/toolchains/llvm/prebuilt/${HOST_TAG}
  SYSROOT=${TOOLCHAIN_PATH}/sysroot

  CC_ANDROID_POSTFIX=
  EXTRA_CFLAGS=
  EXTRA_CONFIGURE_FLAGS=

  case $ARCH in
  	armeabi-v7a)
      FFMPEG_ARCH_FLAG=arm
      CROSS_PREFIX=arm-linux-androideabi-
      CC_PREFIX=armv7a
      CC_ANDROID_POSTFIX=eabi
  		;;
  	arm64-v8a)
      FFMPEG_ARCH_FLAG=aarch64
      CROSS_PREFIX=aarch64-linux-android-
      CC_PREFIX=aarch64
  		;;
    x86)
      FFMPEG_ARCH_FLAG=x86
      CROSS_PREFIX=i686-linux-android-
      CC_PREFIX=i686
      EXTRA_CFLAGS=-mno-stackrealign
      EXTRA_CONFIGURE_FLAGS=--disable-asm
  		;;
    x86_64)
      FFMPEG_ARCH_FLAG=x86_64
      CROSS_PREFIX=x86_64-linux-android-
      CC_PREFIX=x86_64
      EXTRA_CONFIGURE_FLAGS=--x86asmexe=${TOOLCHAIN_PATH}/bin/yasm
  		;;
  esac

  CC=${TOOLCHAIN_PATH}/bin/${CC_PREFIX}-linux-android${CC_ANDROID_POSTFIX}${API_LEVEL}-clang

  DECODERS_TO_ENABLE=
  while IFS= read -r line; do DECODERS_TO_ENABLE="${DECODERS_TO_ENABLE} --enable-decoder=$line"; done < ${BASE_DIR}/video_decoders_list.txt
  
  if [ "$TYPE" == android ]; then
    echo "Configuring $TYPE of arch $ARCH..."
    ./configure \
    --prefix=${BUILD_DIR}/android/${ARCH} \
    --disable-doc \
    --enable-cross-compile \
    --cross-prefix=${TOOLCHAIN_PATH}/bin/${CROSS_PREFIX} \
    --target-os=android \
    --cc=${CC} \
    --arch=${FFMPEG_ARCH_FLAG} \
    --extra-cflags="-O3 -fPIC $EXTRA_CFLAGS" \
    --sysroot=${SYSROOT} \
    --enable-shared \
    --disable-static \
    --disable-debug \
    --disable-runtime-cpudetect \
    --disable-programs \
    --disable-muxers \
    --disable-encoders \
    --disable-decoders \
    ${DECODERS_TO_ENABLE} \
    --disable-bsfs \
    --disable-pthreads \
    --disable-avdevice \
    --disable-network \
    --disable-postproc \
    #--disable-swresample \
    #--disable-avfilter \
    ${EXTRA_CONFIGURE_FLAGS}

    make clean
    make -j8
    make install

    # Saving stats about text relocation presence.
    # If the result file doesn't have 'TEXTREL' at all, then we are good.
    ${TOOLCHAIN_PATH}/bin/${CROSS_PREFIX}readelf --dynamic ${BUILD_DIR}/${ARCH}/lib/*.so | grep 'TEXTREL\|File' >> ${STATS_DIR}/text-relocations.txt

    cd ${BASE_DIR}
  elif [ "$TYPE" == pc ]; then
      echo "Configuring $TYPE of arch $ARCH..."
      ./configure \
      --prefix=${BUILD_DIR}/${ARCH} \
      --enable-nonfree \
      --enable-nvenc \
      --enable-libx264 \
      --enable-shared \
      --disable-static \
      --enable-gpl \
      --enable-cuda \
      --enable-cuvid 

  elif [ "$TYPE" == desktop ]; then
     #https://gist.github.com/Brainiarc7/4f831867f8e55d35cbcb527e15f9f116
     #TODO: add intel media sink
     #TODO: make x_86 and x_86_64 versions of this
     #TODO: enable vaapi support!
     echo "Configuring $TYPE of arch $ARCH..."
     PATH="$HOME/bin:$PATH" PKG_CONFIG_PATH="$HOME/ffmpeg_build/lib/pkgconfig:/opt/intel/mediasdk/lib/pkgconfig"
     
     ./configure \
      --prefix=${BUILD_DIR}/desktop/${ARCH} \
      --extra-cflags="-I$HOME/ffmpeg_build/include" \
      --extra-ldflags="-L$HOME/ffmpeg_build/lib" \
      --enable-shared \
      #--extra-cflags="-I/opt/intel/mediasdk/include" \
      #--extra-ldflags="-L/opt/intel/mediasdk/lib" \
      #--extra-ldflags="-L/opt/intel/mediasdk/plugins" \
      --arch=${ARCH} \ #command does not exist
      #--enable-libmfx \ #command does not exist
      --enable-vaapi \
      --disable-vaapi \ #command does not exist
      --enable-opencl \
      --disable-debug \
      --enable-nvenc \
      --enable-cuda \
      --enable-cuvid \
      #--enable-libvorbis \
      --enable-libvpx \
      --enable-libdrm \
      --enable-gpl \
      --enable-runtime-cpudetect \
      --enable-libfdk-aac \
      --enable-libx264 \
      --enable-libx265 \
      --enable-openssl \
      --enable-pic \
      --extra-libs="-lpthread -libm -libc -lz -ldl" \
      --enable-nonfree 
      PATH="$HOME/bin:$PATH" make -j$(nproc) -n
      make -j$(nproc) install 
      make -j$(nproc) distclean 
      hash -r

  else
      echo target $TYPE not supported
  fi

  
}

# Placing build *.so files into the /bin directory
function installLibs() {
  BUILD_SUBDIR=$1
  TYPE=$2

  OUTPUT_SUBDIR=${OUTPUT_DIR}/${TYPE}/lib/${BUILD_SUBDIR}
  CP_DIR=${BUILD_DIR}/${BUILD_SUBDIR}

  mkdir -p ${OUTPUT_SUBDIR}
  cp ${CP_DIR}/lib/*.so ${OUTPUT_SUBDIR}
}

function build() {
  ARCH=$1
  ANDROID_API=$2
  TYPE=$3

  assemble ${ARCH} ${ANDROID_API} ${TYPE}
  #installLibs ${ARCH} ${TYPE}
}

# Placing build header files into the /bin directory
# Note, there is a only one such a folder since this headers are the same for all architectures
# May not be true for different configurations though
function installHeaders() {

  echo "cd ${BUILD_DIR}
  cd "$(ls -1 | head -n1)"
  cp -r include ${OUTPUT_DIR}
  cd ${BASE_DIR}"

  cd ${BUILD_DIR}
  cd "$(ls -1 | head -n1)"
  cp -r include ${OUTPUT_DIR}
  cd ${BASE_DIR}
}

# Actual work

#ensureSources

build armeabi-v7a 16 android
build arm64-v8a 21 android
build x86 16 android
build x86_64 21 android
build x86_64 _ desktop

installHeaders
