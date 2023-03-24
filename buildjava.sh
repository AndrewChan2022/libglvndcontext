
echo "******************************************************"
echo "build c++ project first"
echo "./build.sh"
./build.sh

echo "build c++ project end"
echo "******************************************************"
echo ""

rm -rf java/out
mkdir -p java/out/production/testjava


echo "javac -classpath java -d java/out/production/testjava java/project/android/fastimage/filter/soul/SoulRenderLinuxJNI.java"
javac -classpath java -d java/out/production/testjava java/project/android/fastimage/filter/soul/SoulRenderLinuxJNI.java
echo "javac -classpath java  -d java/out/production/testjava java/project/android/fastimage/filter/soul/TestSoulRenderLinuxJNI.java"
javac -classpath java  -d java/out/production/testjava java/project/android/fastimage/filter/soul/TestSoulRenderLinuxJNI.java

echo "java -Djava.library.path=build -classpath  java/out/production/testjava project.android.fastimage.filter.soul.TestSoulRenderLinuxJNI"
java -Djava.library.path=build -classpath  java/out/production/testjava project.android.fastimage.filter.soul.TestSoulRenderLinuxJNI

