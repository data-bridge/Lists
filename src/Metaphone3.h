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
 * Ported to C++.
 * Soren Hein, August 2017
 */

#ifndef METAPHONE3_H
#define METAPHONE3_H

#include <string>

using namespace std;


class Metaphone3
{
  private:

    // Length of word to be encoded (before encoding).
    int  m_length;

    // Length of encoded key string.
    int m_metaphLength;

    // True if we should encode non-initial vowels.
    bool m_encodeVowels;

    // True if we should encode consonants as exactly as possible.
    bool m_encodeExact;

    // Internal copy of word to be encoded.
    string m_inWord;

    // Running copy of primary key.
    string m_primary;

    // Running copy of secondary key.
    string m_secondary;

    // Index of character in m_inWord currently being encoded.
    int m_current;

    // Index of last character in m_inWord.
    int m_last;

    // True if an AL inversion has already been done.
    bool flag_AL_inversion;


    void addExactApprox(
      const string& mainExact,
      const string& altExact,
      const string& main,
      const string& alt);
    void addExactApprox(
      const string& mainExact,
      const string& main);

    bool front_Vowel(const int at) const;

    bool slavoGermanic() const;

    bool isVowel(const char in) const;
    bool isVowel(const int at) const;

    int skipVowels(const int at) const;

    void advanceCounter(
      const int ifNotEncodeVowels,
      const int ifEncodeVowels);

    char charAt(const int pos) const;

    bool rootOrInflections(
      const string& inWord,
      const string& root);

    bool stringAt(
      const string& target,
      const char * element) const;

    template<typename... Args>
    bool stringAt(
      const string& target,
      const char * first,
      const Args... args) const;

    bool stringAt(
      const int start,
      const int length,
      const char * element) const;

    template<typename... Args>
    bool stringAt(
      const int start,
      const int length,
      const char * element,
      const Args... args) const;

    void encode_Vowels();
    void encode_E_Pronounced();
    bool o_Silent();
    bool e_Silent();
    bool e_Pronounced_At_End();
    bool silent_Internal_E();
    bool e_Silent_Suffix(const int at);
    bool e_Pronouncing_Suffix(const int at) const;
    bool e_Pronounced_Exceptions();
    bool skip_Silent_UE();

    void encode_B();
    bool encode_Silent_B();

    void encode_C();
    bool encode_Silent_C_At_Beginning();
    bool encode_CA_To_S();
    bool encode_CO_To_S();
    bool encode_CH();
    bool encode_CHAE();
    bool encode_CH_To_H();
    bool encode_Silent_CH();
    bool encode_CH_To_X();
    bool encode_English_CH_To_K();
    bool encode_Germanic_CH_To_K();
    bool encode_ARCH();
    bool encode_Greek_CH_Initial();
    bool encode_Greek_CH_Non_Initial();
    bool encode_CCIA();
    bool encode_CC();
    bool encode_CK_CG_CQ();
    bool encode_C_Front_Vowel();
    bool encode_British_Silent_CE();
    bool encode_CE();
    bool encode_CI();
    bool encode_Latinate_Suffixes();
    bool encode_Silent_C();
    bool encode_CZ();
    bool encode_CS();

    void encode_D();
    bool encode_DG();
    bool encode_DJ();
    bool encode_DT_DD();
    bool encode_D_To_J();
    bool encode_DOUS();
    bool encode_Silent_D();

    void encode_F();

    void encode_G();
    bool encode_Silent_G_At_Beginning();
    bool encode_GG();
    bool encode_GK();
    bool encode_GH();
    bool encode_GH_After_Consonant();
    bool encode_Initial_GH();
    bool encode_GH_To_J();
    bool encode_GH_To_H();
    bool encode_UGHT();
    bool encode_GH_H_Part_Of_Other_Word();
    bool encode_Silent_GH();
    bool encode_GH_Special_Cases();
    bool encode_GH_To_F();
    bool encode_Silent_G();
    bool encode_GN();
    bool encode_GL();
    bool initial_G_Soft();
    bool encode_Initial_G_Front_Vowel();
    bool encode_NGER();
    bool encode_GER();
    bool encode_GEL();
    bool encode_Non_Initial_G_Front_Vowel();
    bool hard_GE_At_End();
    bool internal_Hard_G();
    bool internal_Hard_G_Other();
    bool internal_Hard_G_Open_Syllable();
    bool internal_Hard_GEN_GIN_GET_GIT();
    bool internal_Hard_NG();
    bool encode_GA_To_J();

    void encode_H();
    bool encode_Initial_Silent_H();
    bool encode_Initial_HS();
    bool encode_Initial_HU_HW();
    bool encode_Non_Initial_Silent_H();
    bool encode_H_Pronounced();

