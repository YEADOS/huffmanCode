#include <gtest/gtest.h>
#include "huffman.h"
#include <iostream>
#include <stdio.h>
#include <string>

TEST(Huffamn, Test1) {
    std::string input = "BCCABBDDAECCBBAEDDCC";
    EXPECT_EQ(input, huffmanCode(input));
}

TEST(Huffman, Test2_LowerCaseAlphabet) {
    std::string input = "abcdefghijklmnopqrstuvwxyz";
    EXPECT_EQ(input, huffmanCode(input));
}

TEST(Huffman, Test3_text) {
    std::string input = "The output from Huffman's algorithm can be viewed as a variable-length code table for encoding a source symbol (such as a character in a file). The algorithm derives this table from the estimated probability or frequency of occurrence (weight) for each possible value of the source symbol. As in other entropy encoding methods, more common symbols are generally represented using fewer bits than less common symbols. Huffman's method can be efficiently implemented, finding a code in time linear to the number of input weights if these weights are sorted.[2] However, although optimal among methods encoding symbols separately, Huffman coding is not always optimal among all compression methods - it is replaced with arithmetic coding[3] or asymmetric numeral systems[4] if a better compression ratio is required.";
    EXPECT_EQ(input, huffmanCode(input));
}

TEST(Huffman, Test4_SpecialCharacters) {
    std::string input = "!>@:{:#}?--}+~(*&&?],{-)/@!+^:\"&*):!=(?:/#&([\"@.`%=@-@^,-%#&=<!^'=,}\"_]$<,!])];|>/[={'!,>&$^$?.$''$|:>>!?[=:%/'{-\"(-<#=+;\"_\">{~(*#;[~:|?#}:#&:,?@~#>;>@(/;&*`:%#?\\)/<%~])!~#<??%|_,=";
    EXPECT_EQ(input, huffmanCode(input));
}

TEST(Huffman, Test5_ASCII) {

    std::string input = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    EXPECT_EQ(input, huffmanCode(input));
}

TEST(Huffman, Test6_SingleCharacter) {
    std::string input = "w";
    EXPECT_EQ(input, huffmanCode(input));
}

TEST(Huffman, Test7_SingleCharacterString) {
    std::string input = "zzzzzzzzzzzzzzzzzzz";
    EXPECT_EQ(input, huffmanCode(input));
}

TEST(Huffman, Test8_LargeInput) {
    std::string input(1000000, 'a');
    EXPECT_EQ(input, huffmanCode(input));
}

TEST(Huffman, Test9_EmptyString) {
    std::string input = "";
    EXPECT_EQ(input, huffmanCode(input));
}

TEST(Huffman, Test10_Numbers) {
    std::string input = "54980349341390128506983597301957187134298278419291";
    EXPECT_EQ(input, huffmanCode(input));
}

// TEST(Huffman, Test11_NonASCII) {
//     std::string input = u8"你好, мир, 안녕하세요,こんにちは, مرحبا";
//     EXPECT_EQ(input, huffmanCode(input));
// }

int main(int argc, char **argv) {
  
    ::testing::InitGoogleTest(&argc, argv);    
    return RUN_ALL_TESTS();

}

