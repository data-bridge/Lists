#!perl

use strict;
use warnings;

# Detects equal and different pronunciations of words in the
# sorted word list.

my $FILE;
if ($#ARGV == 0)
{
  $FILE = $ARGV[0];
}
else
{
  $FILE = "wordsort.txt";
}

my $ACCEPTS = "accepts.lst";
my %accepts;
read_accepts();

my $lineno = 0;
my $word;
my $prev_word = "";
my %group;
my ($num_words, $num_good_words, $num_good_multi_words, $num_bad_words);
my $num_salvaged = 0;
my @hist;

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

  if (lc($a[0]) ne $prev_word)
  {
    process_group($prev_word, \%group);
    %group = ();
    $prev_word = lc($a[0]);
  }

  # Remove stresses.
  $a[2] =~ s/'/\//g;
  $a[2] =~ s/,/\//g;
  $a[2] =~ s/^\///g;
  $a[2] =~ s/\/$//g;
  $a[2] =~ s/\/\//\//g;

  push @{$group{$a[2]}}, $a[1];
}
close $fh;

process_group($prev_word, \%group);

printf "%-30s %8d\n", "Number of words", $num_words;
printf "%-30s %8d\n", "Number of good words", $num_good_words;
printf "%-30s %8d\n", "Number of good multi-words", $num_good_multi_words;
printf "%-30s %8d\n\n", "Number of salvaged words", $num_salvaged;
printf "%-30s %8d\n\n", "Number of bad words", $num_bad_words;

print "Histogram\n";
my $m = ($#hist > 50 ? 50 : $#hist);
for my $i (0 .. $m)
{
  printf "%3d  %6d\n", $i, $hist[$i] if defined $hist[$i];
}

sub process_group
{
  my ($word, $group) = @_;

  my @keys = keys %group;
  my $count = $#keys;
  return if $count < 0;

  $num_words++;
  if ($count == 0)
  {
    $num_good_words++;
    my $n = $#{$group{$keys[0]}} + 1;
    $hist[$n]++;

    if ($n > 1)
    {
      $num_good_multi_words++;
    }
    elsif ($n != 1)
    {
      die "Odd count";
    }
  }
  else
  {
if ($word =~ /rust/)
{
  print "HERE\n";
}
    my $salvaged = 1;
    for my $k (@keys)
    {
      if (! defined $accepts{$word}{$k})
      {
        $salvaged = 0;
        last;
      }
    }
    
    if ($salvaged)
    {
      $num_salvaged++;
    }
    else
    {
      $num_bad_words++;
      print "$word:\n";
      for my $k (sort @keys)
      {
        printf "%2d  %s  ", $#{$group{$k}}+1, $k;
        print join ", ", sort {$a <=> $b} @{$group{$k}};
        print "\n";
      }
      print "\n";
    }
  }
}


sub read_accepts
{
  open my $fa, '<', $ACCEPTS or die "Can't open $ACCEPTS $!";
  while (my $line = <$fa>)
  {
    chomp $line;
    $line =~ s///g;
    $lineno++;
    next if $line eq "";

    die "Bad line '$line'" unless $line =~ /(^.*):\s+(.*)$/;
    my ($word, $rest) = ($1, $2);

    my @list = split /\s+/, $rest;
    $accepts{$word}{$_} = 1 for @list;
  }
}