    void encode_J();
    bool encode_Spanish_J();
    bool encode_German_J();
    bool encode_Spanish_OJ_UJ();
    bool encode_J_To_J();
    bool encode_Spanish_J_2();
    bool encode_J_As_Vowel();
    void encode_Other_J();

    void encode_K();
    bool encode_Silent_K();

    void encode_L();
    void interpolate_Vowel_When_Cons_L_At_End();
    bool encode_LELY_To_L();
    bool encode_COLONEL();
    bool encode_French_AULT();
    bool encode_French_EUIL();
    bool encode_French_OULX();
    bool encode_Silent_L_In_LM();
    bool encode_Silent_L_In_LK_LV();
    bool encode_Silent_L_In_OULD();
    bool encode_LL_As_Vowel_Special_Cases();
    bool encode_LL_As_Vowel();
    bool encode_LL_As_Vowel_Cases();
    bool encode_Vowel_LE_Transposition(const int save_current);
    bool encode_Vowel_Preserve_Vowel_After_L(const int save_current);
    void encode_LE_Cases(const int save_current);

    void encode_M();
    bool encode_Silent_M_At_Beginning();
    bool encode_MR_And_MRS();
    bool encode_MAC();
    bool encode_MPT();
    bool test_Silent_MB_1();
    bool test_Pronounced_MB();
    bool test_Silent_MB_2();
    bool test_Pronounced_MB_2();
    bool test_MN();
    void encode_MB();

    void encode_N();
    bool encode_NCE();

    void encode_P();
    bool encode_Silent_P_At_Beginning();
    bool encode_PT();
    bool encode_PH();
    bool encode_PPH();
    bool encode_RPS();
    bool encode_COUP();
    bool encode_PNEUM();
    bool encode_PSYCH();
    bool encode_PSALM();
    void encode_PB();

    void encode_Q();

    void encode_R();
    bool encode_RZ();
    bool test_Silent_R();
    bool encode_Vowel_RE_Transposition();

    void encode_S();
    bool encode_Special_SW();
    bool encode_SKJ();
    bool encode_SJ();
    bool encode_Silent_French_S_Final();
    bool encode_Silent_French_S_Internal();
    bool encode_ISL();
    bool encode_STL();
    bool encode_Christmas();
    bool encode_STHM();
    bool encode_ISTEN();
    bool encode_Sugar();
    bool encode_SH();
    bool encode_SCH();
    bool encode_SUR();
    bool encode_SU();
    bool encode_SSIO();
    bool encode_SS();
    bool encode_SIA();
    bool encode_SIO();
    bool encode_Anglicisations();
    bool encode_SC();
    bool encode_SEA_SUI_SIER();
    bool encode_SEA();

    void encode_T();
    bool encode_T_Initial();
    bool encode_TCH();
    bool encode_Silent_French_T();
    bool encode_TUN_TUL_TUA_TUO();
    bool encode_TUE_TEU_TEOU_TUL_TIE();
    bool encode_TUR_TIU_Suffixes();
    bool encode_TI();
    bool encode_TIENT();
    bool encode_TSCH();
    bool encode_TZSCH();
    bool encode_TH_Pronounced_Separately();
    bool encode_TTH();
    bool encode_TH();

    void encode_V();

    void encode_W();
    bool encode_Silent_W_At_Beginning();
    bool encode_WITZ_WICZ();
    bool encode_WR();
    bool encode_Initial_W_Vowel();
    bool encode_WH();
    bool encode_Eastern_European_W();

    void encode_X();
    bool encode_Initial_X();
    bool encode_Greek_X();
    bool encode_X_Special_Cases();
    bool encode_X_To_H();
    bool encode_X_Vowel();
    bool encode_French_X_Final();

    void encode_Z();
    bool encode_ZZ();
    bool encode_ZU_ZIER_ZS();
    bool encode_French_EZ();
    bool encode_German_Z();
    bool encode_ZH();

    bool names_Beginning_With_SW_That_Get_Alt_SV();
    bool names_Beginning_With_SW_That_Get_Alt_XV();
    bool germanic_Or_Slavic_Name_Beginning_With_W();
    bool names_Beginning_With_J_That_Get_Alt_Y();

  public:

    Metaphone3();
    ~Metaphone3();
    void reset();

    void setWord(const string in);

    bool setKeyLength(const int inKeyLength);
    int getKeyLength() const;
    int getMaximumKeyLength() const;

    void setEncodeVowels(const bool inEncodeVowels);
    bool getEncodeVowels() const;

    void setEncodeExact(const bool inEncodeVowels);
    bool getEncodeExact() const;

    void add(const string& in);
    void add(
      const string& main,
      const string& alt);

    void encode();

    string getMetaph() const;
    string getAlternateMetaph() const;
};

#endif
