/*
 * Copyright 2010, Lawrence Philips
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following 
 *    disclaimer in the documentation and/or other materials provided 
 *    with the distribution.
 *  - Neither the name of Google Inc. nor the names of its contributors 
 *    may be used to endorse or promote products derived from this 
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * METAPHONE3 IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND. 
 * LAWRENCE PHILIPS AND ANTHROPOMORPHIC SOFTWARE LLC MAKE NO WARRANTIES, 
 * EXPRESS OR IMPLIED, THAT IT IS FREE OF ERROR, OR ARE CONSISTENT WITH 
 * ANY PARTICULAR STANDARD OF MERCHANTABILITY, OR THAT IT WILL MEET 
 * YOUR REQUIREMENTS FOR ANY PARTICULAR APPLICATION.
 * LAWRENCE PHILIPS AND ANTHROPOMORPHIC SOFTWARE LLC DISCLAIM ALL 
 * LIABILITY FOR DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES RESULTING 
 * FROM USE OF THIS SOFTWARE.
 *
 * DISCLAIMER:
 * Anthropomorphic Software LLC claims only that Metaphone 3 will 
 * return correct encodings, within the 'fuzzy' definition of correct 
 * as above, for a very high percentage of correctly spelled English 
 * and commonly recognized non-English words. Anthropomorphic Software LLC
 * warns the user that a number of words remain incorrectly encoded, 
 * that misspellings may not be encoded 'properly', and that people 
 * often have differing ideas about the pronunciation of a word. 
 * Therefore, Metaphone 3 is not guaranteed to return correct 
 * results every time, and so a desired target word may very well 
 * be missed. Creators of commercial products should keep in mind 
 * that systems like Metaphone 3 produce a 'best guess' result, 
 * and should condition the expectations of end users accordingly.
 */

/*
 * Metaphone 3
 * VERSION 2.1.3
 *
 * by Lawrence Philips
 *
 * Metaphone 3 is designed to return an *approximate* phonetic key (and 
 * an alternate approximate phonetic key when appropriate) that should 
 * be the same for English words, and most names familiar in the United 
 * States, that are pronounced *similarly*.
 * The key value is *not* intended to be an *exact* phonetic, or even 
 * phonemic, representation of the word. This is because a certain 
 * degree of 'fuzziness' has proven to be useful in compensating for 
 * variations in pronunciation, as well as misheard pronunciations. 
 * For example, although americans are not usually aware of it,
 * the letter 's' is normally pronounced 'z' at the end of words 
 * such as "sounds".
 *
 * The 'approximate' aspect of the encoding is implemented according 
 * to the following rules:
 *
 * (1) All vowels are encoded to the same value - 'A'. 
 *     - If the parameter encodeVowels is set to false, only 
 *       *initial* vowels will be encoded at all. 
 *     - If encodeVowels is set to true, 'A' will be encoded at all 
 *       places in the word that any vowels are normally pronounced. 
 *
 * 'W' as well as 'Y' are treated as vowels. Although there are 
 * differences in the pronunciation of 'W' and 'Y' in different 
 * circumstances that lead to their being classified as vowels under 
 * some circumstances and as consonants in others, for the purposes
 * of the 'fuzziness' component of the Soundex and Metaphone family 
 * of algorithms they will be always be treated here as vowels.
 *
 * (2) Voiced and un-voiced consonant pairs are mapped to the same 
 * encoded value. This means that:
 * 'D' and 'T' -> 'T'
 * 'B' and 'P' -> 'P'
 * 'G' and 'K' -> 'K'
 * 'Z' and 'S' -> 'S'
 * 'V' and 'F' -> 'F'
 *
 * - In addition to the above voiced/unvoiced rules, 
 *   'CH' and 'SH' -> 'X', where 'X' represents the "-SH-" and "-CH-" 
 *   sounds in Metaphone 3 encoding.
 *
 * - Also, the sound that is spelled as "TH" in English is encoded 
 *   to '0' (zero symbol). (Although Americans are not usually aware 
 *   of it, "TH" is pronounced in a voiced (e.g. "that") as well as 
 *   an unvoiced (e.g. "theater") form, which are naturally mapped 
 *   to the same encoding.)
 *
 * In the "Exact" encoding, voiced/unvoiced pairs are not mapped to 
 * the same encoding, except for the voiced and unvoiced versions of 
 * 'TH', sounds such as 'CH' and 'SH', and for 'S' and 'Z',
 * so that the words whose metaph keys match will in fact be closer 
 * in pronunciation that with the more approximate setting. Keep in 
 * mind that encoding settings for search strings should always
 * be exactly the same as the encoding settings of the stored metaph 
 * keys in your database!
 *
 * Because of the considerably increased accuracy of Metaphone3, 
 * it is now possible to use this setting and have a very good chance 
 * of getting a correct encoding.
 * 
 * In the encodeVowels encoding, all non-initial vowels and diphthongs 
 * will be encoded to 'A', and there will only be one such vowel 
 * encoding character between any two consonants.  It turns out that 
 * there are some surprising wrinkles to encoding non-initial vowels in
 * practice, pre-eminently in inversions between spelling and 
 * pronunciation such as e.g.  "wrinkle" => 'RANKAL', where the last 
 * two sounds are inverted when spelled.
 *
 * The encodings in this version of Metaphone 3 are according to 
 * pronunciations common in the United States. This means that they 
 * will be inaccurate for consonant pronunciations that are different 
 * in the United Kingdom, for example "tube" -> "CHOOBE" -> XAP rather 
 * than american TAP.
 *
 * Metaphone 3 was preceded by by Soundex, patented in 1919, and 
 * Metaphone and Double Metaphone, developed by Lawrence Philips. 
 * All of these algorithms resulted in a significant number of
 * incorrect encodings. Metaphone3 was tested against a database of 
 * about 100 thousand English words, names common in the United States, 
 * and non-English words found in publications in the United States,
 * with an emphasis on words that are commonly mispronounced, 
 * prepared by the Moby Words website, but with the Moby Words 
 * 'phonetic' encodings algorithmically mapped to Double Metaphone 
 * encodings.  Metaphone3 increases the accuracy of encoding of 
 * English words, common names, and non-English words found in 
 * American publications from the 89% for Double Metaphone, to 
 * over 98%.
 *
 */

/*
 * Ported to C++.
 * Soren Hein, August 2017
 */

#include <iostream>
#include <cstdarg>

#if defined(_WIN32) && defined(__MINGW32__)
  #include "mingw.mutex.h"
#else
  #include <mutex>
#endif

#include "Metaphone3.h"

#include "charsets.h"

static mutex mtx;
static bool setTables = false;
static CharTables tablesASCII, tablesExtended;


// Default size of key storage allocation
#define MAX_KEY_ALLOCATION 32

// Default maximum length of encoded key
#define DEFAULT_MAX_KEY_LENGTH 8


Metaphone3::Metaphone3()
{
  m_metaphLength = DEFAULT_MAX_KEY_LENGTH;
  m_encodeVowels = false;
  m_encodeExact = false;

  if (! setTables)
  {
    mtx.lock();
    if (! setTables)
      setCharTables(tablesASCII, tablesExtended);
    setTables = true;
    mtx.unlock();
  }
}


Metaphone3::~Metaphone3()
{
}


void Metaphone3::setWord(const string in)
{
  convertToUpper(in, m_inWord, tablesASCII);
  m_length = static_cast<int>(m_inWord.size());
}


bool Metaphone3::setKeyLength(const int inKeyLength)
{
  // Set length allocated for output keys.
  // Return false if input is too large.
  if (inKeyLength > MAX_KEY_ALLOCATION)
  {
    m_metaphLength = MAX_KEY_ALLOCATION;
    return false;
  }

  m_metaphLength = (inKeyLength < 1 ? 1 : inKeyLength);
  return true;
}

   
void Metaphone3::add(const string& in)
{
  // Adds an encoding character to the encoded key value string -
  // one parameter version.
  if (in != "A" || m_primary == "" || m_primary.back() != 'A')
    m_primary += in;

  if (in != "A" || m_secondary == "" || m_secondary.back() != 'A')
    m_secondary += in;
}


void Metaphone3::add(
  const string& main, 
  const string& alt)
{
  // Adds an encoding character to the encoded key value string - 
  // two parameter version
  if (main != "A" || m_primary == "" || m_primary.back() != 'A')
    m_primary += main;

  if (alt != "A" || m_secondary == "" || m_secondary.back() != 'A')
    m_secondary += alt;
}


void Metaphone3::addExactApprox(
  const string& mainExact, 
  const string& altExact, 
  const string& main, 
  const string& alt)
{
  // Adds an encoding character to the encoded key value string - 
  // Exact/Approx version.
  if (m_encodeExact)
    add(mainExact, altExact);
  else
    add(main, alt);
}


void Metaphone3::addExactApprox(
  const string& mainExact, 
  const string& main)
{
  // Adds an encoding character to the encoded key value string - 
  // Exact/Approx version.
  add(m_encodeExact ? mainExact : main);
}


int Metaphone3::getKeyLength() const
{
  return m_metaphLength;
}


int Metaphone3::getMaximumKeyLength() const
{
  // Maximum number of characters allowed for encoded key.
  return MAX_KEY_ALLOCATION;
}


void Metaphone3::setEncodeVowels(const bool inEncodeVowels)
{
  // Sets flag that causes Metaphone3 to encode non-initial vowels. 
  // However, even if there are more than one vowel sound in a vowel 
  // sequence (i.e.  vowel diphthong, etc.), only one 'A' will be 
  // encoded before the next consonant or the end of the word.
  m_encodeVowels = inEncodeVowels;
}


bool Metaphone3::getEncodeVowels() const
{
  // Retrieves setting determining whether or not non-initial vowels 
  // will be encoded.
  return m_encodeVowels;
}


void Metaphone3::setEncodeExact(const bool inEncodeExact)
{
  // Sets flag that causes Metaphone3 to encode consonants as exactly 
  // as possible.
  // This does not include 'S' vs. 'Z', since Americans will pronounce 
  // 'S' at the at the end of many words as 'Z', nor does it include 
  // "CH" vs. "SH". It does cause a distinction to be made between 
  // 'B' and 'P', 'D' and 'T', 'G' and 'K', and 'V' and 'F'.
  m_encodeExact = inEncodeExact;
}


bool Metaphone3::getEncodeExact() const
{
  // Retrieves setting determining whether or not consonants will be 
  // encoded "exactly".
  return m_encodeExact;
}


string Metaphone3::getMetaph() const
{
  // Retrieves primary encoded key.
  return m_primary;
}


string Metaphone3::getAlternateMetaph() const
{
  // Retrieves alternate encoded key, if any.
  return m_secondary;
}


bool Metaphone3::front_Vowel(const int at) const
{
  // Test for close front vowels.
  const char c = charAt(at);
  return (c == 'E' || c == 'I' || c == 'Y');
}


bool Metaphone3::slavoGermanic() const
{
  // Detect names or words that begin with spellings typical of 
  // German or Slavic words.
  return (stringAt(0, 3, "SCH") || 
      stringAt(0, 2, "SW") || 
      charAt(0) == 'J' || 
      charAt(0) == 'W');
}


bool Metaphone3::isVowel(const char in) const
{
  // Tests if character is a vowel.
  if (in == 'A' || in == 'E' || in == 'I' || 
      in == 'O' || in == 'U' || in == 'Y' || 
      in == 'Ŕ' || 
      in == 'Á' || in == 'Â' || in == 'Ă' || in == 'Ä' || 
      in == 'Ĺ' || in == 'Ć' || in == 'Č' || 
      in == 'É' || in == 'Ę' || in == 'Ë' || in == 'Ě' || 
      in == 'Í' || in == 'Î' || 
      in == 'Ď' || in == 'Ň' || 
      in == 'Ó' || in == 'Ô' || in == 'Ő' || in == 'Ö' || 
      in == '?' || in == 'Ř' || 
      in == 'Ů' || in == 'Ú' || in == 'Ű' || in == 'Ü' || 
      in == 'Ý' || in == '?')
    return true;
  else
    return false;
}


bool Metaphone3::isVowel(const int at) const
{
  // Tests if character in the input string is a vowel.
  if (at < 0 || at >= m_length)
    return false;
  else
    return isVowel(charAt(at));
}


int Metaphone3::skipVowels(const int at) const
{
  // Skips over vowels in a string. Has exceptions for skipping 
  // consonants that will not be encoded.  Returns position of
  // next consonent in string to be encoded.
  if (at < 0)
    return 0;
  if (at >= m_length)
    return m_length;

  int p = at;
  char it = charAt(p);
  while (isVowel(it) || it == 'W')
  {
    if (stringAt(p, 4, "WICZ", "WITZ", "WIAK") || 
        stringAt(p-1, 5, "EWSKI", "EWSKY", "OWSKI", "OWSKY") || 
       (p+4 == m_last && stringAt(p, 5, "WICKI", "WACKI")))
      break;

    p++;
    if ((charAt(p-1) == 'W' && 
         charAt(p) == 'H') && 
         ! (stringAt(p, 3, "HOP") || 
            stringAt(p, 4, "HIDE", "HARD", "HEAD", "HAWK", 
                     "HERD", "HOOK", "HAND", "HOLE") || 
            stringAt(p, 5, "HEART", "HOUSE", "HOUND") || 
            stringAt(p, 6, "HAMMER")))
      p++;

    if (p >= m_length)
      return m_length;
    it = charAt(p);
  }
  return p;
}


void Metaphone3::advanceCounter(
  const int ifNotEncodeVowels, 
  const int ifEncodeVowels)
{
  // Advance counter m_current so that it indexes the next character 
  // to be encoded (either by ifNot or by if).
  m_current += (m_encodeVowels ? ifEncodeVowels : ifNotEncodeVowels);
}


char Metaphone3::charAt(const int pos) const
{
  if (pos < 0 || pos >= m_length)
    return '\0';
  else
    return m_inWord.at(static_cast<size_t>(pos));
}


bool Metaphone3::rootOrInflections(
  const string& inWord, 
  const string& root)
{
  // Tests whether the word is the root or a regular English inflection
  // of it, e.g. "ache", "achy", "aches", "ached", "aching", "achingly"
  // This is for cases where we want to match only the root and 
  // corresponding inflected forms, and not completely different words 
  // which may have the same substring in them.
  if (inWord == root || inWord == root + "S")
    return true;

  string localRoot = root;
  if (localRoot.back() == 'E')
    localRoot.pop_back();

  // TODO shein: Can speed up by checking lengths and taking substr
  // or inWord.
  if (inWord == localRoot + "ES" ||
      inWord == localRoot + "ED" ||
      inWord == localRoot + "ING" ||
      inWord == localRoot + "INGLY" ||
      inWord == localRoot + "Y")
    return true;
  else
    return false;
}


bool Metaphone3::stringAt(
  const string& target,
  const char * element) const
{
  return (target == string(element));
}


template<typename... Args>
bool Metaphone3::stringAt(
  const string& target,
  const char * first,
  const Args... args) const
{
  return (target == string(first) || stringAt(target, args...));
}


bool Metaphone3::stringAt(
  const int start, 
  const int length,
  const char * element) const
{
  if (start <  0 || start+length > m_length)
    return false;

  const string segment = m_inWord.substr(static_cast<size_t>(start), 
    static_cast<size_t>(length));

  return (segment == string(element));
}


template<typename... Args>
bool Metaphone3::stringAt(
  const int start, 
  const int length,
  const char * element,
  const Args... args) const
{
  if (start <  0 || start+length > m_length)
    return false;

  const string segment = m_inWord.substr(static_cast<size_t>(start), 
    static_cast<size_t>(length));

  return (segment == string(element) || 
      stringAt(segment, args...));
}


void Metaphone3::encode()
{
  // Encodes input string to one or two key values according to 
  // Metaphone 3 rules.
  flag_AL_inversion = false;

  m_current = 0;
  m_primary = "";
  m_secondary = "";

  if (m_length < 1)
    return;

  // Zero-based index;
  m_last = m_length - 1;

  // Main loop.
  const size_t l = static_cast<size_t>(m_metaphLength);
  while (m_primary.length() <= l && m_secondary.length() <= l)
  {
    if (m_current >= m_length)
      break;

    // switch (m_inWord.at(static_cast<size_t>(m_current)))
    switch (const char c = m_inWord[static_cast<unsigned>(m_current)])
    {
      case 'B': encode_B(); break;
      case 'C': encode_C(); break;
      case 'D': encode_D(); break;
      case 'F': encode_F(); break;
      case 'G': encode_G(); break;
      case 'H': encode_H(); break;
      case 'J': encode_J(); break;
      case 'K': encode_K(); break;
      case 'L': encode_L(); break;
      case 'M': encode_M(); break;
      case 'N': encode_N(); break;
      case 'P': encode_P(); break;
      case 'Q': encode_Q(); break;
      case 'R': encode_R(); break;
      case 'S': encode_S(); break;
      case 'T': encode_T(); break;
      case 'V': encode_V(); break;
      case 'W': encode_W(); break;
      case 'X': encode_X(); break;
      case 'Z': encode_Z(); break;

      case 'ß':
      case 'Ç':
        add("S"); 
        m_current++; 
        break;

      case 'Ń':
        add("N");
        m_current++;
        break;

      case 'Đ': // eth
      case 'Ţ': // thorn
        add("0");
        m_current++;
        break;

      case '?': // TODO shein: Check, there was also an "S" case
        add("X");
        m_current++;
        break;

      default:
        // if (isVowel(charAt(m_current)))
        if (isVowel(c))
          encode_Vowels();
        else
          m_current++;
        break;
    }
  }

  // Only give back m_metaphLength number of chars in m_metaph
  if (m_primary.length() > l)
    m_primary = m_primary.substr(0, l);

  if (m_secondary.length() > l)
    m_secondary = m_secondary.substr(0, l);

  // It is possible for the two metaphs to be the same
  // after truncation. lose the second one if so
  if (m_primary == m_secondary)
    m_secondary = "";
}


void Metaphone3::encode_Vowels()
{
  // Encodes all initial vowels to A.
  // Encodes non-initial vowels to A if m_encodeVowels is true.
  if (m_current == 0)
    add("A");
  else if (m_encodeVowels)
  {
    if (charAt(m_current) == 'E')
      encode_E_Pronounced();
    else if (skip_Silent_UE())
      return;
    else if (o_Silent())
    {
      m_current++;
      return;
    }
    else
      add("A");
  }

  if (isVowel(m_current-2) ||
      ! stringAt(m_current-1, 4, "LEWA", "LEWO", "LEWI"))
  {
    m_current = skipVowels(m_current);
  }
  else
    m_current++;
}


void Metaphone3::encode_E_Pronounced()
{
  // Encodes cases where non-initial 'e' is pronounced, taking
  // care to detect unusual cases from the Greek.
  if ((m_length == 4 && stringAt(0, 4, "LAME", "SAKE", "PATE")) || 
      (m_length == 5 && stringAt(0, 5, "AGAPE")) || 
      (m_current == 5 && stringAt(0, 6, "RESUME")))
      // TODO shein: m_current? 5?
  {
    // Special cases with two pronunciations.
    add("", "A");
    return;
  }

  if (m_length == 4 && stringAt(0, 4, "INGE"))
  {
    // Special case "inge" => 'INGA', 'INJ'.
    add("A", "");
    return;
  }

  if (m_current == 5 && stringAt(0, 7, "BLESSED", "LEARNED"))
  {
    // Special handling due to two pronunciations of the '-D'.
    addExactApprox("D", "AD", "T", "AT");
    m_current += 2;
    return;
  }

  // Encode all vowels and diphthongs to the same value.
  if ((! flag_AL_inversion && ! e_Silent() && ! silent_Internal_E()) || 
      e_Pronounced_Exceptions())
  {
    add("A");
  }

  // Now that we've visited the vowel in question.
  flag_AL_inversion = false;
}


bool Metaphone3::o_Silent()
{
  // Tests for cases where non-initial 'o' is not pronounced.
  // Only executed if non initial vowel encoding is turned on.
  // "iron" at beginning or end of word and not "ironic".

  if ((m_current == 2 || m_current+1 == m_last) &&
      stringAt(m_current-2, 4, "IRON") &&
      ! stringAt(m_current-2, 6, "IRONIC"))
    return true;
  else
    return false;
}


bool Metaphone3::e_Silent()
{
  // Tests and encodes cases where non-initial 'e' is never pronounced.
  // Only executed if non initial vowel encoding is turned on.
  if (m_current == m_last)
    return (! e_Pronounced_At_End());

  if (m_current > 1 && 
      m_current+1 == m_last &&
      stringAt(m_last, 1, "S", "D") && 
      ! (stringAt(m_current-1, 3, "TED", "SES", "CES") || 
         stringAt(0, 9, "ANTIPODES", "ANOPHELES") || 
         stringAt(0, 8, "MOHAMMED", "MUHAMMED", "MOUHAMED") || 
         stringAt(0, 7, "MOHAMED") || 
         stringAt(0, 6, "NORRED", "MEDVED", "MERCED", "ALLRED", 
           "KHALED", "RASHED", "MASJED") || 
         stringAt(0, 5, "JARED", "AHMED", "HAMED", "JAVED") || 
         stringAt(0, 4, "ABED", "IMED")))
  {
    // Also silent if before plural 's' or past tense or 
    // participle 'd', e.g. 'grapes' and 'banished' => PNXT,
    // and not e.g. "nested", "rises", or "pieces" => RASAS.
    return true;
  }
  else if (m_current+4 == m_last &&
      stringAt(m_current+1, 4, "NESS", "LESS"))
  {
    // E.g.  'wholeness', 'boneless', 'barely'.
    return true;
  }
  else if (m_current+2 == m_last && 
      stringAt(m_current+1, 2, "LY") && 
      ! stringAt(0, 6, "CICELY"))
  {
    return true;
  }
  else
    return false;
}


bool Metaphone3::e_Pronounced_At_End()
{
  // Tests for words where an 'E' at the end is pronounced.
  //
  // Special cases, mostly from the Greek, Spanish, Japanese,
  // Italian, and French words normally having an acute accent.
  // Also, pronouns and articles
  //
  // Many thanks to ali, QuentinCompson, JeffCO, ToonScribe, Xan,
  // Trafalz, and VictorLaszlo, all of them atriots from the Eschaton,
  // for all their fine contributions!
  if (stringAt(m_current-6, 7, "STROPHE"))
    return true;
  else if (m_length == 2 || (m_length == 3 && ! isVowel(0)))
  {
    // If a vowel is before the 'E', vowel eater will have eaten it.
    // Otherwise, consonant + 'E' will need 'E' pronounced.
    return true;
  }
  else if (stringAt(m_last-2, 3, "BKE", "DKE", "FKE", "KKE", "LKE",
      "NKE", "MKE", "PKE", "TKE", "VKE", "ZKE") && 
      ! stringAt(0, 5, "FINKE", "FUNKE") && 
      ! stringAt(0, 6, "FRANKE"))
  {
    // These German name endings can be relied on to have the 'e' 
    // pronounced.
    return true;
  }
  else if (stringAt(m_last-4, 5, "SCHKE"))
    return true;
  else if ((m_length == 4 &&
      stringAt(0, 4, "ACME", "NIKE", "CAFE", "RENE", "LUPE", 
        "JOSE", "ESME")) ||
      (m_length == 5 &&
      stringAt(0, 5, "LETHE", "CADRE", "TILDE", "SIGNE", "POSSE", 
        "LATTE", "ANIME", "DOLCE", "CROCE", "ADOBE", "OUTRE", 
        "JESSE", "JAIME", "JAFFE", "BENGE", "RUNGE", "CHILE", 
        "DESME", "CONDE", "URIBE", "LIBRE", "ANDRE")) ||
      (m_length == 6 &&
      stringAt(0, 6, "HECATE", "PSYCHE", "DAPHNE", "PENSKE", "CLICHE", 
        "RECIPE", "TAMALE", "SESAME", "SIMILE", "FINALE", "KARATE", 
        "RENATE", "SHANTE", "OBERLE", "COYOTE", "KRESGE", "STONGE", 
        "STANGE", "SWAYZE", "FUENTE", "SALOME", "URRIBE")) ||
      (m_length == 7 &&
        stringAt(0, 7, "ECHIDNE", "ARIADNE", "MEINEKE", "PORSCHE", 
          "ANEMONE", "EPITOME", "SYNCOPE", "SOUFFLE", "ATTACHE", 
          "MACHETE", "KARAOKE", "BUKKAKE", "VICENTE", "ELLERBE", 
          "VERSACE")) ||
      (m_length == 8 &&
        stringAt(0, 8, "PENELOPE", "CALLIOPE", "CHIPOTLE", "ANTIGONE", 
          "KAMIKAZE", "EURIDICE", "YOSEMITE", "FERRANTE")) ||
      (m_length == 9 &&
        stringAt(0, 9, "HYPERBOLE", "GUACAMOLE", "XANTHIPPE")) ||
      (m_length == 10 &&
        stringAt(0, 10, "SYNECDOCHE")))
  {
    return true;
  }
  else
    return false;
}


