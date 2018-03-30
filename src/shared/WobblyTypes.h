/*

Copyright (c) 2018, John Smith

Permission to use, copy, modify, and/or distribute this software for
any purpose with or without fee is hereby granted, provided that the
above copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR
BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES
OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

*/


#ifndef WOBBLYTYPES_H
#define WOBBLYTYPES_H

#include <map>
#include <set>
#include <string>
#include <vector>


struct FreezeFrame {
    int first;
    int last;
    int replacement;
};


struct Preset {
    std::string name; // Must be suitable for use as Python function name.
    std::string contents;
};


struct Section {
    int start;
    std::vector<std::string> presets; // Preset names, in user-defined order.

    Section(int _start)
        : start(_start)
    { }
};


struct FrameRange {
    int first;
    int last;
};


struct CustomList {
    std::string name;
    std::string preset; // Preset name.
    int position;
    std::map<int, FrameRange> ranges; // Key is FrameRange::first

    CustomList(const std::string &_name, const std::string &_preset = "", int _position = 0)
        : name(_name)
        , preset(_preset)
        , position(_position)
    { }
};


struct Resize {
    bool enabled;
    int width;
    int height;
    std::string filter;
};


struct Crop {
    bool enabled;
    bool early;
    int left;
    int top;
    int right;
    int bottom;
};


struct Depth {
    bool enabled;
    int bits;
    bool float_samples;
    std::string dither;
};


struct DecimationRange {
    int start;
    int num_dropped;
};


struct DecimationPatternRange {
    int start;
    std::set<int8_t> dropped_offsets;
};


enum PositionInFilterChain {
    PostSource = 0,
    PostFieldMatch,
    PostDecimate
};


enum UseThirdNMatch {
    UseThirdNMatchAlways = 0,
    UseThirdNMatchNever,
    UseThirdNMatchIfPrettier
};


enum DropDuplicate {
    DropFirstDuplicate = 0,
    DropSecondDuplicate,
    DropUglierDuplicatePerCycle,
    DropUglierDuplicatePerSection
};


enum Patterns {
    PatternCCCNN = 1 << 0,
    PatternCCNNN = 1 << 1,
    PatternCCCCC = 1 << 2
};


struct FailedPatternGuessing {
    int start;
    int reason;
};


enum PatternGuessingFailureReason {
    SectionTooShort = 0,
    AmbiguousMatchPattern
};


enum PatternGuessingMethods {
    PatternGuessingFromMatches = 0,
    PatternGuessingFromMics
};


struct PatternGuessing {
    int method;
    int minimum_length;
    int third_n_match;
    int decimation;
    int use_patterns;
    std::map<int, FailedPatternGuessing> failures; // Key is FailedPatternGuessing::start
};


struct InterlacedFade {
    int frame;
    double field_difference;
};


struct ImportedThings {
    bool geometry;
    bool presets;
    bool custom_lists;
    bool crop;
    bool resize;
    bool bit_depth;
    bool mic_search;
    bool zoom;
};

#endif // WOBBLYTYPES_H