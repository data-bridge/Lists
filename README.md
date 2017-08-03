Introduction
============
Lists is a small set of tools for bridge player names and event names.  As it stands, these are probably mainly useful for me.

The code is licensed under the Apache 2.0 license in the LICENSE file except where otherwise noted.  Specifically, Metaphone3 is a C++ port of Lawrence Philips' Java code, Version 2.1.3, which was released under the license included in that source file (as part of a Google tool, [Refine](https://github.com/OpenRefine/OpenRefine/blob/master/main/src/com/google/refine/clustering/binning/Metaphone3.java).

(c) Soren Hein 2017.

Metaphone3 port
===============
The original Java code is included for reference in the Java directory.  There is also a jar file that can be executed as

java -jar Metaphone3.jar input.txt [output.txt]

The pure Metaphone3 C++ port is included under src/ports.  This makes it easier to diff the source against later changes.

The Metaphone3 C++ port has been validated against a large set of ASCII files from the Gutenberg project (a total of 856,368 lines in 16 files, no doubt with some overlap).  These files do contain a small number of non-ASCII characters, almost all of which are treated identically.  Annoyingly there is a single difference, "play dØ" (where the last character is extended ASCII 0xD8, a capital 0 with a slash).  The port correctly (in my opinion) treats this as a vowel.

There are some subtleties with UTF-8 and extended-ASCII data.  The Java code used UTF-8 in a couple of places, though not in a very consistent manner, and whether issues arose in the coding or in the download, there are places where the codes are wrong.  As it stands, the Java code is also not very well suited to non-ASCII input.  For example, a non-ASCII vowel is always encoded as "A", even if the preceding character was a normal ASCII vowel.  José (with an accent) is encoded differently than Jose, although it is clear from the code that that was not the intention.

Here are the specific issues that arose on a list of names with UTF-8 and/or extended ASCII.

* Pittalà: Should treat à as vowel, then we no longer get "PATAL".
* Danièle: Should treat è as vowel, then the double vowel "iè" is eliminated and we no longer get "TANAAL/DANAAL".
* Gisèle: Should treat è as vowel, then the G is soft ("JSL/KSL/JSL/GSL", no longer "KSL/JSL/GSL/JSL").
* Irene: Should treat è as vowel, then we get "ARAN" and not "ARN".
* Gérard: Should treat é as vowel, then we get "JRRT/KRRT/JRRD/GRRD", longer "KTTR//GRRD/".
* José: Should treat é as vowel, then we get "HS" and "HASA", no longer "JS" and "JASA".
* Tengå: Should treat å as vowel, then we get "TANKA/TANGA", no longer "TANK/TANG".
* Mårten: Ditto, "MARTAN" and not "MRTAN".
* Rudenstål: Ditto, "RADANSTAL" (when length 9 is OK) and not "RADANSTL".
* Londoño: Should treat ñ as consonent, then we get "LNTN" etc. and not "LNT" etc.
* Muñoz: Ditto, "MNS" and not "MS".

There is also one issue with the port that was not fixed until after the port:

* Hervé comes out of the C++ port as "HARF/HARV" and not "HARFA/HARVA".
* Gagné comes out as "KN/KKN/GN/GGN" and not "KKN//GGN".

The é is translated into a normal e, which is then no longer stressed ("e\_Pronounced\_At\_End").  In contrast, the Java source leaves the é as a special character that is forced into a pronounced vowel.

On the other hand, both sources agree on "Herve" and "Gagne".

It would be possible to add these two exceptions in "e\_Pronounced\_At\_End"
 (under m\_length == 5), but then the ASCII sources would no longer agree.  So this change was left for later.

Supported systems
=================
The code should be quite portable, but so far I've only tested it on Windows 10 using the Microsoft Visual Studio C++ compiler and linker.

