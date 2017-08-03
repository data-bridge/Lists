set arg = $argv[1]
echo $arg
./test $arg > tmp/a$arg
java -jar ../java/Metaphone3.jar $arg tmp/b$arg
diff --ignore-all-space tmp/a$arg tmp/b$arg
cat tmp/d$arg
