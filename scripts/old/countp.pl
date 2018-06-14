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
    die "Usage: perl countp.pl file\n";
}

my %hash;
open my $fh, '<', $FILE or die "Can't open $FILE: $!";
while (my $line = <$fh>)
{
  chomp $line;
  $line =~ s///g;

  if ($line =~ /fix (\w+):/)
  {
    $hash{$1}++;
  }
}
close $fh;

for my $k (sort keys %hash)
{
  printf "%3d  %s\n", $hash{$k}, $k;
}
