
echo "mkdir build && cd build"
rm -rf build
mkdir build && cd build

echo "cmake .."
cmake ..

echo "make"
make

echo "./test/testglvndcontext"
./test/testglvndcontext

echo "cd .."
cd ..
