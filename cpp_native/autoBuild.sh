cd Graph_Algo
sh ./autoBuild.sh
cd ../
rm -rf build
mkdir build
cd build
cmake ..
make -j$procs
