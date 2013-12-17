gcc -I`gcc -print-file-name=plugin`/include -fPIC -shared -O2 plugin-pragma-gcc.c -o plugin.so
gcc test.c -fplugin=/home/jed/KEVOREE_PROJECT/kevoree-cpp/tests/plugin.so -o test
