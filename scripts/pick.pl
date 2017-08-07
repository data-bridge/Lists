#!perl

use strict;
use warnings;

# Picks all words with given phonemes.

my $FILE = "wordsort.txt";
if ($#ARGV != 0)
{
  print "Usage: perl pick.pl \"p\/h\"\n";
  exit(0);
}

my $term = $ARGV[0];

my $plain_flag;
if (length($term) > 2 && $term !~ /\//)
{
  $plain_flag = 1;
}
else
{
  $plain_flag = 0;
}


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

  if ($plain_flag)
  {
    if (index($a[0], $term) != -1)
    {
      print "$line\n";
    }
  }
  elsif (index($a[2], $term) != -1)
  {
    print "$line\n";
  }
}
close $fh;
