#!perl

use strict;
use warnings;

# Makes a csv table of pairs of phonemes.

my $SEP = ";";

my $FILE;
if ($#ARGV == 0)
{
  $FILE = $ARGV[0];
}
else
{
  $FILE = "wordsort.txt";
}

my (%singles, %pairs);

my $lineno = 0;
open my $fh, '<', $FILE or die "Can't open $FILE: $!";
while (my $line = <$fh>)
{
  chomp $line;
  $line =~ s///g;
  $lineno++;

  my @a = split / /, $line;
  if ($#a != 2)
  {
    warn "line should have one space ($lineno): $line";
    next;
  }

  # Remove stresses.
  $a[2] =~ s/'/\//g;
  $a[2] =~ s/,/\//g;
  $a[2] =~ s/^\///g;
  $a[2] =~ s/\/$//g;
  $a[2] =~ s/\/\//\//g;

  my @phonemes = split /\//, $a[2];
  $singles{$_}++ for @phonemes;

  for my $p (0 .. $#phonemes-1)
  {
    $pairs{$phonemes[$p]}{$phonemes[$p+1]}++;
# if ($phonemes[$p] =~ /^\s*$/ || $phonemes[$p+1] =~ /^\s*$/)
# {
  # print "XXX $lineno $line\n";
# }
  }
}
close $fh;

print $SEP;
my @slist = sort keys %singles;
print join $SEP, @slist;
print "\n";
for my $first (0 .. $#slist)
{
  print "$slist[$first]$SEP";
  for my $second (0 .. $#slist)
  {
    print $pairs{$slist[$first]}{$slist[$second]} || 0;
    print $SEP unless $second eq $#slist;
  }
  print "\n";
}
