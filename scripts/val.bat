foreach i (../../../bridgedata/words/Moby/Words/files/*)
  set b = `basename $i`
  echo $b
  ./test $i > tmp/a$b
  # java -jar ../java/Metaphone3.jar $i tmp/b$b
  diff --ignore-all-space tmp/a$b tmp/b$b > tmp/d$b
end
wc tmp/d*.TXT
