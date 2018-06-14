set arg = "../../../bridgedata/players/list.txt"
set base = `basename $arg`
echo ${base}
./test ${arg} > tmp/a${base}
java -jar ../java/Metaphone3.jar ${arg} tmp/b${base}
diff --ignore-all-space tmp/a${base} tmp/b${base} > tmp/d${base}
wc tmp/d${base}
