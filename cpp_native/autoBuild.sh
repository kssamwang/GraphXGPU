cd Graph_Algo
sh ./autoBuild.sh
cd ../
rm -rf build
cp -f ./jni.h $(find /usr/lib/jvm/ -name jni.h)
mkdir build
cd build
cmake ..
make -j$procs
