#ifndef SPELLCORRECTOR_HPP
#define SPELLCORRECTOR_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <optional>
#include <nuspell/dictionary.hxx>
#include <nuspell/finder.hxx>


class SpellCorrector
{
private:
    std::optional<nuspell::Dictionary> englishDict;
    std::optional<nuspell::Dictionary> russianDict;

    std::vector<std::string> FilterSuggestions(std::string baseWord, std::vector<std::string> suggestions);
public:

    void Init();

    bool CheckQuery(const std::vector<std::string>& queryWords, std::vector<std::vector<std::string>>& suggestions);

    std::optional<nuspell::Dictionary> getEnglishDict();
    std::optional<nuspell::Dictionary> getRussianDict();

};

#endif