bool Metaphone3::silent_Internal_E()
{
  // Detect internal silent 'E', e.g. "roseman", "firestone".
  if ((stringAt(0, 3, "OLE") && 
      e_Silent_Suffix(3) && ! e_Pronouncing_Suffix(3)) ||
      (stringAt(0, 4, "BARE", "FIRE", "FORE", "GATE", "HAGE", "HAVE",
         "HAZE", "HOLE", "CAPE", "HUSE", "LACE", "LINE", "LIVE", 
         "LOVE", "MORE", "MOSE", "MORE", "NICE", "RAKE", "ROBE", 
         "ROSE", "SISE", "SIZE", "WARE", "WAKE", "WISE", "WINE") && 
      e_Silent_Suffix(4) && ! e_Pronouncing_Suffix(4)) || 
      (stringAt(0, 5, "BLAKE", "BRAKE", "BRINE", "CARLE", "CLEVE", 
        "DUNNE", "HEDGE", "HOUSE", "JEFFE", "LUNCE", "STOKE", 
        "STONE", "THORE", "WEDGE", "WHITE") &&
      e_Silent_Suffix(5) && ! e_Pronouncing_Suffix(5)) || 
      (stringAt(0, 6, "BRIDGE", "CHEESE") && 
      e_Silent_Suffix(6) && ! e_Pronouncing_Suffix(6)) || 
      stringAt(m_current-5, 7, "CHARLES"))
  {
    // 'olesen' but not 'olen'.
    return true;
  }
  else
    return false;
}

bool Metaphone3::e_Silent_Suffix(const int at)
{
  // Detect conditions required for the 'E' not to be pronounced.
  if (m_current == at-1 &&
      m_length > at+1 && 
      (isVowel(at+1) || (stringAt(at, 2, "ST", "SL") && m_length > at+2)))
    return true;
  else
    return false;
}


bool Metaphone3::e_Pronouncing_Suffix(const int at) const
{
  // Detect endings that will cause the 'e' to be pronounced,
  // e.g. 'bridgewood' - the other vowels will get eaten up,
  // so we need to put one in here.
  if ((m_length == at+5 && stringAt(at, 5, "WATER", "WORTH")) ||
      (m_length == at+4 && stringAt(at, 4, "WOOD")) ||
      (m_length == at+3 && 
        stringAt(at, 3, "TTE", "LIA", "NOW", "ROS", "RAS")) ||
      (m_length == at+2 && stringAt(at, 2, "TA", "TT", "NA", "NO", 
        "NE", "RS", "RE", "LA", "AU", "RO", "RA")) ||
      (m_length == at+1 && stringAt(at, 1, "T", "R")))
    return true;
  else
    return false;
  }


bool Metaphone3::e_Pronounced_Exceptions()
{
  // Exceptions where 'E' is pronounced where it usually wouldn't be, 
  // and also some cases where 'LE' transposition rules don't apply
  // and the vowel needs to be encoded here.
  // Greek names e.g. "herakles" or Hispanic names e.g. "robles", 
  // where 'e' is pronounced, other exceptions.
  if ((m_current+1 == m_last &&
      (stringAt(m_current-3, 5, "OCLES", "ACLES", "AKLES") ||
       stringAt(0, 4, "INES") ||
       stringAt(0, 5, "LOPES", "ESTES", "GOMES", "NUNES", "ALVES", 
         "ICKES", "INNES", "PERES", "WAGES", "NEVES", "BENES", 
         "DONES") ||
       stringAt(0, 6, "CORTES", "CHAVES", "VALDES", "ROBLES", "TORRES", 
         "FLORES", "BORGES", "NIEVES", "MONTES", "SOARES", "VALLES", 
         "GEDDES", "ANDRES", "VIAJES", "CALLES", "FONTES", "HERMES", 
         "ACEVES", "BATRES", "MATHES") ||
       stringAt(0, 7, "DELORES", "MORALES", "DOLORES", "ANGELES", 
         "ROSALES", "MIRELES", "LINARES", "PERALES", "PAREDES", 
         "BRIONES", "SANCHES", "CAZARES", "REVELES", "ESTEVES",
         "ALVARES", "MATTHES", "SOLARES", "CASARES", "CACERES", 
         "STURGES", "RAMIRES", "FUNCHES", "BENITES", "FUENTES", 
         "PUENTES", "TABARES", "HENTGES", "VALORES") ||
       stringAt(0, 8, "GONZALES", "MERCEDES", "FAGUNDES", 
         "JOHANNES", "GONSALES", "BERMUDES", "CESPEDES", "BETANCES", 
         "TERRONES", "DIOGENES", "CORRALES", "CABRALES", "MARTINES", 
         "GRAJALES") ||
       stringAt(0, 9, "CERVANTES", "FERNANDES", "GONCALVES", 
         "BENEVIDES", "CIFUENTES", "SIFUENTES", "SERVANTES", 
         "HERNANDES", "BENAVIDES") ||
       stringAt(0, 10, "ARCHIMEDES", "CARRIZALES", "MAGALLANES"))) ||
      stringAt(m_current-2, 4, "FRED", "DGES", "DRED", "GNES") ||
      stringAt(m_current-5, 7, "PROBLEM", "RESPLEN") ||
      stringAt(m_current-4, 6, "REPLEN") ||
      stringAt(m_current-3, 4, "SPLE"))
    return true;
  else
    return false;
}


bool Metaphone3::skip_Silent_UE()
{
  // Encodes "-UE": Always silent except for cases listed below.
  if (stringAt(m_current-1, 3, "QUE", "GUE") &&
      ! stringAt(0, 8, "BARBEQUE", "PALENQUE", "APPLIQUE") &&
      // '-que' cases usually French but missing the acute accent
      ! stringAt(0, 6, "RISQUE") &&
      ! stringAt((m_current - 3), 5, "ARGUE", "SEGUE") &&
      ! stringAt(0, 7, "PIROGUE", "ENRIQUE") &&
      ! stringAt(0, 10, "COMMUNIQUE") &&
      m_current > 1 &&
      (m_current+1 == m_last || stringAt(0, 7, "JACQUES")))
  {
    m_current = skipVowels(m_current);
    return true;
  }
  else
    return false;
}


void Metaphone3::encode_B()
{
  // Encodes 'B'.
  if (encode_Silent_B())
    return;

  // "-mb", e.g", "dumb", already skipped over under
  // 'M', although it should really be handled here...
  addExactApprox("B", "P");

  if (charAt(m_current+1) == 'B' || 
     (charAt(m_current+1) == 'P' && 
     m_current+1 < m_last && 
     charAt(m_current+2) != 'H'))
    m_current += 2;
  else
    m_current++;
}


bool Metaphone3::encode_Silent_B()
{
  // Encodes silent 'B' for cases not covered under "-mb-":
  // 'debt', 'doubt', 'subtle'
  if (stringAt((m_current-2), 4, "DEBT") || 
      stringAt((m_current-2), 5, "SUBTL") || 
      stringAt((m_current-2), 6, "SUBTIL") || 
      stringAt((m_current-3), 5, "DOUBT"))
  {
    add("T");
    m_current += 2;
    return true;
  }
  else
    return false;
}


void Metaphone3::encode_C()
{
  if (encode_Silent_C_At_Beginning() ||
      encode_CA_To_S() ||
      encode_CO_To_S() ||
      encode_CH() ||
      encode_CCIA() ||
      encode_CC() ||
      encode_CK_CG_CQ() ||
      encode_C_Front_Vowel() ||
      encode_Silent_C() ||
      encode_CZ() ||
      encode_CS())
    return;

  if (! stringAt(m_current-1, 1, "C", "K", "G", "Q"))
    add("K");

  // 'mac caffrey', 'mac gregor'
  if (stringAt(m_current+1, 2, " C", " Q", " G"))
    m_current += 2;
  else if (stringAt(m_current+1, 1, "C", "K", "Q") &&
      ! stringAt(m_current+1, 2, "CE", "CI"))
  {
    m_current += 2;
    // Account for combinations such as Ro-ckc-liffe
    if (stringAt(m_current, 1, "C", "K", "Q") &&
        ! stringAt(m_current+1, 2, "CE", "CI"))
      m_current++;
  }
  else
    m_current++;
}


bool Metaphone3::encode_Silent_C_At_Beginning()
{
  // Encodes cases where 'C' is silent at beginning of word.
  if (m_current == 0 && stringAt(0, 2, "CT", "CN"))
  {
    m_current += 1;
    return true;
  }
  else
    return false;
}



