#!perl

use strict;
use warnings;

my $FILE;
if ($#ARGV == 0)
{
  $FILE = $ARGV[0];
}
else
{
  $FILE = "../../../bridgedata/words/Moby/Pronunciator II/mpron.txt";
}

my $lineno = 0;
open my $fh, '<', $FILE or die "Can't open $FILE: $!";
while (my $line = <$fh>)
{
  chomp $line;
  $line =~ s///g;
  $lineno++;

  my @a = split / /, $line;
  if ($#a != 1)
  {
    warn "line should have one space: $line" unless $#a == 1;
    next;
  }

  my @plain = split /[_-]/, $a[0];
  my @pron = split /_/, $a[1];

  if ($#plain != $#pron)
  {
    if ($#plain == 1 && $#pron == 0)
    {
      my $bulk = substr $a[1], 1;
      my $commas = ($bulk =~ tr/,//);
      my $ticks = ($bulk =~ tr/'//);

      if ($commas + $ticks != 1)
      {
        warn "$lineno ($#plain, $#pron): $line\n";
        next;
      }

      my $cand = index($a[1], ',', 1);
      if ($cand == -1)
      {
        $cand = index($a[1], "'", 1);
      }

      $pron[0] = substr($a[1], 0, $cand);
      $pron[1] = substr($a[1], $cand+1);
    }
  }

  for my $i (0 .. $#plain)
  {
    my $plainword = $plain[$i];
    my $pronword = $pron[$i];

    print "$plainword $lineno $pronword\n";
  }
}
close $fh;


