
echo "Cleaning previous generation"
./clean.sh
echo "Generating Model"
wget  https://oss.sonatype.org/content/repositories/snapshots/org/kevoree/modeling/org.kevoree.modeling.cpp.generator/1.9.1-SNAPSHOT/org.kevoree.modeling.cpp.generator-1.9.1-20131114.095000-5.jar --quiet
java -jar org.kevoree.modeling.cpp.generator-1.9.1-20131114.095000-5.jar -i metamodel/kevoree.ecore -t . > generation.log
rm -rf META-INF
rm -rf *.jar
rm compile.sh