bool Metaphone3::encode_CA_To_S()
{
  // Encode exceptions where "-CA-" should encode to S
  // instead of K, including cases where the cedilla has not been used.
  // Special case: 'caesar'.
  // Also, where cedilla not used, as in "linguica" => LNKS
  if ((m_current == 0 && 
       stringAt(0, 4, "CAES", "CAEC", "CAEM")) ||
      stringAt(0, 8, "FRANCAIS", "FRANCAIX", "LINGUICA") ||
      stringAt(0, 6, "FACADE") ||
      stringAt(0, 9, "GONCALVES", "PROVENCAL"))
  {
    add("S");
    advanceCounter(2, 1);
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_CO_To_S()
{
  // Encode exceptions where "-CO-" encodes to S instead of K,
  // including cases where the cedilla has not been used,
  // e.g. 'coelecanth' => SLKN0
  if ((stringAt(m_current, 4, "COEL") &&
       (isVowel(m_current+4) || m_current+3 == m_last)) ||
      stringAt(m_current, 5, "COENA", "COENO") ||
      stringAt(0, 8, "FRANCOIS", "MELANCON") ||
      stringAt(0, 6, "GARCON"))
  {
    add("S");
    advanceCounter(3, 1);
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_CH()
{
  // Encode "-CH-".
  if (stringAt(m_current, 2, "CH"))
  {
    if (encode_CHAE() || 
        encode_CH_To_H() || 
        encode_Silent_CH() || 
        encode_ARCH() || 
        encode_CH_To_X() || // Call before Germanic/Greek functions
        encode_English_CH_To_K() || 
        encode_Germanic_CH_To_K() || 
        encode_Greek_CH_Initial() || 
        encode_Greek_CH_Non_Initial())
    {
      return true;
    }

    if (m_current == 0)
      add("X");
    else if (m_current == 1 && stringAt(0, 2, "MC"))
    {
      // "McHugh".
      add("K");
    }
    else
      add("X", "K");

    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_CHAE()
{
  // Encodes "-CHAE-", e.g. 'michael'.
  if (m_current > 0 && stringAt(m_current+2, 2, "AE"))
  {
    if (stringAt(0, 7, "RACHAEL"))
      add("X");
    else if (! stringAt(m_current-1, 1, "C", "K", "G", "Q"))
      add("K");

    advanceCounter(4, 2);
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_CH_To_H()
{
  // Encodes transliterations from the Hebrew where the
  // sound 'kh' is represented as "-CH-". The normal pronunciation
  // of this in English is either 'h' or 'kh', and alternate
  // spellings most often use "-H-", e.g. 'channukah', 'chabad'
  if ((m_current == 0 &&
       (stringAt(m_current+2, 3, "AIM", "ETH", "ELM") ||
        stringAt(m_current+2, 4, "ASID", "AZAN") ||
        stringAt(m_current+2, 5, "UPPAH", "UTZPA", "ALLAH", 
          "ALUTZ", "AMETZ") ||
        stringAt(m_current+2, 6, "ESHVAN", "ADARIM", "ANUKAH") ||
        stringAt(m_current+2, 7, "ALLLOTH", "ANNUKAH", "AROSETH"))) ||
      // An Irish name with the same encoding.
      stringAt(m_current-3, 7, "CLACHAN"))
  {
    add("H");
    advanceCounter(3, 2);
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_Silent_CH()
{
  // Encodes cases where "-CH-" is not pronounced.
  if (stringAt(m_current-2, 7, "FUCHSIA") ||
      stringAt(m_current-2, 5, "YACHT") ||
      stringAt(0, 8, "STRACHAN") ||
      stringAt(0, 8, "CRICHTON") ||
      (stringAt(m_current-3, 6, "DRACHM")) &&
       ! stringAt(m_current-3, 7, "DRACHMA"))
  {
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_CH_To_X()
{
  // Encodes "-CH-" to X, English language patterns, 
  // e.g. 'approach', 'beach'.
  if ((stringAt(m_current-2, 4, "OACH", "EACH", "EECH", "OUCH", 
    "OOCH", "MUCH", "SUCH") &&
      ! stringAt(m_current-3, 5, "JOACH")) ||
      // E.g. 'dacha', 'macho'
      (m_current+2 == m_last && 
       stringAt(m_current-1, 4, "ACHA", "ACHO")) ||
      (m_current+3 == m_last &&
       stringAt(m_current, 4, "CHOT", "CHOD", "CHAT")) ||
      (m_current+2 == m_last &&
       stringAt(m_current-1, 4, "OCHE") && 
       ! stringAt(m_current-2, 5, "DOCHE")) ||
      stringAt(m_current-4, 6, "ATTACH", "DETACH", "KOVACH") ||
      stringAt(m_current-5, 7, "SPINACH") ||
      stringAt(0, 6, "MACHAU") ||
      stringAt(m_current-4, 8, "PARACHUT") ||
      stringAt(m_current-5, 8, "MASSACHU") ||
      (stringAt(m_current-3, 5, "THACH") && 
       ! stringAt(m_current-1, 4, "ACHE")) ||
      stringAt(m_current-2, 6, "VACHON"))
  {
    add("X");
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_English_CH_To_K()
{
  // Encodes "-CH-" to K in contexts of initial "A" or "E" follwed 
  // by "CH": 'ache', 'echo', alternate spelling of 'michael'.
  if ((m_current == 1 && rootOrInflections(m_inWord, "ACHE")) ||
      ((m_current > 3 && 
        rootOrInflections(m_inWord.substr(
          static_cast<size_t>(m_current)-1), "ACHE")) &&
          (stringAt(0, 3, "EAR") ||
           stringAt(0, 4, "HEAD", "BACK") ||
           stringAt(0, 5, "HEART", "BELLY", "TOOTH"))) ||
      stringAt(m_current-1, 4, "ECHO") ||
      stringAt(m_current-2, 7, "MICHEAL") ||
      stringAt(m_current-4, 7, "JERICHO") ||
      stringAt(m_current-5, 7, "LEPRECH"))
  {
    add("K", "X");
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_Germanic_CH_To_K()
{
  // "<consonant><vowel>CH-" implies a German word where 'ch' => K
  // Encodes "-CH-" to K in mostly Germanic context of internal 
  // "-ACH-", with exceptions.
  if ((m_current > 1 &&
       ! isVowel(m_current-2) &&
       stringAt(m_current-1, 3, "ACH") &&
       ! stringAt(m_current-2, 7, "MACHADO", "MACHUCA", 
         "LACHANC", "LACHAPE", "KACHATU") &&
       ! stringAt(m_current-3, 7, "KHACHAT") &&
       (charAt(m_current+2) != 'I' &&
        (charAt(m_current+2) != 'E' ||
         stringAt(m_current-2, 6, "BACHER", "MACHER", "MACHEN", 
           "LACHER")))) ||
      // shein: Note that the parentheses in the original method
      // were different (probably wrong).  The (m_current > 1)
      // parenthesis went down a lot further.

      // E.g. 'brecht', 'fuchs'
      (stringAt(m_current+2, 1, "T", "S") &&
       ! stringAt(0, 11, "WHICHSOEVER") &&
       ! stringAt(0, 9, "LUNCHTIME")) ||
      stringAt(0, 4, "SCHR") ||
      // E.g. 'andromache' but not 'machete'
      (m_current > 2 && stringAt(m_current-2, 5, "MACHE")) ||
      (m_current == 2 && stringAt(0, 4, "ZACH")) ||
      stringAt(m_current-4, 6, "SCHACH") ||
      stringAt(m_current-1, 5, "ACHEN") ||
      stringAt(m_current-3, 5, "SPICH", "ZURCH", "BUECH") ||

      (m_current+1 != m_last &&
       stringAt(m_current-3, 5, "KIRCH", "JOACH", "BLECH", "MALCH") &&
       // "kirch" and "blech" both get 'X'
       ! stringAt(m_current-3, 8, "KIRCHNER")) ||

      (m_current+1 == m_last && 
       stringAt(m_current-2, 4, "NICH", "LICH", "BACH")) ||

      (m_current+1 == m_last &&
       stringAt(m_current-3, 5, "URICH", "BRICH", "ERICH", 
         "DRICH", "NRICH") &&
       ! stringAt(m_current-5, 7, "ALDRICH") &&
       ! stringAt(m_current-6, 8, "GOODRICH") &&
       ! stringAt(m_current-7, 9, "GINGERICH")) ||

      (m_current+1 == m_last && 
       stringAt(m_current-4, 6, "ULRICH", "LFRICH", "LLRICH",
          "EMRICH", "ZURICH", "EYRICH")) ||

      // e.g., 'wachtler', 'wechsler', but not 'tichner'
      (((m_current == 0 || stringAt(m_current-1, 1, "A", "O", "U", "E")) &&
       stringAt(m_current+2, 1, "L", "R", "N", "M", "B", "H", "F", 
         "V", "W"))))
  {
    // 'chris' does not get alternative pronunciation of 'X'.
    if (stringAt(m_current+2, 1, "R", "L") || slavoGermanic())
      add("K");
    else
      add("K", "X");

    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_ARCH()
{
  // Encode "-ARCH-". Some occurrences are from Greek roots and 
  // therefore encode to 'K', others are from English words and 
  // therefore encode to 'X'.
  if (stringAt(m_current-2, 4, "ARCH"))
  {
    // shein: Refactored a bit, hopefully correctly.
    if ((m_current+1 == m_last ||
         stringAt(m_current-2, 5, "ARCHA", "ARCHI", "ARCHO", "ARCHU", 
           "ARCHY") ||
         stringAt(m_current-2, 6, "ARCHEA", "ARCHEG", "ARCHEO", 
           "ARCHET", "ARCHEL", "ARCHES", "ARCHEP", "ARCHEM", "ARCHEN") ||
         stringAt(0, 7, "MENARCH")) &&

        ! rootOrInflections(m_inWord, "ARCH") &&
        ! stringAt(m_current-4, 6, "SEARCH", "POARCH") &&
        ! stringAt(0, 9, "ARCHENEMY", "ARCHIBALD", "ARCHULETA", 
          "ARCHAMBAU") &&
        ! stringAt(0, 6, "ARCHER", "ARCHIE") &&
           
        ((! stringAt(m_current-3, 5, "LARCH", "MARCH", "PARCH") &&
          ! stringAt(m_current-4, 6, "STARCH")) ||
           stringAt(0, 6, "EPARCH") ||
           stringAt(0, 7, "NOMARCH") ||
           stringAt(0, 8, "EXILARCH", "HIPPARCH", "MARCHESE") || 
           stringAt(0, 9, "ARISTARCH", "MARCHETTI") ) &&

        (! rootOrInflections(m_inWord, "STARCH") ||
         (stringAt(m_current-2, 5, "ARCHU", "ARCHY") && 
          ! stringAt(0, 7, "STARCHY"))))
    {
      add("K", "X");
    }
    else
      add("X");
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_Greek_CH_Initial()
{
  // Encode "-CH-" to K when from greek roots,
  // e.g. 'chemistry', 'chorus', ch at beginning of root
  if ((stringAt(m_current, 6, "CHAMOM", "CHARAC", "CHARIS", "CHARTO", 
        "CHARTU", "CHARYB", "CHRIST", "CHEMIC", "CHILIA") ||

      (stringAt(m_current, 5, "CHEMI", "CHEMO", "CHEMU", "CHEMY", 
        "CHOND", "CHONA", "CHONI", "CHOIR", "CHASM", "CHARO", "CHROM", 
        "CHROI", "CHAMA", "CHALC", "CHALD", "CHAET", "CHIRO", "CHILO", 
        "CHELA", "CHOUS", "CHEIL", "CHEIR", "CHEIM", "CHITI", "CHEOP") &&
       ! stringAt(m_current, 6, "CHEMIN") && 
       ! stringAt(m_current-2, 8, "ANCHONDO")) ||

      (stringAt(m_current, 5, "CHISM", "CHELI") &&
       ! stringAt(0, 6, "MICHEL") &&
       ! stringAt(0, 8, "MACHISMO") &&
       ! stringAt(0, 9, "RICHELIEU") &&
       ! stringAt(0, 10, "REVANCHISM") &&
       (m_length != 5 || ! stringAt(0, 5, "CHISM"))) ||

      // E.g. "chorus", "chyme".
      (stringAt(m_current, 4, "CHOR", "CHOL", "CHYM", "CHYL", 
        "CHLO", "CHOS", "CHUS", "CHOE") && 
       ! stringAt(0, 6, "CHOLLO", "CHOLLA", "CHORIZ")) ||

      // E.g. "chaos" => K but not "chao"
      (m_current + 3 != m_last && stringAt(m_current, 4, "CHAO")) ||

      // E.g. "abranchiate"
      (stringAt(m_current, 4, "CHIA") && 
       ! stringAt(0, 10, "APPALACHIA") && 
       ! stringAt(0, 7, "CHIAPAS")) ||

      // E.g. "chimera"
      stringAt(m_current, 7, "CHIMERA", "CHIMAER", "CHIMERI") ||

      // E.g. "chameleon"
      (m_current == 0 && stringAt(0, 5, "CHAME", "CHELO", "CHITO")) ||

      // E.g. "spirochete"
      ((m_current+4 == m_last || m_current+5 == m_last) && 
       stringAt(m_current-1, 6, "OCHETE"))) &&

      // More exceptions where "-CH-" => X e.g. "chortle", "crocheter"
      (m_length != 5 || ! stringAt(0, 5, "CHORE", "CHOLO", "CHOLA")) &&
       ! stringAt(m_current, 5, "CHORT", "CHOSE") &&
       ! stringAt(m_current-3, 7, "CROCHET") &&
       ! stringAt(0, 7, "CHEMISE", "CHARISE", "CHARISS", "CHAROLE"))
  {
    // "CHR/L-" e.g. 'christ', 'chlorine' do not get
    // alt pronunciation of 'X'
    if (stringAt(m_current+2, 1, "R", "L"))
      add("K");
    else
      add("K", "X");
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_Greek_CH_Non_Initial()
{
  // ch in middle or end of root.
  // Encode a variety of Greek and some German roots where "-CH-" => K,
  // e.g. 'tachometer', 'orchid'.
  if (stringAt(m_current-2, 6, "ORCHID", "NICHOL", "MECHAN", "LICHEN", 
        "MACHIC", "PACHEL", "RACHIF", "RACHID", "RACHIS", "RACHIC", 
        "MICHAL") || 
      stringAt(m_current-3, 5, "MELCH", "GLOCH", "TRACH", "TROCH", 
        "BRACH", "SYNCH", "PSYCH", "STICH", "PULCH", "EPOCH") ||

      (stringAt(m_current-3, 5, "TRICH") && 
       ! stringAt(m_current-5, 7, "OSTRICH")) ||

      (stringAt(m_current-2, 4, "TYCH", "TOCH", "BUCH", "MOCH", "CICH", 
        "DICH", "NUCH", "EICH", "LOCH", "DOCH", "ZECH", "WYCH") && 
       ! stringAt(m_current-4, 9, "INDOCHINA") && 
       ! stringAt(m_current-2, 6, "BUCHON")) ||

      stringAt(m_current-2, 5, "LYCHN", "TACHO", "ORCHO", "ORCHI", 
        "LICHO") ||
      ((m_current == 1 || m_current == 2) && 
        stringAt(m_current-1, 5, "OCHER", "ECHIN", "ECHID")) ||

      stringAt(m_current-4, 6, "BRONCH", "STOICH", "STRYCH", "TELECH", 
        "PLANCH", "CATECH", "MANICH", "MALACH", "BIANCH", "DIDACH") ||
      (m_current == 1 && stringAt(0, 4, "ICHA", "ICHN")) ||
      stringAt(m_current-2, 8, "ORCHESTR") ||
      stringAt(m_current-4, 8, "BRANCHIO", "BRANCHIF") ||
      (stringAt(m_current-1, 5, "ACHAB", "ACHAD", "ACHAN", "ACHAZ") &&
       ! stringAt(m_current-2, 7, "MACHADO", "LACHANC")) ||
      stringAt(m_current-1, 6, "ACHISH", "ACHILL", "ACHAIA", "ACHENE") ||
      stringAt(m_current-1, 7, "ACHAIAN", "ACHATES", "ACHIRAL", 
        "ACHERON") ||
      stringAt(m_current-1, 8, "ACHILLEA", "ACHIMAAS", "ACHILARY", 
        "ACHELOUS", "ACHENIAL", "ACHERNAR") ||
      stringAt(m_current-1, 9, "ACHALASIA", "ACHILLEAN", "ACHIMENES") ||
      stringAt(m_current-1, 10, "ACHIMELECH", "ACHITOPHEL") ||

      // E.g. 'inchoate', 'ischemia'
      (m_current == 2 && 
       (stringAt(0, 6, "INCHOA") || stringAt(0, 4, "ISCH"))) ||

      // E.g. 'ablimelech', 'antioch', 'pentateuch'
      (m_current+1 == m_last && 
       stringAt(m_current-1, 1, "A", "O", "U", "E") && 
       ! stringAt(0, 7, "DEBAUCH") &&
       ! stringAt(m_current-2, 4, "MUCH", "SUCH", "KOCH") &&
       ! stringAt(m_current-5, 7, "OODRICH", "ALDRICH")))
  {
    add("K", "X");
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_CCIA()
{
  // Reliably encodes Italian "-CCIA-", e.g., 'focaccia'.
  if (stringAt(m_current+1, 3, "CIA"))
  {
    add("X", "S");
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_CC()
{
  // Encode '-CC-', but not if e.g. 'McClellan'.
  if (stringAt(m_current, 2, "CC") && 
      (m_current != 1 || (charAt(0) != 'M')))
  {
    // Exceptions.
    if (stringAt(m_current-3, 7, "FLACCID"))
    {
      add("S");
      advanceCounter(3, 2);
      return true;
    }

    // 'bacci', 'bertucci', other Italian.
    if ((m_current+2 == m_last && stringAt(m_last, 1, "I")) ||
        stringAt(m_current+2, 2, "IO") ||
        (m_current+4 == m_last && stringAt(m_current+2, 3, "INO", "INI")))
    {
      add("X");
      advanceCounter(3, 2);
      return true;
    }

    // 'accident', 'accede' 'succeed'
    if (stringAt(m_current+2, 1, "I", "E", "Y") &&
        // Except 'bellocchio','bacchus', 'soccer' get K
        charAt(m_current+2) != 'H' &&
        ! stringAt(m_current-2, 6, "SOCCER"))
    {
      add("KS");
      advanceCounter(3, 2);
      return true;
    }
    else
    {
      //Pierce's rule
      add("K");
      m_current += 2;
      return true;
    }
  }
  else
    return false;
}


bool Metaphone3::encode_CK_CG_CQ()
{
  // Encode cases where the consonant following "C" is redundant
  if (stringAt(m_current, 2, "CK", "CG", "CQ"))
  {
    // Eastern European spelling, e.g. 'gorecki' == 'goresky'
    if (m_length > 6 &&
        m_current+2 == m_last &&
        stringAt(m_current, 3, "CKI", "CKY"))
    {
      add("K", "SK");
    }
    else
      add("K");

    m_current += 2;

    if (stringAt(m_current, 1, "K", "G", "Q"))
      m_current++;

    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_C_Front_Vowel()
{
  // Encode cases where "C" preceeds a front vowel such as 
  // "E", "I", or "Y".  These cases most likely => S or X.
  if (stringAt(m_current, 2, "CI", "CE", "CY"))
  {
    if (encode_British_Silent_CE() ||
        encode_CE() ||
        encode_CI() ||
        encode_Latinate_Suffixes())
    {
      advanceCounter(2, 1);
      return true;
    }

    add("S");
    advanceCounter(2, 1);
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_British_Silent_CE()
{
  // English place names like e.g.'gloucester' pronounced glo-ster.
  if ((stringAt(m_current+1, 5, "ESTER") && m_current+5 == m_last) || 
       stringAt(m_current+1, 10, "ESTERSHIRE"))
    return true;
  else
    return false;
}


bool Metaphone3::encode_CE()
{
  // 'Ocean', 'commercial', 'provincial', 'cello'.
  if ((stringAt(m_current+1, 3, "EAN") && 
       isVowel(m_current-1)) ||
      // E.g. 'rosacea'
      (stringAt(m_current-1, 4, "ACEA") &&
       m_current+2 == m_last &&
       ! stringAt(0, 7, "PANACEA")) ||
      // E.g. 'botticelli', 'concerto'
      stringAt(m_current+1, 4, "ELLI", "ERTO", "EORL") ||
      // Some Italian names familiar to Americans.
      (m_current+1 == m_last && 
       stringAt(m_current-3, 5, "CROCE")) ||
      stringAt(m_current-3, 5, "DOLCE")  ||
      // E.g. 'cello'
      (m_current+4 == m_last &&
       stringAt(m_current+1, 4, "ELLO")))
  {
    add("X", "S");
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_CI()
{
  // With consonant before C.
  if ((m_current+3 == m_last &&
      stringAt(m_current+1, 3, "INI") && 
      ! stringAt(0, 7, "MANCINI")) ||
      // E.g. 'medici'
      (m_current+1 == m_last && stringAt(m_current-1, 3, "ICI")) ||
      // E.g. "commercial', 'provincial', 'cistercian'
      stringAt(m_current-1, 5, "RCIAL", "NCIAL", "RCIAN", "UCIUS") ||
      stringAt(m_current-3, 6, "MARCIA") ||
      stringAt(m_current-2, 7, "ANCIENT"))
  {
    // E.g. 'fettucini', but exception for the Americanized 
    // pronunciation of 'mancini'.
    add("X", "S");
    return true;
  }

  // With vowel before C (or at beginning?), or "ciao".
  if (stringAt(m_current, 3, "CIO", "CIE", "CIA") &&
     (isVowel(m_current-1) || 
      stringAt((m_current + 1), 3, "IAO")))
  {
    if ((stringAt(m_current, 4, "CIAN", "CIAL", "CIAO", "CIES", 
        "CIOL", "CION") ||
        stringAt(m_current-3, 7, "GLACIER") ||
        stringAt(m_current, 5, "CIENT", "CIENC", "CIOUS", "CIATE", 
            "CIATI", "CIATO", "CIABL", "CIARY") ||
        (m_current+2 == m_last && 
         stringAt(m_current, 3, "CIA", "CIO")) ||
        (m_current+3 == m_last && 
         stringAt(m_current, 3, "CIAS", "CIOS"))) &&
        // exceptions
        ! (stringAt((m_current - 4), 11, "ASSOCIATION") ||
           stringAt(0, 4, "OCIE") ||
           // Exceptions mostly because these names are usually from
           // the Spanish rather than the Italian in America.
           stringAt(m_current-2, 5, "LUCIO", "SOCIO", "SOCIE") ||
           stringAt(m_current-2, 6, "MACIAS") ||
           stringAt(m_current-2, 7, "LUCIANO") ||
           stringAt(m_current-2, 8, "HACIENDA") ||
           stringAt(m_current-3, 6, "GRACIE", "GRACIA") ||
           stringAt(m_current-3, 8, "MARCIANO") ||
           stringAt(m_current-4, 7, "PALACIO") ||
           stringAt(m_current-4, 8, "POLICIES") ||
           stringAt(m_current-4, 9, "FELICIANO") ||
           stringAt(m_current-5, 8, "MAURICIO") ||
           stringAt(m_current-6, 9, "ANDALUCIA") ||
           stringAt(m_current-7, 11, "ENCARNACION")))
      add("X", "S");
    else
      add("S", "X");

    return true;
  }

  // Exception.
  if (stringAt(m_current-4, 8, "COERCION"))
  {
    add("J");
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_Latinate_Suffixes()
{
  if (stringAt(m_current+1, 4, "EOUS", "IOUS"))
  {
    add("X", "S");
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_Silent_C()
{
  // Encodes some exceptions where "C" is silent
  if (stringAt(m_current+1, 1, "T", "S") &&
     (stringAt(0, 11, "CONNECTICUT") || 
      stringAt(0, 6, "INDICT", "TUCSON")))
  {
    m_current++;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_CZ()
{
  // Encodes slavic spellings or transliterations written as "-CZ-".
  if (stringAt(m_current+1, 1, "Z") && 
      ! stringAt(m_current-1, 6, "ECZEMA"))
  {
    if (stringAt(m_current, 4, "CZAR"))
      add("S");
    else
      add("X"); // Otherwise most likely a czech word...

    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_CS()
{
  // "-CS" special cases: Give an 'etymological' 2nd encoding for 
  // "kovacs" so that it matches "kovach".
  if (stringAt(0, 6, "KOVACS"))
  {
    add("KS", "X");
    m_current += 2;
    return true;
  }

  if (m_current+1 == m_last &&
      stringAt(m_current-1, 3, "ACS") &&
      ! stringAt(m_current-4, 6, "ISAACS"))
  {
    add("X");
    m_current += 2;
    return true;
  }
  else
    return false;
}


void Metaphone3::encode_D()
{
  // Encode "-D-".
  if (encode_DG() || 
      encode_DJ() || 
      encode_DT_DD() || 
      encode_D_To_J() || 
      encode_DOUS() || 
      encode_Silent_D())
    return;

  if (! m_encodeExact)
    add("T");
  else if (m_current == m_last && stringAt(m_current-3, 4, "SSED"))
    // "Final de-voicing" in this case, e.g. 'missed' == 'mist'.
    add("T");
  else
    add("D");

  m_current++;
}


bool Metaphone3::encode_DG()
{
  // Encode "-DG-".
  if (stringAt(m_current, 2, "DG"))
  {
    // Excludes exceptions e.g. 'edgar', or cases where 'g' is 
    // the first letter of a combining form, e.g. 'handgun', 'waldglas'.
    if (stringAt(m_current+2, 1, "A", "O") || // e.g. "midgut"
        stringAt(m_current+1, 3, "GUN", "GUT") || // e.g. "handgrip"
        stringAt(m_current+1, 4, "GEAR", "GLAS", "GRIP", "GREN", 
          "GILL", "GRAF") || // e.g. "mudgard"
        stringAt(m_current+1, 5, "GUARD", "GUILT", "GRAVE", "GRASS") ||
        // e.g. "woodgrouse"
        stringAt(m_current+1, 6, "GROUSE"))
    {
      addExactApprox("DG", "TK");
    }
    else
      add("J"); // E.g. "edge", "abridgment"

    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_DJ()
{
  // Encode "-DJ-", e.g. "adjacent".
  if (stringAt(m_current, 2, "DJ"))
  {
    add("J");
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_DT_DD()
{
  // Encode "-DD-" and "-DT-".
  if (! stringAt(m_current, 2, "DT", "DD"))
    return false;

  if (stringAt(m_current, 3, "DTH"))
  {
    addExactApprox("D0", "T0");
    m_current += 3;
  }
  else if (m_encodeExact && stringAt(m_current, 2, "DD"))
  {
    add("D");
    m_current += 2;
  }
  else
  {
    add("T");
    m_current += 2;
  }

  return true;
}


bool Metaphone3::encode_D_To_J()
{
  // Encode cases where "-DU-" "-DI-", and "-DI-" => J,
  // e.g. "module", "adulate", "soldier", "grandeur", "procedure",
  // e.g. "pendulum", "education", "individual", "individual", 
  // "residuum".
  if ((stringAt(m_current, 3, "DUL") &&
      isVowel(m_current-1) && 
      isVowel(m_current+3)) ||
     (m_current+3 == m_last &&
     (stringAt(m_current-1, 5, "LDIER", "NDEUR", "EDURE", "RDURE")) ||
      stringAt(m_current-3, 7, "CORDIAL")) ||
      stringAt(m_current-1, 5, "NDULA", "NDULU", "EDUCA") ||
      stringAt(m_current-1, 4, "ADUA", "IDUA", "IDUU"))
  {
    addExactApprox("J", "D", "J", "T");
    advanceCounter(2, 1);
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_DOUS()
{
  // Encode latinate suffix "-DOUS" where 'D' is pronounced as J,
  // e.g. "assiduous", "arduous".
  if (stringAt(m_current+1, 4, "UOUS"))
  {
    addExactApprox("J", "D", "J", "T");
    advanceCounter(4, 1);
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_Silent_D()
{
  // Encode silent "-D-", e.g. 'wednesday', 'handsome'.
  // Also French silent D at end in words or names familiar to Americans.
  if (stringAt(m_current-2, 9, "WEDNESDAY") || 
      stringAt(m_current-3, 7, "HANDKER", "HANDSOM", "WINDSOR") ||
      stringAt(m_current-5, 6, "PERNOD", "ARTAUD", "RENAUD") ||
      stringAt(m_current-6, 7, "RIMBAUD", "MICHAUD", "BICHAUD"))
  {
    m_current++;
    return true;
  }
  else
    return false;
}


void Metaphone3::encode_F()
{
  // Encode '-F': Cases where "-FT-" => "T" is usually silent,
  // e.g. 'often', 'soften'.  This should really be covered under "T"!
  if (stringAt(m_current-1, 5, "OFTEN"))
  {
    add("F", "FT");
    m_current += 2;
    return;
  }

  // Eat redundant 'F'.
  if (charAt(m_current + 1) == 'F')
    m_current += 2;
  else
    m_current++;

  add("F");
}


void Metaphone3::encode_G()
{
  // Encode "-G-".
  if (encode_Silent_G_At_Beginning() || 
      encode_GG() || 
      encode_GK() || 
      encode_GH() || 
      encode_Silent_G() || 
      encode_GN() || 
      encode_GL() || 
      encode_Initial_G_Front_Vowel() || 
      encode_NGER() || 
      encode_GER() || 
      encode_GEL() || 
      encode_Non_Initial_G_Front_Vowel() || 
      encode_GA_To_J())
    return;

  if (! stringAt(m_current-1, 1, "C", "K", "G", "Q"))
    addExactApprox("G", "K");

  m_current++;
}


bool Metaphone3::encode_Silent_G_At_Beginning()
{
  // Encode cases where 'G' is silent at beginning of word.
  if (m_current == 0 && stringAt(0, 2, "GN"))
  {
    m_current += 1;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_GG()
{
  // Encode "-GG-".
  if (charAt(m_current+1) != 'G')
    return false;

  // Italian e.g, 'loggia', 'caraveggio', also 'suggest', 'exaggerate';
  // 'ruggiero' but not 'snuggies'
  if (stringAt(m_current-1, 5, "AGGIA", "OGGIA", "AGGIO", 
    "EGGIO", "EGGIA", "IGGIO") ||
      (m_current+3 != m_last && 
       m_current+4 != m_last &&
       stringAt(m_current-1, 5, "UGGIE")) ||
      (m_current+2 == m_last && 
       stringAt(m_current-1, 4, "AGGI", "OGGI")) ||
      stringAt(m_current-2, 6, "SUGGES", "XAGGER", "REGGIE"))
  {
    // Exception where "-GG-" => KJ.
    if (stringAt(m_current-2, 7, "SUGGEST"))
      addExactApprox("G", "K");

    add("J");
    advanceCounter(3, 2);
  }
  else
  {
    addExactApprox("G", "K");
    m_current += 2;
  }
  return true;
}


bool Metaphone3::encode_GK()
{
  // Encode "-GK-": 'gingko'.
  if (charAt(m_current + 1) == 'K')
  {
    add("K");
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_GH()
{
  // Encode "-GH-".
  if (charAt(m_current+1) == 'H')
  {
    if (encode_GH_After_Consonant() || 
        encode_Initial_GH() || 
        encode_GH_To_J() || 
        encode_GH_To_H() || 
        encode_UGHT() || 
        encode_GH_H_Part_Of_Other_Word() || 
        encode_Silent_GH() || 
        encode_GH_To_F())
      return true;

    addExactApprox("G", "K");
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_GH_After_Consonant()
{
  if (m_current > 0 && 
      ! isVowel(m_current-1) && 
      ! (stringAt(m_current-3, 5, "HALGH") && m_current+1 == m_last))
  {
    // E.g. 'burgher', 'bingham'.  Not e.g. 'greenhalgh'.
    addExactApprox("G", "K");
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_Initial_GH()
{
  if (m_current > 0)
    return false;

  // E.g. "ghislane", "ghiradelli".
  if (charAt(m_current+2) == 'I')
    add("J");
  else
    addExactApprox("G", "K");

  m_current += 2;
  return true;
}



bool Metaphone3::encode_GH_To_J()
{
  // E.g., 'greenhalgh', 'dunkenhalgh', english names
  if (m_current+1 == m_last && stringAt(m_current-2, 4, "ALGH"))
  {
    add("J", "");
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_GH_To_H()
{
  // Special cases, e.g., 'donoghue', 'donaghy'.
  if ((stringAt(m_current-4, 4, "DONO", "DONA") && 
      isVowel(m_current+2)) || 
      stringAt(m_current-5, 9, "CALLAGHAN"))
  {
    add("H");
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_UGHT()
{
  // E.g. "ought", "aught", "daughter", "slaughter"
  if (stringAt(m_current-1, 4, "UGHT"))
  {
    if ((stringAt(m_current-3, 5, "LAUGH") &&
        ! stringAt(m_current-4, 7, "SLAUGHT") &&
        ! stringAt(m_current-3, 7, "LAUGHTO")) ||
        stringAt(m_current-4, 6, "DRAUGH"))
    {
      add("FT");
    }
    else
      add("T");
    m_current += 3;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_GH_H_Part_Of_Other_Word()
{
  // Encode 'H' at the beginning of another word or syllable.
  if (stringAt(m_current+1, 4, "HOUS", "HEAD", "HOLE", "HORN", "HARN"))
  {
    addExactApprox("G", "K");
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_Silent_GH()
{
  // Parker's rule (with some further refinements) - e.g., 'hugh'.
  if ((stringAt(m_current-2, 1, "B", "H", "D", "G", "L") ||

      // E.g., 'bough'.
      (stringAt(m_current-3, 1, "B", "H", "D", "K", "W", "N", "P", "V") &&
       ! stringAt(0, 6, "ENOUGH")) ||

      // E.g., 'broughton'.
      stringAt(m_current-4, 1, "B", "H") ||

      // E.g. 'plough', 'slaugh'.
      stringAt(m_current-4, 2, "PL", "SL") ||

      // 'sigh', 'light'
      charAt(m_current-1) == 'I' || 

      stringAt(0, 4, "PUGH") ||

      // E.g. 'MCDONAGH', 'MURTAGH', 'CREAGH'
      (m_current+1 == m_last && stringAt(m_current-1, 3, "AGH")) ||
      stringAt(m_current-4, 6, "GERAGH", "DRAUGH") ||
      (stringAt(m_current-3, 5, "GAUGH", "GEOGH", "MAUGH") &&
       ! stringAt(0, 9, "MCGAUGHEY")) ||
      // Exceptions to 'tough', 'rough', 'lough'.
      (m_current > 3 &&
       stringAt(m_current-2, 4, "OUGH") &&
       ! stringAt(m_current-4, 6, "CCOUGH", "ENOUGH", "TROUGH", "CLOUGH")))

      &&

       // Suffixes starting with vowel where "-GH-" is usually silent.
      (m_current+1 == m_last ||
       ! isVowel(m_current+2) ||
       stringAt(m_current-4, 8, "BROUGHAM") ||
       stringAt(m_current-3, 5, "VAUGH", "FEIGH", "LEIGH", "GAUGH", 
         "GEOGH", "MAUGH") ||
       stringAt(m_current-2, 4, "HIGH", "TIGH") ||
       (m_current+2 == m_last && stringAt(m_last, 1, "Y")) ||
       (m_current+3 == m_last &&
        stringAt(m_current+2, 2, "IE", "EY", "ES", "ER", "ED", "TY") &&
        ! stringAt(m_current-5, 9, "GALLAGHER")) ||
       (m_current+4 == m_last && stringAt(m_current+2, 3, "ING", "OUT")) ||
       (m_current+5 == m_last && stringAt(m_current+2, 4, "ERTY"))) &&

      // Exceptions where '-g-' pronounced.
      ! stringAt(0, 6, "BALOGH", "SABAGH") &&
      ! stringAt(m_current-2, 7, "BAGHDAD") &&
      ! stringAt(m_current-3, 5, "WHIGH") &&
      ! stringAt(m_current-5, 7, "SABBAGH"))
  {
    // silent - do nothing
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_GH_Special_Cases()
{
  bool handled = false;

  if (stringAt(m_current-6, 8, "HICCOUGH"))
  {
    // Special case: 'hiccough' == 'hiccup'
    add("P");
    handled = true;
  }
  else if (stringAt(0, 5, "LOUGH"))
  {
    // Special case: 'lough' alt spelling for scots 'loch'
    add("K");
    handled = true;
  }
  else if (stringAt(0, 6, "BALOGH"))
  {
    // Hungarian
    addExactApprox("G", "", "K", "");
    handled = true;
  }
  else if (stringAt(m_current-3, 8, "LAUGHLIN", "COUGHLAN", "LOUGHLIN"))
  {
    // "maclaughlin"
    add("K", "F");
    handled = true;
  }
  else if (stringAt(m_current-3, 5, "GOUGH") || 
      stringAt(m_current-7, 9, "COLCLOUGH"))
  {
    add("", "F");
    handled = true;
  }

  if (handled)
  {
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_GH_To_F()
{
  // These cases would otherwise fall under the GH_To_F rule below.
  if (encode_GH_Special_Cases())
    return true;

  // E.g., 'laugh', 'cough', 'rough', 'tough'.
  if (charAt(m_current-1) == 'U' &&
      isVowel(m_current-2) &&
      stringAt(m_current-3, 1, "C", "G", "L", "R", "T", "N", "S") &&
      ! stringAt(m_current-4, 8, "BREUGHEL", "FLAUGHER"))
  {
    add("F");
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_Silent_G()
{
  // Encode some silent "G"'s, e.g. "phlegm", "apothegm", "voigt".
  if ((m_current+1 == m_last &&
      (stringAt(m_current-1, 3, "EGM", "IGM", "AGM") || 
       stringAt(m_current, 2, "GT"))) ||
      (m_length == 5 && stringAt(0, 5, "HUGES")))
  {
    m_current++;
    return true;
  }

  // Vietnamese names e.g. "Nguyen" but not "Ng".
  if (m_current != m_last && stringAt(0, 2, "NG"))
  {
    m_current++;
    return true;
  }
  else
    return false;
}

 
bool Metaphone3::encode_GN()
{
  // ENcode "-GN-".
  if (charAt(m_current+1) == 'N')
  {
    // 'align' 'sign', 'resign' but not 'resignation',
    // also 'impugn', 'impugnable', but not 'repugnant'
    if ((m_current > 1 &&
        ((stringAt(m_current-1, 1, "I", "U", "E") ||
         stringAt(m_current-3, 9, "LORGNETTE") ||
         stringAt(m_current-2, 9, "LAGNIAPPE") ||
         stringAt(m_current-2, 6, "COGNAC") ||
         stringAt(m_current-3, 7, "CHAGNON") ||
         stringAt(m_current-5, 9, "COMPAGNIE") ||
         stringAt(m_current-4, 6, "BOLOGN")) &&

        // Exceptions: following are cases where 'G' is pronounced
        // in "assign", 'g' is silent, but not in "assignation"
        ! stringAt(m_current+2, 5, "ATION") &&
        ! stringAt(m_current+2, 4, "ATOR") &&
        ! stringAt(m_current+2, 3, "ATE", "ITY") &&
        // Exception to exceptions, not pronounced:
        (! stringAt(m_current+2, 2, "AN", "AC", "IA", "UM") ||
         stringAt(m_current-3, 8, "POIGNANT") ||
         stringAt(m_current-2, 6, "COGNAC")) &&
        ! stringAt(0, 7, "SPIGNER", "STEGNER") &&
        (m_length != 5 || ! stringAt(0, 5, "SIGNE")) &&
        ! stringAt(m_current-2, 5, "LIGNI", "LIGNO", "REGNA", "DIGNI", 
            "WEGNE", "TIGNE", "RIGNE", "REGNE", "TIGNO") &&
        ! stringAt(m_current-2, 6, "SIGNAL", "SIGNIF", "SIGNAT",
            "SIGNET", "LIGNEO") &&
        ! stringAt(m_current-1, 5, "IGNIT"))) ||

        // Not e.g. 'cagney', 'magna'.
        (m_current+2 == m_last &&
         stringAt(m_current, 3, "GNE", "GNA") &&
         ! stringAt(m_current-2, 5, "SIGNA", "MAGNA", "SIGNE")))
    {
      addExactApprox("N", "GN", "N", "KN");
    }
    else
      addExactApprox("GN", "KN");
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_GL()
{
  // Encode "-GL-": 'tagliaro', 'puglia', BUT add K in alternative
  // since Americans sometimes do this.
  if (stringAt(m_current+1, 3, "LIA", "LIO", "LIE") && 
      isVowel(m_current-1))
  {
    addExactApprox("L", "GL", "L", "KL");
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::initial_G_Soft()
{
  if (((stringAt(m_current+1, 2, "EL", "EM", "EN", "EO", "ER", "ES", 
          "IA", "IN", "IO", "IP", "IU", "YM", "YN", "YP", "YR", "EE") ||
        stringAt(m_current+1, 3, "IRA", "IRO")) &&

       // Except for smaller set of cases where => K, e.g. "gerber"
       ! stringAt(m_current+1, 3, "ELD", "ELT", "ERT", "INZ", "ERH", 
           "ITE", "ERD", "ERL", "ERN", "INT", "EES", "EEK", "ELB", 
           "EER") &&
         ! stringAt(m_current+1, 4, "ERSH", "ERST", "INSB", "INGR", 
           "EROW", "ERKE", "EREN") &&
         ! stringAt(m_current+1, 5, "ELLER", "ERDIE", "ERBER", "ESUND", 
           "ESNER", "INGKO", "INKGO", "IPPER", "ESELL", "IPSON", 
           "EEZER", "ERSON", "ELMAN") &&
         ! stringAt(m_current+1, 6, "ESTALT", "ESTAPO", "INGHAM", 
           "ERRITY", "ERRISH", "ESSNER", "ENGLER") &&
         ! stringAt(m_current+1, 7, "YNAECOL", "YNECOLO", "ENTHNER", 
           "ERAGHTY") &&
         ! stringAt(m_current+1, 8, "INGERICH", "EOGHEGAN"))

        || (isVowel(m_current + 1) &&
            (stringAt(m_current+1, 3, "EE ", "EEW") ||
             (stringAt(m_current+1, 3, "IGI", "IRA", "IBE", "AOL", 
               "IDE", "IGL") && 
              ! stringAt(m_current+1, 5, "IDEON")) ||
             stringAt(m_current+1, 4, "ILES", "INGI", "ISEL") ||
             (stringAt(m_current+1, 5, "INGER") && 
              ! stringAt(m_current+1, 8, "INGERICH")) ||
             stringAt(m_current+1, 5, "IBBER", "IBBET", "IBLET", 
               "IBRAN", "IGOLO", "IRARD", "IGANT") ||
             stringAt(m_current+1, 6, "IRAFFE", "EEWHIZ") ||
             stringAt(m_current+1, 7, "ILLETTE", "IBRALTA"))))
  {
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_Initial_G_Front_Vowel()
{
  // Encode cases where 'G' is at start of word followed
  // by a "front" vowel e.g. 'E', 'I', 'Y'
  if (m_current == 0 && front_Vowel(1))
  {
    // Special case "gila", as in "gila monster"
    if (m_length == 4 && stringAt(1, 3, "ILA"))
      add("H");
    else if (initial_G_Soft())
      addExactApprox("J", "G", "J", "K");
    else
    {
      // Only code alternate 'J' if front vowel.
      if ((m_inWord.at(1) == 'E') || (m_inWord.at(1) == 'I'))
        addExactApprox("G", "J", "K", "J");
      else
        addExactApprox("G", "K");
    }

    advanceCounter(2, 1);
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_NGER()
{
  if (m_current > 1 && stringAt(m_current-1, 4, "NGER"))
  {
    // Default 'G' => J  such as 'ranger', 'stranger', 'manger', 
    // 'messenger', 'orangery', 'granger', 'boulanger', 'challenger', 
    // 'danger', 'changer', 'harbinger', 'lounger', 'ginger', 
    // 'passenger'.  Except for the following:
    if (rootOrInflections(m_inWord, "ANGER") ||
        rootOrInflections(m_inWord, "LINGER") ||
        rootOrInflections(m_inWord, "MALINGER") ||
        rootOrInflections(m_inWord, "FINGER") ||
        (stringAt(m_current-3, 4, "HUNG", "FING", "BUNG", "WING", "RING",
          "DING", "ZENG", "ZING", "JUNG", "LONG", "PING", "CONG", "MONG",
          "BANG", "GANG", "HANG", "LANG", "SANG", "SING", "WANG", 
          "ZANG") &&
         // Exceptions to above where 'G' => J.
         ! stringAt(m_current-6, 7, "BOULANG", "SLESING", "KISSING", 
             "DERRING") &&
         ! stringAt(m_current-8, 9, "SCHLESING") &&
         ! stringAt(m_current-5, 6, "SALING", "BELANG") &&
         ! stringAt(m_current-6, 7, "BARRING") &&
         ! stringAt(m_current-6, 9, "PHALANGER") &&
         ! stringAt(m_current-4, 5, "CHANG")) ||
        stringAt(m_current-4, 5, "STING", "YOUNG") ||
        stringAt(m_current-5, 6, "STRONG") ||
        stringAt(0, 3, "UNG", "ENG", "ING") ||
        stringAt(m_current, 6, "GERICH") ||
        stringAt(0, 6, "SENGER") ||
        stringAt(m_current-3, 6, "WENGER", "MUNGER", "SONGER", "KINGER") ||
        stringAt(m_current-4, 7, "FLINGER", "SLINGER", "STANGER", 
          "STENGER", "KLINGER", "CLINGER") ||
        stringAt(m_current-5, 8, "SPRINGER", "SPRENGER") ||
        stringAt(m_current-3, 7, "LINGERF") ||
        stringAt(m_current-2, 7, "ANGERLY", "ANGERBO", "INGERSO") )
    {
      addExactApprox("G", "J", "K", "J");
    }
    else
      addExactApprox("J", "G", "J", "K");

    advanceCounter(2, 1);
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_GER()
{
  if (m_current > 0 && stringAt(m_current+1, 2, "ER"))
  {
    // Exceptions to 'GE' where 'G' => K, e.g. "JAGER", "TIGER", 
    // "LIGER", "LAGER", "LUGER", "AUGER", "EAGER", "HAGER", "SAGER".
    if (((m_current == 2 && isVowel(1) && ! isVowel(0) &&
          ! stringAt(0, 5, "PAGER", "WAGER", "NIGER", "ROGER", "LEGER", 
            "CAGER", "AUGER", "EAGER", "INGER", "YAGER")) ||
          stringAt(m_current-2, 5, "AUGER", "EAGER", "INGER", "YAGER") ||
          stringAt(m_current-3, 6, "SEEGER", "JAEGER", "GEIGER", 
            "KRUGER", "SAUGER", "BURGER", "MEAGER", "MARGER", "RIEGER", 
            "YAEGER", "STEGER", "PRAGER", "SWIGER", "YERGER", "TORGER", 
            "FERGER", "HILGER", "ZEIGER", "YARGER", "COWGER", "CREGER", 
            "KROGER", "KREGER", "GRAGER", "STIGER", "BERGER") ||
          // 'berger' but not 'bergerac'
          (m_current+2 == m_last && stringAt(m_current-3, 6, "BERGER")) ||
          stringAt(m_current-4, 7, "KREIGER", "KRUEGER", "METZGER", 
            "KRIEGER", "KROEGER", "STEIGER", "DRAEGER", "BUERGER", 
            "BOERGER", "FIBIGER") ||
          // E.g. 'harshbarger', 'winebarger'
          (m_current > 4 && stringAt(m_current-3, 6, "BARGER")) ||
          // E.g. 'weisgerber'
          (m_current > 0 && stringAt(m_current, 6, "GERBER")) ||
          stringAt(m_current-5, 8, "SCHWAGER", "LYBARGER", "SPRENGER", 
            "GALLAGER", "WILLIGER") ||
          stringAt(0, 4, "HARGER") ||
          (m_length == 4 && stringAt(0, 4, "AGER", "EGER")) ||
          stringAt(m_current-1, 6, "YGERNE") ||
          stringAt(m_current-6, 9, "SCHWEIGER")) &&

      ! stringAt(m_current-5, 10, "BELLIGEREN") &&
      ! stringAt(0, 7, "MARGERY") &&
      ! stringAt(m_current-3, 8, "BERGERAC"))
    {
      if (slavoGermanic())
        addExactApprox("G", "K");
      else
        addExactApprox("G", "J", "K", "J");
    }
    else
      addExactApprox("J", "G", "J", "K");

    advanceCounter(2, 1);
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_GEL()
{
  // Encode "-GEL-": More likely to be "-GEL-" => JL.
  if (m_current > 0 && stringAt(m_current+1, 2, "EL"))
  {
    // Except for "BAGEL", "HEGEL", "HUGEL", "KUGEL", "NAGEL", 
    // "VOGEL", "FOGEL", "PAGEL".
    if ((m_length == 5 &&
         isVowel(m_current-1) &&
         ! isVowel(m_current-2) &&
         ! stringAt(m_current-2, 5, "NIGEL", "RIGEL")) ||
        // Or the following as combining forms.
        stringAt(m_current-2, 5, "ENGEL", "HEGEL", "NAGEL", "VOGEL") ||
        stringAt(m_current-3, 6, "MANGEL", "WEIGEL", "FLUGEL", 
          "RANGEL", "HAUGEN", "RIEGEL", "VOEGEL") ||
        stringAt(m_current-4, 7, "SPEIGEL", "STEIGEL", "WRANGEL", 
          "SPIEGEL") ||
        stringAt(m_current-4, 8, "DANEGELD"))
    {
      if (slavoGermanic())
        addExactApprox("G", "K");
      else
        addExactApprox("G", "J", "K", "J");
    }
    else
      addExactApprox("J", "G", "J", "K");

    advanceCounter(2, 1);
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_Non_Initial_G_Front_Vowel()
{
  // Encode "-G-" followed by a vowel when non-initial letter.
  // Default for this is a 'J' sound, so check exceptions where
  // it is pronounced 'G': -gy-, gi-, ge-.
  if (stringAt(m_current+1, 1, "E", "I", "Y"))
  {
    if (m_current == m_last-1 && stringAt(m_current, 2, "GE"))
    {
      // '-ge' at end is almost always 'j 'sound.
      if (! hard_GE_At_End())
        add("J");
      else if (slavoGermanic())
        addExactApprox("G", "K");
      else
        addExactApprox("G", "J", "K", "J");
    }
    else if (! internal_Hard_G())
      addExactApprox("J", "G", "J", "K");
    else
    {
      // Don't encode KG or KK if e.g. "mcgill".
      if (! (m_current == 2 && stringAt(0, 2, "MC")) ||
            (m_current == 3 && stringAt(0, 3, "MAC")))
      {
        if (slavoGermanic())
          addExactApprox("G", "K");
        else
          addExactApprox("G", "J", "K", "J");
      }
    }

    advanceCounter(2, 1);
    return true;
  }
  else
    return false;
}


bool Metaphone3::hard_GE_At_End()
  {
  // Detect German names and other words that have a 'hard' 'g' 
  // in the context of "-ge" at end.
  if (stringAt(0, 6, "RENEGE", "STONGE", "STANGE", "PRANGE", "KRESGE") || 
      stringAt(0, 5, "BYRGE", "BIRGE", "BERGE", "HAUGE",
        "LANGE", "SYNGE", "BENGE", "RUNGE", "HELGE") || 
      stringAt(0, 4, "INGE", "LAGE", "HAGE"))
    return true;
  else
    return false;
}


bool Metaphone3::internal_Hard_G()
{
  // Exceptions to default encoding to 'J':
  // encode "-G-" to 'G' in "-g<frontvowel>-" words
  // where we are not at "-GE" at the end of the word.
  if (! (m_current+1 == m_last && charAt(m_last) == 'E') &&
      (internal_Hard_NG() ||
       internal_Hard_GEN_GIN_GET_GIT() ||
       internal_Hard_G_Open_Syllable() ||
       internal_Hard_G_Other()))
    return true;
  else
    return false;
}


bool Metaphone3::internal_Hard_G_Other()
{
  // Detect words where "-ge-" or "-gi-" get a 'hard' 'g',
  // even though this is usually a 'soft' 'g' context
  if ((stringAt(m_current, 4, "GETH", "GEAR", "GEIS", "GIRL", "GIVI", 
         "GIVE", "GIFT", "GIRD", "GIRT", "GILV", "GILD", "GELD") &&
      ! stringAt(m_current-3, 6, "GINGIV")) ||

      // "gish" but not "largish"
      (m_current > 0 && 
       stringAt(m_current+1, 3, "ISH") && 
       ! stringAt(0, 4, "LARG")) ||
      (m_current+2 != m_last && 
       stringAt(m_current-2, 5, "MAGED", "MEGID")) ||
      stringAt(m_current, 3, "GEZ") ||
      stringAt(0, 4, "WEGE", "HAGE") ||
      (m_current+3 == m_last &&
       stringAt(m_current-2, 6, "ONGEST", "UNGEST") &&
       ! stringAt(m_current-3, 7, "CONGEST")) ||
      stringAt(0, 5, "VOEGE", "BERGE", "HELGE") ||
      (m_length == 4 && stringAt(0, 4, "ENGE", "BOGY")) ||
      stringAt(m_current, 6, "GIBBON") ||
      stringAt(0, 10, "CORREGIDOR") ||
      stringAt(0, 8, "INGEBORG") ||
      (stringAt(m_current, 4, "GILL") &&
       (m_current+3 == m_last || m_current+4 == m_last) &&
        ! stringAt(0, 8, "STURGILL")))
  {
    return true;
  }
  else
    return false;
}


bool Metaphone3::internal_Hard_G_Open_Syllable()
{
  // Detect words where "-gy-", "-gie-", "-gee-", or "-gio-" get a 
  // 'hard' 'g', even though this is usually a 'soft' 'g' context.
  if (stringAt(m_current+1, 3, "EYE") ||
      stringAt(m_current-2, 4, "FOGY", "POGY", "YOGI") ||
      stringAt(m_current-2, 5, "MAGEE", "MCGEE", "HAGIO") ||
      stringAt(m_current-1, 4, "RGEY", "OGEY") ||
      stringAt(m_current-3, 5, "HOAGY", "STOGY", "PORGY") ||
      stringAt(m_current-5, 8, "CARNEGIE") ||
      (m_current+2 == m_last &&
       stringAt(m_current-1, 4, "OGEY", "OGIE")))
    return true;
  else
    return false;
}


bool Metaphone3::internal_Hard_GEN_GIN_GET_GIT()
{
  // Detect a number of contexts, mostly German names, that
  // take a 'hard' 'g'.
  if ((stringAt(m_current-3, 6, "FORGET", "TARGET", "MARGIT", 
         "MARGET", "TURGEN", "BERGEN", "MORGEN", "JORGEN", "HAUGEN", 
         "JERGEN", "JURGEN", "LINGEN", "BORGEN", "LANGEN", "KLAGEN", 
         "STIGER", "BERGER") &&
       ! stringAt(m_current, 7, "GENETIC", "GENESIS") &&
       ! stringAt(m_current-4, 8, "PLANGENT")) ||

      (m_current+2 == m_last && 
       stringAt(m_current-3, 6, "BERGIN", "FEAGIN", "DURGIN")) ||

      (stringAt(m_current-2, 5, "ENGEN") && 
       ! stringAt(m_current+3, 3, "DER", "ETI", "ESI")) ||

      stringAt(m_current-4, 7, "JUERGEN") ||
      stringAt(0, 5, "NAGIN", "MAGIN", "HAGIN") ||
      (m_length == 5 &&
       stringAt(0, 5, "ENGIN", "DEGEN", "LAGEN", "MAGEN", "NAGIN")) ||
      (stringAt(m_current-2, 5, "BEGET", "BEGIN", "HAGEN", "FAGIN",
         "BOGEN", "WIGIN", "NTGEN", "EIGEN", "WEGEN", "WAGEN") &&
       ! stringAt(m_current-5, 8, "OSPHAGEN")))
  {
    return true;
  }
  else
    return false;
}


bool Metaphone3::internal_Hard_NG()
{
  // Detect a number of contexts of '-ng-' that will
  // take a 'hard' 'g' despite being followed by a front vowel.
  if ((stringAt(m_current-3, 4, "DANG", "FANG", "SING") &&
       // Exception to exception
       ! stringAt(m_current-5, 8, "DISINGEN")) ||

      stringAt(0, 5, "INGEB", "ENGEB") ||

      (stringAt(m_current-3, 4, "RING", "WING", "HANG", "LONG") &&
       ! stringAt(m_current-4, 5, "CRING", "FRING", "ORANG", "TWING", 
           "CHANG", "PHANG") &&
       ! stringAt(m_current-5, 6, "SYRING") &&
       ! stringAt(m_current-3, 7, "RINGENC", "RINGENT", "LONGITU", 
            "LONGEVI") &&
       // E.g. 'longino', 'mastrangelo'.
       (m_current+3 != m_last || 
        ! stringAt(m_current, 4, "GELO", "GINO"))) ||

      (stringAt(m_current-1, 3, "NGY") &&
       // Exceptions to exception
       ! stringAt(m_current-3, 5, "RANGY", "MANGY", "MINGY") &&
       ! stringAt(m_current-4, 6, "SPONGY", "STINGY")))
  {
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_GA_To_J()
{
  // Encode special case where "-GA-" => J: 'margary', 'margarine'.
  if ((stringAt(m_current-3, 7, "MARGARY", "MARGARI") &&
      // But not in spanish forms such as "margarita".
      ! stringAt(m_current-3, 8, "MARGARIT")) ||
      stringAt(0, 4, "GAOL") ||
      stringAt(m_current-2, 5, "ALGAE"))
  {
    addExactApprox("J", "G", "J", "K");
    advanceCounter(2, 1);
    return true;
  }
  else
  return false;
}


void Metaphone3::encode_H()
{
  //  Encode 'H'.
  if (encode_Initial_Silent_H() || 
      encode_Initial_HS() || 
      encode_Initial_HU_HW() || 
      encode_Non_Initial_Silent_H())
    return;

  // Only keep if first & before vowel or between two vowels.
  if (! encode_H_Pronounced())
    m_current++; // Also takes care of 'HH'.
}


bool Metaphone3::encode_Initial_Silent_H()
{
  // Encode cases where initial 'H' is not pronounced (in American):
  // 'hour', 'herb', 'heir', 'honor'.
  if (stringAt(m_current+1, 3, "OUR", "ERB", "EIR") ||
      stringAt(m_current+1, 4, "ONOR") ||
      stringAt(m_current+1, 5, "ONOUR", "ONEST"))
  {
    // British pronounce H in this word, Americans give it 'H' for 
    // the name, no 'H' for the plant.
    if (m_current == 0 && stringAt(0, 4, "HERB"))
      add(m_encodeVowels ? "HA" : "H", "A");
    else if (m_current == 0 || m_encodeVowels)
      add("A");

    m_current++;
    // Don't encode vowels twice.
    m_current = skipVowels(m_current);
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_Initial_HS()
{
  // Encode "HS-": Old Chinese Pinyin transliteration, e.g., 'HSIAO'.
  if (m_current == 0 && stringAt(0, 2, "HS"))
  {
    add("X");
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_Initial_HU_HW()
{
  // Encode cases where "HU-" is pronounced as part of a vowel dipthong.
  // Spanish spellings and Chinese Pinyin transliteration.
  if (stringAt(0, 3, "HUA", "HUE", "HWA") &&
      ! stringAt(m_current, 4, "HUEY"))
  {
    add("A");

    if ( !m_encodeVowels)
      m_current += 3;
    else
    {
      m_current++;
      // Don't encode vowels twice.
      while (isVowel(m_current) || (charAt(m_current) == 'W'))
        m_current++;
    }
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_Non_Initial_Silent_H()
{
  // Encode cases where 'H' is silent between vowels.
  // "PROHIB" but not "PROHIBIT".
  if (stringAt(m_current-2, 5, "NIHIL", "VEHEM", "LOHEN", "NEHEM",
        "MAHON", "MAHAN", "COHEN", "GAHAN") ||
      stringAt(m_current-3, 6, "GRAHAM", "PROHIB", "FRAHER",
        "TOOHEY", "TOUHEY") ||
      stringAt(m_current-3, 5, "TOUHY") ||
      stringAt(0, 9, "CHIHUAHUA"))
  {
    if ( !m_encodeVowels)
      m_current += 2;
    else
    {
      m_current++;
      // Don't encode vowels twice
      m_current = skipVowels(m_current);
    }
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_H_Pronounced()
{
  // Encode cases where 'H' is pronounced.
  if ((isVowel(m_current+1) &&
      (m_current == 0 || 
       isVowel(m_current-1) || 
       charAt(m_current-1) == 'W')) ||
      // E.g. 'alWahhab'
      (charAt(m_current+1) == 'H' && isVowel(m_current+2)))
  {
    add("H");
    advanceCounter(2, 1);
    return true;
  }
  else
    return false;
}


void Metaphone3::encode_J()
{
  // Encode 'J'.
  if (encode_Spanish_J() || 
      encode_Spanish_OJ_UJ())
    return;

  encode_Other_J();
}


bool Metaphone3::encode_Spanish_J()
{
  // Encode cases where initial or medial "j" is in a Spanish word or 
  // name e.g. "jose", "san jacinto".
  if ((stringAt(m_current+1, 3, "UAN", "ACI", "ALI", "EFE", "ICA", 
        "IME", "OAQ", "UAR") &&
       ! stringAt(m_current, 8, "JIMERSON", "JIMERSEN")) ||
      (m_current+3 == m_last && stringAt(m_current+1, 3, "OSE")) ||
      stringAt(m_current+1, 4, "EREZ", "UNTA", "AIME", "AVIE", "AVIA") ||
      stringAt(m_current+1, 6, "IMINEZ", "ARAMIL") ||
      (m_current+2 == m_last && stringAt(m_current-2, 5, "MEJIA")) ||
      stringAt(m_current-2, 5, "TEJED", "TEJAD", "LUJAN", "FAJAR", 
        "BEJAR", "BOJOR", "CAJIG", "DEJAS", "DUJAR", "DUJAN", "MIJAR", 
        "MEJOR", "NAJAR", "NOJOS", "RAJED", "RIJAL", "REJON", "TEJAN", 
        "UIJAN") ||
      stringAt(m_current-3, 8, "ALEJANDR", "GUAJARDO", "TRUJILLO") ||
      (m_current > 2 && stringAt(m_current-2, 5, "RAJAS")) ||
      (stringAt(m_current-2, 5, "MEJIA") && 
       ! stringAt(m_current-2, 6, "MEJIAN")) ||
      stringAt(m_current-1, 5, "OJEDA") ||
      stringAt(m_current-3, 5, "LEIJA", "MINJA") ||
      stringAt(m_current-3, 6, "VIAJES", "GRAJAL") ||
      stringAt(m_current, 8, "JAUREGUI") ||
      stringAt(m_current-4, 8, "HINOJOSA") ||
      stringAt(0, 4, "SAN ") ||
      (m_current+1 == m_last &&
       charAt(m_current+1) == 'O' &&
       // exceptions
       ! stringAt(0, 4, "TOJO") &&
       ! stringAt(0, 5, "BANJO") &&
       ! stringAt(0, 6, "MARYJO")))
  {
    // Americans pronounce "juan" as 'wan', and "marijuana" and 
    // "tijuana" also do not get the 'H' as in Spanish, so
    // just treat it like a vowel in these cases.
    if (! stringAt(m_current, 4, "JUAN") && 
        ! stringAt(m_current, 4, "JOAQ"))
      add("H");
    else if (m_current == 0)
      add("A");

    advanceCounter(2, 1);
    return true;
  }

  // Jorge gets 2nd HARHA. Also JULIO, JESUS.
  if (stringAt(m_current+1, 4, "ORGE", "ULIO", "ESUS") &&
      ! stringAt(0, 6, "JORGEN"))
  {
    // Get both consonants for "jorge".
    if (m_current+4 == m_last && stringAt(m_current+1, 4, "ORGE"))
    {
      if (m_encodeVowels)
        add("JARJ", "HARHA");
      else
        add("JRJ", "HRH");

      advanceCounter(5, 5);
      return true;
    }

    add("J", "H");
    advanceCounter(2, 1);
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_German_J()
{
  // Encode cases where 'J' is clearly in a German word or name
  // that Americans pronounce in the German fashion.
  if (stringAt(m_current+1, 2, "AH") ||
      (m_current+5 == m_last && stringAt(m_current+1, 5, "OHANN")) ||
      (stringAt(m_current+1, 3, "UNG") && 
       ! stringAt(m_current+1, 4, "UNGL")) ||
      stringAt(m_current+1, 3, "UGO"))
  {
    add("A");
    advanceCounter(2, 1);
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_Spanish_OJ_UJ()
{
  // Encode "-JOJ-" and "-JUJ-" as spanish words.
  if (stringAt(m_current+1, 5, "OJOBA", "UJUY ")) // TODO shein: ?? space
  {
    if (m_encodeVowels)
    {
      add("HAH");
      m_current += 3;
    }
    else
    {
      add("HH");
      m_current += 4;
    }
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_J_To_J()
{
  // Encode 'J' => J
  if (isVowel(m_current+1))
  {
    if (m_current == 0 && names_Beginning_With_J_That_Get_Alt_Y())
    {
      // 'Y' is a vowel, so encode it as 'A'.
      add(m_encodeVowels ? "JA" : "J", "A");
    }
    else
      add(m_encodeVowels ? "JA" : "J");

    m_current++;
    m_current = skipVowels(m_current);
    return false;
  }
  else
  {
    add("J");
    m_current++;
    return true;
  }
}


bool Metaphone3::encode_Spanish_J_2()
{
  // Encode 'J' toward end in Spanish words, e.g. "brujo", "badajoz".
  if ((m_current == 2 && 
      stringAt(0, 4, "BOJA", "BAJA", "BEJA", "BOJO", "MOJA", "MOJI", 
        "MEJI")) ||
      (m_current == 3 && 
        stringAt(0, 5, "FRIJO", "BRUJO", "BRUJA", "GRAJE", "GRIJA", 
          "LEIJA", "QUIJA")) ||
      (m_current+3 == m_last && stringAt(m_current-1, 5, "AJARA")) ||
      (m_current + 2 == m_last &&
        stringAt(m_current-1, 4, "AJOS", "EJOS", "OJAS", "OJOS", 
          "UJON", "AJOZ", "AJAL", "UJAR", "EJON", "EJAN")) ||
      (m_current+1 == m_last &&
        stringAt(m_current-1, 3, "OJA", "EJA") && 
        ! stringAt(0, 4, "DEJA")))
  {
    add("H");
    advanceCounter(2, 1);
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_J_As_Vowel()
{
  // Encode 'J' as vowel in some exception cases.
  if (stringAt(m_current, 5, "JEWSK"))
  {
    add("J", "");
    return true;
  }

  // E.g. "stijl", "sejm" - Dutch, Scandanavian, and Eastern European 
  // spellings.
  if ((stringAt(m_current+1, 1, "L", "T", "K", "S", "N", "M") &&
       // Except words from Hindi and Arabic
       ! stringAt(m_current+2, 1, "A")) ||
      stringAt(0, 9, "HALLELUJA", "LJUBLJANA") ||
      stringAt(0, 4, "LJUB", "BJOR") ||
      stringAt(0, 5, "HAJEK") ||
      stringAt(0, 3, "WOJ") ||
      // E.g. 'fjord'
      stringAt(0, 2, "FJ") ||
      // E.g. 'rekjavik', 'blagojevic'
      stringAt(m_current, 5, "JAVIK", "JEVIC") ||
      (m_current+1 == m_last && 
       stringAt(0, 5, "SONJA", "TANJA", "TONJA")))
    return true;
  else
    return false;
}

void Metaphone3::encode_Other_J()
{
  // Call routines to encode 'J', in proper order.
  if (m_current == 0)
  {
    if (encode_German_J() ||
        encode_J_To_J())
      return;
  }
  else
  {
    if (encode_Spanish_J_2())
      return;
    else if (! encode_J_As_Vowel())
      add("J");

    // It could happen! e.g. "hajj".  Aat redundant 'J'.
    if (charAt(m_current+1) == 'J')
      m_current += 2;
    else
      m_current++;
  }
}


void Metaphone3::encode_K()
{
  if (! encode_Silent_K())
  {
    add("K");

    // Eat redundant 'K's and 'Q's.
    if (charAt(m_current+1) == 'K' ||
        charAt(m_current+1) == 'Q')
      m_current += 2;
    else
      m_current++;
  }
}

bool Metaphone3::encode_Silent_K()
{
  // Encode cases where 'K' is not pronounced.
  // Skip this except for special cases.
  if (m_current == 0 && stringAt(0, 2, "KN"))
  {
    if (! stringAt(m_current+2, 5, "ESSET", "IEVEL") && 
        ! stringAt(m_current+2, 3, "ISH"))
    {
      m_current++;
      return true;
    }
  }

  // E.g. "know", "knit", "knob".
  if ((stringAt(m_current+1, 3, "NOW", "NIT", "NOT", "NOB") &&
       // Exception: "slipknot" => SLPNT but "banknote" => PNKNT.
       ! stringAt(0, 8, "BANKNOTE")) ||
      stringAt(m_current+1, 4, "NOCK", "NUCK", "NIFE", "NACK") ||
      stringAt(m_current+1, 5, "NIGHT"))
  {
    // N already encoded before, e.g. "penknife".
    if (m_current > 0 && charAt(m_current-1) == 'N')
      m_current += 2;
    else
      m_current++;

    return true;
  }
  else
    return false;
}


void Metaphone3::encode_L()
{
  // Logic below needs to know this after 'm_current' variable changed.
  const int save_current = m_current;

  interpolate_Vowel_When_Cons_L_At_End();

  if (encode_LELY_To_L() ||
      encode_COLONEL() ||
      encode_French_AULT() ||
      encode_French_EUIL() ||
      encode_French_OULX() ||
      encode_Silent_L_In_LM() ||
      encode_Silent_L_In_LK_LV() ||
      encode_Silent_L_In_OULD())
    return;

  if (encode_LL_As_Vowel_Cases())
    return;

  encode_LE_Cases(save_current);
}


void Metaphone3::interpolate_Vowel_When_Cons_L_At_End()
{
  // Cases where an L follows D, G, or T at the
  // end have a schwa pronounced before the L.
  if (m_encodeVowels == true)
  {
    // E.g. "ertl", "vogl"
    if (m_current == m_last && stringAt(m_current-1, 1, "D", "G", "T"))
      add("A");
  }
}


bool Metaphone3::encode_LELY_To_L()
{
  // Catch cases where 'L' spelled twice but pronounced
  // once, e.g., 'DOCILELY' => TSL, "agilely".
  if (m_current+3 == m_last && stringAt(m_current-1, 5, "ILELY"))
  {
    add("L");
    m_current += 3;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_COLONEL()
{
  // Encode special case "colonel" => KRNL. Can somebody tell
  // me how this pronounciation came to be?
  if (stringAt(m_current-2, 7, "COLONEL"))
  {
    add("R");
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_French_AULT()
{
  // Encode "-AULT-", found in a French names,
  // e.g. "renault" and "foucault", well known to Americans, 
  // but not "fault".
  if (m_current > 3 &&
      (stringAt(m_current-3, 5, "RAULT", "NAULT", "BAULT", "SAULT", 
        "GAULT", "CAULT") ||
       stringAt(m_current-4, 6, "REAULT", "RIAULT", "NEAULT", "BEAULT")) &&
       ! rootOrInflections(m_inWord, "ASSAULT") &&
       ! stringAt(m_current-8, 10, "SOMERSAULT") &&
       ! stringAt(m_current-9, 11, "SUMMERSAULT"))
  {
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_French_EUIL()
{
  // Encode "-EUIL-", always found in a french word, e.g. "auteuil".
  if (m_current == m_last &&
      stringAt(m_current-3, 4, "EUIL"))
  {
    m_current++;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_French_OULX()
{
  // Encode "-OULX", always found in a French word, e.g. "proulx".
  if (m_current+1 == m_last &&
      stringAt(m_current-2, 4, "OULX"))
  {
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_Silent_L_In_LM()
{
  // Encodes contexts where 'L' is not pronounced in "-LM-".
  if (stringAt(m_current, 2, "LM", "LN"))
  {
    // E.g. "lincoln", "holmes", "psalm", "salmon".
    if ((stringAt(m_current-2, 4, "COLN", "CALM", "BALM", "MALM", 
           "PALM") ||
         (m_current+1 == m_last && stringAt(m_current-1, 3, "OLM")) ||
         stringAt(m_current-3, 5, "PSALM", "QUALM") ||
         stringAt(m_current-2, 6,  "SALMON", "HOLMES") ||
         stringAt(m_current-1, 6,  "ALMOND") ||
         (m_current == 1 && stringAt(0, 4, "ALMS"))) &&

        ! stringAt(m_current+2, 1, "A") &&
        ! stringAt(m_current-2, 5, "BALMO") &&
        ! stringAt(m_current-2, 6, "PALMER", "PALMOR", "BALMER") &&
        ! stringAt(m_current-3, 5, "THALM"))
    {
      m_current++;
      return true;
    }
    else
    {
      add("L");
      m_current++;
      return true;
    }
  }
  else
    return false;
}


bool Metaphone3::encode_Silent_L_In_LK_LV()
{
  // Encodes contexts where '-L-' is silent in 'LK', 'LV'.
  if ((stringAt(m_current-2, 4, "WALK", "YOLK", "FOLK", "HALF", "TALK", 
         "CALF", "BALK", "CALK") ||
       (stringAt(m_current-2, 4, "POLK") &&
        ! stringAt(m_current-2, 5, "POLKA", "WALKO")) ||
       (stringAt(m_current-2, 4, "HALV") &&
        ! stringAt(m_current-2, 5, "HALVA", "HALVO")) ||
       (stringAt(m_current-3, 5, "CAULK", "CHALK", "BAULK", "FAULK") &&
        ! stringAt(m_current-4, 6, "SCHALK")) ||
       (stringAt(m_current-2, 5, "SALVE")  &&
        ! stringAt(m_current-2, 6, "SALVER")) ||
       (stringAt(m_current-2, 5, "CALVE")  &&
        ! stringAt(m_current-2, 6, "CALVER")) ||
       stringAt(m_current-2, 6, "SOLDER")) &&

       // Exceptions to above cases where 'L' is usually pronounced.
      ! stringAt(m_current-5, 9, "GONSALVES", "GONCALVES") &&
      ! stringAt(m_current-2, 6, "BALKAN", "TALKAL") &&
      ! stringAt(m_current-3, 5, "PAULK", "CHALF"))
  {
    m_current++;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_Silent_L_In_OULD()
{
  // Encode 'L' in contexts of "-OULD-" where it is silent:
  // 'would', 'could'
  if (stringAt(m_current-3, 5, "WOULD", "COULD") ||
      (stringAt(m_current-4, 6, "SHOULD") &&
       ! stringAt(m_current-4, 8, "SHOULDER")))
  {
    addExactApprox("D", "T");
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_LL_As_Vowel_Special_Cases()
{
  // Encode "-ILLA-" and "-ILLE-" in Spanish and French
  // contexts were Americans know to pronounce it as a 'Y'.
  if (stringAt(m_current-5, 8, "TORTILLA") ||
      stringAt(m_current-8, 11, "RATATOUILLE") ||

      // E.g. 'guillermo', "veillard"
      (stringAt(0, 5, "GUILL", "VEILL", "GAILL") &&
       // 'guillotine' usually has '-ll-' pronounced as 'L' in English.
       !(stringAt(m_current-3, 7, "GUILLOT", "GUILLOR", "GUILLEN") ||
        (m_length == 5 && stringAt(0, 5, "GUILL")))) ||

      // E.g. "brouillard", "gremillion"
      stringAt(0, 7, "BROUILL", "GREMILL", "ROBILL") ||

      // E.g. 'mireille'
      (m_current+2 == m_last && 
       stringAt(m_current-2, 5, "EILLE") &&
       // Exception: "reveille" usually pronounced as 're-vil-lee'.
       ! stringAt(m_current-5, 8, "REVEILLE")))
  {
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_LL_As_Vowel()
{
  // Encode other spanish cases where "-LL-" is pronounced as 'Y'.
  // Spanish e.g. "cabrillo", "gallegos" but also "gorilla", 
  // "ballerina" - give both pronounciations since an American 
  // might pronounce "cabrillo" in the Spanish or the American fashion.
  if ((m_current+3 == m_length &&
       stringAt(m_current-1, 4, "ILLO", "ILLA", "ALLE")) ||

      (((stringAt(m_last-1, 2, "AS", "OS") ||
         stringAt(m_last, 1, "A", "O")) &&
         stringAt(m_current-1, 2, "AL", "IL")) &&
         ! stringAt(m_current-1, 4, "ALLA")) ||
      // shein: This looks odd.  There is no link between m_current
      // and m_last.  

      stringAt(0, 5, "VILLE", "VILLA") ||
      stringAt(0, 8, "GALLARDO", "VALLADAR", "MAGALLAN", "CAVALLAR", 
        "BALLASTE") ||
      stringAt(0, 3, "LLA"))
  {
    add("L", "");
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_LL_As_Vowel_Cases()
{
  // Call routines to encode "-LL-", in proper order.
  if (charAt(m_current+1) == 'L')
  {
    if (encode_LL_As_Vowel_Special_Cases() ||
        encode_LL_As_Vowel())
      return true;

    m_current += 2;
  }
  else
    m_current++;

  return false;
}


bool Metaphone3::encode_Vowel_LE_Transposition(const int save_current)
{
  // Encode vowel-encoding cases where "-LE-" is pronounced "-EL-".
  // Transposition of vowel sound and L occurs in many words,
  // e.g. "bristle", "dazzle", "goggle" => KAKAL.
  if (m_encodeVowels &&
      save_current > 1 &&
      ! isVowel(save_current-1) &&
      charAt(save_current + 1) == 'E' &&
      charAt(save_current-1) != 'L' &&
      charAt(save_current-1) != 'R' &&
      charAt(save_current-1) != 'H' &&
      charAt(save_current-1) != 'W' &&
      // Lots of exceptions to this:
      ! isVowel(save_current+2) &&
      ! stringAt(0, 7, "ECCLESI", "COMPLEC", "COMPLEJ", "ROBLEDO") &&
      ! stringAt(0, 5, "MCCLE", "MCLEL") &&
      ! stringAt(0, 6, "EMBLEM", "KADLEC") &&
      ! (save_current+2 == m_last && stringAt(save_current, 3, "LET")) &&
      ! stringAt(save_current, 7, "LETTING") &&
      ! stringAt(save_current, 6, "LETELY", "LETTER", "LETION", 
        "LETIAN", "LETING", "LETORY") &&
      ! stringAt(save_current, 5, "LETUS", "LETIV") &&
      ! stringAt(save_current, 4, "LESS", "LESQ", "LECT", "LEDG", 
        "LETE", "LETH", "LETS", "LETT") &&
      ! stringAt(save_current, 3, "LEG", "LER", "LEX") &&
      // E.g. "complement" !=> KAMPALMENT.
      ! (stringAt(save_current, 6, "LEMENT") &&
         ! stringAt(m_current-5, 6, "BATTLE", "TANGLE", "PUZZLE", 
           "RABBLE", "BABBLE") &&
         ! stringAt(m_current-4, 5, "TABLE")) &&
      ! (save_current+2 == m_last && 
         stringAt(save_current-2, 5, "OCLES", "ACLES", "AKLES")) &&
      ! stringAt((save_current - 3), 5, "LISLE", "AISLE") &&
      ! stringAt(0, 4, "ISLE") &&
      ! stringAt(0, 6, "ROBLES") &&
      ! stringAt((save_current - 4), 7, "PROBLEM", "RESPLEN") &&
      ! stringAt((save_current - 3), 6, "REPLEN") &&
      ! stringAt((save_current - 2), 4, "SPLE"))
  {
    add("AL");
    flag_AL_inversion = true;

    // Eat redundant 'L'.
    if (charAt(save_current+2) == 'L')
      m_current = save_current + 3;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_Vowel_Preserve_Vowel_After_L(
  const int save_current)
{
  // Encode special vowel-encoding cases where 'E' is not
  // silent at the end of a word as is the usual case.
  // An example of where the vowel would NOT need to be preserved
  // would be "hustled", where there is no vowel pronounced
  // between the 'l' and the 'd'.
  if (m_encodeVowels &&
      save_current > 1 &&
      save_current+1 != m_last &&
      ! isVowel(save_current-1) &&
      charAt(save_current+1) == 'E' &&
      ! (save_current+2 == m_last && 
       stringAt(save_current+1, 2, "ES", "ED")) &&
      ! stringAt(save_current-1, 5, "RLEST") )
  {
    add("LA");
    m_current = skipVowels(m_current);
    return true;
  }
  else
    return false;
}


void Metaphone3::encode_LE_Cases(const int save_current)
{
  // Encode "-LE-" in proper order.
  if (encode_Vowel_LE_Transposition(save_current) ||
      encode_Vowel_Preserve_Vowel_After_L(save_current))
    return;
  else
    add("L");
}


void Metaphone3::encode_M()
{
  // Encode "-M-".
  if (encode_Silent_M_At_Beginning() || 
      encode_MR_And_MRS() || 
      encode_MAC() || 
      encode_MPT())
    return;

  // Silent 'B' should really be handled under 'B", not under 'M'!
  encode_MB();
  add("M");
}


bool Metaphone3::encode_Silent_M_At_Beginning()
{
  // Encode (skip) silent 'M' at beginning of word.
  if (m_current == 0 && stringAt(0, 2, "MN"))
  {
    m_current += 1;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_MR_And_MRS()
{
  // Encode special cases "Mr." and "Mrs.".
  if (m_current == 0 && stringAt(0, 2, "MR"))
  {
    if (m_length == 2)
    {
      add(m_encodeVowels ? "MASTAR" : "MSTR");
      m_current += 2;
      return true;
    }
    else if (m_length == 3 && stringAt(0, 3, "MRS"))
    {
      add(m_encodeVowels ? "MASAS": "MSS");
      m_current += 3;
      return true;
    }
  }

  return false;
}

bool Metaphone3::encode_MAC()
{
  // Encode "Mac-" and "Mc-".  Should only find Irish and Scottish 
  // names, e.g. 'macintosh'.
  if (m_current == 0 && 
     (stringAt(0, 7, "MACIVER", "MACEWEN") || 
      stringAt(0, 8, "MACELROY", "MACILROY") ||  
      stringAt(0, 9, "MACINTOSH") || 
      stringAt(0, 2, "MC")))
  {
    add(m_encodeVowels ? "MAK" : "MK");

    if (stringAt(0, 2, "MC"))
    {
      if (stringAt(2, 1, "K", "G", "Q") && ! stringAt(2, 4, "GEOR"))
        // E.g. "McGeorge".
        m_current += 3;
      else
        m_current += 2;
    }
    else
      m_current += 3;

    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_MPT()
{
  // Encode silent 'M' in context of "-MPT-".
  if (stringAt((m_current - 2), 8, "COMPTROL") || 
      stringAt((m_current - 4), 7, "ACCOMPT"))
  {
    add("N");
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::test_Silent_MB_1()
{
  // Test if 'B' is silent in these contexts, e.g. "LAMB", "COMB", 
  // "LIMB", "DUMB", "BOMB".  Handle combining roots first.
  if ((m_current == 3 && stringAt(0, 5, "THUMB")) || 
       (m_current == 2 && stringAt(0, 4, "DUMB", "BOMB", "DAMN", 
         "LAMB", "NUMB", "TOMB")))
    return true;
  else
    return false;
}


bool Metaphone3::test_Pronounced_MB()
{
  // Test if 'B' is pronounced in this context.
  if (stringAt(m_current-2, 6, "NUMBER") ||
      (stringAt(m_current+2, 1, "A") &&
       ! stringAt(m_current-2, 7, "DUMBASS")) ||
      stringAt(m_current+2, 1, "O") ||
      stringAt(m_current-2, 6, "LAMBEN", "LAMBER", "LAMBET", 
        "TOMBIG", "LAMBRE"))
    return true;
  else
    return false;
}


bool Metaphone3::test_Silent_MB_2()
{
  // Test whether "-B-" is silent in these contexts;
  // 'M' is the current letter.
  if (m_current > 1 && 
      charAt(m_current+1) == 'B' &&
      (m_current+1 == m_last ||
       // Other situations where "-MB-" is at end of root
       // but not at end of word. The tests are for standard
       // noun suffixes, e.g. "climbing" => KLMNK.
       stringAt(m_current+2, 3, "ING", "ABL") ||
       stringAt(m_current+2, 4, "LIKE") ||
       (m_current+2 == m_last && (charAt(m_last) == 'S')) ||
       stringAt(m_current-5, 7, "BUNCOMB") ||

       // E.g. "bomber",
       (m_current+3 == m_last &&
        stringAt(m_current+2, 2, "ED", "ER") &&
        (stringAt(0, 5, "CLIMB", "PLUMB") ||
        // E.g. "beachcomber"
         ! stringAt(m_current-1, 5, "IMBER", "AMBER", "EMBER", "UMBER")) &&
        // Exceptions.
        ! stringAt(m_current-2, 6, "CUMBER", "SOMBER"))))
    return true;
  else
    return false;
}


bool Metaphone3::test_Pronounced_MB_2()
{
  // Test if 'B' is pronounced in these "-MB-" contexts,
  // e.g. "bombastic", "umbrage", "flamboyant".
  if (stringAt(m_current-1, 5, "OMBAS", "OMBAD", "UMBRA") || 
      stringAt(m_current-3, 4, "FLAM"))
    return true;
  else
    return false;
}


bool Metaphone3::test_MN()
{
  // Tests for contexts where "-N-" is silent when after "-M-".
  if (charAt(m_current+1) == 'N' &&
      (m_current+1 == m_last ||
       // Or at the end of a word, but followed by suffixes.
      (m_current+4 == m_last && 
       stringAt(m_current+2, 3, "ING", "EST")) ||
      (m_current+2 == m_last && charAt(m_current+2) == 'S') ||
      (m_current+3 == m_last &&
       stringAt(m_current+2, 2, "LY", "ER", "ED")) ||
      stringAt(m_current-2, 9, "DAMNEDEST") ||
      stringAt(m_current-5, 9, "GODDAMNIT")))
    return true;
  else
    return false;
}


void Metaphone3::encode_MB()
{
  // Encode "-MB-", in proper order.
  if (test_Silent_MB_1())
  {
    if (test_Pronounced_MB())
      m_current++;
    else
      m_current += 2;
  }
  else if (test_Silent_MB_2())
  {
    if (test_Pronounced_MB_2())
      m_current++;
    else
      m_current += 2;
  }
  else if (test_MN())
    m_current += 2;
  else
  {
    // Eat redundant 'M'.
    if (charAt(m_current+1) == 'M')
      m_current += 2;
    else
      m_current++;
  }
}
  
 
void Metaphone3::encode_N()
{
  // Encode "-N-".
  if (encode_NCE())
    return;

  // Eat redundant 'N'.
  if (charAt(m_current+1) == 'N')
    m_current += 2;
  else
    m_current++;

  if (! stringAt(m_current-3, 8, "MONSIEUR") &&
      ! stringAt(m_current-3, 6, "NENESS")) // e.g. "aloneness",
    add("N");
}


bool Metaphone3::encode_NCE()
{
  // Encode "-NCE-" and "-NSE-".
  // "entrance" is pronounced exactly the same as "entrants"
  // 'acceptance', 'accountancy'.
  if (stringAt(m_current+1, 1, "C", "S") &&
      stringAt((m_current + 2), 1, "E", "Y", "I") &&
      (m_current+2 == m_last ||
      (m_current+3 == m_last && charAt(m_current+3) == 'S')))
  {
    add("NTS");
    m_current += 2;
    return true;
  }
  else
  return false;
}


void Metaphone3::encode_P()
{
  // Encode "-P-".
  if (encode_Silent_P_At_Beginning() || 
      encode_PT() || 
      encode_PH() || 
      encode_PPH() || 
      encode_RPS() || 
      encode_COUP() || 
      encode_PNEUM() || 
      encode_PSYCH() || 
      encode_PSALM())
    return;

  encode_PB();
  add("P");
}


bool Metaphone3::encode_Silent_P_At_Beginning()
{
  // Encode /skip cases where "-P-" is silent at the start of a word.
  if (m_current == 0 && stringAt(0, 2, "PN", "PF", "PS", "PT"))
  {
    m_current += 1;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_PT()
{
  // Encode cases where "-P-" is silent before "-T-":
  // 'pterodactyl', 'receipt', 'asymptote'.
  if ((charAt(m_current+1) == 'T'))
  {
    if ((m_current == 0 && stringAt(0, 5, "PTERO")) || 
        stringAt(m_current-5, 7, "RECEIPT") || 
        stringAt(m_current-4, 8, "ASYMPTOT"))
    {
      add("T");
      m_current += 2;
      return true;
    }
  }
  return false;
}


bool Metaphone3::encode_PH()
{
  // Encode "-PH-", usually as F, with exceptions for cases where it 
  // is silent, or where the 'P' and 'T' are pronounced separately 
  // because they belong to two different words in a combining form.
  if (charAt(m_current+1) == 'H')
  {
    if (stringAt(m_current, 9, "PHTHALEIN") || 
        (m_current == 0 && stringAt(0, 4, "PHTH")) || 
        stringAt(m_current-3, 10, "APOPHTHEGM"))
    {
      // 'PH' silent in these contexts.
      add("0");
      m_current += 4;
    }
    // Combining forms: 'sheepherd', 'upheaval', 'cupholder'.
    else if (m_current > 0 && 
        (stringAt(m_current+2, 3, "EAD", "OLE", "ELD", "ILL", 
          "OLD", "EAP", "ERD", "ARD", "ANG", "ORN", "EAV", "ART") || 
         stringAt(m_current+2, 4, "OUSE") || 
         (stringAt(m_current+2, 2, "AM") && 
          ! stringAt(m_current-1, 5, "LPHAM")) || 
         stringAt(m_current+2, 5, "AMMER", "AZARD", "UGGER") || 
         (stringAt(m_current+2, 6, "OLSTER")) && 
          ! stringAt(m_current-3, 5, "LYMPH", "NYMPH")))
    {
      add("P");
      advanceCounter(3, 2);
    }
    else
    {
      add("F");
      m_current += 2;
    }
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_PPH()
{
  // Encode "-PPH-". I don't know why the Greek poet's
  // name is transliterated this way...: 'sappho'.
  if (m_current+2 < m_length && 
      charAt(m_current+1) == 'P' && 
      charAt(m_current+2) == 'H')
      // TODO shein: can write as stringAt(m_current, 2, "PH")?
  {
    add("F");
    m_current += 3;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_RPS()
{
  // Encode "-CORPS-" where "-PS-" not pronounced, since the 
  // cognate is here from the french: '-corps-', 'corpsman'.
  if (stringAt(m_current-3, 5, "CORPS") && 
      ! stringAt(m_current-3, 6, "CORPSE"))
  {
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_COUP()
{
  // Encode "-COUP-" where "-P-" is not pronounced, since the word 
  // is from the French 'coup'.
  if (m_current == m_last && 
      stringAt(m_current-3, 4, "COUP") && 
      ! stringAt(m_current-5, 6, "RECOUP"))
  {
    m_current++;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_PNEUM()
{
  // Encode 'P' in non-initial contexts of "-PNEUM-" where it is also 
  // silent.
  if (stringAt(m_current+1, 4, "NEUM"))
  {
    add("N");
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_PSYCH()
{
  // Encode special case "-PSYCH-" where two encodings need to be
  // accounted for in one syllable, one for the 'PS' and one for
  // the 'CH'.
  if (stringAt(m_current+1, 4, "SYCH"))
  {
    add(m_encodeVowels ? "SAK" : "SK");
    m_current += 5;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_PSALM()
{
  // Encode 'P' in context of "-PSALM-", where it has become silent.
  if (stringAt(m_current+1, 4, "SALM"))
  {
    add(m_encodeVowels ? "SAM" : "SM");
    m_current += 5;
    return true;
  }
  else
    return false;
}


void Metaphone3::encode_PB()
{
  // Eat redundant 'B' or 'P', e.g. "campbell", "raspberry".
  if (stringAt(m_current+1, 1, "P", "B"))
    m_current += 2;
  else
    m_current++;
}


void Metaphone3::encode_Q()
{
  // Encode "-Q-": current Pinyin.
  if (stringAt(m_current, 3, "QIN"))
  {
    add("X");
    m_current++;
    return;
  }

  // Eat redundant 'Q'.
  if (charAt(m_current+1) == 'Q')
    m_current += 2;
  else
    m_current++;

  add("K");
}


void Metaphone3::encode_R()
{
  // Encode "-R-".
  if (encode_RZ())
    return;

  if (! test_Silent_R() &&
      ! encode_Vowel_RE_Transposition())
    add("R");

  // Eat redundant 'R'; also skip 'S' as well as 'R' in "poitiers".
  if (charAt(m_current+1) == 'R' || 
      stringAt(m_current-6, 8, "POITIERS"))
    m_current += 2;
  else
    m_current++;
}


bool Metaphone3::encode_RZ()
{
  // Encode "-RZ-" according to American and Polish pronunciations.
  if (stringAt(m_current-2, 4, "GARZ", "KURZ", "MARZ", "MERZ", 
    "HERZ", "PERZ", "WARZ") ||
      stringAt(m_current, 5, "RZANO", "RZOLA") ||
      stringAt(m_current-1, 4, "ARZA", "ARZN"))
  {
    return false;
  }

  // 'YASTRZEMSKI' usually has 'z' silent in United States, 
  // but should get 'X' in Poland.
  if (stringAt(m_current-4, 11, "YASTRZEMSKI"))
  {
    add("R", "X");
    m_current += 2;
    return true;
  }

  // 'BRZEZINSKI' gets two pronunciations in the United States, 
  // neither of which are authentically Polish.
  if (stringAt(m_current-1, 10, "BRZEZINSKI"))
  {
    // Skip over second 'Z'.
    add("RS", "RJ");
    m_current += 4;
    return true;
  }

  // 'z' in 'rz' after voiceless consonant gets 'X'
  // in alternate Polish style pronunciation
  if (stringAt(m_current-1, 3, "TRZ", "PRZ", "KRZ") ||
     (stringAt(m_current, 2, "RZ") && 
       (isVowel(m_current-1) || m_current == 0)))
  {
    add("RS", "X");
    m_current += 2;
    return true;
  }

  // 'z' in 'rz after voiceled consonant, vowel, or at
  // beginning gets 'J' in alternate Polish style pronunciation.
  if (stringAt(m_current-1, 3, "BRZ", "DRZ", "GRZ"))
  {
    add("RS", "J");
    m_current += 2;
    return true;
  }

  return false;
}


bool Metaphone3::test_Silent_R()
{
  // Test whether 'R' is silent in this context, either because the
  // word is from the French or because it is no longer pronounced,
  // e.g. "rogier", "monsieur", "surburban".
  if ((m_current == m_last &&
       // Reliably French word ending.
       stringAt(m_current-2, 3, "IER") &&
       (stringAt(m_current-5, 3, "MET", "VIV", "LUC") ||
        stringAt(m_current-6, 4, "CART", "DOSS", "FOUR", "OLIV", "BUST", 
          "DAUM", "ATEL", "SONN", "CORM", "MERC", "PELT", "POIR", 
          "BERN", "FORT", "GREN", "SAUC", "GAGN", "GAUT", "GRAN", 
          "FORC", "MESS", "LUSS", "MEUN", "POTH", "HOLL", "CHEN") ||
        stringAt(m_current-7, 5, "CROUP", "TORCH", "CLOUT", "FOURN", 
          "GAUTH", "TROTT", "DEROS", "CHART") ||
        stringAt(m_current-8, 6, "CHEVAL", "LAVOIS", "PELLET", 
          "SOMMEL", "TREPAN", "LETELL", "COLOMB") ||
        stringAt(m_current-9, 7, "CHARCUT") ||
        stringAt(m_current-10, 8, "CHARPENT"))) ||
      stringAt(m_current-2, 7, "SURBURB", "WORSTED") ||
      stringAt(m_current-2, 9, "WORCESTER") ||
      stringAt(m_current-7, 8, "MONSIEUR") ||
      stringAt(m_current-6, 8, "POITIERS") )
  {
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_Vowel_RE_Transposition()
{
  // Encode '-re-" as 'AR' in contexts where this is the correct 
  // pronunciation.
  // -re inversion is just like -le inversion, e.g. 
  // "fibre" => FABAR or "centre" => SANTAR.
  if (m_encodeVowels && 
      m_length > 3 && 
      charAt(m_current+1) == 'E' && 
      ! stringAt(0, 5, "OUTRE", "LIBRE", "ANDRE") && 
      ! (m_length == 4 && stringAt(0, 4, "FRED", "TRES")) && 
      ! stringAt(m_current-2, 5, "LDRED", "LFRED", "NDRED", "NFRED", 
          "NDRES", "TRES", "IFRED") && 
      ! isVowel(m_current-1) && 
      (m_current+1 == m_last || 
      (m_current+2 == m_last && stringAt(m_last, 1, "D", "S"))))
  {
    add("AR");
    return true;
  }
  else
    return false;
}


void Metaphone3::encode_S()
{
  // Encode "-S-".
  if (encode_SKJ() || 
      encode_Special_SW() || 
      encode_SJ() || 
      encode_Silent_French_S_Final() || 
      encode_Silent_French_S_Internal() || 
      encode_ISL() || 
      encode_STL() || 
      encode_Christmas() || 
      encode_STHM() || 
      encode_ISTEN() || 
      encode_Sugar() || 
      encode_SH() || 
      encode_SCH() || 
      encode_SUR() || 
      encode_SU() || 
      encode_SSIO() || 
      encode_SS() || 
      encode_SIA() || 
      encode_SIO() || 
      encode_Anglicisations() || 
      encode_SC() || 
      encode_SEA_SUI_SIER() || 
      encode_SEA())
    return;

  add("S");

  if (stringAt(m_current+1, 1, "S", "Z") && 
      ! stringAt(m_current+1, 2, "SH"))
    m_current += 2;
  else
    m_current++;
}


bool Metaphone3::encode_Special_SW()
{
  // Encode a couple of contexts where Scandinavian, Slavic
  // or German names should get an alternate, native
  // pronunciation of 'SV' or 'XV'.
  if (m_current == 0)
  {
    if (names_Beginning_With_SW_That_Get_Alt_SV())
    {
      add("S", "SV");
      m_current += 2;
      return true;
    }

    if (names_Beginning_With_SW_That_Get_Alt_XV())
    {
      add("S", "XV");
      m_current += 2;
      return true;
    }
  }
  return false;
}


bool Metaphone3::encode_SKJ()
{
  // Encode "-SKJ-" as X ("sh"), since Americans pronounce
  // the Scandinavian name Dag Hammerskjold as "hammer-shold".
  if (stringAt(m_current, 4, "SKJO", "SKJU") && isVowel(m_current+3))
  {
    add("X");
    m_current += 3;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_SJ()
{
  // Encode initial swedish "SJ-" as X ("sh").
  if (stringAt(0, 2, "SJ"))
  {
    add("X");
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_Silent_French_S_Final()
{
  // Encode final 'S' in words from the French, where they
  // are not pronounced.
  // "louis" is an exception because it gets two pronunciations.
  if (m_current != m_last)
    return false;

  if (stringAt(0, 5, "LOUIS"))
  {
    add("S", "");
    m_current++;
    return true;
  }

  // French words familiar to Americans where final s is silent.
  if (stringAt(0, 4, "YVES") ||
      (m_current == 3 && stringAt(0, 4, "HORS")) ||
      stringAt(m_current-4, 5, "CAMUS", "YPRES") ||
      stringAt(m_current-5, 6, "MESNES", "DEBRIS", "BLANCS", "INGRES", 
        "CANNES") ||
      stringAt(m_current-6, 7, "CHABLIS", "APROPOS", "JACQUES", 
        "ELYSEES", "OEUVRES", "GEORGES", "DESPRES") ||
      stringAt(0, 8, "ARKANSAS", "FRANCAIS", "CRUDITES", "BRUYERES") ||
      stringAt(0, 9, "DESCARTES", "DESCHUTES", "DESCHAMPS", 
        "DESROCHES", "DESCHENES") ||
      stringAt(0, 10, "RENDEZVOUS") ||
      stringAt(0, 11, "CONTRETEMPS", "DESLAURIERS") ||
      (stringAt(m_current-2, 2, "AI", "OI", "UI") &&
       ! stringAt(0, 4, "LOIS", "LUIS")))
  {
    m_current++;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_Silent_French_S_Internal()
{
  // Encode non-final 'S' in words from the French where they
  // are not pronounced.
  if (stringAt(m_current-2, 9, "DESCARTES") || 
      stringAt(m_current-2, 7, "DESCHAM", "DESPRES", "DESROCH", 
        "DESROSI", "DESJARD", "DESMARA", "DESCHEN", "DESHOTE", 
        "DESLAUR") || 
      stringAt(m_current-2, 6, "MESNES") || 
      stringAt(m_current-5, 8, "DUQUESNE", "DUCHESNE") || 
      stringAt(m_current-7, 10, "BEAUCHESNE") || 
      stringAt(m_current-3, 7, "FRESNEL") || 
      stringAt(m_current-3, 9, "GROSVENOR") || 
      stringAt(m_current-4, 10, "LOUISVILLE") || 
      stringAt(m_current-7, 10, "ILLINOISAN"))
  {
    m_current++;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_ISL()
{
  // Encode silent 'S' in context of "-ISL-":
  // Special cases 'island', 'isle', 'carlisle', 'carlysle'.
  if ((stringAt(m_current-2, 4, "LISL", "LYSL", "AISL") && 
     ! stringAt(m_current-3, 7, "PAISLEY", "BAISLEY", "ALISLAM", 
       "ALISLAH", "ALISLAA")) || 
      (m_current == 1 && 
      ((stringAt(0, 4, "ISLE") || stringAt(0, 5, "ISLAN")) && 
      ! stringAt(0, 5, "ISLEY", "ISLER"))))
  {
    m_current++;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_STL()
{
  // Encode "-STL-" in contexts where the 'T' is silent. Also
  // encode "-USCLE-" in contexts where the 'C' is silent.
  // 'hustle', 'bustle', 'whistle'
  if ((stringAt(m_current, 4, "STLE", "STLI") &&
       ! stringAt(m_current+2, 4, "LESS", "LIKE", "LINE")) ||
      stringAt(m_current-3, 7, "THISTLY", "BRISTLY",  "GRISTLY") ||
      // E.g. "corpuscle"
      stringAt(m_current-1, 5, "USCLE"))
  {
    // KRISTEN, KRYSTLE, CRYSTLE, KRISTLE all pronounce the 't'.
    // Also, exceptions where "-LING" is a nominalizing suffix.
    if (stringAt(0, 7, "KRISTEN", "KRYSTLE", "CRYSTLE", "KRISTLE") ||
        stringAt(0, 11, "CHRISTENSEN", "CHRISTENSON") ||
        stringAt(m_current-3, 9, "FIRSTLING") ||
        stringAt(m_current-2, 8,  "NESTLING",  "WESTLING"))
    {
      add("ST");
      m_current += 2;
    }
    else if (m_encodeVowels &&
        charAt(m_current+3) == 'E' &&
        charAt(m_current+4) != 'R' &&
        ! stringAt(m_current+3, 4, "ETTE", "ETTA") &&
        ! stringAt(m_current+3, 2, "EY"))
    {
      add("SAL");
      flag_AL_inversion = true;
      m_current += 3;
    }
    else
    {
      add("SL");
      m_current += 3;
    }
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_Christmas()
{
  // Encode "christmas". Americans always pronounce this as "krissmuss".
  if (stringAt(m_current-4, 8, "CHRISTMA"))
  {
    add("SM");
    m_current += 3;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_STHM()
{
  // Encode "-STHM-" in contexts where the 'TH' is silent.
  if (stringAt(m_current, 4, "STHM"))
  {
    add("SM");
    m_current += 4;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_ISTEN()
{
  // Encode "-ISTEN-" and "-STNT-" in contexts where the 'T' is silent.
  // 't' is silent in verb, pronounced in name
  if (stringAt(0, 8, "CHRISTEN"))
  {
    // The word itself.
    if (rootOrInflections(m_inWord, "CHRISTEN") || 
        stringAt(0, 11, "CHRISTENDOM"))
      add("S", "ST");
    else
      add("ST"); // e.g. 'christenson', 'christene'

    m_current += 2;
    return true;
  }

  // e.g. 'glisten', 'listen'
  if (stringAt(m_current-2, 6, "LISTEN", "RISTEN", "HASTEN", "FASTEN", 
        "MUSTNT") ||
      stringAt(m_current-3, 7,  "MOISTEN"))
  {
    add("S");
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_Sugar()
{
  // Encode special case "sugar".
  if (stringAt(m_current, 5, "SUGAR"))
  {
    add("X");
    m_current++;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_SH()
{
  // Encode "-SH-" as X ("sh"), except in cases where the 'S' and 'H' 
  // belong to different combining * roots and are therefore pronounced 
  // separately.
  if (stringAt(m_current, 2, "SH"))
  {
    // Exception.
    if (stringAt(m_current-2, 8, "CASHMERE"))
    {
      add("J");
      m_current += 2;
      return true;
    }

    // Combining forms, e.g. 'clotheshorse', 'woodshole'.
    if (m_current == 0)
      add("X");
    else if ((m_current+3 == m_last && stringAt(m_current+1, 3, "HAP")) ||
        // E.g. "mishap" (above), "hartsheim", "clothshorse"
        stringAt(m_current+1, 4, "HEIM", "HOEK", "HOLM", "HOLZ", "HOOD", 
          "HEAD", "HEID", "HAAR", "HORS", "HOLE", "HUND", "HELM", "HAWK", 
          "HILL") ||
        // E.g. "dishonor"
        stringAt(m_current+1, 5, "HEART", "HATCH", "HOUSE", "HOUND", 
          "HONOR") ||
        // E.g. "mishear"
        (m_current+4 == m_last && stringAt(m_current+2, 3, "EAR")) ||
        // E.g. "hartshorn"
        (stringAt(m_current+2, 3, "ORN") && 
         ! stringAt(m_current-2, 7, "UNSHORN")) ||
        // E.g. "newshour" but not "bashour", "manshour".
        (stringAt(m_current+1, 4, "HOUR") &&
         ! stringAt(0, 7, "BASHOUR") &&
         ! stringAt(0, 8, "MANSHOUR") && 
         ! stringAt(0, 6, "ASHOUR")) ||
        // E.g. "dishonest", "grasshopper"
        stringAt(m_current+2, 5, "ARMON", "ONEST", "ALLOW", "OLDER", 
          "OPPER", "EIMER", "ANDLE", "ONOUR") ||
        // E.g. "dishabille", "transhumance".
        stringAt(m_current+2, 6, "ABILLE", "UMANCE", "ABITUA"))
    {
      if (! stringAt(m_current-1, 1, "S"))
        add("S");
    }
    else
      add("X");

    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_SCH()
{
  // Encode "-SCH-" in cases where the 'S' is pronounced
  // separately from the "CH", in words from the Dutch, Italian,
  // and Greek where it can be pronounced SK, and German words
  // these words were combining forms many centuries ago
  if (stringAt(m_current+1, 2, "CH"))
  {
    if (m_current > 0 &&
        // E.g. "mischief", "escheat"
        (stringAt(m_current+3, 3, "IEF", "EAT") ||
          // E.g. "mischance"
          stringAt(m_current+3, 4, "ANCE", "ARGE") ||
          // E.g. "eschew"
          stringAt(0, 6, "ESCHEW")))
    {
      add("S");
      m_current++;
      return true;
    }

    // Schlesinger's rule:
    // Dutch, Danish, Italian, Greek origin, e.g. "school", "schooner", 
    // "schiavone", "schiz-".
    if ((stringAt(m_current+3, 2, "OO", "ER", "EN", "UY", "ED", "EM", 
          "IA", "IZ", "IS", "OL") &&
        ! stringAt(m_current, 6, "SCHOLT", "SCHISL", "SCHERR")) ||
        stringAt(m_current+3, 3, "ISZ") ||
        (stringAt(m_current-1, 6, "ESCHAT", "ASCHIN", "ASCHAL", "ISCHAE", 
          "ISCHIA") &&
         ! stringAt(m_current-2, 8, "FASCHING")) ||

        (m_current+3 == m_last && stringAt(m_current-1, 5, "ESCHI")) ||
        charAt(m_current+3) == 'Y')
    {
      // E.g. "schermerhorn", "schenker", "schistose"
      if (stringAt(m_current+3, 2, "ER", "EN", "IS") &&
          (m_current+4 == m_last ||
           stringAt(m_current+3, 3, "ENK", "ENB", "IST")))
      {
        add("X", "SK");
      }
      else
        add("SK");

      m_current += 3;
      return true;
    }
    else
    {
      add("X");
      m_current += 3;
      return true;
    }
  }
  else
    return false;
}


bool Metaphone3::encode_SUR()
{
  // Encode "-SUR<E,A,Y>-" to J, unless it is at the beginning,
  // or preceeded by 'N', 'K', or "NO": 'erasure', 'usury'.
  if (stringAt(m_current+1, 3, "URE", "URA", "URY"))
  {
    // E.g. 'sure', 'ensure'
    if (m_current == 0 ||
        stringAt(m_current-1, 1, "N", "K") ||
        stringAt(m_current-2, 2, "NO"))
      add("X");
    else
      add("J");

    advanceCounter(2, 1);
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_SU()
{
  // Encode "-SU<O,A>-" to X ("sh") unless it is preceded by
  // an 'R', in which case it is encoded to S, or it is
  // preceded by a vowel, in which case it is encoded to J:
  // 'sensuous', 'consensual'.
  if (m_current != 0 && stringAt(m_current+1, 2, "UO", "UA"))
  {
    // Exceptions e.g. "persuade".
    if (stringAt(m_current-1, 4, "RSUA"))
      add("S");
    // Exceptions e.g. "casual"
    else if (isVowel(m_current-1))
      add("J", "S");
    else
      add("X", "S");

    advanceCounter(3, 1);
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_SSIO()
{
  // Encode "-SSIO-" in contexts where it is pronounced
  // either J or X ("sh").
  if (stringAt(m_current+1, 4, "SION"))
  {
    if (stringAt(m_current-2, 2, "CI"))
      add("J"); // "Abcission"
    else if (isVowel(m_current-1))
      add("X"); // 'Mission'

    advanceCounter(4, 2);
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_SS()
{
  // Encode "-SS-" in contexts where it is pronounced X ("sh"),
  // e.g. "russian", "pressure".
  if (stringAt(m_current-1, 5, "USSIA", "ESSUR", "ISSUR", "ISSUE") ||
      // e.g. "hessian", "assurance"
      stringAt(m_current-1, 6, "ESSIAN", "ASSURE", "ASSURA", 
        "ISSUAB", "ISSUAN", "ASSIUS"))
  {
    add("X");
    advanceCounter(3, 2);
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_SIA()
{
  // Encodes "-SIA-" in contexts where it is pronounced
  // as X ("sh"), J, or S: "controversial", also "fuchsia", 
  // "ch" is silent.
  if (stringAt(m_current-2, 5, "CHSIA") ||
      stringAt(m_current-1, 5, "RSIAL"))
  {
    add("X");
    advanceCounter(3, 1);
    return true;
  }

  // Names generally get 'X' where terms, e.g. "aphasia" get 'J'.
  if ((m_current == 3 &&
       stringAt(0, 6, "ALESIA", "ALYSIA", "ALISIA", "STASIA") &&
       ! stringAt(0, 9, "ANASTASIA")) ||
      stringAt(m_current-5, 9, "DIONYSIAN") ||
      stringAt(m_current-5, 8, "THERESIA"))
  {
    add("X", "S");
    advanceCounter(3, 1);
    return true;
  }

  if ((m_current+2 == m_last && stringAt(m_current, 3, "SIA")) ||
      (m_current+3 == m_last && stringAt(m_current, 4, "SIAN")) ||
      stringAt(m_current-5, 9, "AMBROSIAL"))
  {
    if ((isVowel(m_current-1) || stringAt(m_current-1, 1, "R")) &&
        // Exclude compounds based on names, or French or Greek words.
        ! stringAt(0, 5, "JAMES", "NICOS", "PEGAS", "PEPYS") &&
        ! stringAt(0, 6, "HOBBES", "HOLMES", "JAQUES", "KEYNES") &&
        ! stringAt(0, 7, "MALTHUS", "HOMOOUS") &&
        ! stringAt(0, 8, "MAGLEMOS", "HOMOIOUS") &&
        ! stringAt(0, 9, "LEVALLOIS", "TARDENOIS") &&
        ! stringAt(m_current-4, 5, "ALGES"))
      add("J");
    else
      add("S");

    advanceCounter(2, 1);
    return true;
  }
  return false;
}


bool Metaphone3::encode_SIO()
{
  // Encode "-SIO-" in contexts where it is pronounced as J or X ("sh").
  // Special case, irish name
  if (stringAt(0, 7, "SIOBHAN"))
  {
    add("X");
    advanceCounter(3, 1);
    return true;
  }

  if (stringAt(m_current+1, 3, "ION"))
  {
    if (isVowel(m_current-1) || stringAt(m_current-2, 2, "ER", "UR"))
      add("J"); // E.g. "vision", "version".
    else 
      add("X"); // E.g. "declension"

    advanceCounter(3, 1);
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_Anglicisations()
{
  // Encode cases where "-S-" might well be from a German name
  // and add encoding of German pronounciation in alternate m_metaph
  // so that it can be found in a genealogical search,
  // e.g. 'smith' match 'schmidt', 'snider' match 'schneider'.
  // Also, -sz- in Slavic language although in Hungarian it is 
  // pronounced 's'.
  if ((m_current == 0 && stringAt(1, 1, "M", "N", "L")) ||
       stringAt(m_current+1, 1, "Z"))
  {
    add("S", "X");

    // Eat redundant 'Z'
    if (stringAt(m_current+1, 1, "Z"))
      m_current += 2;
    else
      m_current++;

    return true;
  }
  else
    return false;
}

   
bool Metaphone3::encode_SC()
{
  // Encode "-SC<vowel>-" in contexts where it is silent,
  // or pronounced as X ("sh"), S, or SK
  if (stringAt(m_current, 2, "SC"))
  {
    // Exception 'viscount'.
    if (stringAt(m_current-2, 8, "VISCOUNT"))
    {
      m_current += 1;
      return true;
    }

    // Encode "-SC<front vowel>-".
    if (stringAt(m_current+2, 1, "I", "E", "Y"))
    {
      if (stringAt(m_current+2, 4, "IOUS") ||
          // e.g. "conscious" (above), "prosciutto".
          stringAt(m_current+2, 3, "IUT") ||
          stringAt(m_current-4, 9, "OMNISCIEN") ||
          stringAt(m_current-3, 8, "CONSCIEN", "CRESCEND", "CONSCION") ||
          stringAt(m_current-2, 6, "FASCIS"))
      {
        add("X");
      }
      else if (stringAt(m_current, 7, "SCEPTIC", "SCEPSIS") ||
          stringAt(m_current, 5, "SCIVV", "SCIRO") ||
          // commonly pronounced this way in U.S.
          stringAt(m_current, 6, "SCIPIO") ||
          stringAt(m_current-2, 10, "PISCITELLI"))
      {
        add("SK");
      }
      else
        add("S");

      m_current += 2;
      return true;
    }

    add("SK");
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_SEA_SUI_SIER()
{
  // Encode "-S<EA,UI,IER>-" in contexts where it is pronounced
  // as J.  "Nausea" by itself has => NJ as a more likely encoding. 
  // Other forms using "nause-" (see encode_SEA()) have X or S as more 
  // familiar pronunciations.
  if ((m_current+2 == m_last && stringAt(m_current-3, 6, "NAUSEA")) ||
      // E.g. "casuistry", "frasier", "hoosier"
      stringAt(m_current-2, 5, "CASUI") ||
      (stringAt(m_current-1, 5, "OSIER", "ASIER") &&
        ! (stringAt(0, 6, "EASIER") ||
           stringAt(0, 5, "OSIER") ||
           stringAt(m_current-2, 6, "ROSIER", "MOSIER"))))
  {
    add("J", "X");
    advanceCounter(3, 1);
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_SEA()
{
  // Encode cases where "-SE-" is pronounced as X ("sh").
  if ((m_current+3 == m_last && stringAt(0, 4, "SEAN")) ||
      (stringAt(m_current-3, 6, "NAUSEO") &&
       ! stringAt(m_current-3, 7, "NAUSEAT")))
  {
    add("X");
    advanceCounter(3, 1);
    return true;
  }
  else
    return false;
}

void Metaphone3::encode_T()
{
  // Encode "-T-".
  if (encode_T_Initial() ||
      encode_TCH() ||
      encode_Silent_French_T() ||
      encode_TUN_TUL_TUA_TUO() ||
      encode_TUE_TEU_TEOU_TUL_TIE() ||
      encode_TUR_TIU_Suffixes() ||
      encode_TI() ||
      encode_TIENT() ||
      encode_TSCH() ||
      encode_TZSCH() ||
      encode_TH_Pronounced_Separately() ||
      encode_TTH() ||
      encode_TH())
    return;

  // Eat redundant 'T' or 'D'.
  if (stringAt(m_current+1, 1, "T", "D"))
    m_current += 2;
  else
    m_current++;

  add("T");
}


bool Metaphone3::encode_T_Initial()
{
  // Encode some exceptions for initial 'T'.
  if (m_current != 0)
    return false;

  // Americans usually pronounce "tzar" as "zar".
  if (stringAt(m_current+1, 3, "SAR", "ZAR"))
  {
    m_current++;
    return true;
  }

  // Old 'École française d'Extręme-Orient' Chinese Pinyin where 
  // 'ts-' => 'X'.
  if ((m_length == 3 && stringAt(m_current+1, 2, "SO", "SA", "SU")) ||
      (m_length == 4 && stringAt(m_current+1, 3, "SAO", "SAI")) ||
      (m_length == 5 && stringAt(m_current+1, 4, "SING", "SANG")))
  {
    add("X");
    advanceCounter(3, 2);
    return true;
  }

  // "TS<vowel>-" at start can be pronounced both with and without 'T'.
  if (stringAt(m_current+1, 1, "S") && isVowel(m_current+2))
  {
    add("TS", "S");
    advanceCounter(3, 2);
    return true;
  }

  // E.g. "Tjaarda"
  if (stringAt(m_current+1, 1, "J"))
  {
    add("X");
    advanceCounter(3, 2);
    return true;
  }

  // Cases where initial "TH-" is pronounced as T and not 0 ("th").
  if ((m_length == 3 && stringAt(m_current+1, 2, "HU")) ||
      stringAt(m_current+1, 3, "HAI", "HUY", "HAO") ||
      stringAt(m_current+1, 4, "HYME", "HYMY", "HANH") ||
      stringAt(m_current+1, 5, "HERES"))
  {
    add("T");
    advanceCounter(3, 2);
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_TCH()
{
  // Encode "-TCH-", reliably X ("sh", or in this case, "ch").
  if (stringAt(m_current+1, 2, "CH"))
  {
    add("X");
    m_current += 3;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_Silent_French_T()
{
  // Encode the many cases where Americans are aware that a certain 
  // word is French and know to not pronounce the 'T'.
  if ((m_current == m_last && 
      (stringAt(m_current-4, 5, "MONET", "GENET", "CHAUT")) ||
       stringAt(m_current-2, 9, "POTPOURRI") ||
       stringAt(m_current-3, 9, "BOATSWAIN") ||
       stringAt(m_current-3, 8, "MORTGAGE") ||
       stringAt(m_current-4, 5, "BERET", "BIDET", "FILET", "DEBUT", 
         "DEPOT", "PINOT", "TAROT") ||
       stringAt(m_current-5, 6, "BALLET", "BUFFET", "CACHET", 
         "CHALET", "ESPRIT", "RAGOUT", "GOULET", "CHABOT", "BENOIT") ||
       stringAt(m_current-6, 7, "GOURMET", "BOUQUET", "CROCHET", 
         "CROQUET", "PARFAIT", "PINCHOT", "CABARET", "PARQUET", 
         "RAPPORT", "TOUCHET", "COURBET", "DIDEROT") ||
       stringAt(m_current-7, 8, "ENTREPOT", "CABERNET", "DUBONNET", 
         "MASSENET", "MUSCADET", "RICOCHET", "ESCARGOT") ||
       stringAt(m_current-8, 9, "SOBRIQUET", "CABRIOLET", "CASSOULET", 
         "OUBRIQUET", "CAMEMBERT")) &&
      ! stringAt(m_current+1, 2, "AN", "RY", "IC", "OM", "IN"))
  {
    m_current++;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_TUN_TUL_TUA_TUO()
{
  // Encode "-TU<N,L,A,O>-" in cases where it is pronounced
  // X ("sh", or in this case, "ch"). E.g. "fortune", "fortunate".
  if (stringAt(m_current-3, 6, "FORTUN") ||
      // E.g. "capitulate"
      (stringAt(m_current, 3, "TUL") &&
        isVowel(m_current-1) && isVowel(m_current+3)) ||
      // E.g. "obituary", "barbituate"
      stringAt(m_current-2, 5, "BITUA", "BITUE") ||
      // e.g. "actual"
      (m_current > 1 && stringAt(m_current, 3, "TUA", "TUO")))
  {
    add("X", "T");
    m_current++;
    return true;
  }
  else
    return false;
}

bool Metaphone3::encode_TUE_TEU_TEOU_TUL_TIE()
{
  // Encode "-T<vowel>-" forms where 'T' is pronounced as X
  // ("sh", or in this case "ch"): 'constituent', 'pasteur'.
  if (stringAt(m_current+1, 4, "UENT") ||
      stringAt(m_current-4, 9, "RIGHTEOUS") ||
      stringAt(m_current-3, 7, "STATUTE") ||
      stringAt(m_current-3, 7, "AMATEUR") ||
      // E.g. "blastula", "pasteur"
      stringAt(m_current-1, 5, "NTULE", "NTULA", "STULE", "STULA", 
        "STEUR") ||
      // E.g. "statue"
      (m_current+2 == m_last && stringAt(m_current, 3, "TUE")) ||
      // E.g. "constituency"
      stringAt(m_current, 5, "TUENC") ||
      // E.g. "statutory"
      stringAt(m_current-3, 8, "STATUTOR") ||
      // E.g. "patience"
      (m_current+5 == m_last && stringAt(m_current, 6, "TIENCE")))
  {
    add("X", "T");
    advanceCounter(2, 1);
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_TUR_TIU_Suffixes()
{
  // Encode "-TU-" forms in suffixes where it is usually
  // pronounced as X ("sh"): 'adventure', 'musculature'.
  if (m_current > 0 && 
     stringAt(m_current+1, 3, "URE", "URA", "URI", "URY", "URO", "IUS"))
  {
    // Exceptions e.g. 'tessitura', mostly from Romance languages.
    if ((m_current+3 == m_last &&
        stringAt(m_current+1, 3, "URA", "URO") &&
        ! stringAt(m_current-3, 7, "VENTURA")) ||
        // E.g. "kachaturian", "hematuria"
        stringAt(m_current+1, 4, "URIA"))
      add("T");
    else
      add("X", "T");

    advanceCounter(2, 1);
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_TI()
{
  // Encode "-TI<O,A,U>-" as X ("sh"), except in cases where it is 
  // part of a combining form, or as J: '-tio-', '-tia-', '-tiu-'.
  // Except combining forms where T already pronounced e.g 
  // 'rooseveltian'.
  if ((stringAt(m_current+1, 2, "IO") && 
       ! stringAt(m_current-1, 5, "ETIOL")) ||
      stringAt(m_current+1, 3, "IAL") ||
      stringAt(m_current-1, 5, "RTIUM", "ATIUM") ||

      ((m_current > 0 && stringAt(m_current+1, 3, "IAN")) &&
       ! stringAt((m_current - 4), 8, "FAUSTIAN") &&
       ! stringAt((m_current - 5), 9, "PROUSTIAN") &&
       ! stringAt((m_current - 2), 7, "TATIANA") &&
       ! stringAt((m_current - 3), 7, "KANTIAN", "GENTIAN") &&
       ! stringAt((m_current - 8), 12, "ROOSEVELTIAN")) ||

      (m_current+2 == m_last &&
       stringAt(m_current, 3, "TIA") &&
       // Exceptions where the pronounciation is usually X.
       ! stringAt(m_current-3, 6, "HESTIA", "MASTIA") &&
       ! stringAt(m_current-2, 5, "OSTIA") &&
       ! stringAt(0, 3, "TIA") &&
       ! stringAt(m_current-5, 8, "IZVESTIA")) ||

      stringAt(m_current+1, 4, "IATE", "IATI", "IABL", "IATO", "IARY") ||
      stringAt(m_current-5, 9, "CHRISTIAN"))
  {
    if ((m_current == 2 && stringAt(0, 4, "ANTI")) ||
        stringAt(0, 5, "PATIO", "PITIA", "DUTIA"))
      add("T");
    else if (stringAt((m_current - 4), 8, "EQUATION"))
      add("J");
    else if (stringAt(m_current, 4, "TION"))
      add("X");
    else if (stringAt(0, 5, "KATIA", "LATIA"))
      add("T", "X");
    else
      add("X", "T");

    advanceCounter(3, 1);
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_TIENT()
{
  // Encode "-TIENT-" where "TI" is pronounced X ("sh"),
  // e.g. 'patient'
  if (stringAt(m_current+1, 4, "IENT"))
  {
    add("X", "T");
    advanceCounter(3, 1);
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_TSCH()
{
  // Encode "-TSCH-" as X ("ch"), e.g. 'deutsch'.
  if (stringAt(m_current, 4, "TSCH") &&
      // combining German forms where the 'T' is pronounced separately.
      ! stringAt(m_current- 3, 4, "WELT", "KLAT", "FEST"))
  {
    // Pronounced the same as "ch" in "chit" => X
    add("X");
    m_current += 4;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_TZSCH()
{
  // Encode "-TZSCH-" as X ("ch"): "Neitzsche is peachy".
  if (stringAt(m_current, 5, "TZSCH"))
  {
    add("X");
    m_current += 5;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_TH_Pronounced_Separately()
{
  // Encodes cases where the 'H' in "-TH-" is the beginning of
  // another word in a combining form, special cases where it is
  // usually pronounced as 'T', and a special case where it has
  // become pronounced as X ("sh", in this case "ch").
  // 'adulthood', 'bithead', 'apartheid'
  if ((m_current > 0 &&
       stringAt(m_current+1, 4, "HOOD", "HEAD", "HEID", "HAND", "HILL", 
         "HOLD", "HAWK", "HEAP", "HERD", "HOLE", "HOOK", "HUNT",
         "HUMO", "HAUS", "HOFF", "HARD") &&
       ! stringAt(m_current-3, 5, "SOUTH", "NORTH")) ||

      stringAt(m_current+1, 5, "HOUSE", "HEART", "HASTE", "HYPNO", 
         "HEQUE") ||

      // Watch out for greek root "-thallic".
      (m_current+4 == m_last &&
       stringAt(m_current+1, 4, "HALL") &&
       ! stringAt(m_current-3, 5, "SOUTH", "NORTH")) ||

      (m_current+3 == m_last &&
       stringAt(m_current+1, 3, "HAM") &&
       ! stringAt(0, 6, "GOTHAM", "WITHAM", "LATHAM") &&
       ! stringAt(0, 7, "BENTHAM", "WALTHAM", "WORTHAM") &&
       ! stringAt(0, 8, "GRANTHAM")) ||

      (m_current != 0 && 
       stringAt(m_current+1, 5, "HATCH") &&
       ! stringAt(m_current-2, 8, "UNTHATCH")) ||

      stringAt(m_current-3, 7, "WARTHOG") ||

      // Some special cases where "-TH-" is usually pronounced 'T'.
      stringAt(m_current-2, 6, "ESTHER") ||
      stringAt(m_current-3, 6, "GOETHE") ||
      stringAt(m_current-2, 8, "NATHALIE"))
  {
    // Special case.
    if (stringAt(m_current-3, 7, "POSTHUM"))
      add("X");
    else
      add("T");

    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_TTH()
{
  // Encode the "-TTH-" in "matthew", eating the redundant 'T':
  // 'matthew' vs. 'outthink'
  if (stringAt(m_current, 3, "TTH"))
  {
    if (stringAt(m_current-2, 5, "MATTH"))
      add("0");
    else
      add("T0");

    m_current += 3;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_TH()
{
  // Encode "-TH-". 0 (zero) is used in Metaphone to encode this sound
  // when it is pronounced as a dipthong, either voiced or unvoiced
  if (stringAt(m_current, 2, "TH"))
  {
    // '-clothes-'
    if (stringAt(m_current-3, 7, "CLOTHES"))
    {
      // Vowel already encoded so skip right to S
      m_current += 3;
      return true;
    }

    // Special cases "thomas", "thames", "beethoven" or Germanic words.
    if (stringAt(m_current+2, 4, "OMAS", "OMPS", "OMPK", "OMSO", "OMSE",
          "AMES", "OVEN", "OFEN", "ILDA", "ILDE") ||
        (m_length == 4 && stringAt(0, 4, "THOM")) ||
        (m_length == 5 && stringAt(0, 5, "THOMS")) ||
        stringAt(0, 4, "VAN ", "VON ") ||
        stringAt(0, 3, "SCH"))
        // shein: So spaces are treated in some cases?
      add("T");
    else if (stringAt(0, 2, "SM"))
      // Give an 'etymological' 2nd encoding for "smith".
      add("0", "T");
    else
      add("0");

    m_current += 2;
    return true;
  }
  else
    return false;
}


void Metaphone3::encode_V()
{
  // Encode "-V-".  Eat redundant 'V'?
  if (charAt(m_current+1) == 'V')
    m_current += 2;
  else
    m_current++;

  addExactApprox("V", "F");
}


void Metaphone3::encode_W()
{
  // Encode "-W-".
  if (encode_Silent_W_At_Beginning() || 
      encode_WITZ_WICZ() || 
      encode_WR() || 
      encode_Initial_W_Vowel() || 
      encode_WH() || 
      encode_Eastern_European_W())
    return;

  // E.g. 'zimbabwe'.
  if (m_encodeVowels && 
      m_current+1 == m_last &&
      stringAt(m_current, 2, "WE"))
    add("A");

  // Else skip it.
  m_current++;
}


bool Metaphone3::encode_Silent_W_At_Beginning()
{
  // Encode cases where 'W' is silent at beginning of word.
  if (m_current == 0 && stringAt(0, 2, "WR"))
  {
    m_current += 1;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_WITZ_WICZ()
{
  // Encode Polish patronymic suffix, mapping alternate spellings to 
  // the same encoding, and including Eastern European pronunciation
  // to the American so that both forms can be found in a genealogy 
  //  search: 'filipowicz'.
  if (m_current+3 == m_last && 
      stringAt(m_current, 4, "WICZ", "WITZ"))
  {
    if (! m_encodeVowels)
      add("TS", "FX");
    else if (m_primary.length() > 0 && m_primary.back() == 'A')
      add("TS", "FAX");
    else
      add("ATS", "FAX");

    m_current += 4;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_WR()
{
  // Encode "-WR-" as R ('W' always effectively silent).
  // Can also be in middle of word.
  if (stringAt(m_current, 2, "WR"))
  {
    add("R");
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_Initial_W_Vowel()
{
  // Encode "W-", adding Central and Eastern European pronunciations 
  // so that both forms can be found in a genealogy search.
  if (m_current == 0 && isVowel(1))
  {
    // Witter should match Vitter
    if (! germanic_Or_Slavic_Name_Beginning_With_W())
      add("A");
    else if (m_encodeVowels)
      addExactApprox("A", "VA", "A", "FA");
    else
      addExactApprox("A", "V", "A", "F");

    m_current++;
    // Don't encode vowels twice
    m_current = skipVowels(m_current);
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_WH()
{
  // Encode "-WH-" either as H, or close enough to 'U' to be
  // considered a vowel.
  if (stringAt(m_current, 2, "WH"))
  {
    // Cases where it is pronounced as H, e.g. 'who', 'whole'.
    if (charAt(m_current+2) == 'O' &&
        // Exclude cases where it is pronounced like a vowel.
        ! stringAt(m_current+2, 4, "OOSH") &&
        ! stringAt(m_current+2, 3, "OOP", "OMP", "ORL", "ORT") &&
        ! stringAt(m_current+2, 2, "OA", "OP"))
    {
      add("H");
      advanceCounter(3, 2);
      return true;
    }
    else if (stringAt(m_current+2, 3, "IDE", "ARD", "EAD", "AWK", "ERD",
               "OOK", "AND", "OLE", "OOD") ||
        stringAt(m_current+2, 4, "EART", "OUSE", "OUND") ||
        stringAt(m_current+2, 5, "AMMER"))
    {
      // Combining forms, e.g. 'hollowhearted', 'rawhide'.
      add("H");
      m_current += 2;
      return true;
    }
    else if (m_current == 0)
    {
      add("A");
      m_current += 2;
      // Don't encode vowels twice.
      m_current = skipVowels(m_current);
      return true;
    }
    else
    {
      m_current += 2;
      return true;
    }
  }
  else
    return false;
}


bool Metaphone3::encode_Eastern_European_W()
{
  // Encode "-W-" when in Eastern European names, adding
  // the Eastern European pronounciation to the American so
  // that both forms can be found in a genealogy search.
  // Arnow should match Arnoff.
  if ((m_current == m_last && isVowel(m_current-1)) ||
      stringAt(m_current-1, 5, "EWSKI", "EWSKY", "OWSKI", "OWSKY") ||
      (m_current+4 == m_last && stringAt(m_current, 5, "WICKI", 
        "WACKI")) ||
      (m_current+3 == m_last && stringAt(m_current, 4, "WIAK")) ||
      stringAt(0, 3, "SCH"))
  {
    addExactApprox("", "V", "", "F");
    m_current++;
    return true;
  }
  else
    return false;
}


void Metaphone3::encode_X()
{
  if (encode_Initial_X() ||
      encode_Greek_X() ||
      encode_X_Special_Cases() ||
      encode_X_To_H() ||
      encode_X_Vowel() ||
      encode_French_X_Final())
    return;

  // Eat redundant 'X' or other redundant cases.
  if (stringAt(m_current+1, 1, "X", "Z", "S") ||
      // E.g. "excite", "exceed"
      stringAt(m_current+1, 2, "CI", "CE"))
    m_current += 2;
  else
    m_current++;
}


bool Metaphone3::encode_Initial_X()
{
  // Encode initial X where it is usually pronounced as S.
  // Current Chinese Pinyin spelling.
    if (stringAt(0, 3, "XIA", "XIO", "XIE") ||
        stringAt(0, 2, "XU"))
  {
    add("X");
    m_current++;
    return true;
  }
  else if (m_current == 0)
  {
    add("S");
    m_current++;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_Greek_X()
{
  // Encode X when from Greek roots where it is usually pronounced as S:
  // 'xylophone', xylem', 'xanthoma', 'xeno-'.
  if (stringAt(m_current+1, 3, "YLO", "YLE", "ENO") || 
      stringAt(m_current+1, 4, "ANTH"))
  {
    add("S");
    m_current++;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_X_Special_Cases()
{
  // Encode special cases, "LUXUR-", "Texeira": 'luxury'.
  if (stringAt(m_current-2, 5, "LUXUR"))
  {
    addExactApprox("GJ", "KJ");
    m_current++;
    return true;
  }

  // 'Texeira', Portuguese/Galician name
  if (stringAt(0, 7, "TEXEIRA") || stringAt(0, 8, "TEIXEIRA"))
  {
    add("X");
    m_current++;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_X_To_H()
{
  // Encode special case where Americans know the proper Mexican/Indian 
  // pronounciation of this name.
  // TODO: look for other Mexican/Indian words where 'X' is usually 
  // pronounced this way.
  if (stringAt(m_current-2, 6, "OAXACA") || 
      stringAt(m_current-3, 7, "QUIXOTE"))
  {
    add("H");
    m_current++;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_X_Vowel()
{
  // Encode "-X-" in vowel contexts where it is usually pronounced 
  // KX ("ksh").  Account also for BBC pronounciation of => KS,
  // e.g. "sexual", "connexion" (British), "noxious".
  if (stringAt(m_current+1, 3, "UAL", "ION", "IOU"))
  {
    add("KX", "KS");
    advanceCounter(3, 1);
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_French_X_Final()
{
  // Encode cases of "-X", encoding as silent when part of a French 
  // word where it is not pronounced French e.g. "breaux", "paix".
  if (! (m_current == m_last &&
      (stringAt(m_current-3, 3, "IAU", "EAU", "IEU") ||
       stringAt(m_current-2, 2, "AI", "AU", "OU", "OI", "EU"))))
    add("KS");

  return false;
  // shein: This is rather ugly: We log the "KS" but we advance
  // by a variable amount in the main X function.
}


void Metaphone3::encode_Z()
{
  // Encode "-Z-".
  if (encode_ZZ() || 
      encode_ZU_ZIER_ZS() || 
      encode_French_EZ() || 
      encode_German_Z() ||
      encode_ZH())
    return;

  add("S");

  // Eat redundant 'Z'.
  if (charAt(m_current+1) == 'Z')
    m_current += 2;
  else
    m_current++;
}


bool Metaphone3::encode_ZZ()
{
  // Encode cases of "-ZZ-" where it is obviously part of an Italian 
  // word where "-ZZ-" is pronounced as TS: "abruzzi", 'pizza'.
  if (charAt(m_current+1) == 'Z' && 
      ((m_current+2 == m_last && stringAt(m_last, 1, "I", "O", "A")) || 
      stringAt(m_current-2, 9, "MOZZARELL", "PIZZICATO", "PUZZONLAN")))
  {
    add("TS", "S");
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_ZU_ZIER_ZS()
{
  // Encode special cases where "-Z-" is pronounced as J.
  if ((m_current == 1 && stringAt(0, 4, "AZUR")) || 
      (stringAt(m_current, 4, "ZIER") && 
       ! stringAt(m_current-2, 6, "VIZIER")) || 
      stringAt(m_current, 3, "ZSA"))
  {
    add("J", "S");

    if (stringAt(m_current, 3, "ZSA"))
      m_current += 2;
    else
      m_current++;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_French_EZ()
{
  // Encode cases where Americans recognize "-EZ" as part
  // of a French word where Z not pronounced.
  if ((m_current == 3 && stringAt(0, 4, "CHEZ")) || 
      stringAt(m_current-5, 6, "RENDEZ"))
  {
    m_current++;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_German_Z()
{
  // Encode cases where "-Z-" is in a German word,
  // where Z => TS in German.
  if ((m_current == 2 && 
       m_current+1 == m_last && 
       stringAt(m_current-2, 4, "NAZI")) ||
      stringAt(m_current-2, 6, "NAZIFY", "MOZART") ||
      stringAt(m_current-3, 4, "HOLZ", "HERZ", "MERZ", "FITZ") ||
      (stringAt(m_current-3, 4, "GANZ") && ! isVowel(m_current+1)) ||
      stringAt(m_current-4, 5, "STOLZ", "PRINZ") ||
      stringAt(m_current-4, 7, "VENEZIA") ||
      stringAt(m_current-3, 6, "HERZOG") ||
      // German words beginning with "sch-" but not schlimazel, schmooze
      (m_inWord.find("SCH") != string::npos && 
        ! stringAt(m_last-2, 3, "IZE", "OZE", "ZEL")) ||
      (m_current > 0 && stringAt(m_current, 4, "ZEIT")) ||
      stringAt(m_current-3, 4, "WEIZ"))
  {
    if (m_current > 0 && 
        m_inWord.at(static_cast<size_t>(m_current)-1) == 'T')
      add("S");
    else
      add("TS");

    m_current++;
    return true;
  }
  else
    return false;
}


bool Metaphone3::encode_ZH()
{
  // Encode "-ZH-" as J: Chinese Pinyin, e.g. 'zhao', also 
  // English "phonetic spelling".
  if (charAt(m_current+1) == 'H')
  {
    add("J");
    m_current += 2;
    return true;
  }
  else
    return false;
}


bool Metaphone3::names_Beginning_With_SW_That_Get_Alt_SV()
{
  // Test for names derived from the Swedish, Dutch, or Slavic that 
  // should get an alternate pronunciation of 'SV' to match the native
  // version.
  if (stringAt(0, 7, "SWANSON", "SWENSON", "SWINSON", "SWENSEN",
         "SWOBODA") || 
      stringAt(0, 9, "SWIDERSKI", "SWARTHOUT") || 
      stringAt(0, 10, "SWEARENGIN"))
    return true;
  else
    return false;
}


bool Metaphone3::names_Beginning_With_SW_That_Get_Alt_XV()
{
  // Test for names derived from the German that should get an 
  // alternate pronunciation of 'XV' to match the German version 
  // spelled // "schw-".
  if (stringAt(0, 5, "SWART") ||
      stringAt(0, 6, "SWARTZ", "SWARTS", "SWIGER") ||
      stringAt(0, 7, "SWITZER", "SWANGER", "SWIGERT",
        "SWIGART", "SWIHART") ||
      stringAt(0, 8, "SWEITZER", "SWATZELL", "SWINDLER") ||
      stringAt(0, 9, "SWINEHART") ||
      stringAt(0, 10, "SWEARINGEN"))
    return true;
  else
    return false;
}


bool Metaphone3::germanic_Or_Slavic_Name_Beginning_With_W()
{
  // Test whether the word in question is a name of Germanic or 
  // Slavic origin, for the purpose of determining whether to add an
  // alternate encoding of 'V'.
  if (stringAt(0, 3, "WEE", "WIX", "WAX") ||
      stringAt(0, 4, "WOLF", "WEIS", "WAHL", "WALZ", "WEIL", "WERT",
        "WINE", "WILK", "WALT", "WOLL", "WADA", "WULF", "WEHR", "WURM", 
        "WYSE", "WENZ", "WIRT", "WOLK", "WEIN", "WYSS", "WASS", "WANN", 
        "WINT", "WINK", "WILE", "WIKE", "WIER", "WELK", "WISE") ||
      stringAt(0, 5, "WIRTH", "WIESE", "WITTE", "WENTZ", "WOLFF", 
        "WENDT", "WERTZ", "WILKE", "WALTZ", "WEISE", "WOOLF", "WERTH",
        "WEESE", "WURTH", "WINES", "WARGO", "WIMER", "WISER", "WAGER", 
        "WILLE", "WILDS", "WAGAR", "WERTS", "WITTY", "WIENS", "WIEBE", 
        "WIRTZ", "WYMER", "WULFF", "WIBLE", "WINER", "WIEST", "WALKO", 
        "WALLA", "WEBRE", "WEYER", "WYBLE", "WOMAC", "WILTZ", "WURST", 
        "WOLAK", "WELKE", "WEDEL", "WEIST", "WYGAN", "WUEST", "WEISZ", 
        "WALCK", "WEITZ", "WYDRA", "WANDA", "WILMA", "WEBER") ||
      stringAt(0, 6, "WETZEL", "WEINER", "WENZEL", "WESTER", "WALLEN", 
        "WENGER", "WALLIN", "WEILER", "WIMMER", "WEIMER", "WYRICK", 
        "WEGNER", "WINNER", "WESSEL", "WILKIE", "WEIGEL", "WOJCIK", 
        "WENDEL", "WITTER", "WIENER", "WEISER", "WEXLER", "WACKER", 
        "WISNER", "WITMER", "WINKLE", "WELTER", "WIDMER", "WITTEN", 
        "WINDLE", "WASHER", "WOLTER", "WILKEY", "WIDNER", "WARMAN", 
        "WEYANT", "WEIBEL", "WANNER", "WILKEN", "WILTSE", "WARNKE", 
        "WALSER", "WEIKEL", "WESNER", "WITZEL", "WROBEL", "WAGNON", 
        "WINANS", "WENNER", "WOLKEN", "WILNER", "WYSONG", "WYCOFF", 
        "WUNDER", "WINKEL", "WIDMAN", "WELSCH", "WEHNER", "WEIGLE", 
        "WETTER", "WUNSCH", "WHITTY", "WAXMAN", "WILKER", "WILHAM", 
        "WITTIG", "WITMAN", "WESTRA", "WEHRLE", "WASSER", "WILLER", 
        "WEGMAN", "WARFEL", "WYNTER", "WERNER", "WAGNER", "WISSER") ||
      stringAt(0, 7, "WISEMAN", "WINKLER", "WILHELM", "WELLMAN", 
        "WAMPLER", "WACHTER", "WALTHER", "WYCKOFF", "WEIDNER", "WOZNIAK",
        "WEILAND", "WILFONG", "WIEGAND", "WILCHER", "WIELAND", "WILDMAN",
        "WALDMAN", "WORTMAN", "WYSOCKI", "WEIDMAN", "WITTMAN", "WIDENER",
        "WOLFSON", "WENDELL", "WEITZEL", "WILLMAN", "WALDRUP", "WALTMAN",
        "WALCZAK", "WEIGAND", "WESSELS", "WIDEMAN", "WOLTERS", "WIREMAN",
        "WILHOIT", "WEGENER", "WOTRING", "WINGERT", "WIESNER", "WAYMIRE",
        "WHETZEL", "WENTZEL", "WINEGAR", "WESTMAN", "WYNKOOP", "WALLICK",
        "WURSTER", "WINBUSH", "WILBERT", "WALLACH", "WYNKOOP", "WALLICK",
        "WURSTER", "WINBUSH", "WILBERT", "WALLACH", "WEISSER", "WEISNER",
        "WINDERS", "WILLMON", "WILLEMS", "WIERSMA", "WACHTEL", "WARNICK",
        "WEIDLER", "WALTRIP", "WHETSEL", "WHELESS", "WELCHER", "WALBORN",
        "WILLSEY", "WEINMAN", "WAGAMAN", "WOMMACK", "WINGLER", "WINKLES",
        "WIEDMAN", "WHITNER", "WOLFRAM", "WARLICK", "WEEDMAN", "WHISMAN",
        "WINLAND", "WEESNER", "WARTHEN", "WETZLER", "WENDLER", "WALLNER",
        "WOLBERT", "WITTMER", "WISHART", "WILLIAM") ||
      stringAt(0, 8, "WESTPHAL", "WICKLUND", "WEISSMAN", "WESTLUND", 
        "WOLFGANG", "WILLHITE", "WEISBERG", "WALRAVEN", "WOLFGRAM", 
        "WILHOITE", "WECHSLER", "WENDLING", "WESTBERG", "WENDLAND", 
        "WININGER", "WHISNANT", "WESTRICK", "WESTLING", "WESTBURY", 
        "WEITZMAN", "WEHMEYER", "WEINMANN", "WISNESKI", "WHELCHEL",
        "WEISHAAR", "WAGGENER", "WALDROUP", "WESTHOFF", "WIEDEMAN", 
        "WASINGER", "WINBORNE") || 
      stringAt(0, 9, "WHISENANT", "WEINSTEIN", "WESTERMAN", "WASSERMAN",
        "WITKOWSKI", "WEINTRAUB", "WINKELMAN", "WINKFIELD", "WANAMAKER",
        "WIECZOREK", "WIECHMANN", "WOJTOWICZ", "WALKOWIAK", "WEINSTOCK",
        "WILLEFORD", "WARKENTIN", "WEISINGER", "WINKLEMAN", "WILHEMINA") ||
      stringAt(0, 10, "WISNIEWSKI", "WUNDERLICH", "WHISENHUNT", 
        "WEINBERGER", "WROBLEWSKI", "WAGUESPACK", "WEISGERBER", 
        "WESTERVELT", "WESTERLUND", "WASILEWSKI", "WILDERMUTH", 
        "WESTENDORF", "WESOLOWSKI", "WEINGARTEN", "WINEBARGER",
        "WESTERBERG", "WANNAMAKER", "WEISSINGER") ||
      stringAt(0, 11, "WALDSCHMIDT", "WEINGARTNER", "WINEBRENNER") ||
      stringAt(0, 12, "WOLFENBARGER") ||
      stringAt(0, 13, "WOJCIECHOWSKI"))
    return true;
  else
  return false;
}


bool Metaphone3::names_Beginning_With_J_That_Get_Alt_Y()
{
  // Test whether the word in question is a name starting with 'J' 
  // that should match names starting with a 'Y' sound.
  // All forms of 'John', 'Jane', etc, get and alt to match e.g. 
  // 'Ian', 'Yana'. Joelle should match 'Yael', 'Joseph' should 
  // match 'Yusef'. German and Slavic last names are also included.
  if (stringAt(0, 3, "JAN", "JON", "JAN", "JIN", "JEN") ||
      stringAt(0, 4, "JUHL", "JULY", "JOEL", "JOHN", "JOSH", "JUDE", 
        "JUNE", "JONI", "JULI", "JENA", "JUNG", "JINA", "JANA", "JENI", 
        "JOEL", "JANN", "JONA", "JENE", "JULE", "JANI", "JONG", "JOHN", 
        "JEAN", "JUNG", "JONE", "JARA", "JUST", "JOST", "JAHN", "JACO",
        "JANG", "JUDE", "JONE") ||
      stringAt(0, 5, "JOANN", "JANEY", "JANAE", "JOANA", "JUTTA",
        "JULEE", "JANAY", "JANEE", "JETTA", "JOHNA", "JOANE", "JAYNA", 
        "JANES", "JONAS", "JONIE", "JUSTA", "JUNIE", "JUNKO", "JENAE", 
        "JULIO", "JINNY", "JOHNS", "JACOB", "JETER", "JAFFE", "JESKE", 
        "JANKE", "JAGER", "JANIK", "JANDA", "JOSHI", "JULES", "JANTZ", 
        "JEANS", "JUDAH", "JANUS", "JENNY", "JENEE", "JONAH", "JONAS",
        "JACOB", "JOSUE", "JOSEF", "JULES", "JULIE", "JULIA", "JANIE", 
        "JANIS", "JENNA", "JANNA", "JEANA", "JENNI", "JEANE", "JONNA") ||
      stringAt(0, 6, "JORDAN", "JORDON", "JOSEPH", "JOSHUA", "JOSIAH",
        "JOSPEH", "JUDSON", "JULIAN", "JULIUS", "JUNIOR", "JUDITH", 
        "JOESPH", "JOHNIE", "JOANNE", "JEANNE", "JOANNA", "JOSEFA", 
        "JULIET", "JANNIE", "JANELL", "JASMIN", "JANINE", "JOHNNY", 
        "JEANIE", "JEANNA", "JOHNNA", "JOELLE", "JOVITA", "JOSEPH", 
        "JONNIE", "JANEEN", "JANINA", "JOANIE", "JAZMIN", "JOHNIE",
        "JANENE", "JOHNNY", "JONELL", "JENELL", "JANETT", "JANETH", 
        "JENINE", "JOELLA", "JOEANN", "JULIAN", "JOHANA", "JENICE", 
        "JANNET", "JANISE", "JULENE", "JOSHUA", "JANEAN", "JAIMEE", 
        "JOETTE", "JANYCE", "JENEVA", "JORDAN", "JACOBS", "JENSEN", 
        "JOSEPH", "JANSEN", "JORDON", "JULIAN", "JAEGER", "JACOBY",
        "JENSON", "JARMAN", "JOSLIN", "JESSEN", "JAHNKE", "JACOBO", 
        "JULIEN", "JOSHUA", "JEPSON", "JULIUS", "JANSON", "JACOBI", 
        "JUDSON", "JARBOE", "JOHSON", "JANZEN", "JETTON", "JUNKER", 
        "JONSON", "JAROSZ", "JENNER", "JAGGER", "JASMIN", "JEPSEN", 
        "JORDEN", "JANNEY", "JUHASZ", "JERGEN", "JAKOB") ||
      stringAt(0, 7, "JOHNSON", "JOHNNIE", "JASMINE", "JEANNIE", 
        "JOHANNA", "JANELLE", "JANETTE", "JULIANA", "JUSTINA", "JOSETTE",
        "JOELLEN", "JENELLE", "JULIETA", "JULIANN", "JULISSA", "JENETTE",
        "JANETTA", "JOSELYN", "JONELLE", "JESENIA", "JANESSA", "JAZMINE",
        "JEANENE", "JOANNIE", "JADWIGA", "JOLANDA", "JULIANE", "JANUARY",
        "JEANICE", "JANELLA", "JEANETT", "JENNINE", "JOHANNE", "JOHNSIE",
        "JANIECE", "JOHNSON", "JENNELL", "JAMISON", "JANSSEN", "JOHNSEN",
        "JARDINE", "JAGGERS", "JURGENS", "JOURDAN", "JULIANO", "JOSEPHS",
        "JHONSON", "JOZWIAK", "JANICKI", "JELINEK", "JANSSON", "JOACHIM",
        "JANELLE", "JACOBUS", "JENNING", "JANTZEN", "JOHNNIE") ||
      stringAt(0, 8, "JOSEFINA", "JEANNINE", "JULIANNE", "JULIANNA", 
        "JONATHAN", "JONATHON", "JEANETTE", "JANNETTE", "JEANETTA", 
        "JOHNETTA", "JENNEFER", "JULIENNE", "JOSPHINE", "JEANELLE", 
        "JOHNETTE", "JULIEANN", "JOSEFINE", "JULIETTA", "JOHNSTON", 
        "JACOBSON", "JACOBSEN", "JOHANSEN", "JOHANSON", "JAWORSKI", 
        "JENNETTE", "JELLISON", "JOHANNES", "JASINSKI", "JUERGENS", 
        "JARNAGIN", "JEREMIAH", "JEPPESEN", "JARNIGAN", "JANOUSEK") ||
      stringAt(0, 9, "JOHNATHAN", "JOHNATHON", "JORGENSEN", "JEANMARIE",
        "JOSEPHINA", "JEANNETTE", "JOSEPHINE", "JEANNETTA", "JORGENSON",
        "JANKOWSKI", "JOHNSTONE", "JABLONSKI", "JOSEPHSON", "JOHANNSEN",
        "JURGENSEN", "JIMMERSON", "JOHANSSON") ||
      stringAt(0, 10, "JAKUBOWSKI"))
    return true;
  else
    return false;
}

