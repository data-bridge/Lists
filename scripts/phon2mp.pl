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

my (%TABLE, %COMPOSITES);
set_table();

my %COMBOS;
my $under_errors = 0;
my %under_stats;

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

  my $salvaged = 0;
  if ($#plain != $#pron)
  {
    my $symbol;
    if ($#plain == 1 && $#pron == 0)
    {
      my $cand = -1;

      my $firstchar = substr($a[1], 0, 1);
      my $pos = ($firstchar eq ',' || $firstchar eq "'" ? 1 : 0);

      my $commas = ($a[1] =~ tr/,//);
      my $ticks = ($a[1] =~ tr/'//);

      if ($commas + $ticks - $pos == 1)
      {
        $cand = index($a[1], ',', $pos);
        if ($cand == -1)
        {
          $cand = index($a[1], "'", $pos);
        }
      }

      if ($cand >= 0)
      {
        my $next_plain = lc(substr $plain[1], 0, 1);
        my $next_pron = lc(substr $a[1], $cand+1, 1);
        if ($next_pron eq '/')
        {
          $next_pron = lc(substr $a[1], $cand+2, 1);
        }

        if ($next_plain eq $next_pron)
        {
          $pron[0] = substr($a[1], 0, $cand);
          $pron[1] = substr($a[1], $cand+2);
          print "Salvaged $line: $pron[0] || $pron[1]\n";
          $salvaged = 1;
        }
      }
    }

    if (! $salvaged)
    {
      my $u = "$#plain $#pron";
      $under_stats{$u}++;
      print "under $lineno: $line\n";
      $under_errors++;
      next;
    }
  }

  for my $i (0 .. $#plain)
  {
    my $plainword = $plain[$i];
    my $pronword = $pron[$i];
    $pronword =~ s/'/\//g;
    $pronword =~ s/,/\//g;
    $pronword =~ s/^\///g;
    $pronword =~ s/\/$//g;

    my @sounds = split /\//, $pronword;

    my @codes;
    my $notfound = 1;
    my @prev = qw(- - - -);
    for my $s (@sounds)
    {
      next unless $s;
      if (! defined $TABLE{$s})
      {
        $notfound = 0;
        # warn "Could not find '$s'";
        print "MISS $lineno, $s: $line\n";
        $COMBOS{$s}++;
        last;
      }

      for my $c (0 .. 3)
      {
        my $p = $TABLE{$s}[$c];
        next if (substr $p, -1) eq '-';
        next if $p eq 'A' && $prev[$c] eq 'A';
        $codes[$c] .= $p;
        $prev[$c] = substr $p, -1;
      }
    }

    next unless $notfound;
    my $out = "$plainword ";
    for my $c (0 .. 3)
    {
      $out .= $codes[$c] || "";
      $out .= ";" unless $c == 3;
    }
    print "$out\n";
  }
}

close $fh;

print "\n";
for my $k (sort keys %COMBOS)
{
  printf "%4d %8s\n", $COMBOS{$k}, $k;
}

print "\n";
for my $k (sort keys %under_stats)
{
  printf "%4d %8s\n", $under_stats{$k}, $k;
}

print "\nUnder $under_errors\n";



sub set_table
{
  # "Vowels".
  push @{$TABLE{"&"}}, qw(- A - A);
  push @{$TABLE{"@"}}, qw(- A - A);
  push @{$TABLE{"(@)"}}, qw(- A - A);
  push @{$TABLE{"[@]"}}, qw(- A - A);
  push @{$TABLE{"-"}}, qw(- A - A);
  push @{$TABLE{"A"}}, qw(- A - A);
  push @{$TABLE{"AU"}}, qw(- A - A);
  push @{$TABLE{"aI"}}, qw(- A - A);
  push @{$TABLE{"E"}}, qw(- A - A);
  push @{$TABLE{"eI"}}, qw(- A - A);
  push @{$TABLE{"hw"}}, qw(- A - A);
  push @{$TABLE{"I"}}, qw(- A - A);
  push @{$TABLE{"i"}}, qw(- A - A);
  push @{$TABLE{"j"}}, qw(- A - A);
  push @{$TABLE{"O"}}, qw(- A - A);
  push @{$TABLE{"Oi"}}, qw(- A - A);
  push @{$TABLE{"oU"}}, qw(- A - A);
  push @{$TABLE{"U"}}, qw(- A - A);
  push @{$TABLE{"u"}}, qw(- A - A);
  push @{$TABLE{"w"}}, qw(- A - A);
  push @{$TABLE{"y"}}, qw(- A - A);
  push @{$TABLE{"Y"}}, qw(- A - A);

  # Consonants.
  push @{$TABLE{"b"}}, qw(P P B B);
  push @{$TABLE{"c"}}, qw(S S S S);
  push @{$TABLE{"D"}}, qw(0 0 0 0); # Zero
  push @{$TABLE{"d"}}, qw(T T D D);
  push @{$TABLE{"dZ"}}, qw(J J J J);
  push @{$TABLE{"f"}}, qw(F F F F);
  push @{$TABLE{"g"}}, qw(K K G G);
  push @{$TABLE{"h"}}, qw(H H H H);
  push @{$TABLE{"k"}}, qw(K K K K);
  push @{$TABLE{"l"}}, qw(L L L L);
  push @{$TABLE{"m"}}, qw(M M M M);
  push @{$TABLE{"N"}}, qw(NK NK NG NG);
  push @{$TABLE{"n"}}, qw(N N N N);
  push @{$TABLE{"p"}}, qw(P P P P);
  push @{$TABLE{"r"}}, qw(R R R R);
  push @{$TABLE{"R"}}, qw(R R R R);
  push @{$TABLE{"S"}}, qw(X X X X);
  push @{$TABLE{"s"}}, qw(S S S S);
  push @{$TABLE{"T"}}, qw(0 0 0 0); # Zero
  push @{$TABLE{"t"}}, qw(T T T T);
  push @{$TABLE{"tS"}}, qw(X X X X);
  push @{$TABLE{"v"}}, qw(F F V V);
  push @{$TABLE{"x"}}, qw(X X X X);
  push @{$TABLE{"Z"}}, qw(J J J J);
  push @{$TABLE{"z"}}, qw(S S S S);
}

