#!perl

use strict;
use warnings;

my $a = "<name/>";
$a =~ s/\<\s*(\w+)([^>]*)\/\s*\>/<$1$2><\/$1>/g;
# <name attr attr2></name>
print "$a\n";
