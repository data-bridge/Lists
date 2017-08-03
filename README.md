Introduction
============
Lists is a small set of tools for bridge player names and event names.  As it stands, these are probably mainly useful for me.

The code is licensed under the Apache 2.0 license in the LICENSE file except where otherwise noted.  Specifically, Metaphone3 is a C++ port of Lawrence Philips' Java code, Version 2.1.3, which was released under the license included in that source file (as part of a Google tool, [Refine](https://github.com/OpenRefine/OpenRefine/blob/master/main/src/com/google/refine/clustering/binning/Metaphone3.java).

(c) Soren Hein 2017.

Metaphone3
==========
The original Java code is included for reference in the Java directory.  There is also a jar file that can be executed as

java -jar Metaphone3.jar input.txt [output.txt]

The Metaphone3 C++ port has been validated against a large set of ASCII files from the Gutenberg project (a total of 856,368 lines), and it generates identical outputs to the Java version. (Not quite true yet, 170 differences.)

There are some subtleties with UTF-8 and extended-ASCII data.  The Java code used UTF-8 in a couple of places, though not in a very consistent manner, and whether issues arose in the coding or in the download, there are places where the codes are wrong.  As it stands, the Java code is also not very well suited to non-ASCII input.  For example, a non-ASCII vowel is always encoded as "A", even if the preceding character was a normal ASCII vowel.  José (with an accent) is encoded differently than Jose, although it is clear from the code that that was not the intention.

Supported systems
=================
The code should be quite portable, but so far I've only tested it on Windows 10 using the Microsoft Visual Studio C++ compiler and linker.

