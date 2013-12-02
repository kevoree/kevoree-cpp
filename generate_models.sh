echo "Cleanup"
find . -name "CMakeFiles" | xargs rm -rf
find . -name "Makefile" | xargs rm -rf
find . -name "cmake_install.cmake_modules" | xargs rm -rf
find . -name "cmake_install.cmake" | xargs rm -rf
find . -name "CMakeCache.txt" | xargs rm -rf                                                
rm -rf kevoree-core/model/kevoree 
rm -rf kevoree-core/model/microframework
rm -rf kevoree-core/model/sparsehash
rm -rf kevoree-core/model/check_leak.sh 
rm -rf kevoree-core/model/clean_cmake_files.sh 
rm -rf kevoree-core/model/generation.log

echo "Downloading generator"
wget https://oss.sonatype.org/content/repositories/snapshots/org/kevoree/modeling/org.kevoree.modeling.cpp.generator/1.1-SNAPSHOT/org.kevoree.modeling.cpp.generator-1.1-20131202.122613-5.jar --quiet

echo "Generating Model"
java -jar org.kevoree.modeling.cpp.generator-1.1-20131202.122613-5.jar -i kevoree-core/model/metamodel/kevoree.ecore -t kevoree-core/model
echo "Generating Adaptation Model"
java -jar org.kevoree.modeling.cpp.generator-1.1-20131202.122613-5.jar -i kevoree-core/model/metamodel/kevoree.adaptation.ecore -t kevoree-core/model
rm -rf org.kevoree.modeling.cpp.generator-1.1-20131202.122613-5.jar


