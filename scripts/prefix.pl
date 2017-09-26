#!perl

use strict;
use warnings;

# Checks prefix pronunciations against actual ones.

my $FILE = "wordsort.txt";
my $DIFFPRON = "diffpron.log";

my $reverse_flag = 0;
my $FIXES = "prefixes.log";
my $NOFIXES = "noprefixes.log";

if ($#ARGV == 0)
{
  if ($ARGV[0] ne "rev")
  {
    die "Usage: perl prefix.pl [rev]\n";
  }
  $reverse_flag = 1;
  $FIXES = "postfixes.log";
  $NOFIXES = "nopostfixes.log";
}

my (%words, %wordlen, %wordfirst);
my $lineno = 0;
my $num_words = 0;
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

  $a[0] = lc $a[0];

  if ($reverse_flag)
  {
    $a[0] = reverse $a[0];
    $a[2] = reverse $a[2];
  }

  if (! defined $words{$a[0]} || ! defined $words{$a[0]}{$a[2]})
  {
    # One line number that is an example of pronunciation.
    $words{$a[0]}{$a[2]} = $a[1];
    $wordlen{$a[0]} = length $a[0];
    $wordfirst{$a[0]} = substr $a[0], 0, 1;
    $num_words++;
  }
}
close $fh;

my (%prefixes, %prefixlen, %prefixfirst);
open my $fp, '<', $FIXES or die "Can't open $FIXES: $!";
while (my $line = <$fp>)
{
  chomp $line;
  $line =~ s///g;
  $lineno++;

  my @a = split / /, $line;
  if ($#a < 1)
  {
    warn "line should have at least one space ($lineno): $line";
    next;
  }

  $a[0] = reverse $a[0] if ($reverse_flag);

  $prefixlen{$a[0]} = length $a[0];
  $prefixfirst{$a[0]} = substr $a[0], 0, 1;
  for my $i (1 .. $#a)
  {
    # Remove stresses.
    $a[$i] =~ s/'/\//g;
    $a[$i] =~ s/,/\//g;
    $a[$i] =~ s/^\///g;
    $a[$i] =~ s/\/$//g;
    $a[$i] =~ s/\/\//\//g;

    $a[$i] = reverse $a[$i] if ($reverse_flag);

    push @{$prefixes{$a[0]}}, $a[$i];
  }
}
close $fp;

my %noprefixes;
open my $fe, '<', $NOFIXES or die "Can't open $NOFIXES: $!";
while (my $line = <$fe>)
{
  chomp $line;
  $line =~ s///g;
  $lineno++;

  $line = reverse $line if ($reverse_flag);

  $noprefixes{$line} = 1;
}
close $fe;

my (%diffpron);
open my $fd, '<', $DIFFPRON or die "Can't open $DIFFPRON: $!";
while (my $line = <$fd>)
{
  chomp $line;
  $line =~ s///g;
  $lineno++;

  my @a = split / /, $line;
  if ($#a < 1)
  {
    warn "line should have at least one space ($lineno): $line";
    next;
  }

  $a[0] = reverse $a[0] if ($reverse_flag);

  for my $i (1 .. $#a)
  {
    # Remove stresses.
    $a[$i] =~ s/'/\//g;
    $a[$i] =~ s/,/\//g;
    $a[$i] =~ s/^\///g;
    $a[$i] =~ s/\/$//g;
    $a[$i] =~ s/\/\//\//g;

    $a[$i] = reverse $a[$i] if ($reverse_flag);

    push @{$diffpron{$a[0]}}, $a[$i];
  }
}
close $fd;

my @pre = sort keys %prefixes;
my @wd = sort keys %words;
my %prefixmatches;

for my $p (@pre)
{
  my $firstp = $prefixfirst{$p};
  for my $w (@wd)
  {
    next if defined $noprefixes{$w};
    next if $wordfirst{$w} lt $firstp;
    last if $wordfirst{$w} gt $firstp;
    next unless $wordlen{$w} > $prefixlen{$p}+1; # Not e.g. "withe"
    next unless $p eq substr $w, 0, $prefixlen{$p};
    my $rest = substr $w, $prefixlen{$p};
    next unless defined $words{$rest};

    my $found = 0;
    my $wholerestpron;
    my $prefix_pron_matches = 0;
    for my $prefixpron (@{$prefixes{$p}})
    {
      last if $found;
      my $l = length $prefixpron;
      for my $wordpron (keys %{$words{$w}})
      {
        next unless $l < length $wordpron;
        if ($prefixpron eq substr $wordpron, 0, $l)
        {
          $wholerestpron = substr $wordpron, $l+1; # Skip /
          $prefix_pron_matches = 1;
          my $restfound = 0;
          for my $rpron (keys %{$words{$rest}})
          {
            if ($wholerestpron eq $rpron)
            {
              $restfound = 1;
              last;
            }
          }
          if (! $restfound)
          {
            if (defined $diffpron{$rest})
            {
              for my $rpron (@{$diffpron{$rest}})
              {
                if ($wholerestpron eq $rpron)
                {
                  $restfound = 1;
                  last;
                }
              }
            }
            next unless $restfound;
          }

          $found = 1;
          $prefixmatches{$p}{$prefixpron}++;
          last;
        }
      }
    }

    if (! $found)
    {
      if (! $reverse_flag)
      {
        print "Word $w, prefix $p:\n";
        print "prefix ", join " ", @{$prefixes{$p}}, "\n";
        for my $wordpron (keys %{$words{$w}})
        {
          print "word   $wordpron\n";
          if ($prefix_pron_matches)
          {
            for my $ww (keys %{$words{$rest}})
            {
              print "rest   ";
              print " " x (length($wordpron) - length($ww));
              print "$ww\n";
            }
          }
        }
      }
      else
      {
        my $wr = reverse $w;
        my $pr = reverse $p;
        print "Word $wr, suffix $pr:\n";
        print "prefix ";
        my $t = join " ", @{$prefixes{$p}};
        my $tr = reverse $t;
        print "$tr\n";
        for my $wordpron (keys %{$words{$w}})
        {
          my $wpr = reverse $wordpron;
          print "word   $wpr\n";
          if ($prefix_pron_matches)
          {
            for my $ww (keys %{$words{$rest}})
            {
              print "rest   ";
              print " " x (length($wordpron) - length($ww));
              my $wwr = reverse $ww;
              printf "$wwr\n";
            }
          }
        }
      }
      print "\n";
    }
  }
}

print "Number of distinct words: $num_words\n\n";
exit;

# TODO: Look at this later.
for my $p (@pre)
{
  print "Prefix: $p\n";
  for my $prefixpron (@{$prefixes{$p}})
  {
    if (defined $prefixmatches{$p}{$prefixpron})
    {
      print "$prefixpron: $prefixmatches{$p}{$prefixpron}\n";
    }
    else
    {
      print "$prefixpron: 0\n";
    }
  }
  print "\n";
}
