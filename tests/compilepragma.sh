gcc -I`gcc -print-file-name=plugin`/include -fPIC -shared -O2 plugin-pragma-gcc.c -o plugin.so
g++ test.c -fplugin=`pwd`/plugin.so -o test
